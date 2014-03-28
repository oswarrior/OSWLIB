/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
** 	Filename: 	 gpio.h
** 	Description: OSWarrior Generic Purpose I/O library
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							 LICENSE:
** =============================================================================
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the Attribution-ShareAlike
**  License as published by the Creative Commons Organisation; either
**  version 3.0 of the License, or (at your option) any later version.
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
**  See the Attribution-ShareAlike License for more details.
**  You should have received a copy of the Creative Commons Attribution-ShareAlike 
**  License along with this library; if not send a email to the library author.
** =============================================================================
*/

#ifndef OSWARRIOR_GPIO_H_
	
	#define OSWARRIOR_GPIO_H_
	
	extern void pinMode(int pin, int direction);
	extern void digitalWrite(int pin, int value);
	extern void togglePin(int pin);
	extern int digitalRead(int pin);
	extern void writeNibble( T_UBYTE data, T_UBYTE bit3, T_UBYTE bit2, T_UBYTE bit1, T_UBYTE bit0 );
	
#endif
