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

#ifndef OSWARRIOR_SERVO_H_
	
	#define OSWARRIOR_SERVO_H_

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

	#define SERVO_FREQ			50									//50Hz
	#define SERVO_PS			16									//Bus Clock Prescale factor
	#define SERVO_PERIOD 		(BUSCLOCK/(SERVO_FREQ*SERVO_PS))	//20mS Period	

	#define SERVO_0				( 6 * (SERVO_PERIOD /200))	//0.10 mS *  6 = 0.06 mS Ton --> Servomotor 0º
	#define SERVO_180			(24 * (SERVO_PERIOD /200))	//0.10 mS * 24 = 2.40 mS Ton --> Servomotor 180º
	#define SERVO_MAX_STEPS		(SERVO_180 - SERVO_0)		
	
	/*
	** ===================================================================
	** PWM type definitions
	** ===================================================================
	*/

	typedef struct{	
		int channel_pos[MAX_PWM_CHANNELS];				/*** Servo - Read position array 	***/
		void (*enable)(int pin);						/*** Servo - Enable Channel 		***/
		void (*disable)(int pin);						/*** Servo - Enable Channel 		***/
		void (*setDegrees)(int pin, int deg);			/*** Servo - Set Degrees position 	***/
		int (*readPosition)(int pin);					/*** Servo - Read position 			***/
	}S_SERVOSTR;

	/*
	** ===================================================================
    ** Servomotor functions prototypes
	** ===================================================================
	*/
	
	PUBLIC_FCT void Servo_enable (int pin);
	PUBLIC_FCT void Servo_disable(int pin);
	
	PUBLIC_FCT void Servo_degrees (int pin, int deg);
	PUBLIC_FCT void Servo_setPosition(int pin, int pwm_position);
	PUBLIC_FCT int  Servo_read_pos (int pin);
		
	/*
	** ===================================================================
    ** Analog Structure declaration
	** ===================================================================
	*/
	
	PUBLIC_DATA S_SERVOSTR 	Servo;
	
#endif /* OSWARRIORMICRO_DELAY_H_ */
