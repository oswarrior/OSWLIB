/*
 * OSWarrior_demo.h
 *
 *  Created on: Nov 6, 2013
 *      Author: HuAr
 */

#ifndef OSWARRIOR_Demo_1_H_
#define OSWARRIOR_Demo_1_H_
	
	#include "oswlib/settings.h"
	#include "oswlib/Demos/Demo_1/Demo_1_modules.h"

	/*
	** ===================================================================
	** Function declarations	
	** ===================================================================
	*/
	
	PUBLIC_FCT void Demo_1_main(S_SCISTR * userSerialPort, T_ULONG br);
	PUBLIC_FCT void Demo_1_loop(void);
	
	PUBLIC_DATA S_SCISTR * Demo_1_Serial;

#endif /* OSWARRIOR_DEMO_H_ */
