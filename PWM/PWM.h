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

#ifndef OSWARRIOR_PWM_H_
	
	#define OSWARRIOR_PWM_H_

	/*
	** ===================================================================
	** PWM constants
	** ===================================================================
	*/

	/* 
	**	  OVERFLOW                 COMPARE  OVERFLOW        COMPARE
	**	     |                        |        |               |
	**       |                        |        |               |
	**      
	**	     <-------- 75% D.C. ------>        <--- 50% D.C. -->
	**	     __________________________        _________________                 _________
	**	     |                        |        |               |                 |              
	**	_____|                        |________|               |_________________|    
	**
	**	     <--------   TON    ------><-TOFF-><----- TON -----><----- TOFF ----->
	**	     
	**       <------------ PERIOD ------------> <------------ PERIOD ----------->
	*/

	/*
	**	Period =  ( Modulo  / ( BUSFREQ  / PRESCALER ) )
	**	Modulo =  ( Period  * ( BUSFREQ  / PRESCALER ) )
	**	Modulo =  ( BUSFREQ / ( PWM_FREQ * PRESCALER ) )
	**	
	*/

	#define PWM_FREQ			500								//50Hz
	#define PWM_PS				4								//Bus Clock Prescale factor
	#define PWM_PERIOD 			(BUSCLOCK/(PWM_FREQ*PWM_PS))	//20mS Period	
	
	#define PWM_DC_0			0				//D.C.   0%
	#define PWM_DC_50			PWM_PERIOD/2	//D.C.  50%
	#define PWM_DC_100			PWM_PERIOD		//D.C. 100%
	#define PWM_MAX_STEPS		PWM_PERIOD		
	
	/*
	** ===================================================================
	** PWM type definitions
	** ===================================================================
	*/

	typedef struct{
		int channel_dc[MAX_PWM_CHANNELS];				/*** PWM - Read duty cycle array ***/
		void (*enable)(int pin);						/*** PWM - Enable Channel 		 ***/
		void (*disable)(int pin);						/*** PWM - Enable Channel 		 ***/
		
		void (*freq)(int pin, int frequency);			/*** PWM - Enable Channel 		 ***/
		void (*dutyCycle)(int pin, int duty_cycle);		/*** PWM - Channel Duty Cycle 	 ***/
		
		int (*readDutyCycle)(int pin);					/*** PWM - Read duty cycle 		 ***/
	}S_PWMSTR;

	/*
	** ===================================================================
    ** PWM functions prototypes
	** ===================================================================
	*/
	
	PUBLIC_FCT void PWM_enable (int pin);
	PUBLIC_FCT void PWM_disable (int pin);

	PUBLIC_FCT void PWM_changeFrequency (int pin, int frequency);
	PUBLIC_FCT void PWM_dutycycle (int pin, int duty_cycle);
	
	PUBLIC_FCT int  PWM_read_dc (int pin);
	PUBLIC_FCT void PWM_setPosition (int pin, int value);

			
	/*
	** ===================================================================
    ** PWM Structure declaration
	** ===================================================================
	*/
	
	PUBLIC_DATA S_PWMSTR PWM;
	
#endif /* OSWARRIORMICRO_DELAY_H_ */
