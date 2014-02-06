/*
** 	Filename: Motor_Shield.h
** 	Description: Library for the OSWarrior Mini Motor Shield
**
**	Author: Isaac Ávila (isaac.avila.gut@gmail.com)
** 	Current Version: 1.0
** 	Status: Development
**
**	CHANGE LOG:
**	Date: 10/09/2013 - Library created
**	
** 	LICENSE:
** 	This library is free software; you can redistribute it and/or
** 	modify it under the terms of the Attribution-ShareAlike
** 	License as published by the Creative Commons Organization; either
** 	version 3.0 of the License, or (at your option) any later version.
** 	This library is distributed in the hope that it will be useful,
** 	but WITHOUT ANY WARRANTY; without even the implied warranty of
** 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
** 	See the Attribution-ShareAlike License for more details.
** 	You should have received a copy of the Creative Commons Attribution-ShareAlike 
** 	License along with this library; if not send a email to the library author.
*/

#ifndef OSWARRIOR_MOTORSHIELD_H_
	#define OSWARRIOR_MOTORSHIELD_H_

	#define MOTOR_SHIELD_DIR_A		15
	#define MOTOR_SHIELD_DIR_B		12

	#define MOTOR_SHIELD_BRAKE_A	14
	#define MOTOR_SHIELD_BRAKE_B	13

	#define MOTOR_SHIELD_PWM_A		PWM4
	#define MOTOR_SHIELD_PWM_B		PWM5

	#define MOTOR_SHIELD_SENSE_A	A0
	#define MOTOR_SHIELD_SENSE_B	A1

	/*
	** ===================================================================
	** Function prototypes	
	** ===================================================================
	*/

	extern void _motor_shield_enable(E_DIRECTION motor_side);	
	extern void _motor_shield_disable(E_DIRECTION motor_side);	
	extern void _motor_shield_run(E_DIRECTION motor_side, E_DIRECTION motor_direction);
	extern void _motor_shield_stop(E_DIRECTION motor_side);
	extern void _motor_shield_setSpeed(E_DIRECTION motor_side, T_UBYTE motor_speed);
	
	extern void _motor_shield_motors_enable(void);	
	extern void _motor_shield_motors_disable(void);	
	extern void _motor_shield_motors_forward(void);	
	extern void _motor_shield_motors_backward(void);	
	extern void _motor_shield_motors_left(void);	
	extern void _motor_shield_motors_right(void);	
	extern void _motor_shield_motors_stop(void);	
	extern void _motor_shield_motors_speed(T_UBYTE motors_speed);	

	
	/*
	** ===================================================================
	** Motor Shield Structure Definition
	** ===================================================================
	*/
	
	typedef struct{
		void (*enable)(E_DIRECTION motor_side);	
		void (*disable)(E_DIRECTION motor_side);		
		void (*run)(E_DIRECTION motor_side, E_DIRECTION motor_direction);
		void (*stop)(E_DIRECTION motor_side);
		void (*setSpeed)(E_DIRECTION motor_side, T_UBYTE motor_speed);
	}MOTORSTR;	
	
	extern MOTORSTR Motor;
	
	typedef struct{
		void (*enable)(void);	
		void (*disable)(void);	
		void (*forward)(void);	
		void (*backward)(void);		
		void (*left)(void);
		void (*right)(void);
		void (*stop)(void);
		void (*speed)(T_UBYTE motors_speed);	
	}MOTORSSTR;	
	
	extern MOTORSSTR Motors;
	
#endif
