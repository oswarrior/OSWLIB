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
#include "oswlib/PWM/pwm.h"

/*
** ===================================================================
** PWM Macros
** ===================================================================
*/

#define case_pwmAdd(_channel)				\
	case _channel:							\
		PWM##_channel##_SC 	= 0x28U; 		\
		PWM##_channel##_V 	= PWM_DC_0;		\
		TPM##_channel##_MOD = PWM_PERIOD;	\
		TPM##_channel##_SC 	= 0x0AU;		\
	break;

#define case_pwmChangeFreq(_channel)				\
	case _channel:									\
		PWM##_channel##_V 	= (new_pwm_period / 2);	\
		TPM##_channel##_MOD = new_pwm_period;		\
	break;
	
#define macro_pwmRemove(_channel)		\
	PWM##_channel##_SC 	&= 0xF0U;
	
/*
** ===================================================================
** PWM Structure definition
** ===================================================================
*/

S_PWMSTR PWM = {
	{0,0,0,0,0,0,0,0},
	PWM_enable,
	PWM_disable,
	PWM_changeFrequency,
	PWM_dutycycle,
	PWM_read_dc
};	

/*
** ===================================================================
**     Function : PWM.readDutyCycle
**     Handler  : PWM_read_dc
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

int PWM_read_dc (int pin)
{
	return PWM.channel_dc[pin];
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

void PWM_enable(int pin)
{ 
	switch(pin)
	{
		#if ( 0 < MAX_PWM_CHANNELS)	
			case_pwmAdd(0);	
		#endif
		#if ( 1 < MAX_PWM_CHANNELS)	
			case_pwmAdd(1);	
		#endif
		#if ( 2 < MAX_PWM_CHANNELS)	
			case_pwmAdd(2);	
		#endif
		#if ( 3 < MAX_PWM_CHANNELS)	
			case_pwmAdd(3);	
		#endif
		#if ( 4 < MAX_PWM_CHANNELS)	
			case_pwmAdd(4);	
		#endif
		#if ( 5 < MAX_PWM_CHANNELS)	
			case_pwmAdd(5);	
		#endif
		#if ( 6 < MAX_PWM_CHANNELS)	
			case_pwmAdd(6);	
		#endif
		#if ( 7 < MAX_PWM_CHANNELS)	
			case_pwmAdd(7);	
		#endif
		#if ( 8 < MAX_PWM_CHANNELS)	
			case_pwmAdd(8);	
		#endif
		#if ( 9 < MAX_PWM_CHANNELS)	
			case_pwmAdd(9);	
		#endif
		#if ( 10 < MAX_PWM_CHANNELS)	
			case_pwmAdd(10);	
		#endif
		#if ( 11 < MAX_PWM_CHANNELS)	
			case_pwmAdd(11);	
		#endif
		#if ( 12 < MAX_PWM_CHANNELS)	
			case_pwmAdd(12);	
		#endif
		#if ( 13 < MAX_PWM_CHANNELS)	
			case_pwmAdd(13);	
		#endif
		#if ( 14 < MAX_PWM_CHANNELS)	
			case_pwmAdd(14);	
		#endif
		#if ( 15 < MAX_PWM_CHANNELS)	
			case_pwmAdd(15);	
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

void PWM_disable(int pin)
{
	#if ( 0 < MAX_PWM_CHANNELS)		 	 
		if(pin == 0) { macro_pwmRemove(0); } 
	#endif
	#if ( 1 < MAX_PWM_CHANNELS)		
		else if(pin == 1) { macro_pwmRemove(1); }
	#endif
	#if ( 2 < MAX_PWM_CHANNELS)		
		else if(pin == 2) { macro_pwmRemove(2); } 
	#endif
	#if ( 3 < MAX_PWM_CHANNELS)		
		else if(pin == 3) { macro_pwmRemove(3); }
	#endif
	#if ( 4 < MAX_PWM_CHANNELS)		
		else if(pin == 4) { macro_pwmRemove(4); } 
	#endif
	#if ( 5 < MAX_PWM_CHANNELS)		
		else if(pin == 5) { macro_pwmRemove(5); } 
	#endif
	#if ( 6 < MAX_PWM_CHANNELS)	
		else if(pin == 6) { macro_pwmRemove(6); } 
	#endif
	#if ( 7 < MAX_PWM_CHANNELS)		
		else if(pin == 7) { macro_pwmRemove(7); } 
	#endif
	#if ( 8 < MAX_PWM_CHANNELS)		
		else if(pin == 8) { macro_pwmRemove(8); } 
	#endif
	#if ( 9 < MAX_PWM_CHANNELS)		
		else if(pin == 9) { macro_pwmRemove(9); } 
	#endif
	#if ( 10 < MAX_PWM_CHANNELS)	
		else if(pin == 10) { macro_pwmRemove(10); } 
	#endif
	#if ( 11 < MAX_PWM_CHANNELS)	
		else if(pin == 11) { macro_pwmRemove(11); } 
	#endif
	#if ( 12 < MAX_PWM_CHANNELS)	
		else if(pin == 12) { macro_pwmRemove(12); } 
	#endif
	#if ( 13 < MAX_PWM_CHANNELS)	
		else if(pin == 13) { macro_pwmRemove(13); } 
	#endif
	#if ( 14 < MAX_PWM_CHANNELS)	
		else if(pin == 14) { macro_pwmRemove(14); } 
	#endif
	#if ( 15 < MAX_PWM_CHANNELS)	
		else if(pin == 15) { macro_pwmRemove(15); }
	#endif
}

/*
** ===================================================================
**     Function : PWM.dutyCycle
**     Handler  : PWM_dutycycle
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

void PWM_dutycycle (int pin, int duty_cycle)
{
	int pwm_dc;
	
	PWM.channel_dc[pin] = duty_cycle;
	#if ( 0 < MAX_PWM_CHANNELS)		 	 
		if(pin == 0)		pwm_dc = (int)((TPM0_MOD / 100) * duty_cycle);
	#endif
	#if ( 1 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 1)	pwm_dc = (int)((TPM1_MOD / 100) * duty_cycle);
	#endif
	#if ( 2 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 2)	pwm_dc = (int)((TPM2_MOD / 100) * duty_cycle);
	#endif
	#if ( 3 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 3)	pwm_dc = (int)((TPM3_MOD / 100) * duty_cycle);
	#endif
	#if ( 4 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 4)	pwm_dc = (int)((TPM4_MOD / 100) * duty_cycle);
	#endif
	#if ( 5 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 5)	pwm_dc = (int)((TPM5_MOD / 100) * duty_cycle);
	#endif
	#if ( 6 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 6)	pwm_dc = (int)((TPM6_MOD / 100) * duty_cycle);
	#endif
	#if ( 7 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 7)	pwm_dc = (int)((TPM7_MOD / 100) * duty_cycle);
	#endif
	#if ( 8 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 8)	pwm_dc = (int)((TPM8_MOD / 100) * duty_cycle);
	#endif
	#if ( 9 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 9)	pwm_dc = (int)((TPM9_MOD / 100) * duty_cycle);
	#endif
	#if ( 10 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 10)	pwm_dc = (int)((TPM10_MOD / 100) * duty_cycle);
	#endif
	#if ( 11 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 11)	pwm_dc = (int)((TPM11_MOD / 100) * duty_cycle);
	#endif
	#if ( 12 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 12)	pwm_dc = (int)((TPM12_MOD / 100) * duty_cycle);
	#endif
	#if ( 13 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 13)	pwm_dc = (int)((TPM13_MOD / 100) * duty_cycle);
	#endif
	#if ( 14 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 14)	pwm_dc = (int)((TPM14_MOD / 100) * duty_cycle);
	#endif
	#if ( 15 < MAX_PWM_CHANNELS)		 	 
		else if(pin == 15)	pwm_dc = (int)((TPM15_MOD / 100) * duty_cycle);
	#endif

	PWM_setPosition(pin, pwm_dc);
}

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

void PWM_setPosition(int pin, int value)
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

void PWM_changeFrequency (int pin, int frequency)
{
	int new_pwm_period = (int)(BUSCLOCK/(frequency*PWM_PS));
	
	switch(pin)
	{
		#if ( 0 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(0);	
		#endif
		#if ( 1 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(1);	
		#endif
		#if ( 2 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(2);	
		#endif
		#if ( 3 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(3);	
		#endif
		#if ( 4 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(4);	
		#endif
		#if ( 5 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(5);	
		#endif
		#if ( 6 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(6);	
		#endif
		#if ( 7 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(7);	
		#endif
		#if ( 8 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(8);	
		#endif
		#if ( 9 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(9);	
		#endif
		#if ( 10 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(10);	
		#endif
		#if ( 11 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(11);	
		#endif
		#if ( 12 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(12);	
		#endif
		#if ( 13 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(13);	
		#endif
		#if ( 14 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(14);	
		#endif
		#if ( 15 < MAX_PWM_CHANNELS)	
			case_pwmChangeFreq(15);	
		#endif
	}
}
