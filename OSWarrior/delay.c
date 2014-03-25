
#include "oswlib/settings.h"
#include "oswlib/OSWarrior/delay.h"		//Delay control

/*
** ===================================================================
** Delay variables declarations
** ===================================================================
*/

static volatile T_ULONG _OSWarrior_tickCounter = 0;
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

T_ULONG millis(void)
{
	return _OSWarrior_tickCounter;
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
	_OSWarrior_tickCounter++;
	OSWARRIOR_TICK_ACK;
	(*_OSWarrior_tickISR_handler)();
};
