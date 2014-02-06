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
#include "oswlib/Serial/serial_SCIPort.h"

/*
** ===================================================================
** Serial interrupt handlers
** ===================================================================
*/

static void (* near const _vect_SCIPort[])(void) @OSWarrior_SCIPort_ISR_Vector = {
	_OSWarrior_SCIPort_ISR_Write,				/* Int.no. 18 Vsci1tx (at FFDA)               Unassigned */
	_OSWarrior_SCIPort_ISR_Read,				/* Int.no. 17 Vsci1rx (at FFDC)               Unassigned */
	_OSWarrior_SCIPort_ISR_Error,				/* Int.no. 16 Vsci1err (at FFDE)              Unassigned */
};

/*
** ===================================================================
** Serial variables declarations
** ===================================================================
*/

PRIVATE_DATA T_UBYTE serial2_read_active;
PRIVATE_DATA T_UBYTE serial2_read_counter;
PRIVATE_DATA T_UBYTE serial2_read_data[32];
PRIVATE_DATA T_UBYTE serial2_getChar_active;

/*
** ===================================================================
** Serial Structures definition
** ===================================================================
*/

S_SCISTR Serial2 = {
	0x00,
	_OSWarrior_SCIPort_Init,
	_OSWarrior_SCIPort_End,
	_OSWarrior_SCIPort_Clear,
	_OSWarrior_SCIPort_NewLine,
	_OSWarrior_SCIPort_Available,
	
	_OSWarrior_SCIPort_Print,
	_OSWarrior_SCIPort_Print_Line,
	_OSWarrior_SCIPort_PrintChar,
	_OSWarrior_SCIPort_PrintNum,
	_OSWarrior_SCIPort_PrintDigits,
	_OSWarrior_SCIPort_PrintFloatNumber,
	
	_OSWarrior_SCIPort_Read,
	_OSWarrior_SCIPort_GetChar,
	_OSWarrior_SCIPort_ReadNumber,
	
	_OSWarrior_Dummy_Fnc
};

/*
** ===================================================================
**     Function : Serial2.init
**     Handler  : _OSWarrior_SCI2_Init
**
**     Description :
**         	This function enable the Serial communication trough the 
**         	onBoard COM2 Port, configuring the communication speed. 
**     
**     Parameters  : 
**         	br     : configure the data transfer baud rate 
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SCIPort_Init(T_ULONG br)
{	
	#ifdef __OSWarrior_DK__
	{	
		//Registers configuration
		SCI1C2 = 0x00U;                      // Disable the SCI1 module
		(void)(SCI1S1 == 0U);                // Dummy read of the SCI1S1 register to clear flags
		(void)(SCI1D == 0U);                 // Dummy read of the SCI1D register to clear flags 
		SCI1S2 = 0xC0U;   
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
		SCI1BD = (unsigned int)(BUSCLOCK / (16 * br));
		SCI1C1 = 0x00U;                                      
		SCI1C3 = 0x00U; 
		//SCI1C2 = 0x6CU;   	// SCI1C2_RE = 	1; SCI1C2_TE = 	1; SCI1C2_RIE = 1;  SCI1C2_TCIE = 1; 
		//SCI1C2 = 0xACU;   	// SCI1C2_RE = 	1; SCI1C2_TE = 	1; SCI1C2_RIE = 1;  SCI1C2_TIE = 1; 
		//SCI1C2 = 0x8CU;   	// SCI1C2_RE = 	1; SCI1C2_TE = 	1; SCI1C2_TIE = 1; 
		SCI1C2 = 0x2CU;   		// SCI1C2_RE = 	1; SCI1C2_TE = 	1; SCI1C2_RIE = 1; 
		//SCI1C2 = 0x0CU;   	// SCI1C2_RE = 	1; SCI1C2_TE = 	1; 	
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial2.end
**     Handler  : _OSWarrior_SCIPort_End
**
**     Description :
**         	This function disable the onBoard COMPort. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SCIPort_End(void)
{
	#ifdef __OSWarrior_DK__
	{	
		SCI1C2 = 0x00U;                      // Disable the SCI2 module
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial2.clear
**     Handler  : _OSWarrior_SCIPort_Clear
**
**     Description :
**         	When used this function send a command to display a new
**         	form page (blank page).
**         
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SCIPort_Clear(void)
{
	Serial2.printChar(ASCII_NP);			//FF - Form Feed : NP - New Page
}

/*
** ===================================================================
**     Function : Serial2.newLine
**     Handler  : _OSWarrior_SCIPort_NewLine
**
**     Description :
**         	Commands the onBoard COM Port to display a new blank line,
**        	also called as "jump" a line. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_SCIPort_NewLine(void)
{
	Serial2.printChar(ASCII_LF);				//LF - Line Feed
	Serial2.printChar(ASCII_CR);				//CR - Carriage return	
}

/*
** ===================================================================
**     Function : Serial2.available
**     Handler  : _OSWarrior_SCIPort_Available
**
**     Description :
**         This function checks if the onBoard COM Port is avaliable
**         or idle (have no pending data transfers). 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

T_UBYTE _OSWarrior_SCIPort_Available(void)
{
	#ifdef __OSWarrior_DK__
	{	
		if( SCI1S1_IDLE == 1 ) return 1;
		else return 0;
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial2.printChar
**     Handler  : _OSWarrior_SCIPort_PrintChar
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

void _OSWarrior_SCIPort_PrintChar(T_UBYTE data)
{
	#ifdef __OSWarrior_DK__
	{	
		while(!SCI1S1_TDRE){}
		SCI1D = data;		
	}
	#endif
}

/*
** ===================================================================
**     Function : Serial2.print
**     Handler  : _OSWarrior_SCIPort_Print
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

void _OSWarrior_SCIPort_Print(T_UBYTE *data)
{
	while (*data)
	{
		_OSWarrior_SCIPort_PrintChar(*data);
		data++;
	}
}

/*
** ===================================================================
**     Function : Serial2.print
**     Handler  : _OSWarrior_SCIPort_Print
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

void _OSWarrior_SCIPort_PrintFloatNumber(double number, int decimals)
{
	number_explode_FloatNumbers( number, _OSWarrior_SCIPort_PrintChar, decimals);	
}

/*
** ===================================================================
**     Function : Serial2.println
**     Handler  : _OSWarrior_SCIPort_Print_Line
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

void _OSWarrior_SCIPort_Print_Line(T_UBYTE *data)
{
	Serial2.print(data);						//Print Data
	Serial2.printChar(ASCII_LF);				//LF - Line Feed
	Serial2.printChar(ASCII_CR);				//CR - Carriage return	
};

/*
** ===================================================================
**     Function : Serial2.printNum
**     Handler  : _OSWarrior_SCIPort_PrintNum
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

void _OSWarrior_SCIPort_PrintNum (T_SLONG number)
{
	number_explode( number, _OSWarrior_SCIPort_PrintChar, 0);
}

/*
** ===================================================================
**     Function : Serial2.printDigits
**     Handler  : _OSWarrior_SCIPort_PrintDigits
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

void _OSWarrior_SCIPort_PrintDigits (T_SLONG number, int digits)
{
	number_explode( number, _OSWarrior_SCIPort_PrintChar, digits);
}

/*
** ===================================================================
**     Function : Serial2.read
**     Handler  : _OSWarrior_SCIPort_Read
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

T_UBYTE * _OSWarrior_SCIPort_Read(void)
{
	T_UBYTE *str;
	serial2_read_counter = 0;
	serial2_read_active = TRUE;
	while(serial2_read_active);
	str = serial2_read_data;
	return str;
}

int _OSWarrior_SCIPort_ReadNumber(void)
{
	T_UBYTE * userFnc;
	userFnc = Serial2.read();
	return str_to_int(userFnc);
}

/*
** ===================================================================
**     Function : Serial2.getChar
**     Handler  : _OSWarrior_SCIPort_GetChar
**
**     Description :
**         This function waits until a data T_UBYTE is received by the 
**         onBoard COM Port. 
**     
**     Parameters  : Nothing
**     Returns     : Character received
** ===================================================================
*/

T_UBYTE _OSWarrior_SCIPort_GetChar(void){
	serial2_getChar_active = 1;
	while(serial2_getChar_active);
	return Serial2.data;
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_SCIPort_Write_isr
**
**     Description :
**         This interruption is called after the last data was sent, 
**         it checks for pending data to send for the onBoard COM Port. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_SCIPort_ISR_Write(void){
	#ifdef __OSWarrior_DK__
	{	
		T_UBYTE status;
		status = SCI1S1;
		if(status & SCI1S1_TDRE_MASK)
		{
			/* Interrupt Code Here */
		}
	}
	#endif
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_SCIPort_ISR_Read
**
**     Description :
**         This interruption is called every time a data T_UBYTE is 
**         received trough the onBoard COM Port, the last value 
**         received is stored for future needs and he function 
**         onReceive is executed to handle the data. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_SCIPort_ISR_Read(void)
{
	#ifdef __OSWarrior_DK__
	{	
		T_UBYTE status;
		status = SCI1S1;
		if(status & SCI1S1_RDRF_MASK)
		{
			
			Serial2.data = SCI1D;
			
			if (Serial2.data != 0x00)
			{
				if(serial2_read_active)
				{
					if( ( Serial2.data != ASCII_CR ) && serial2_read_counter < 32 )	//If not Carriage return
					{	
						serial2_read_data[serial2_read_counter] = Serial2.data;		//Save data
						Serial2.printChar(Serial2.data);								//Echo data
						serial2_read_counter++;				
					}
					else
					{
						serial2_read_data[serial2_read_counter] = 0x00;				//End array
						Serial2.newLine();											//Echo a new line
						serial2_read_active = FALSE;
					}
				}
				if(serial2_getChar_active) 
					serial2_getChar_active = 0;
				Serial2.onReceive();
			}
		}
	}
	#endif	
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_SCIPort_ISR_Error
**
**     Description :
**         This function is executed when an error is occurred with 
**         the communication for the onBoard COM Port. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_SCIPort_ISR_Error(void)
{
	/* Insert interruption code here */			
}
