/*
 * Full_Demo_commands.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Demo_1/Demo_1_modules.h"
#include "oswlib/Demos/Demo_1/Demo_1_commands.h"
#include "oswlib/Demos/Demo_1/Demo_1_functions.h"

/*
** ===================================================================
** Demo list definitions
** ===================================================================
*/

const S_OSWARRIOR_DEMO_TYPE Demo_1_List[] = 
{		
	// CMD 		//Function, 					//Command Name
	{ "1", 		Demo_1_fnc1,					"Function 1"				},
	{ "2", 		Demo_1_fnc2, 					"Function 2"				},
	{ "3", 		Demo_1_fnc3, 					"Function 3"				},
	{ "4", 		Demo_1_fnc4, 					"Function 4"				},
	{ "5", 		Demo_1_fnc5, 					"Function 5"				}
};

const T_UBYTE Demo_1_Total = (sizeof(Demo_1_List)/sizeof(S_OSWARRIOR_DEMO_TYPE));
