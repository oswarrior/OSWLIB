/*
** ===================================================================
** Pin includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/OSWarrior/pin.h"
	
T_ULONG pulseIn(int pin, E_LEVEL state, T_ULONG timeout)
{
	T_ULONG initial_time;
	T_ULONG final_time;
	T_ULONG limit;
	T_BOOLEAN to_flag = FALSE;
	
	initial_time = micros();
	limit = initial_time + timeout;
		
	while(digitalRead(pin) == !state)
	{
		if(micros() > limit)
		{
			to_flag = TRUE;
		}
	}
	
	initial_time = micros();
	limit = initial_time + timeout;
	
	while(digitalRead(pin) == state && !to_flag )
	{
		if(micros() > limit)
		{
			to_flag = TRUE;
		}
	}
	
	if(to_flag)
	{
		final_time = initial_time;
	}
	else
	{
		final_time = micros();
	}
	
	return (final_time - initial_time);	
}
