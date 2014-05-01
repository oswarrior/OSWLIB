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
** Delay functions definition
** ===================================================================
*/

void oswarrior_enableDelays(void)
{
	#ifdef __OSWarrior_DK__
	{
		TPM3SC = 0x00u; 							/* Disable TPM3 Module */
		TPM3MOD = timerCountForMillisecond();		/* Set timer period to 1 millisecond */ 
		(void)TPM3SC; 								/* Clear any pending flags */
		
		#if DELAY_PS == 1
			TPM3SC = 0x08;		/* PS = 1 */			
		#elif DELAY_PS == 2
			TPM3SC = 0x09;		/* PS = 2 */				
		#elif DELAY_PS == 4
			TPM3SC = 0x0A;		/* PS = 4 */ 		
		#elif DELAY_PS == 8
			TPM3SC = 0x0B;		/* PS = 8 */ 		
		#elif DELAY_PS == 16
			TPM3SC = 0x0C;		/* PS = 16 */ 		
		#elif DELAY_PS == 32
			TPM3SC = 0x0D;		/* PS = 32 */ 		
		#elif DELAY_PS == 64
			TPM3SC = 0x0E;		/* PS = 64 */		
		#else
			TPM3SC = 0x00;		/* Disable TPM3 Module */
			#error "The selected Prescaler is not supported"
		#endif
  
		TPM3SC |= 0x40;				/* Enable Timer Overflow ISR */ 		
	}
	#endif
};

void oswarrior_disableDelays(void)
{
	#ifdef __OSWarrior_DK__
	{
		TPM3SC = 0x00u;		/* Disable TPM3 Module */
	}
	#endif	
};

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

T_ULONG micros(void)
{
	#ifdef __OSWarrior_DK__
	{
		return (TPM3CNT * 1000 / timerCountForMillisecond()) + (_OSWarrior_msCounter * 1000);
	}
	#endif		
};

T_ULONG millis(void)
{
	return _OSWarrior_msCounter;
};

__interrupt void oswarrior_tick_counter(void)
{
	_OSWarrior_msCounter++;
	oswarrior_tick_ack();
	(*_OSWarrior_tickISR_handler)();
};

void oswarrior_tick_ack(void)
{
	#ifdef __OSWarrior_DK__
	{
		(void)TPM3SC;
		TPM3SC_TOF = 0;		/* Clear Timer Overflow Flag */
	}
	#endif		
}

