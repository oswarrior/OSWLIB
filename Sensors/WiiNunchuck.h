/*
** 	Filename: WiiNunchuck.h
** 	Description: I2C communication with the Wii Nunchuck sensors
**
**	Author: Hugo Arganda (e.arganda.salazar@gmail.com)
** 	Current Version: 1.0
** 	Status: Development
**
**	CHANGE LOG:
**	Date: 10/09/2013 - Library created
**	
** 	LICENSE:
** 	This library is free software; you can redistribute it and/or
** 	modify it under the terms of the Attribution-ShareAlike
** 	License as published by the Creative Commons Organization; either
** 	version 3.0 of the License, or (at your option) any later version.
** 	This library is distributed in the hope that it will be useful,
** 	but WITHOUT ANY WARRANTY; without even the implied warranty of
** 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
** 	See the Attribution-ShareAlike License for more details.
** 	You should have received a copy of the Creative Commons Attribution-ShareAlike 
** 	License along with this library; if not send a email to the library author.
*/

#ifndef OSWARRIOR_WIINUNCHUCK_H_
	#define OSWARRIOR_WIINUNCHUCK_H_

	#define _I2C_WIINUNCHUCK_DEFAULT_ZERO_ACC_X		533
	#define _I2C_WIINUNCHUCK_DEFAULT_ZERO_ACC_Y		515
	#define _I2C_WIINUNCHUCK_DEFAULT_ZERO_ACC_Z		519

	#define _I2C_WIINUNCHUCK_DEFAULT_ZERO_JOY_X		122
	#define _I2C_WIINUNCHUCK_DEFAULT_ZERO_JOY_Y		127

	#define _I2C_WIINUNCHUCK_ADD					0x52

	/*
	** ===================================================================
	** Function prototypes	
	** ===================================================================
	*/

	extern void _i2c_wiinunchuck_init(void);
	extern void _i2c_wiinunchuck_update(void);
	extern void _i2c_wiinunchuck_sendZero(void);
	
	extern int _i2c_wiinunchuck_readAccelX(void);
	extern int _i2c_wiinunchuck_readAccelY(void);
	extern int _i2c_wiinunchuck_readAccelZ(void);
	
	extern T_UBYTE _i2c_wiinunchuck_zPressed(void);
	extern T_UBYTE _i2c_wiinunchuck_cPressed(void);

	extern void _i2c_wiinunchuck_calibrateJoystick(void);
	extern int _i2c_wiinunchuck_readJoystickX(void);
	extern int _i2c_wiinunchuck_readJoystickY(void);

	/*
	** ===================================================================
	** HC-SR04 Sensor Structure Definition
	** ===================================================================
	*/
	
	typedef struct{
		T_UBYTE buttonC;
		T_UBYTE buttonZ;
		void (*init)(void);	
		void (*update)(void);
		int (*readAccelX)(void);	
		int (*readAccelY)(void);	
		int (*readAccelZ)(void);
		T_UBYTE (*cPressed)(void);
		T_UBYTE (*zPressed)(void);
		void (*calibrateJoy)(void);
		int (*joyX)(void);
		int (*joyY)(void);		
	}WIINUNCHUCKSTR;	
	
	extern WIINUNCHUCKSTR WiiNunchuck;
	
#endif
