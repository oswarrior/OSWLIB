/*
 * Full_Demo_commands.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Demo_3/Demo_3_modules.h"
#include "oswlib/Demos/Demo_3/Demo_3_commands.h"
#include "oswlib/Demos/Demo_3/Demo_3_functions.h"

/*
** ===================================================================
** Demo list definitions
** ===================================================================
*/

const S_OSWARRIOR_DEMO_TYPE Demo_3_List[] = 
{		
	// CMD 		//Function, 					//Command Name
	{ "1", 		demo_serial_wASCII,				"Serial - ASCII Table"				},
	{ "2", 		demo_serial_wString, 			"Serial - Write String"				},
	{ "3", 		demo_serial_wChar, 				"Serial - Write Character"			},
	{ "4", 		demo_serial_wNumber, 			"Serial - Write Number"				},
	{ "5", 		demo_serial_wDigits, 			"Serial - Write Digits"				},
	{ "6", 		demo_serial_rAvailable,			"Serial - Data Available"			},	
	{ "6", 		demo_serial_rString, 			"Serial - Read String"				},	
	{ "7", 		demo_serial_rChar, 				"Serial - Read Character"			},	
	{ "8", 		demo_serial_rNumber,			"Serial - Read Number"				},	
	//{ "9", 		demo_i2c_rAccelerometer,		"I2C - Read Accelerometer"			},
	//{ "10", 	demo_i2c_rNunchuck,				"I2C - Read WiiNunchuk"				},
	//{ "11", 	demo_i2c_rNunchuck_servo,		"I2C - Read WiiNunchuk & Servo"		},
	{ "9", 	demo_i2c_wParallel,				"I2C - Write PCF8574"				}
};

const T_UBYTE Demo_3_Total = (sizeof(Demo_3_List)/sizeof(S_OSWARRIOR_DEMO_TYPE));
