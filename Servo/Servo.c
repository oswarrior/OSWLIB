/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 pwm.h
** 	Description: OSWarrior Pulse Width Modulation (PWM) library
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
** PWM includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/Servo/Servo.h"

/*
** ===================================================================
** PWM Macros
** ===================================================================
*/

#define case_servoAdd(_channel)				\
	case _channel:							\
		PWM##_channel##_SC 	= 0x28U; 		\
		PWM##_channel##_V 	= SERVO_0;		\
		TPM##_channel##_MOD = SERVO_PERIOD;	\
		TPM##_channel##_SC 	= 0x0CU;		\
	break;
	
#define macro_servoRemove(_channel)		\
	PWM##_channel##_SC 	&= 0xF0U;

/*
** ===================================================================
** Servomotor Structure definition
** ===================================================================
*/

S_SERVOSTR Servo = {
	{0,0,0,0,0,0,0,0},
	Servo_enable, 
	Servo_disable,
	Servo_degrees,
	Servo_read_pos
};

/*
** ===================================================================
**     Function : Servo.readPosition
**     Handler  : PWM_read_pos
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

int Servo_read_pos (int pin)
{
	return Servo.channel_pos[pin];
}

/*
** ===================================================================
**     Function : PWM.enable, Servo.enable
**     Handler  : PWM_enable
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

void Servo_enable(int pin)
{ 
	switch(pin)
	{
		#if ( 0 < MAX_PWM_CHANNELS)	
			case_servoAdd(0);	
		#endif
		#if ( 1 < MAX_PWM_CHANNELS)	
			case_servoAdd(1);	
		#endif
		#if ( 2 < MAX_PWM_CHANNELS)	
			case_servoAdd(2);	
		#endif
		#if ( 3 < MAX_PWM_CHANNELS)	
			case_servoAdd(3);	
		#endif
		#if ( 4 < MAX_PWM_CHANNELS)	
			case_servoAdd(4);	
		#endif
		#if ( 5 < MAX_PWM_CHANNELS)	
			case_servoAdd(5);	
		#endif
		#if ( 6 < MAX_PWM_CHANNELS)	
			case_servoAdd(6);	
		#endif
		#if ( 7 < MAX_PWM_CHANNELS)	
			case_servoAdd(7);	
		#endif
		#if ( 8 < MAX_PWM_CHANNELS)	
			case_servoAdd(8);	
		#endif
		#if ( 9 < MAX_PWM_CHANNELS)	
			case_servoAdd(9);	
		#endif
		#if ( 10 < MAX_PWM_CHANNELS)	
			case_servoAdd(10);	
		#endif
		#if ( 11 < MAX_PWM_CHANNELS)	
			case_servoAdd(11);	
		#endif
		#if ( 12 < MAX_PWM_CHANNELS)	
			case_servoAdd(12);	
		#endif
		#if ( 13 < MAX_PWM_CHANNELS)	
			case_servoAdd(13);	
		#endif
		#if ( 14 < MAX_PWM_CHANNELS)	
			case_servoAdd(14);	
		#endif
		#if ( 15 < MAX_PWM_CHANNELS)	
			case_servoAdd(15);	
		#endif
	}
}

/*
** ===================================================================
**     Function : PWM.disable, Servo.disable
**     Handler  : PWM_disable
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

void Servo_disable(int pin)
{
	#if ( 0 < MAX_PWM_CHANNELS)		 	 
		if(pin == 0) { macro_servoRemove(0); } 
	#endif
	#if ( 1 < MAX_PWM_CHANNELS)		
		else if(pin == 1) { macro_servoRemove(1); }
	#endif
	#if ( 2 < MAX_PWM_CHANNELS)		
		else if(pin == 2) { macro_servoRemove(2); } 
	#endif
	#if ( 3 < MAX_PWM_CHANNELS)		
		else if(pin == 3) { macro_servoRemove(3); }
	#endif
	#if ( 4 < MAX_PWM_CHANNELS)		
		else if(pin == 4) { macro_servoRemove(4); } 
	#endif
	#if ( 5 < MAX_PWM_CHANNELS)		
		else if(pin == 5) { macro_servoRemove(5); } 
	#endif
	#if ( 6 < MAX_PWM_CHANNELS)	
		else if(pin == 6) { macro_servoRemove(6); } 
	#endif
	#if ( 7 < MAX_PWM_CHANNELS)		
		else if(pin == 7) { macro_servoRemove(7); } 
	#endif
	#if ( 8 < MAX_PWM_CHANNELS)		
		else if(pin == 8) { macro_servoRemove(8); } 
	#endif
	#if ( 9 < MAX_PWM_CHANNELS)		
		else if(pin == 9) { macro_servoRemove(9); } 
	#endif
	#if ( 10 < MAX_PWM_CHANNELS)	
		else if(pin == 10) { macro_servoRemove(10); } 
	#endif
	#if ( 11 < MAX_PWM_CHANNELS)	
		else if(pin == 11) { macro_servoRemove(11); } 
	#endif
	#if ( 12 < MAX_PWM_CHANNELS)	
		else if(pin == 12) { macro_servoRemove(12); } 
	#endif
	#if ( 13 < MAX_PWM_CHANNELS)	
		else if(pin == 13) { macro_servoRemove(13); } 
	#endif
	#if ( 14 < MAX_PWM_CHANNELS)	
		else if(pin == 14) { macro_servoRemove(14); } 
	#endif
	#if ( 15 < MAX_PWM_CHANNELS)	
		else if(pin == 15) { macro_servoRemove(15); }
	#endif
}

/*
** ===================================================================
**     Function : Servo.setDegrees
**     Handler  : PWM_degrees
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

void Servo_degrees(int pin, int deg)
{
	if(deg >= 180) deg = 180;
	if(deg <= 0) deg = 0;
	Servo.channel_pos[pin] = deg;
	Servo_setPosition(pin, (int)(SERVO_0 + ( SERVO_MAX_STEPS / 180 ) * deg));
};

/*
** ===================================================================
**     Function : PWM_setPosition
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

void Servo_setPosition(int pin, int value)
{	
	if(pin == 0)		PWM0_V = (int)value;
	else if(pin == 1)	PWM1_V = (int)value;
	else if(pin == 2)	PWM2_V = (int)value;
	else if(pin == 3)	PWM3_V = (int)value;
	else if(pin == 4)	PWM4_V = (int)value;
	else if(pin == 5)	PWM5_V = (int)value;
	else if(pin == 6)	PWM6_V = (int)value;
	else if(pin == 7)	PWM7_V = (int)value;
}
