/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 Serial2.c
**  Description: OSWarrior Serial library functions definitions
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
** =============================================================================
**  							 LICENSE:
** =============================================================================
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the Attribution-ShareAlike
**  License as published by the Creative Commons Organization; either
**  version 3.0 of the License, or (at your option) any later version.
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
**  See the Attribution-ShareAlike License for more details.
**  You should have received a copy of the Creative Commons Attribution-ShareAlike 
**  License along with this library; if not send a email to the library author.
** =============================================================================
*/

/*
** ===================================================================
** Serial includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/serial/serial.h"
#include "oswlib/serial/serialPort2.h"

/*
** ===================================================================
** Serial interrupt handlers
** ===================================================================
*/

static void (* near const _vect_SerialPort2[])(void) @OSWarrior_SerialPort2_ISR_Vector = {
	_OSWarrior_SerialPort2_ISR_Write,            	/* Int.no. 21 Vsci2tx (at FFD4) */
	_OSWarrior_SerialPort2_ISR_Read,             	/* Int.no. 20 Vsci2rx (at FFD6) */
	_OSWarrior_SerialPort2_ISR_Error,				/* Int.no. 19 Vsci2er (at FFD8) */
};

/*
** ===================================================================
** Serial variables declarations
** ===================================================================
*/

volatile T_UBYTE _OSWarrior_SerialPort2_available;

volatile T_UBYTE _OSWarrior_SerialPort2_Rx_Buff[OSWARRIOR_SERIAL_BUFF_LEN];
volatile T_UBYTE _OSWarrior_SerialPort2_Rx_nxt = 0;
volatile T_UBYTE _OSWarrior_SerialPort2_Rx_rd = 0;
volatile T_BOOLEAN _OSWarrior_SerialPort2_Rx_Buff_full = FALSE;

volatile T_UBYTE _OSWarrior_SerialPort2_Tx_Buff[OSWARRIOR_SERIAL_BUFF_LEN];
volatile T_UBYTE _OSWarrior_SerialPort2_Tx_nxt = 0;
volatile T_UBYTE _OSWarrior_SerialPort2_Tx_rd = 0;
volatile T_BOOLEAN _OSWarrior_SerialPort2_Tx_Buff_full = FALSE;

volatile T_UBYTE _OSWarrior_SerialPort2_String_Buff[OSWARRIOR_SERIAL_BUFF_LEN];
volatile T_UBYTE _OSWarrior_SerialPort2_String_nxt = 0;

volatile T_BOOLEAN _OSWarrior_SerialPort2_Tx_active = FALSE;

/*
** ===================================================================
** Serial Structures definition
** ===================================================================
*/

S_SCISTR Serial2 = {
	0x00,
	_OSWarrior_SerialPort2_Init,
	_OSWarrior_SerialPort2_End,
	_OSWarrior_SerialPort2_Clear,
	_OSWarrior_SerialPort2_NewLine,
	_OSWarrior_SerialPort2_Available,
	
	_OSWarrior_SerialPort2_Print,
	_OSWarrior_SerialPort2_Print_Line,
	_OSWarrior_SerialPort2_PrintDigits,
	_OSWarrior_SerialPort2_PrintFloatNumber,

	_OSWarrior_SerialPort2_Write,
	_OSWarrior_SerialPort2_WriteChar,
	
	_OSWarrior_SerialPort2_Read,
	_OSWarrior_SerialPort2_Read_String,
	_OSWarrior_SerialPort2_GetChar,
	_OSWarrior_SerialPort2_ReadNumber,
	
	_OSWarrior_Dummy_Fnc
};

/*
** ===================================================================
**     Function : Serial2.init
**     Handler  : _OSWarrior_SerialPort2_Init
**
**     Description :
**         	This function enable the Serial communication trough the 
**         	onBoard COM Port, configuring the communication speed. 
**     
**     Parameters  : 
**         	br     : configure the data transfer baud rate 
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_Init(T_ULONG baudrate)
{	
	#ifdef __OSWarrior_DK__
	{	
		SCI2C2 = 0x00U;                      // Disable the SCI2 module
		(void)(SCI2S1 == 0U);                // Dummy read of the SCI2S1 register to clear flags
		(void)(SCI2D == 0U);                 // Dummy read of the SCI2D register to clear flags 
		SCI2S2 = 0xC0U;   		
		SCI2C1 = 0x00U;                                      
		SCI2C3 = 0x00U; 
	}
	#endif	
	
	_OSWarrior_SerialPort2_setBaudRate(baudrate); 
	
	_OSWarrior_SerialPort2_Enable_Rx();
	_OSWarrior_SerialPort2_Enable_Tx();
	_OSWarrior_SerialPort2_Enable_Rx_ISR();
	//_OSWarrior_SerialPort2_Enable_Tx_ISR();
}

/*
** ==============================================================
** 	SCI Baud Rate Divider (SCIxBD) calculation:
** 		SERIAL_BAUD_RATE = (BUSFREQ / (16 * SCIxBD));
** 		SERIAL_BAUD_RATE * 16 * SCI2BD = BUSFREQ ;  
** 		SCIxBD = BUSFREQ / (16 * SERIAL_BAUD_RATE);    
** 	Example:                                  
** 		SCIxBD = 4MHz / (16 * 9600);         
** 		SCIxBD <= 26.04 <= 26
** ==============================================================
*/

void _OSWarrior_SerialPort2_setBaudRate(T_ULONG baudrate)
{
	#ifdef __OSWarrior_DK__
		SCI2BD = (unsigned int)(BUSCLOCK / (16 * baudrate));
	#endif	
}

/*
** ===================================================================
**     Function : Serial2.end
**     Handler  : _OSWarrior_SerialPort2_End
**
**     Description :
**         	This function disable the onBoard SerialPort2. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_End(void)
{
	#ifdef __OSWarrior_DK__
	{	
		SCI2C2 = 0x00U;                      // Disable the SCI2 module
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial2.clear
**     Handler  : _OSWarrior_SerialPort2_Clear
**
**     Description :
**         	When used this function send a command to display a new
**         	form page (blank page).
**         
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_Clear(void)
{
	Serial2.writeChar(ASCII_NP);				//FF - Form Feed or NP - New Page
}

/*
** ===================================================================
**     Function : Serial2.newLine
**     Handler  : _OSWarrior_SerialPort2_NewLine
**
**     Description :
**         	Commands the onBoard COM Port to display a new blank line,
**        	also called as "jump" a line. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_NewLine(void)
{
	Serial2.writeChar(ASCII_LF);				//LF - Line Feed
	Serial2.writeChar(ASCII_CR);				//CR - Carriage return	
}

/*
** ===================================================================
**     Function : Serial2.available
**     Handler  : _OSWarrior_SerialPort2_Available
**
**     Description :
**         This function checks if the onBoard COM Port is available
**         or idle (have no pending data transfers). 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

T_UBYTE _OSWarrior_SerialPort2_Available(void)
{
	#ifdef __OSWarrior_DK__
	{	
		return	_OSWarrior_SerialPort2_available;		//Return available values
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial2.println
**     Handler  : _OSWarrior_SerialPort2_Print_Line
**
**     Description :
**         This function send a char array variable trough the onBoard
**         COM Port then prints a new line.
**     
**     Parameters  : 
**         data : char array to be printed
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_Print_Line(T_UBYTE *data)
{
	Serial2.write(data);
	Serial2.write("\r\n");
};

/*
** ===================================================================
**     Function : Serial2.printNum
**     Handler  : _OSWarrior_SerialPort2_PrintNum
**
**     Description :
**         	This function send a number trough the onBoard COM Port
**         	in ASCII format. 
**         	
**         	Example: for the number 23 this function send the 
**         	corresponding ASCII characters: 0x32 0x33. 
**     
**     Parameters  : 
**         	number : number to send
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_Print (T_SLONG number)
{
	number_explode( number, _OSWarrior_SerialPort2_WriteChar, 0);
}

/*
** ===================================================================
**     Function : Serial2.printDigits
**     Handler  : SerialPort2_PrintDigits
**
**     Description :
**         	This function send a number trough the onBoard COM Port
**         	in ASCII format where the quantity of digits to display 
**         	can be configured by the user. 
**         	
**         	Example: for the number 75 and 3 digits this function send 
**         	the corresponding ASCII characters: 0x30 0x37 0x35 (075). 
**     
**     Parameters  : 
**         	number : number to send
**         	digits : the number of digits to be displayed
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_PrintDigits (T_SLONG number, int digits)
{
	number_explode( number, _OSWarrior_SerialPort2_WriteChar, digits);
}

/*
** ===================================================================
**     Function : Serial2.printFloat
**     Handler  : _OSWarrior_SerialPort2_PrintFloatNumber
**
**     Description :
**         This function send a char array variable trough the onBoard
**         COM Port. 
**     
**     Parameters  : 
**         data : char array to be printed
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_PrintFloatNumber(T_FLOAT number, int decimals)
{
	number_explode_FloatNumbers( number, _OSWarrior_SerialPort2_WriteChar, decimals);	
}

/*
** ===================================================================
**     Function : Serial2.read
**     Handler  : SerialPort2_Read
**
**     Description :
**         This function reads the data sent trough the serial port
**         until a carriage return is detected or 32 characters are
**         received. 
**     
**     Parameters  : Nothing
**     Returns     : Data read (Returns a pointer type variable)
** ===================================================================
*/

T_UBYTE _OSWarrior_SerialPort2_Read(void)
{
	register T_UBYTE read_data = 0x00;

	if( _OSWarrior_SerialPort2_available >= 1 )									//Buffer data available
	{
		read_data = _OSWarrior_SerialPort2_Rx_Buff[_OSWarrior_SerialPort2_Rx_rd];	//Read the data
		_OSWarrior_SerialPort2_Rx_rd++;
		if(_OSWarrior_SerialPort2_Rx_rd >= OSWARRIOR_SERIAL_BUFF_LEN)			//Buffer overflow			
			_OSWarrior_SerialPort2_Rx_rd = 0;	
		_OSWarrior_SerialPort2_available--;
	}
	return read_data;
}

T_UBYTE *_OSWarrior_SerialPort2_Read_String(void)
{
	T_UBYTE temp;
	T_BOOLEAN stringComplete = FALSE;
	_OSWarrior_SerialPort2_String_nxt = 0;
	while(!stringComplete)
	{
		while(!Serial2.available());
		temp = Serial2.read();
		if( ( temp != '\r' ) && ( temp != 0x00 ))	
		{	
			_OSWarrior_SerialPort2_String_Buff[_OSWarrior_SerialPort2_String_nxt] = temp;
			_OSWarrior_SerialPort2_String_nxt++;	
			Serial2.writeChar(temp);					//Echo data
		}
		else
		{
			_OSWarrior_SerialPort2_String_Buff[_OSWarrior_SerialPort2_String_nxt] = 0x00;						//End string
			Serial2.write("\r\n");					//Print new line
			stringComplete = TRUE;
		}
	}
	return (T_UBYTE *)_OSWarrior_SerialPort2_String_Buff;
}

int _OSWarrior_SerialPort2_ReadNumber(void)
{
	return str_to_int(Serial2.readString());
}

/*
** ===================================================================
**     Function : Serial2.getChar
**     Handler  : _OSWarrior_SerialPort2_GetChar
**
**     Description :
**         This function waits until a data T_UBYTE is received by the 
**         onBoard COM Port. 
**     
**     Parameters  : Nothing
**     Returns     : Character received
** ===================================================================
*/

T_UBYTE _OSWarrior_SerialPort2_GetChar(void)
{
	while(!Serial2.available());
	return Serial2.read();
}

/*
** ===================================================================
**     Enable/Disable functions for Rx and Tx
** ===================================================================
*/

void _OSWarrior_SerialPort2_Enable_Tx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TE = 1u;	
	#endif
}

void _OSWarrior_SerialPort2_Enable_Rx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RE = 1u;	
	#endif
}

void _OSWarrior_SerialPort2_Enable_Tx_Rx(void)
{
	_OSWarrior_SerialPort2_Enable_Tx();
	_OSWarrior_SerialPort2_Enable_Rx();
}

void _OSWarrior_SerialPort2_Disable_Tx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TE = 0u;	
	#endif
}

void _OSWarrior_SerialPort2_Disable_Rx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RE = 0u;	
	#endif	
}

void _OSWarrior_SerialPort2_Disable_Tx_Rx(void)
{
	_OSWarrior_SerialPort2_Disable_Tx();
	_OSWarrior_SerialPort2_Disable_Rx();
}

/* ISR Enable/Disable */

void _OSWarrior_SerialPort2_Enable_Tx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TIE = 1u;	
	#endif
}

void _OSWarrior_SerialPort2_Enable_Rx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RIE = 1u;	
	#endif
}

void _OSWarrior_SerialPort2_Enable_Tx_Rx_ISR(void)
{
	_OSWarrior_SerialPort2_Enable_Tx_ISR();
	_OSWarrior_SerialPort2_Enable_Rx_ISR();
}

void _OSWarrior_SerialPort2_Disable_Tx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TIE = 0u;	
	#endif
}

void _OSWarrior_SerialPort2_Disable_Rx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RIE = 0u;	
	#endif
}

void _OSWarrior_SerialPort2_Disable_Tx_Rx_ISR(void)
{
	_OSWarrior_SerialPort2_Disable_Tx_ISR();
	_OSWarrior_SerialPort2_Disable_Rx_ISR();
}

/*
** ===================================================================
**     Function : Serial2.printChar
**     Handler  : _OSWarrior_SerialPort2_PrintChar
**
**     Description :
**         	This function send the specified value as ASCII
**         	character trough the onBoard COM Port. 
**     
**     Parameters  : 
**         	data : data to be sent in ASCII format
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_WriteChar(T_UBYTE data)
{

	while(_OSWarrior_SerialPort2_Tx_Buff_full);
	
	_OSWarrior_SerialPort2_Tx_Buff[_OSWarrior_SerialPort2_Tx_nxt] = data;
	_OSWarrior_SerialPort2_Tx_nxt++;
	
	if(_OSWarrior_SerialPort2_Tx_nxt >= OSWARRIOR_SERIAL_BUFF_LEN)			//Buffer overflow
		_OSWarrior_SerialPort2_Tx_nxt = 0;

	if(_OSWarrior_SerialPort2_Tx_nxt == _OSWarrior_SerialPort2_Tx_rd)			//Buffer full
		_OSWarrior_SerialPort2_Tx_Buff_full = TRUE;
	else
		_OSWarrior_SerialPort2_Tx_Buff_full = FALSE;
	
	_OSWarrior_SerialPort2_Enable_Tx_ISR();
}

/*
** ===================================================================
**     Function : Serial2.print
**     Handler  : _OSWarrior_SerialPort2_Print
**
**     Description :
**         This function send a char array variable trough the onBoard
**         COM Port. 
**     
**     Parameters  : 
**         data : char array to be printed
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SerialPort2_Write(T_UBYTE *data)
{	
	while (*data)
	{
		_OSWarrior_SerialPort2_WriteChar(*data);
		data++;
	}
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_SerialPort2_ISR_Write
**
**     Description :
**         This interruption is called after the last data byte was sent, 
**         it checks for pending data to send for the serial port. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_SerialPort2_ISR_Write(void)
{
	if(SerialPort2_TF)
	{
		SerialPort2_Data = (T_UBYTE) _OSWarrior_SerialPort2_Tx_Buff[_OSWarrior_SerialPort2_Tx_rd];
		_OSWarrior_SerialPort2_Tx_rd++;
		if( _OSWarrior_SerialPort2_Tx_rd >= OSWARRIOR_SERIAL_BUFF_LEN ) _OSWarrior_SerialPort2_Tx_rd = 0; 	
		if( _OSWarrior_SerialPort2_Tx_rd == _OSWarrior_SerialPort2_Tx_nxt ) _OSWarrior_SerialPort2_Disable_Tx_ISR();
		_OSWarrior_SerialPort2_Tx_Buff_full = FALSE;					
		
	}	
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_SerialPort2_ISR_Read
**
**     Description :
**         This interruption is called every time a data T_UBYTE is 
**         received trough the onBoard COM Port, the last value 
**         received is stored for future needs and he function 
**         onReceive is executed to handle the data. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_SerialPort2_ISR_Read(void)
{
	#ifdef __OSWarrior_DK__
	{	
		T_UBYTE status;
		status = SCI2S1;
		
		if(status & SCI2S1_RDRF_MASK)
		{
			_OSWarrior_SerialPort2_available++;										//Increment available values
			
			_OSWarrior_SerialPort2_Rx_Buff[_OSWarrior_SerialPort2_Rx_nxt] = SCI2D;		//Save the data
			_OSWarrior_SerialPort2_Rx_nxt++;										//Increment index
			
			if(_OSWarrior_SerialPort2_Rx_nxt >= OSWARRIOR_SERIAL_BUFF_LEN)			//Buffer overflow			
				_OSWarrior_SerialPort2_Rx_nxt = 0;
			
			if(_OSWarrior_SerialPort2_Rx_nxt == _OSWarrior_SerialPort2_Rx_rd)			//Buffer full
				_OSWarrior_SerialPort2_Rx_Buff_full = TRUE;
			else
				_OSWarrior_SerialPort2_Rx_Buff_full = FALSE;			
		}
	}
	#endif
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_SerialPort2_ISR_Error
**
**     Description :
**         This function is executed when an error is occurred with 
**         the communication for the onBoard COM Port. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_SerialPort2_ISR_Error(void)
{
	/* Insert interruption code here */			
}
