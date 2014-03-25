/*
 * Full_Demo_commands.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Full_Demo/Full_Demo_modules.h"
#include "oswlib/Demos/Full_Demo/Full_Demo_commands.h"
#include "oswlib/Demos/Full_Demo/Full_Demo_functions.h"

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
	{ "3", 		demo_lcd_demo, 					"LCD Library Demo"						},
	{ "4", 		demo_pwm_rgb,					"PWM - RGB LED" 						},
	{ "5", 		demo_pwm_servo, 				"PWM - Servomotors" 					},
	{ "6", 		demo_i2c_pcf8574, 				"I2C-to-parallel converter (PCF8574)"	},
	{ "7", 		demo_i2c_wii_nunchuck, 			"Reading the Wii Nunchuck" 				},
	{ "8", 		demo_kbi_demo, 					"Keyboard interrupt"					},
	{ "9", 		demo_analog_control_led, 		"Blur LED - Analog control"				},
	{ "10", 	demo_analog_control_servo, 		"Servomotor - Analog control"			},
	{ "11", 	demo_i2c_wii_nunchuck_servo,	"Servomotor - Wii Nunchuck control" 	},
	{ "12", 	demo_led_sequence_1, 			"LED Sequence 1"						},
	{ "13", 	demo_led_sequence_2, 			"LED Sequence 2"						},
	{ "14", 	demo_led_sequence_3, 			"LED Sequence 3"						},
	{ "15", 	demo_motors_demo, 				"Motors Shield Demo" 					},
	{ "16", 	demo_scheduler_demo, 			"Scheduler Demo" 						},
	{ "17", 	demo_tone, 						"Tone Library - Melody" 				},
	{ "18", 	demo_tone_ode_to_joy,			"Tone Library - Ode to joy" 			},	
	{ "19", 	demo_tone_alarm, 				"Tone Library - Alarm" 					},
	{ "20", 	demo_tone_mb_main, 				"Mario Bros - Main Theme" 				},
	{ "21", 	demo_tone_mb_water, 			"Mario Bros - Underwater Theme"			},
	{ "22", 	demo_serial_getChar, 			"Serial Library - Get Char"				},
	{ "23", 	demo_serial_available, 			"Serial Library - Available"			},
	{ "24", 	demo_serial_readString, 		"Serial Library - Read String"			},
	{ "25", 	demo_serial_readNumber, 		"Serial Library - Read Number"			},
	{ "26", 	demo_stepper_driver, 			"Stepper Driver Test"					}
};

const T_UBYTE OSWarrior_Demo_Total = (sizeof(OSWarrior_Demo_List)/sizeof(S_OSWARRIOR_DEMO_TYPE));
