/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 pwm.h
** 	Description: OSWarrior Pulse Width Modulation (PWM) library
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
*	Date: 27/03/2013 - Version 2.0 freeze (Integrated)
*	Date: 28/03/2013 - Status control registers bug fixed.
*	Date: 01/05/2012 - Constants recalculated.
*	Date: 02/05/2013 - Version 2.1 freeze (Tested)
*	Date: 08/05/2013 - Separated structures for PWM and Servomotors
*	Date: 31/05/2013 - Servomotor times calibrated for 4MHz Bus clock
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

#ifndef OSWARRIOR_RGB_H_
	
	#define OSWARRIOR_RGB_H_

	/*
	** ===================================================================
	** RGB type definitions
	** ===================================================================
	*/
	
	typedef struct{
		int channel_red;														/*** RGB - Red Channel 		***/
		int channel_green;														/*** RGB - Green Channel 	***/
		int channel_blue;														/*** RGB - Blue Channel 	***/
		void (*enable)(int channel_red,int channel_green,int channel_blue);		/*** RGB - Enable Channel 	***/
		void (*disable)(void);													/*** RGB - Disable Channel 	***/
		void (*setColor)(int red,int green,int blue);							/*** RGB - Set RGB Colour 	***/
	}S_RGBSTR;	

	/*
	** ===================================================================
    ** RGB functions prototypes
	** ===================================================================
	*/
	
	PUBLIC_FCT void RGB_enable(int channel_red,int channel_green,int channel_blue);
	PUBLIC_FCT void RGB_disable(void);
	PUBLIC_FCT void RGB_setColor(int red,int green,int blue);
			
	/*
	** ===================================================================
    ** Analog Structure declaration
	** ===================================================================
	*/
	
	PUBLIC_DATA S_RGBSTR 	RGB;
	
#endif /* OSWARRIORMICRO_DELAY_H_ */
