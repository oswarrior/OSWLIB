/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 analog.h
**  Description: OSWarrior Analog library functions declarations
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Development
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Version 2.0 freeze (Integrated)
**	Date: 02/05/2013 - Several bus fixed
**	Date: 02/05/2013 - Version 2.1 freeze (Tested)
**	Date: 08/05/2013 - Updated structure name to "Analog"
**	Date: 22/05/2013 - Deleted Set Mode function
**	Date: 22/06/2013 - Function descriptions added
**	Date: 22/06/2013 - Version 3.0 freeze (Tested)
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

#ifndef OSWARRIOR_ANALOG_H_
	
	#define OSWARRIOR_ANALOG_H_

	/*
	** ===================================================================
	** Analog type definitions
	** ===================================================================
	*/

	typedef struct{
		T_UBYTE resolution;					/*** Analog - Default Resolution ***/
		void (*init)(void);							/*** Analog - Initialization function ***/
		void (*setResolution)(T_UBYTE resolution);		/*** Analog - Set Resolution Function ***/
		void (*enable)(int channel);				/*** Analog - Read Function ***/
		void (*disable)(int channel);				/*** Analog - Read Function ***/
		int (*read)(int channel);					/*** Analog - Read Function ***/
	}S_ADCSTR;
	
	/*
	** ===================================================================
    ** Analog functions prototypes
	** ===================================================================
	*/
	
	PUBLIC_FCT void _OSWarrior_adc_init(void);
	PUBLIC_FCT void _OSWarrior_adc_setResolution(T_UBYTE resolution);
	PUBLIC_FCT void _OSWarrior_adc_enable(int channel);
	PUBLIC_FCT void _OSWarrior_adc_disable(int channel);
	PUBLIC_FCT int  _OSWarrior_adc_read(int channel);
	
	/*
	** ===================================================================
    ** Analog Structure declaration
	** ===================================================================
	*/
	
	PUBLIC_DATA S_ADCSTR Analog;

#endif
