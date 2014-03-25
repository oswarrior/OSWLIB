/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 i2c.c
**  Description: I2C library functions definitions
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
** I2C includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/Tone/tone.h"
#include "oswlib/PWM/PWM.h"


/*
** ===================================================================
**     Function : I2C.enable
**     Handler  : _OSWarrior_i2c_enable
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          address: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_pwm_tone(int pin, int * melody, int * durations)
{
	
	int currentNote;
	
	PWM.enable(pin);
	
	for (currentNote = 0; currentNote < sizeof(melody); currentNote++) 
	{
		PWM.freq(pin, *melody);
		delay( 1500 / *durations);
		PWM.dutyCycle(pin, 0); 
		delay(*durations/ 4);
		durations++;
		melody++;
	}

	PWM.disable(pin);
	
	return;
}
