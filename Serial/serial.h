/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 serial.h
**  Description: OSWarrior Serial library functions declarations
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Tested
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Revision 1, stills in development.
**	Date: 08/05/2013 - Added interruption capability for Data reception
**	Date: 08/05/2013 - Write function added
**	Date: 08/05/2013 - Structure name changed to "Serial"
**	Date: 08/05/2013 - SCI1 structure added
**	Date: 18/05/2013 - Get Character function added
**	Date: 18/05/2013 - Reception ISR added and tested
**	Date: 20/05/2013 - onReceive function added
**	Date: 20/05/2013 - Added Clear function and command constants
**	Date: 22/06/2013 - Function descriptions added
**	Date: 22/06/2013 - Version 3.0 freeze (Integrated)
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

#ifndef OSWARRIOR_SERIAL_H_
	
	#define OSWARRIOR_SERIAL_H_

	/*
	** ===================================================================
	** Serial includes
	** ===================================================================
	*/
	
	#include "oswlib/settings.h"
	#include "oswlib/Serial/serial_COMPort.h"
	#include "oswlib/Serial/serial_SCIPort.h"

	/*
	** ===================================================================
	** Serial constants
	** ===================================================================
	*/

	#define OSWARRIOR_SERIAL_BUFF_LEN 64

	/*
    ** ===================================================================
    ** ASCII Characters
    ** ===================================================================
    */

	#define ASCII_NULL 	0x00	//ASCII (HT) - Horizontal Tabulation
	#define ASCII_HT 	0x09	//ASCII (HT) - Horizontal Tabulation
	#define ASCII_LF 	0x0A	//ASCII (LF) - Line Feed
	#define ASCII_FF 	0x0C	//ASCII (FF) - Form Feed
	#define ASCII_NP 	0x0C	//ASCII (NP) - New Page
	#define ASCII_CR 	0x0D	//ASCII (CR) - Carriage Return
	
	#define ASCII_SLASH	0x2F	//ASCII (CR) - Carriage Return
	#define ASCII_N		0x6E	//ASCII (CR) - Carriage Return
	#define ASCII_R		0x72	//ASCII (CR) - Carriage Return
	#define ASCII_T		0x74	//ASCII (CR) - Carriage Return

	/*
	** ===================================================================
	** Serial type definitions
	** ===================================================================
	*/

	typedef struct {
		 char * Buf;
		 int Head;
		 int Tail;
		 int Size;
	}S_SCI_FIFO;

	typedef struct{
		T_UBYTE data;
		void (*init)(T_ULONG br);
		void (*end)(void);
		void (*clear)(void);
		void (*newLine)(void);
		T_UBYTE (*available)(void);
		
		void (*print)(T_UBYTE *);
		void (*println)(T_UBYTE *);
		void (*printChar)(T_UBYTE);
		void (*printNum)(T_SLONG);
		void (*printDigits)(T_SLONG, int);
		void (*printFloat)(T_FLOAT, int);
		
		T_UBYTE * (*read)(void);
		T_UBYTE (*getChar)(void);
		int (*readNumber)(void);
				
		void (*onReceive)(void);
	}S_SCISTR;
	
	/*
	** ===================================================================
	** Serial Structure declaration
	** ===================================================================
	*/

	PUBLIC_DATA S_SCISTR Serial;
	
	PUBLIC_DATA S_SCISTR Serial2;
	
	PUBLIC_DATA S_SCI_FIFO _OSWarrior_COMPort_Tx_FIFO;
		
#endif /* OSWARRIORMINI_SERIAL_H_ */
