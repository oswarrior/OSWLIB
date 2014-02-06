/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 analog.c
**  Description: OSWarrior Analog library functions definitions
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
** Analog includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/Analog/analog.h"

/*
** ===================================================================
** Analog Structure definition
** ===================================================================
*/

S_ADCSTR Analog  = {
	8,
	_OSWarrior_adc_init, 		  
	_OSWarrior_adc_setResolution,
	_OSWarrior_adc_enable,
	_OSWarrior_adc_disable,
	_OSWarrior_adc_read		
};

/*
** ===================================================================
**     Function : ADC.init
**     Handler  : _OSWarrior_adc_init
**
**     Description :
**         Initialize the analog pins as ADC inputs, doing this the 
**         analog pins will can't be used as digital pins.
**         
**     Parameters  : Nothing
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_adc_init(void){

	
	if(Analog.resolution == 10){
		OSWARRIOR_ADC_RES_10;						//Configure ADC
		Analog.resolution = 10;
	}else{
		OSWARRIOR_ADC_RES_8;						//Configure ADC
		Analog.resolution = 8;
	}

	OSWARRIOR_ADC_INIT;
}

/*
** ===================================================================
**     Function : ADC.setResolution
**     Handler  : _OSWarrior_adc_setResolution
**
**     Description :
**         Change the resolution of the analog inputs, as default the
**         analog inputs has a resolution of 8 bits. 
**     
**     Parameters  : 
**         resolution : analog inputs resolution expressed in bits
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_adc_setResolution(T_UBYTE resolution){
	if(resolution != Analog.resolution){
		if(resolution == 8){
			OSWARRIOR_ADC_RES_8;		//8-Bit Res - Low Power
			Analog.resolution = 8;
		}else if(resolution == 10){
				OSWARRIOR_ADC_RES_10;	//10-Bit Res - Low Power
				Analog.resolution = 10;
		}
	}
}

/*
** ===================================================================
**     Function : ADC.read
**     Handler  : _OSWarrior_adc_read
**
**     Description :
**         Reads the value of the specified analog pin. 
**     
**     Parameters  : 
**         channel : Analog channel to be read
**     
**     Returns     : Analog channel value, this value depends of the
**     				 analog module resolution
** ===================================================================
*/

int _OSWarrior_adc_read(int channel){
	switch(channel){
		#if (0 < MAX_ANALOG_PINS)
			case_adcRead(0);
		#endif
		#if (1 < MAX_ANALOG_PINS)
			case_adcRead(1);
		#endif
		#if (2 < MAX_ANALOG_PINS)
			case_adcRead(2);
		#endif
		#if (3 < MAX_ANALOG_PINS)
			case_adcRead(3);
		#endif
		#if (4 < MAX_ANALOG_PINS)
			case_adcRead(4);
		#endif
		#if (5 < MAX_ANALOG_PINS)
			case_adcRead(5);
		#endif
		#if (6 < MAX_ANALOG_PINS)
			case_adcRead(6);
		#endif
		#if (7 < MAX_ANALOG_PINS)
			case_adcRead(7);
		#endif
	}
	
	while(ADC_COCO != 1);
	return ADC_VALUE;
}

/*
** ===================================================================
**     Function : ADC.enable
**     Handler  : _OSWarrior_adc_enable
**
**     Description :
**         Enable a digital pin on the analog port to behave as
**         analog pin. 
**     
**     Parameters  : 
**         channel : Analog channel to be enabled
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_adc_enable(int channel){
	switch(channel){
		#if (0 < MAX_ANALOG_PINS)
			case_adcEnable(0);
		#endif
		#if (1 < MAX_ANALOG_PINS)
			case_adcEnable(1);
		#endif
		#if (2 < MAX_ANALOG_PINS)
			case_adcEnable(2);
		#endif
		#if (3 < MAX_ANALOG_PINS)
			case_adcEnable(3);
		#endif
		#if (4 < MAX_ANALOG_PINS)
			case_adcEnable(4);
		#endif
		#if (5 < MAX_ANALOG_PINS)
			case_adcEnable(5);
		#endif
		#if (6 < MAX_ANALOG_PINS)
			case_adcEnable(6);
		#endif
		#if (7 < MAX_ANALOG_PINS)
			case_adcEnable(7);
		#endif
	}
}

/*
** ===================================================================
**     Function : ADC.disable
**     Handler  : _OSWarrior_adc_disable
**
**     Description :
**         Disable an analog pin, the this pin can be used as a
**         general purpose pin.
**     
**     Parameters  : 
**         channel : Analog channel to be disabled
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_adc_disable(int channel){
	switch(channel){
		#if (0 < MAX_ANALOG_PINS)
			case_adcDisable(0);
		#endif
		#if (1 < MAX_ANALOG_PINS)
			case_adcDisable(1);
		#endif
		#if (2 < MAX_ANALOG_PINS)
			case_adcDisable(2);
		#endif
		#if (3 < MAX_ANALOG_PINS)
			case_adcDisable(3);
		#endif
		#if (4 < MAX_ANALOG_PINS)
			case_adcDisable(4);
		#endif
		#if (5 < MAX_ANALOG_PINS)
			case_adcDisable(5);
		#endif
		#if (6 < MAX_ANALOG_PINS)
			case_adcDisable(6);
		#endif
		#if (7 < MAX_ANALOG_PINS)
			case_adcDisable(7);
		#endif
	}
}
