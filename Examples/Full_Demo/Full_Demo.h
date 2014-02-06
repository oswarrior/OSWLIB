/*
 * OSWarrior_demo.h
 *
 *  Created on: Nov 6, 2013
 *      Author: HuAr
 */

#ifndef OSWARRIOR_DEMO_H_
#define OSWARRIOR_DEMO_H_
	
	#include "oswlib/settings.h"
	#include "oswlib/Examples/Full_Demo/Full_Demo_modules.h"

	/*
	** ===================================================================
	** Function declarations	
	** ===================================================================
	*/
	
	PUBLIC_FCT void example_Full_Demo_main(S_SCISTR * userSerialPort, T_ULONG br);
	PUBLIC_FCT void example_Full_Demo_loop(void);
	
	PUBLIC_DATA S_SCISTR * Demo_Full_Serial;

#endif /* OSWARRIOR_DEMO_H_ */
