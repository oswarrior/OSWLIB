/*
 * OSWarrior_demo.h
 *
 *  Created on: Nov 6, 2013
 *      Author: HuAr
 */

#ifndef OSWARRIOR_Demo_3_H_
#define OSWARRIOR_Demo_3_H_
	
	#include "oswlib/settings.h"
	#include "oswlib/Demos/Demo_3/Demo_3_modules.h"

	/*
	** ===================================================================
	** Function declarations	
	** ===================================================================
	*/
	
	PUBLIC_FCT void Demo_3_main(S_SCISTR * userSerialPort, T_ULONG br);
	PUBLIC_FCT void Demo_3_loop(void);
	
	PUBLIC_DATA S_SCISTR * Demo_3_Serial;

#endif /* OSWARRIOR_DEMO_H_ */
