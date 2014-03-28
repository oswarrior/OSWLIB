/*
 * delays.h
 *
 *  Created on: Oct 30, 2013
 *      Author: HuAr
 */

#ifndef OSWARRIOR_DELAYS_H_
	#define OSWARRIOR_DELAYS_H_

	/*
	** ===================================================================
	** Delay interrupt handlers
	** ===================================================================
	*/

	extern __interrupt void fnc_oswarrior_tick_counter(void);

	static void (* near const _vect_TickISR[])(void) @OSWarrior_ISR_TPM3Ovf_Vector = {
			fnc_oswarrior_tick_counter
	};
	    
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

	PUBLIC_DATA void ( * _OSWarrior_tickISR_handler )(void);

#endif /* DELAYS_H_ */
