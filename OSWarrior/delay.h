/*
 * delays.h
 *
 *  Created on: Oct 30, 2013
 *      Author: HuAr
 */

#ifndef OSWARRIOR_DELAYS_H_
	#define OSWARRIOR_DELAYS_H_

	#define timerCountForMillisecond() ( ( BUSCLOCK / 1000u ) / DELAY_PS )

	/*
	** ===================================================================
	** Delay interrupt handlers
	** ===================================================================
	*/

	extern __interrupt void oswarrior_tick_counter(void);

	#ifdef __OSWarrior_DK__
		static void (* near const _vect_TickISR[])(void) @OSWarrior_ISR_TPM3Ovf_Vector = { oswarrior_tick_counter };
	#endif
	    
	/*
    ** ===================================================================
    ** Delay functions prototypes
    ** ===================================================================
    */
		
	PUBLIC_FCT void oswarrior_enableDelays(void);
	PUBLIC_FCT void oswarrior_disableDelays(void);
	
	PUBLIC_FCT void delay(unsigned int ms);
	PUBLIC_FCT void delayMicroseconds(unsigned int us);
	
	PUBLIC_FCT T_ULONG millis(void);
	PUBLIC_FCT T_ULONG micros(void);

	PRIVATE_FCT void oswarrior_tick_ack(void);

	PUBLIC_DATA void ( * _OSWarrior_tickISR_handler )(void);

#endif /* DELAYS_H_ */
