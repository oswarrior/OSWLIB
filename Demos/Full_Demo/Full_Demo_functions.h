/*
 * Full_Demo_functions.h
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#ifndef FULL_DEMO_FUNCTIONS_H_
#define FULL_DEMO_FUNCTIONS_H_
	
	#define STEP_FULL		0
	#define STEP_HALF		4
	#define STEP_QUARTER	2
	#define STEP_EIGHTH		6
	#define STEP_SIXTEENTH	7

	void demo_led_blinking(void);
	void demo_led_sequence_1(void);
	void demo_led_sequence_2(void);
	void demo_led_sequence_3(void);
	
	void demo_analog_read(void);
	void demo_analog_control_led(void);
	void demo_analog_control_servo(void);
	
	void demo_lcd_demo(void);
	
	void demo_pwm_rgb(void);
	void demo_tone(void);
	void demo_tone_alarm(void);
	void demo_tone_ode_to_joy(void);
	void demo_tone_mb_main(void);
	void demo_tone_mb_water(void);
	void demo_pwm_servo(void);
	
	void demo_i2c_pcf8574(void);
	void demo_i2c_wii_nunchuck(void);
	void demo_i2c_wii_nunchuck_servo(void);
	
	void demo_kbi_demo(void);
	
	void demo_motors_demo(void);
	
	void demo_scheduler_demo(void);
	
	void demo_dummy_car(void);
	
	void demo_Scheduler_Task_1(void);
	void demo_Scheduler_Task_2(void);
	void demo_Scheduler_Task_3(void);
	void demo_Scheduler_Task_4(void);
	void demo_Scheduler_Task_Count_100ms(void);
	void demo_Scheduler_Task_Count_1s(void);
	void demo_Scheduler_Task_Count_1m(void);
	void demo_Scheduler_Task_Count_1h(void);
	void demo_Scheduler_Task_Millis(void);
	
	void demo_serial_getChar(void);
	void demo_serial_available(void);
	void demo_serial_readString(void);
	void demo_serial_readNumber(void);

	void demo_stepper_driver(void);
	
#endif /* FULL_DEMO_FUNCTIONS_H_ */
