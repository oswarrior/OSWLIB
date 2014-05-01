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
		#include "oswlib/OSWarrior/pinout/oswarrior_dk_hal.h"	//OSWarrior Mini Board
	
	#endif
	
    /*
    ** ===================================================================
    ** OSWarrior Micro
    ** ===================================================================
    */

	#ifdef __OSWarrior_Uno__
		
		/*** Includes.- OSWarrior Board Pinout ***/
		#include "oswlib/OSWarrior/pinout/oswarrior_dk_uno.h"	//OSWarrior Micro Board
	
	#endif

    /*
    ** ===================================================================
    ** OSWarrior includes
    ** ===================================================================
    */

	#include "oswlib/OSWarrior/math.h"		//Math constants and operations
	#include "oswlib/OSWarrior/gpio.h"		//GPIO control
	#include "oswlib/OSWarrior/pin.h"		//GPIO control
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
