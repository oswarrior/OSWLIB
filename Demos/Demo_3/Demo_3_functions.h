/*
 * Full_Demo_functions.h
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#ifndef FULL_DEMO_FUNCTIONS_H_
#define FULL_DEMO_FUNCTIONS_H_

	void demo_serial_wASCII(void);
	
	void demo_serial_wString(void);
	void demo_serial_wChar(void);
	void demo_serial_wNumber(void);
	void demo_serial_wDigits(void);
	
	void demo_serial_rAvailable(void);
	void demo_serial_rString(void);
	void demo_serial_rChar(void);
	void demo_serial_rNumber(void);

	void demo_i2c_rAccelerometer(void);
	void demo_i2c_rNunchuck(void);
	void demo_i2c_rNunchuck_servo(void);

	void demo_i2c_wParallel(void);


#endif /* FULL_DEMO_FUNCTIONS_H_ */
