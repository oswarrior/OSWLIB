/*
 * Full_Demo_commands.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Demo_4/Demo_4_modules.h"
#include "oswlib/Demos/Demo_4/Demo_4_commands.h"
#include "oswlib/Demos/Demo_4/Demo_4_functions.h"

/*
** ===================================================================
** Demo list definitions
** ===================================================================
*/

const S_OSWARRIOR_DEMO_TYPE Demo_4_List[] = 
{		
	// CMD 		//Function, 					//Command Name
	{ "1", 		Demo_4_fnc1,					"Function 1"				},
	{ "2", 		Demo_4_fnc2, 					"Function 2"				},
	{ "3", 		Demo_4_fnc3, 					"Function 3"				},
	{ "4", 		Demo_4_fnc4, 					"Function 4"				},
	{ "5", 		Demo_4_fnc5, 					"Function 5"				}
};

const T_UBYTE Demo_4_Total = (sizeof(Demo_4_List)/sizeof(S_OSWARRIOR_DEMO_TYPE));
