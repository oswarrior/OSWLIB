/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 kbi.h
** 	Description: OSWarrior Keyboard interruptions library
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 12/09/2013 - Library created
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

#ifndef OSWARRIOR_KBI_H_
	
	#define OSWARRIOR_KBI_H_

    /*
	** ===================================================================
	** KBI type definitions
	** ===================================================================
	*/

	typedef struct{
		void (*attachInterrupt)(int pin, void (*handler)(void));	/*** KBI - Read Function ***/
		void (*detachInterrupt)(int pin);							/*** KBI - Read Function ***/
		void (*onPress)(void);							/*** KBI - Read Function ***/
	}S_KBISTR;	
	
    /*
    ** ===================================================================
    ** KBI related interrupt function handlers
    ** ===================================================================
    */
	
	PUBLIC_FCT __interrupt void _OSWarrior_ISR_KBI(void);
	
    /*
    ** ===================================================================
    ** KBI functions prototypes
    ** ===================================================================
    */

	PUBLIC_FCT void _OSWarrior_kbi_enable(void);
	PUBLIC_FCT void _OSWarrior_kbi_disable(void);
	
	PUBLIC_FCT void _OSWarrior_kbi_attachInterrupt(int pin, void (*handler)(void));
	PUBLIC_FCT void _OSWarrior_kbi_detachInterrupt(int pin);
	
	PUBLIC_FCT __interrupt void _OSWarrior_kbi_isr_handler(void);
	
	PUBLIC_FCT T_P_FUNCTION_VOID _OSWarrior_kbi_handlers[MAX_KBI_CHANNELS];

	/*
	** ===================================================================
	** KBI Structure declaration
	** ===================================================================
	*/

	PUBLIC_DATA S_KBISTR KBI;

#endif
