/*
** 	Filename: Motor_Shield.h
** 	Description: Library for the OSWarrior Mini Motor Shield
**
**	Author: Isaac Ávila (isaac.avila.gut@gmail.com)
** 	Current Version: 1.0
** 	Status: Development
**
**	CHANGE LOG:
**	Date: 18/09/2013 - Library created
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

#include "oswlib/settings.h"
#include "oswlib/PWM/pwm.h"
#include "oswlib/Analog/analog.h"
#include "oswlib/Shields/Motor_Shield/Motor_Shield.h"

MOTORSTR Motor = {
	_motor_shield_enable,
	_motor_shield_disable,
	_motor_shield_run,
	_motor_shield_stop,
	_motor_shield_setSpeed
};

MOTORSSTR Motors = {
	_motor_shield_motors_enable,
	_motor_shield_motors_disable,
	_motor_shield_motors_forward,
	_motor_shield_motors_backward,
	_motor_shield_motors_left,
	_motor_shield_motors_right,
	_motor_shield_motors_stop,
	_motor_shield_motors_speed
};

void _motor_shield_enable(E_DIRECTION motor_side){
	if(motor_side == LEFT){
		
		pinDirection(MOTOR_SHIELD_DIR_A, OUTPUT);
		pinDirection(MOTOR_SHIELD_BRAKE_A, OUTPUT);
		
		PWM.enable(MOTOR_SHIELD_PWM_A);
		PWM.dutyCycle(MOTOR_SHIELD_PWM_A, 100);
		
		Motor.stop(motor_side);
		
	}else if(motor_side == RIGHT){
		
		pinDirection(MOTOR_SHIELD_DIR_B, OUTPUT);
		pinDirection(MOTOR_SHIELD_BRAKE_B, OUTPUT);
		
		PWM.enable(MOTOR_SHIELD_PWM_B);
		PWM.dutyCycle(MOTOR_SHIELD_PWM_B, 100);
		
		Motor.stop(motor_side);
		
	}
}

void _motor_shield_disable(E_DIRECTION motor_side){
	if(motor_side == LEFT){
		
		pinDirection(MOTOR_SHIELD_DIR_A, INPUT);
		pinDirection(MOTOR_SHIELD_BRAKE_A, INPUT);
		
		PWM.disable(MOTOR_SHIELD_PWM_A);
				
	}else if(motor_side == RIGHT){
		
		pinDirection(MOTOR_SHIELD_DIR_B, INPUT);
		pinDirection(MOTOR_SHIELD_BRAKE_B, INPUT);
		
		PWM.disable(MOTOR_SHIELD_PWM_B);
		
	}	
}

void _motor_shield_run(E_DIRECTION motor_side, E_DIRECTION motor_direction){
	if(motor_side == LEFT){
		writePin(MOTOR_SHIELD_BRAKE_A, OFF);
		if(motor_direction == FORWARD){
				writePin(MOTOR_SHIELD_DIR_A, ON);
		}else if(motor_direction == BACKWARD){
				writePin(MOTOR_SHIELD_DIR_A, OFF);		
		}
	}else if(motor_side == RIGHT){
		writePin(MOTOR_SHIELD_BRAKE_B, OFF);	
		if(motor_direction == FORWARD){
				writePin(MOTOR_SHIELD_DIR_B, ON);
		}else if(motor_direction == BACKWARD){
				writePin(MOTOR_SHIELD_DIR_B, OFF);		
		}
	}	
}

void _motor_shield_stop(E_DIRECTION motor_side){
	if(motor_side == LEFT){
		writePin(MOTOR_SHIELD_BRAKE_A, ON);
	}else if(motor_side == RIGHT){
		writePin(MOTOR_SHIELD_BRAKE_B, ON);	
	}	
}

void _motor_shield_setSpeed(E_DIRECTION motor_side, T_UBYTE motor_speed){
	if(motor_side == LEFT){
		PWM.dutyCycle(MOTOR_SHIELD_PWM_A, motor_speed);
	}else if(motor_side == RIGHT){
		PWM.dutyCycle(MOTOR_SHIELD_PWM_B, motor_speed);
	}		
}

void _motor_shield_motors_enable(void){
	_motor_shield_enable(LEFT);	
	_motor_shield_enable(RIGHT);
}

void _motor_shield_motors_disable(void){
	_motor_shield_disable(LEFT);
	_motor_shield_disable(RIGHT);
}

void _motor_shield_motors_forward(void){
	_motor_shield_run(LEFT,BACKWARD);
	_motor_shield_run(RIGHT,FORWARD);
}

void _motor_shield_motors_backward(void){
	_motor_shield_run(LEFT,FORWARD);
	_motor_shield_run(RIGHT,BACKWARD);	
}

void _motor_shield_motors_left(void){
	_motor_shield_run(LEFT,BACKWARD);
	_motor_shield_run(RIGHT,BACKWARD);		
}

void _motor_shield_motors_right(void){
	_motor_shield_run(LEFT,FORWARD);
	_motor_shield_run(RIGHT,FORWARD);		
}

void _motor_shield_motors_stop(void){
	_motor_shield_stop(LEFT);
	_motor_shield_stop(RIGHT);
}

void _motor_shield_motors_speed(T_UBYTE motors_speed){
	_motor_shield_setSpeed(LEFT, motors_speed);
	_motor_shield_setSpeed(RIGHT, motors_speed);
}
