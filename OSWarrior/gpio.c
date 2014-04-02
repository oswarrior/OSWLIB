/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
** 	Filename: 	 gpio.h
** 	Description: OSWarrior Generic Purpose I/O library
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Version 2.0 freeze (Integrated)
**	Date: 01/05/2012 - Several bugs fixed
**	Date: 02/05/2013 - Version 2.1 freeze (Tested)
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

/*
** ===================================================================
** GPIO includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/OSWarrior/gpio.h"

/*
** ===================================================================
**     Function : pinDirection
**
**     Description :
**         This function configures the specified pin direction as input or output. 
**     
**     Parameters  : 
**         pin : pin to be configured
**         direction : pin direction
**     
**     Returns     : Nothing
** ===================================================================
*/

void pinMode(int pin, int direction)
{		
	
	if(direction > 2) direction = INPUT;
	
	switch(pin)
	{
		//////////////////////////////
		// 		Digital port 0		//
		//////////////////////////////
		#ifdef D0
			case_pinDir(0);
		#endif
		#ifdef D1
			case_pinDir(1);
		#endif
		#ifdef D2
			case_pinDir(2);
		#endif
		#ifdef D3
			case_pinDir(3);
		#endif
		#ifdef D4
			case_pinDir(4);
		#endif
		#ifdef D5
			case_pinDir(5);
		#endif
		#ifdef D6
			case_pinDir(6);
		#endif			
		#ifdef D7
			case_pinDir(7);
		#endif
		
		//////////////////////////////
		// 		Digital port 1		//
		//////////////////////////////
		#ifdef D8
			case_pinDir(8);
		#endif
		#ifdef D9
			case_pinDir(9);
		#endif
		#ifdef D10
			case_pinDir(10);
		#endif
		#ifdef D11
			case_pinDir(11);
		#endif
		#ifdef D12
			case_pinDir(12);
		#endif
		#ifdef D13
			case_pinDir(13);
		#endif
		#ifdef D14
			case_pinDir(14);
		#endif			
		#ifdef D15
			case_pinDir(15);
		#endif

		//////////////////////////////
		// 		Digital port 2		//
		//////////////////////////////
		#ifdef D16
			case_pinDir(16);
		#endif
		#ifdef D17
			case_pinDir(17);
		#endif
		#ifdef D18
			case_pinDir(18);
		#endif
		#ifdef D19
			case_pinDir(19);
		#endif
		#ifdef D20
			case_pinDir(20);
		#endif
		#ifdef D21
			case_pinDir(21);
		#endif
		#ifdef D22
			case_pinDir(22);
		#endif			
		#ifdef D23
			case_pinDir(23);
		#endif
		//////////////////////////////
		// 		Digital port 3		//
		//////////////////////////////
		#ifdef D24
			case_pinDir(24);
		#endif
		#ifdef D25
			case_pinDir(25);
		#endif
		#ifdef D26
			case_pinDir(26);
		#endif
		#ifdef D27
			case_pinDir(27);
		#endif
		#ifdef D28
			case_pinDir(28);
		#endif
		#ifdef D29
			case_pinDir(29);
		#endif
		#ifdef D30
			case_pinDir(30);
		#endif			
		#ifdef D31
			case_pinDir(31);
		#endif
		//////////////////////////
		// 		Onboard LEDS	//
		//////////////////////////
		#if ( 0 < MAX_ONBOARD_LEDS)
			case_ledDir(0);
		#endif
		#if ( 1 < MAX_ONBOARD_LEDS)
			case_ledDir(1);
		#endif
		#if ( 2 < MAX_ONBOARD_LEDS)
			case_ledDir(2);
		#endif
		#if ( 3 < MAX_ONBOARD_LEDS)
			case_ledDir(3);
		#endif
		#if ( 4 < MAX_ONBOARD_LEDS)
			case_ledDir(4);
		#endif
		#if ( 5 < MAX_ONBOARD_LEDS)
			case_ledDir(5);
		#endif
		#if ( 6 < MAX_ONBOARD_LEDS)
			case_ledDir(6);
		#endif
		#if ( 7 < MAX_ONBOARD_LEDS)
			case_ledDir(7);
		#endif
	}
	
};

/*
** ===================================================================
**     Function : digitalWrite
**
**     Description :
**         This function writes a boolean type value to the specified pin. 
**     
**     Parameters  : 
**         pin : pin to be written
**         value : boolean value to be written
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void digitalWrite(int pin, int value)
{
	if(value > 1) value = 1;
	switch(pin)
	{
		//////////////////////////////
		// 		Digital port 0		//
		//////////////////////////////
		#ifdef D0
			case_writePin(0);
		#endif
		#ifdef D1
			case_writePin(1);
		#endif
		#ifdef D2
			case_writePin(2);
		#endif
		#ifdef D3
			case_writePin(3);
		#endif
		#ifdef D4
			case_writePin(4);
		#endif
		#ifdef D5
			case_writePin(5);
		#endif
		#ifdef D6
			case_writePin(6);
		#endif			
		#ifdef D7
			case_writePin(7);
		#endif
		
		//////////////////////////////
		// 		Digital port 1		//
		//////////////////////////////
		#ifdef D8
			case_writePin(8);
		#endif
		#ifdef D9
			case_writePin(9);
		#endif
		#ifdef D10
			case_writePin(10);
		#endif
		#ifdef D11
			case_writePin(11);
		#endif
		#ifdef D12
			case_writePin(12);
		#endif
		#ifdef D13
			case_writePin(13);
		#endif
		#ifdef D14
			case_writePin(14);
		#endif			
		#ifdef D15
			case_writePin(15);
		#endif

		//////////////////////////////
		// 		Digital port 2		//
		//////////////////////////////
		#ifdef D16
			case_writePin(16);
		#endif
		#ifdef D17
			case_writePin(17);
		#endif
		#ifdef D18
			case_writePin(18);
		#endif
		#ifdef D19
			case_writePin(19);
		#endif
		#ifdef D20
			case_writePin(20);
		#endif
		#ifdef D21
			case_writePin(21);
		#endif
		#ifdef D22
			case_writePin(22);
		#endif			
		#ifdef D23
			case_writePin(23);
		#endif
			
		//////////////////////////////
		// 		Digital port 3		//
		//////////////////////////////
		#ifdef D24
			case_writePin(24);
		#endif
		#ifdef D25
			case_writePin(25);
		#endif
		#ifdef D26
			case_writePin(26);
		#endif
		#ifdef D27
			case_writePin(27);
		#endif
		#ifdef D28
			case_writePin(28);
		#endif
		#ifdef D29
			case_writePin(29);
		#endif
		#ifdef D30
			case_writePin(30);
		#endif			
		#ifdef D31
			case_writePin(31);
		#endif
			
		//////////////////////////
		// 		Onboard LEDS	//
		//////////////////////////
		#if ( 0 < MAX_ONBOARD_LEDS)
			case_writeLed(0);
		#endif
		#if ( 1 < MAX_ONBOARD_LEDS)
			case_writeLed(1);
		#endif
		#if ( 2 < MAX_ONBOARD_LEDS)
			case_writeLed(2);
		#endif
		#if ( 3 < MAX_ONBOARD_LEDS)
			case_writeLed(3);
		#endif
		#if ( 4 < MAX_ONBOARD_LEDS)
			case_writeLed(4);
		#endif
		#if ( 5 < MAX_ONBOARD_LEDS)
			case_writeLed(5);
		#endif
		#if ( 6 < MAX_ONBOARD_LEDS)
			case_writeLed(6);
		#endif
		#if ( 7 < MAX_ONBOARD_LEDS)
			case_writeLed(7);
		#endif
	}
	
};

/*
** ===================================================================
**     Function : digitalToggle
**
**     Description :
**         This function toggles the specified pin value. 
**     
**     Parameters  : 
**         pin : pin to be written
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void digitalToggle(int pin)
{
	switch(pin)
	{
		//////////////////////////////
		// 		Digital port 0		//
		//////////////////////////////
		#ifdef D0
			case_togglePin(0);
		#endif
		#ifdef D1
			case_togglePin(1);
		#endif
		#ifdef D2
			case_togglePin(2);
		#endif
		#ifdef D3
			case_togglePin(3);
		#endif
		#ifdef D4
			case_togglePin(4);
		#endif
		#ifdef D5
			case_togglePin(5);
		#endif
		#ifdef D6
			case_togglePin(6);
		#endif			
		#ifdef D7
			case_togglePin(7);
		#endif
		
		//////////////////////////////
		// 		Digital port 1		//
		//////////////////////////////
		#ifdef D8
			case_togglePin(8);
		#endif
		#ifdef D9
			case_togglePin(9);
		#endif
		#ifdef D10
			case_togglePin(10);
		#endif
		#ifdef D11
			case_togglePin(11);
		#endif
		#ifdef D12
			case_togglePin(12);
		#endif
		#ifdef D13
			case_togglePin(13);
		#endif
		#ifdef D14
			case_togglePin(14);
		#endif			
		#ifdef D15
			case_togglePin(15);
		#endif

		//////////////////////////////
		// 		Digital port 2		//
		//////////////////////////////
			
		#ifdef D16
			case_togglePin(16);
		#endif
		#ifdef D17
			case_togglePin(17);
		#endif
		#ifdef D18
			case_togglePin(18);
		#endif
		#ifdef D19
			case_togglePin(19);
		#endif
		#ifdef D20
			case_togglePin(20);
		#endif
		#ifdef D21
			case_togglePin(21);
		#endif
		#ifdef D22
			case_togglePin(22);
		#endif			
		#ifdef D23
			case_togglePin(23);
		#endif
			
		//////////////////////////////
		// 		Digital port 3		//
		//////////////////////////////
			
		#ifdef D24
			case_togglePin(24);
		#endif
		#ifdef D25
			case_togglePin(25);
		#endif
		#ifdef D26
			case_togglePin(26);
		#endif
		#ifdef D27
			case_togglePin(27);
		#endif
		#ifdef D28
			case_togglePin(28);
		#endif
		#ifdef D29
			case_togglePin(29);
		#endif
		#ifdef D30
			case_togglePin(30);
		#endif			
		#ifdef D31
			case_togglePin(31);
		#endif
			
		//////////////////////////
		// 		Onboard LEDS	//
		//////////////////////////
			
		#if ( 0 < MAX_ONBOARD_LEDS)
			case_toggleLed(0);
		#endif
		#if ( 1 < MAX_ONBOARD_LEDS)
			case_toggleLed(1);
		#endif
		#if ( 2 < MAX_ONBOARD_LEDS)
			case_toggleLed(2);
		#endif
		#if ( 3 < MAX_ONBOARD_LEDS)
			case_toggleLed(3);
		#endif
		#if ( 4 < MAX_ONBOARD_LEDS)
			case_toggleLed(4);
		#endif
		#if ( 5 < MAX_ONBOARD_LEDS)
			case_toggleLed(5);
		#endif
		#if ( 6 < MAX_ONBOARD_LEDS)
			case_toggleLed(6);
		#endif
		#if ( 7 < MAX_ONBOARD_LEDS)
			case_toggleLed(7);
		#endif
	}
};

/*
** ===================================================================
**     Function : digitalRead
**
**     Description :
**         This function reads the specified pin value. 
**     
**     Parameters  : 
**         pin : pin to be read
**     
**     Returns     : Boolean type value of the specified pin 
** ===================================================================
*/
	
int digitalRead(int pin)
{
	
	switch(pin)
	{
		
		//////////////////////////////
		// 		Digital port 0		//
		//////////////////////////////
	
		#ifdef D0
			case_readPin(0);
		#endif
		#ifdef D1
			case_readPin(1);
		#endif
		#ifdef D2
			case_readPin(2);
		#endif
		#ifdef D3
			case_readPin(3);
		#endif
		#ifdef D4
			case_readPin(4);
		#endif
		#ifdef D5
			case_readPin(5);
		#endif
		#ifdef D6
			case_readPin(6);
		#endif			
		#ifdef D7
			case_readPin(7);
		#endif
		
		//////////////////////////////
		// 		Digital port 1		//
		//////////////////////////////
			
		#ifdef D8
			case_readPin(8);
		#endif
		#ifdef D9
			case_readPin(9);
		#endif
		#ifdef D10
			case_readPin(10);
		#endif
		#ifdef D11
			case_readPin(11);
		#endif
		#ifdef D12
			case_readPin(12);
		#endif
		#ifdef D13
			case_readPin(13);
		#endif
		#ifdef D14
			case_readPin(14);
		#endif			
		#ifdef D15
			case_readPin(15);
		#endif

		//////////////////////////////
		// 		Digital port 2		//
		//////////////////////////////
			
		#ifdef D16
			case_readPin(16);
		#endif
		#ifdef D17
			case_readPin(17);
		#endif
		#ifdef D18
			case_readPin(18);
		#endif
		#ifdef D19
			case_readPin(19);
		#endif
		#ifdef D20
			case_readPin(20);
		#endif
		#ifdef D21
			case_readPin(21);
		#endif
		#ifdef D22
			case_readPin(22);
		#endif			
		#ifdef D23
			case_readPin(23);
		#endif
			
		//////////////////////////////
		// 		Digital port 3		//
		//////////////////////////////
			
		#ifdef D24
			case_readPin(24);
		#endif
		#ifdef D25
			case_readPin(25);
		#endif
		#ifdef D26
			case_readPin(26);
		#endif
		#ifdef D27
			case_readPin(27);
		#endif
		#ifdef D28
			case_readPin(28);
		#endif
		#ifdef D29
			case_readPin(29);
		#endif
		#ifdef D30
			case_readPin(30);
		#endif			
		#ifdef D31
			case_readPin(31);
		#endif
		
		//////////////////////////
		// 		Onboard LEDS	//
		//////////////////////////
			
		#if ( 0 < MAX_ONBOARD_LEDS)
			case_readLed(0);
		#endif
		#if ( 1 < MAX_ONBOARD_LEDS)
			case_readLed(1);
		#endif
		#if ( 2 < MAX_ONBOARD_LEDS)
			case_readLed(2);
		#endif
		#if ( 3 < MAX_ONBOARD_LEDS)
			case_readLed(3);
		#endif
		#if ( 4 < MAX_ONBOARD_LEDS)
			case_readLed(4);
		#endif
		#if ( 5 < MAX_ONBOARD_LEDS)
			case_readLed(5);
		#endif
		#if ( 6 < MAX_ONBOARD_LEDS)
			case_readLed(6);
		#endif
		#if ( 7 < MAX_ONBOARD_LEDS)
			case_readLed(7);
		#endif
	}
};

/*
** ===================================================================
**     Function : writeNibble
**
**     Description :
**         This function writes data to the specified 4 bits. 
**     
**     Parameters  : 
**         data : data to be written
**         bit3 to bit0 : selected nibble pins
**     
**     Returns     : Nothing
** ===================================================================
*/

void writeNibble( T_UBYTE data, T_UBYTE bit3, T_UBYTE bit2, T_UBYTE bit1, T_UBYTE bit0 )
{
		
	digitalWrite( bit0, ( data & BIT_MASK ) );
	digitalWrite( bit1, ( ( data>>1 ) & BIT_MASK ) );
	digitalWrite( bit2, ( ( data>>2 ) & BIT_MASK ) );
	digitalWrite( bit3, ( ( data>>3 ) & BIT_MASK ) );

};
