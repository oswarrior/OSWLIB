#include "oswlib/settings.h"
#include "oswlib/Sensors/HC-SR04.h"

 HCSR04STR HCSR04 = {
	0,
	0,
	HCSR04_enable, 		  
	HCSR04_read_cm,
	HCSR04_read_cm_float,
	HCSR04_read_inches,
	HCSR04_read_inches_float
};

/*
** ===================================================================
** HC-SR04 Sensor Functions Declarations
** ===================================================================
*/

void HCSR04_enable(int trig, int echo)
{
	HCSR04.ECHO = echo;
	HCSR04.TRIG = trig;
	pinMode(HCSR04.ECHO, INPUT);
	pinMode(HCSR04.TRIG, OUTPUT);
}

T_ULONG HCSR04_read(void)
{	
	T_ULONG timeout = 50000;
	
	/* Send trigger */
	digitalWrite(HCSR04.TRIG,1);
	delayMicroseconds(10);
	digitalWrite(HCSR04.TRIG,0);
	
	return pulseIn(HCSR04.ECHO, HIGH, timeout);		
}

T_ULONG HCSR04_read_cm(void)
{	
	return HCSR04_read() / 58;		
}

T_FLOAT HCSR04_read_cm_float(void)
{	
	return HCSR04_read() * 0.01724;		
}

T_ULONG HCSR04_read_inches(void)
{	
	return HCSR04_read() / 148;		
}

T_FLOAT HCSR04_read_inches_float(void)
{	
	return HCSR04_read() * 0.00675;		
}


