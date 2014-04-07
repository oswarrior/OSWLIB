
#include "oswlib/settings.h"
#include "oswlib/OSWarrior/delay.h"		//Delay control

/*
** ===================================================================
** Delay variables declarations
** ===================================================================
*/

static volatile T_ULONG _OSWarrior_msCounter = 0;

/*
** ===================================================================
** Delay interrupt function handler declarations
** ===================================================================
*/

void ( * _OSWarrior_tickISR_handler )(void) = _OSWarrior_Dummy_Fnc;

/*
** ===================================================================
**     Function : oswarrior_enableDelays
**
**     Description :
**         This function is a dummy, only for avoid errors on Rx handler
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void oswarrior_enableDelays(void)
{
	OSWARRIOR_ENABLE_DELAYS;
};

/*
** ===================================================================
**     Function : oswarrior_disableDelays
**
**     Description :
**         This function is a dummy, only for avoid errors on Rx handler
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void oswarrior_disableDelays(void)
{
	OSWARRIOR_DISABLE_DELAYS
};

/*
** ===================================================================
**     Function : delay
**
**     Description :
**         This function is a dummy, only for avoid errors on Rx handler
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void delayMicroseconds(unsigned int us)
{
	T_ULONG start_time = micros();
	while( ( micros() - start_time ) < us );
};

void delay(unsigned int ms)
{
	T_ULONG start_time = millis();
	while( ( millis() - start_time ) < ms );
};

/*
** ===================================================================
**     Function : millis
**
**     Description :
**         This function is a dummy, only for avoid errors on Rx handler
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

T_ULONG micros(void)
{
	T_ULONG temp = TPM3MOD * 1000 / TPM3CNT;
	return (_OSWarrior_msCounter * 1000) + temp;
};

T_ULONG millis(void)
{
	return _OSWarrior_msCounter;
};

/*
** ===================================================================
**     Interrupt : fnc_oswarrior_tick_counter
**
**     Description :
**          This interruption is programmed to run every time a 
**          millisecond happens. 
**     
** ===================================================================
*/

__interrupt void fnc_oswarrior_tick_counter(void)
{    
	_OSWarrior_msCounter++;
	OSWARRIOR_TICK_ACK;
	(*_OSWarrior_tickISR_handler)();
};
