/*
 * OSWarrior_demo.h
 *
 *  Created on: Nov 6, 2013
 *      Author: HuAr
 */

#ifndef OSWARRIOR_Demo_4_H_
#define OSWARRIOR_Demo_4_H_
	
	#include "oswlib/settings.h"
	#include "oswlib/Demos/Demo_4/Demo_4_modules.h"

	/*
	** ===================================================================
	** Function declarations	
	** ===================================================================
	*/
	
	PUBLIC_FCT void Demo_4_main(S_SCISTR * userSerialPort, T_ULONG br);
	PUBLIC_FCT void Demo_4_loop(void);
	
	PUBLIC_DATA S_SCISTR * Demo_4_Serial;

#endif /* OSWARRIOR_DEMO_H_ */