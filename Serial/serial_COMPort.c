/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 serial.c
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
#include "oswlib/Serial/serial.h"
#include "oswlib/Serial/serial_COMPort.h"

/*
** ===================================================================
** Serial interrupt handlers
** ===================================================================
*/

static void (* near const _vect_COMPort[])(void) @OSWarrior_COMPort_ISR_Vector = {
	_OSWarrior_COMPort_ISR_Write,            	/* Int.no. 21 Vsci2tx (at FFD4) */
	_OSWarrior_COMPort_ISR_Read,             	/* Int.no. 20 Vsci2rx (at FFD6) */
	_OSWarrior_COMPort_ISR_Error,				/* Int.no. 19 Vsci2er (at FFD8) */
};

/*
** ===================================================================
** Serial variables declarations
** ===================================================================
*/

volatile T_UBYTE _OSWarrior_COMPort_Rx_Buff[OSWARRIOR_SERIAL_BUFF_LEN];
volatile T_UBYTE _OSWarrior_COMPort_Rx_nxt;
volatile T_UBYTE _OSWarrior_COMPort_Rx_rd;

volatile T_UBYTE _OSWarrior_COMPort_Tx_Buff[OSWARRIOR_SERIAL_BUFF_LEN];
volatile T_UBYTE _OSWarrior_COMPort_Tx_nxt = 0;
volatile T_UBYTE _OSWarrior_COMPort_Tx_rd = 0;

volatile T_BOOLEAN _OSWarrior_COMPort_Tx_Buff_full = FALSE;
volatile T_BOOLEAN _OSWarrior_COMPort_Tx_active = FALSE;

volatile T_UBYTE _OSWarrior_COMPort_read_active;
volatile T_UBYTE _OSWarrior_COMPort_getChar_active;

/*
** ===================================================================
** Serial Structures definition
** ===================================================================
*/

S_SCISTR Serial = {
	0x00,
	_OSWarrior_COMPort_Init,
	_OSWarrior_COMPort_End,
	_OSWarrior_COMPort_Clear,
	_OSWarrior_COMPort_NewLine,
	_OSWarrior_COMPort_Available,
	
	_OSWarrior_COMPort_Print,
	_OSWarrior_COMPort_Print_Line,
	_OSWarrior_COMPort_PrintChar,
	_OSWarrior_COMPort_PrintNum,
	_OSWarrior_COMPort_PrintDigits,
	_OSWarrior_COMPort_PrintFloatNumber,
	
	_OSWarrior_COMPort_Read,
	_OSWarrior_COMPort_GetChar,
	_OSWarrior_COMPort_ReadNumber,
	
	_OSWarrior_Dummy_Fnc
};

/*
** ===================================================================
**     Function : Serial.init
**     Handler  : _OSWarrior_COMPort_Init
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

void _OSWarrior_COMPort_Init(T_ULONG baudrate)
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
	
	_OSWarrior_COMPort_setBaudRate(baudrate); 
	
	_OSWarrior_COMPort_Enable_Rx();
	_OSWarrior_COMPort_Enable_Tx();
	_OSWarrior_COMPort_Enable_Rx_ISR();
	//_OSWarrior_COMPort_Enable_Tx_ISR();
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

void _OSWarrior_COMPort_setBaudRate(T_ULONG baudrate)
{
	#ifdef __OSWarrior_DK__
		SCI2BD = (unsigned int)(BUSCLOCK / (16 * baudrate));
	#endif	
}

/*
** ===================================================================
**     Function : Serial.end
**     Handler  : _OSWarrior_COMPort_End
**
**     Description :
**         	This function disable the onBoard COMPort. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_COMPort_End(void)
{
	#ifdef __OSWarrior_DK__
	{	
		SCI2C2 = 0x00U;                      // Disable the SCI2 module
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial.clear
**     Handler  : _OSWarrior_COMPort_Clear
**
**     Description :
**         	When used this function send a command to display a new
**         	form page (blank page).
**         
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_COMPort_Clear(void)
{
	Serial.printChar(ASCII_NP);				//FF - Form Feed or NP - New Page
}

/*
** ===================================================================
**     Function : Serial.newLine
**     Handler  : _OSWarrior_COMPort_NewLine
**
**     Description :
**         	Commands the onBoard COM Port to display a new blank line,
**        	also called as "jump" a line. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_COMPort_NewLine(void)
{
	Serial.printChar(ASCII_LF);				//LF - Line Feed
	Serial.printChar(ASCII_CR);				//CR - Carriage return	
}

/*
** ===================================================================
**     Function : Serial.available
**     Handler  : _OSWarrior_COMPort_Available
**
**     Description :
**         This function checks if the onBoard COM Port is available
**         or idle (have no pending data transfers). 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

T_UBYTE _OSWarrior_COMPort_Available(void)
{
	#ifdef __OSWarrior_DK__
	{	
		if( SCI2S1_IDLE == 1 ) return 1;
		else return 0;
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial.println
**     Handler  : _OSWarrior_COMPort_Print_Line
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

void _OSWarrior_COMPort_Print_Line(T_UBYTE *data)
{
	Serial.print(data);
	Serial.print("\r\n");
};

/*
** ===================================================================
**     Function : Serial.printNum
**     Handler  : _OSWarrior_COMPort_PrintNum
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

void _OSWarrior_COMPort_PrintNum (T_SLONG number)
{
	number_explode( number, _OSWarrior_COMPort_PrintChar, 0);
}

/*
** ===================================================================
**     Function : Serial.printDigits
**     Handler  : COMPort_PrintDigits
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

void _OSWarrior_COMPort_PrintDigits (T_SLONG number, int digits)
{
	number_explode( number, _OSWarrior_COMPort_PrintChar, digits);
}

/*
** ===================================================================
**     Function : Serial.printFloat
**     Handler  : _OSWarrior_COMPort_PrintFloatNumber
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

void _OSWarrior_COMPort_PrintFloatNumber(T_FLOAT number, int decimals)
{
	number_explode_FloatNumbers( number, _OSWarrior_COMPort_PrintChar, decimals);	
}

/*
** ===================================================================
**     Function : Serial.read
**     Handler  : COMPort_Read
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

T_UBYTE * _OSWarrior_COMPort_Read(void)
{
	T_UBYTE * str;
	_OSWarrior_COMPort_Rx_nxt = 0;
	_OSWarrior_COMPort_read_active = TRUE;
	Serial.onReceive = _OSWarrior_COMPort_Read_Handler;
	while(_OSWarrior_COMPort_read_active);
	Serial.onReceive = _OSWarrior_Dummy_Fnc;
	str = (T_UBYTE *)_OSWarrior_COMPort_Rx_Buff;
	return str;
}

void _OSWarrior_COMPort_Read_Handler(void)
{
	if( ( Serial.data != '\r' ) && ( Serial.data != 0x00 ) && (_OSWarrior_COMPort_Rx_nxt < OSWARRIOR_SERIAL_BUFF_LEN) )	
	{	
		_OSWarrior_COMPort_Rx_Buff[_OSWarrior_COMPort_Rx_nxt] = Serial.data; 	//Save data to buffer
		_OSWarrior_COMPort_Rx_nxt++;				
	}
	else
	{
		_OSWarrior_COMPort_Rx_Buff[_OSWarrior_COMPort_Rx_nxt] = 0x00;	//End buffer
		_OSWarrior_COMPort_read_active = FALSE;
	}
	Serial.printChar(Serial.data);										//Echo data
}

int _OSWarrior_COMPort_ReadNumber(void)
{
	T_UBYTE * userFnc;
	userFnc = Serial.read();
	return str_to_int(userFnc);
}

/*
** ===================================================================
**     Function : Serial.getChar
**     Handler  : _OSWarrior_COMPort_GetChar
**
**     Description :
**         This function waits until a data T_UBYTE is received by the 
**         onBoard COM Port. 
**     
**     Parameters  : Nothing
**     Returns     : Character received
** ===================================================================
*/

T_UBYTE _OSWarrior_COMPort_GetChar(void)
{
	_OSWarrior_COMPort_getChar_active = 1;
	while(_OSWarrior_COMPort_getChar_active);
	return Serial.data;
}

/*
** ===================================================================
**     Enable/Disable functions for Rx and Tx
** ===================================================================
*/

void _OSWarrior_COMPort_Enable_Tx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TE = 1u;	
	#endif
}

void _OSWarrior_COMPort_Enable_Rx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RE = 1u;	
	#endif
}

void _OSWarrior_COMPort_Enable_Tx_Rx(void)
{
	_OSWarrior_COMPort_Enable_Tx();
	_OSWarrior_COMPort_Enable_Rx();
}

void _OSWarrior_COMPort_Disable_Tx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TE = 0u;	
	#endif
}

void _OSWarrior_COMPort_Disable_Rx(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RE = 0u;	
	#endif	
}

void _OSWarrior_COMPort_Disable_Tx_Rx(void)
{
	_OSWarrior_COMPort_Disable_Tx();
	_OSWarrior_COMPort_Disable_Rx();
}

/* ISR Enable/Disable */

void _OSWarrior_COMPort_Enable_Tx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TIE = 1u;	
	#endif
}

void _OSWarrior_COMPort_Enable_Rx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RIE = 1u;	
	#endif
}

void _OSWarrior_COMPort_Enable_Tx_Rx_ISR(void)
{
	_OSWarrior_COMPort_Enable_Tx_ISR();
	_OSWarrior_COMPort_Enable_Rx_ISR();
}

void _OSWarrior_COMPort_Disable_Tx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_TIE = 0u;	
	#endif
}

void _OSWarrior_COMPort_Disable_Rx_ISR(void)
{
	#ifdef __OSWarrior_DK__
		SCI2C2_RIE = 0u;	
	#endif
}

void _OSWarrior_COMPort_Disable_Tx_Rx_ISR(void)
{
	_OSWarrior_COMPort_Disable_Tx_ISR();
	_OSWarrior_COMPort_Disable_Rx_ISR();
}

/*
** ===================================================================
**     Function : Serial.printChar
**     Handler  : _OSWarrior_COMPort_PrintChar
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

void _OSWarrior_COMPort_PrintChar(T_UBYTE data)
{

	while(_OSWarrior_COMPort_Tx_Buff_full);
	
	_OSWarrior_COMPort_Tx_Buff[_OSWarrior_COMPort_Tx_nxt] = data;
	_OSWarrior_COMPort_Tx_nxt++;
	if(_OSWarrior_COMPort_Tx_nxt >= OSWARRIOR_SERIAL_BUFF_LEN)
	{
		_OSWarrior_COMPort_Tx_nxt = 0;
	}
	if(_OSWarrior_COMPort_Tx_nxt == _OSWarrior_COMPort_Tx_rd)
	{
		_OSWarrior_COMPort_Tx_Buff_full = TRUE;
	}
	else
	{
		_OSWarrior_COMPort_Tx_Buff_full = FALSE;
	}
	
	_OSWarrior_COMPort_Enable_Tx_ISR();
}

/*
** ===================================================================
**     Function : Serial.print
**     Handler  : _OSWarrior_COMPort_Print
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

void _OSWarrior_COMPort_Print(T_UBYTE *data)
{	
	while (*data)
	{
		_OSWarrior_COMPort_PrintChar(*data);
		data++;
	}
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_COMPort_ISR_Write
**
**     Description :
**         This interruption is called after the last data byte was sent, 
**         it checks for pending data to send for the serial port. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_COMPort_ISR_Write(void)
{
	if(COMPort_TF)
	{
		COMPort_Data = (T_UBYTE) _OSWarrior_COMPort_Tx_Buff[_OSWarrior_COMPort_Tx_rd];
		_OSWarrior_COMPort_Tx_rd++;
		if( _OSWarrior_COMPort_Tx_rd >= OSWARRIOR_SERIAL_BUFF_LEN ) _OSWarrior_COMPort_Tx_rd = 0; 	
		if( _OSWarrior_COMPort_Tx_rd == _OSWarrior_COMPort_Tx_nxt ) _OSWarrior_COMPort_Disable_Tx_ISR();
		_OSWarrior_COMPort_Tx_Buff_full = FALSE;										
	}	
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_COMPort_ISR_Read
**
**     Description :
**         This interruption is called every time a data T_UBYTE is 
**         received trough the onBoard COM Port, the last value 
**         received is stored for future needs and he function 
**         onReceive is executed to handle the data. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_COMPort_ISR_Read(void)
{
	#ifdef __OSWarrior_DK__
	{	
		T_UBYTE status;
		status = SCI2S1;
		if(status & SCI2S1_RDRF_MASK)
		{
			Serial.data = SCI2D;
			_OSWarrior_COMPort_getChar_active = 0;
			Serial.onReceive();
		}
	}
	#endif
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_COMPort_ISR_Error
**
**     Description :
**         This function is executed when an error is occurred with 
**         the communication for the onBoard COM Port. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_COMPort_ISR_Error(void)
{
	/* Insert interruption code here */			
}
