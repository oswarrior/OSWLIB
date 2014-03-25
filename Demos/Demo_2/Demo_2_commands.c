/*
 * Full_Demo_commands.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Demo_2/Demo_2_modules.h"
#include "oswlib/Demos/Demo_2/Demo_2_commands.h"
#include "oswlib/Demos/Demo_2/Demo_2_functions.h"

/*
** ===================================================================
** Demo list definitions
** ===================================================================
*/

const S_OSWARRIOR_DEMO_TYPE Demo_2_List[] = 
{		
	// CMD 		//Function, 					//Command Name
	{ "1", 		Demo_2_fnc1,					"Function 1"				},
	{ "2", 		Demo_2_fnc2, 					"Function 2"				},
	{ "3", 		Demo_2_fnc3, 					"Function 3"				},
	{ "4", 		Demo_2_fnc4, 					"Function 4"				},
	{ "5", 		Demo_2_fnc5, 					"Function 5"				}
};

const T_UBYTE Demo_2_Total = (sizeof(Demo_2_List)/sizeof(S_OSWARRIOR_DEMO_TYPE));
