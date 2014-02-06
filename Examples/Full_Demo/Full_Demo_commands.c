/*
 * Full_Demo_commands.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Examples/Full_Demo/Full_Demo_modules.h"
#include "oswlib/Examples/Full_Demo/Full_Demo_commands.h"
#include "oswlib/Examples/Full_Demo/Full_Demo_functions.h"

/*
** ===================================================================
** Demo list definitions
** ===================================================================
*/

const S_OSWARRIOR_DEMO_TYPE OSWarrior_Demo_List[] = 
{		
	/* CMD, 	Function, 								Command Name */	
	{ "1", 		demo_led_blinking, 				"Hello World - Blinking LED"			},
	{ "2", 		demo_analog_read, 				"Analog Pin - Input Reading"			},
	{ "3", 		demo_pwm_rgb,					"PWM - RGB LED" 						},
	{ "4", 		demo_pwm_servo, 				"PWM - Servomotors" 					},
	{ "5", 		demo_i2c_pcf8574, 				"I2C-to-parallel converter (PCF8574)"	},
	{ "6", 		demo_i2c_wii_nunchuck, 			"Reading the Wii Nunchuck" 				},
	{ "7", 		demo_kbi_demo, 					"Keyboard interrupt"					},
	{ "8", 		demo_analog_control_led, 		"Blur LED - Analog control"				},
	{ "9", 		demo_analog_control_servo, 		"Servomotor - Analog control"			},
	{ "10", 	demo_i2c_wii_nunchuck_servo,	"Servomotor - Wii Nunchuck control" 	},
	{ "11", 	demo_led_sequence_1, 			"LED Sequence 1"						},
	{ "12", 	demo_led_sequence_2, 			"LED Sequence 2"						},
	{ "13", 	demo_led_sequence_3, 			"LED Sequence 3"						},
	{ "14", 	demo_motors_demo, 				"Motors Shield Demo" 					},
	{ "15", 	demo_scheduler_demo, 			"Scheduler Demo" 						},
	{ "16", 	demo_pwm_tone, 					"Tone Library - Melody" 				},
	{ "17", 	demo_pwm_tone_alarm, 			"Tone Library - Alarm" 					}
};

const T_UBYTE OSWarrior_Demo_Total = (sizeof(OSWarrior_Demo_List)/sizeof(S_OSWARRIOR_DEMO_TYPE));
