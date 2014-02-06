/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 oswarrior.h
* 	Description: OSWarrior Main library
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Version 2.0 freeze
**	Date: 09/05/2013 - Updated disableDelays function.
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

/*** Includes.- Data types and constants libraries ***/

#ifndef OSWARRIOR_H
	#define OSWARRIOR_H

    /*
    ** ===================================================================
    ** OSWarrior includes
    ** ===================================================================
    */

	#include "oswlib/OSWarrior/dataTypes.h"
	#include "oswlib/OSWarrior/binary.h"
	
    /*
    ** ===================================================================
    ** OSWarrior Mini
    ** ===================================================================
    */

	#ifdef __OSWarrior_DK__
		
		/*** Includes.- OSWarrior Board Pinout ***/
		#include "oswlib/OSWarrior/pinout/OSWarrior_DK_HAL.h"	//OSWarrior Mini Board
	
	#endif
	
    /*
    ** ===================================================================
    ** OSWarrior Micro
    ** ===================================================================
    */

	#ifdef __OSWarrior_Micro__
		
		/*** Includes.- OSWarrior Board Pinout ***/
		#include "oswlib/OSWarrior/pinout/OSWarrior_Micro_HAL.h"	//OSWarrior Micro Board
	
	#endif

    /*
    ** ===================================================================
    ** OSWarrior includes
    ** ===================================================================
    */

	#include "oswlib/OSWarrior/math.h"		//Math constants and operations
	#include "oswlib/OSWarrior/gpio.h"		//GPIO control
	#include "oswlib/OSWarrior/string.h"		//Strings control
	#include "oswlib/OSWarrior/delay.h"		//Delay control
	
    /*
    ** ===================================================================
    ** OSWarrior functions prototypes
    ** ===================================================================
    */

	PUBLIC_FCT void OSWarrior_Clock_Settings(void);
	
	PUBLIC_FCT void setup(void);
	PUBLIC_FCT void loop(void);
	PUBLIC_FCT void _OSWarrior_Dummy_Fnc(void);

#endif
