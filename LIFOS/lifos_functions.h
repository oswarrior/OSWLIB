/*
 * lifos_functions.h
 *
 *  Created on: Nov 23, 2013
 *      Author: HuAr
 */

#ifndef LIFOS_FUNCTIONS_H_
#define LIFOS_FUNCTIONS_H_

	extern int lifos_printCMDList(T_UBYTE Channel, int Value);
	
	extern int lifos_pinDirection(T_UBYTE Channel, int Value);
	extern int lifos_pinRead(T_UBYTE Channel, int Value);
	extern int lifos_pinWrite(T_UBYTE Channel, int Value);
	extern int lifos_pinToggle(T_UBYTE Channel, int Value);
	
	extern int lifos_analogInit(T_UBYTE Channel, int Value);
	extern int lifos_analogEnable(T_UBYTE Channel, int Value);
	extern int lifos_analogDisable(T_UBYTE Channel, int Value);
	extern int lifos_analogRead(T_UBYTE Channel, int Value);
	extern int lifos_analogResolution(T_UBYTE Channel, int Value);
	
	extern int lifos_servoEnable(T_UBYTE Channel, int Value);
	extern int lifos_servoDisable(T_UBYTE Channel, int Value);
	extern int lifos_servoRead(T_UBYTE Channel, int Value);
	extern int lifos_servoWrite(T_UBYTE Channel, int Value);
	
	extern int lifos_pwmEnable(T_UBYTE Channel, int Value);
	extern int lifos_pwmDisable(T_UBYTE Channel, int Value);
	extern int lifos_pwmRead(T_UBYTE Channel, int Value);
	extern int lifos_pwmWrite(T_UBYTE Channel, int Value);

#endif /* LIFOS_FUNCTIONS_H_ */
