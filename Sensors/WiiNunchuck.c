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

#include "oswlib/settings.h"
#include "oswlib/I2C/i2c.h"
#include "oswlib/Serial/serial.h"
#include "oswlib/Sensors/WiiNunchuck.h"

T_UBYTE _i2c_wiinunchuck_byteCounter;
T_UBYTE _i2c_wiinunchuck_avgCounter;
T_UBYTE _i2c_wiinunchuck_i;
T_UBYTE _i2c_wiinunchuck_total;

T_UBYTE _i2c_wiinunchuck_joyX;
T_UBYTE _i2c_wiinunchuck_joyY;
T_UBYTE _i2c_wiinunchuck_zeroJoyX;
T_UBYTE _i2c_wiinunchuck_zeroJoyY;
T_UBYTE _i2c_wiinunchuck_lastJoyX;
T_UBYTE _i2c_wiinunchuck_lastJoyY;

T_UBYTE _i2c_wiinunchuck_lastC;
T_UBYTE _i2c_wiinunchuck_lastZ;

T_UBYTE _i2c_wiinunchuck_data[6];
int _i2c_wiinunchuck_acc_data[3];

WIINUNCHUCKSTR WiiNunchuck = {
	0,
	0,
	_i2c_wiinunchuck_init, 		  
	_i2c_wiinunchuck_update, 		  
	_i2c_wiinunchuck_readAccelX, 		  
	_i2c_wiinunchuck_readAccelY, 		  
	_i2c_wiinunchuck_readAccelZ, 		  
	_i2c_wiinunchuck_cPressed, 
	_i2c_wiinunchuck_zPressed, 		  
	_i2c_wiinunchuck_calibrateJoystick,
	_i2c_wiinunchuck_readJoystickX, 		  
	_i2c_wiinunchuck_readJoystickY 		  
};

void _i2c_wiinunchuck_init(void){
	I2C.enable(I2C.address);
	_i2c_wiinunchuck_byteCounter = 0;
	_i2c_wiinunchuck_avgCounter = 0;
	I2C.start(0x52);	//OK
	I2C.send(0xF0);		//OK
	I2C.send(0x55);		//OK
	I2C.end(TRUE);
	delay(10);
	//Serial.getChar();
	I2C.start(0x52);
	I2C.send(0xFB);
	I2C.send(0x00);
	I2C.end(TRUE);
	//delay(5);

	for(_i2c_wiinunchuck_i = 0; _i2c_wiinunchuck_i < 3; _i2c_wiinunchuck_i++){
		_i2c_wiinunchuck_acc_data[_i2c_wiinunchuck_i] = 0;
	}
	_i2c_wiinunchuck_zeroJoyX = _I2C_WIINUNCHUCK_DEFAULT_ZERO_JOY_X;
	_i2c_wiinunchuck_zeroJoyY = _I2C_WIINUNCHUCK_DEFAULT_ZERO_JOY_Y;

	_i2c_wiinunchuck_update();
}

void _i2c_wiinunchuck_update(void){
	int i;
	I2C.requestFrom(0x52,6);	
	while(I2C.available()){
		_i2c_wiinunchuck_data[_i2c_wiinunchuck_byteCounter] = I2C.read();
		_i2c_wiinunchuck_byteCounter++;
	}
	if(_i2c_wiinunchuck_byteCounter > 5){
		_i2c_wiinunchuck_lastZ = WiiNunchuck.buttonZ;
		_i2c_wiinunchuck_lastC = WiiNunchuck.buttonC;
		_i2c_wiinunchuck_lastJoyX = _i2c_wiinunchuck_joyX;
		_i2c_wiinunchuck_lastJoyY = _i2c_wiinunchuck_joyY;
		
		_i2c_wiinunchuck_byteCounter = 0;
		_i2c_wiinunchuck_joyX = _i2c_wiinunchuck_data[0];
		_i2c_wiinunchuck_joyY = _i2c_wiinunchuck_data[1];
		
		for(i = 0; i < 3; i++){
			_i2c_wiinunchuck_acc_data[i] = _i2c_wiinunchuck_data[i + 2] << 2;
			_i2c_wiinunchuck_acc_data[i] += ((_i2c_wiinunchuck_data[5] & (T_UBYTE)(0x03 << ((i+1)*2) ) >> ((i+1)*2)));
		}
		
		WiiNunchuck.buttonZ = ! (_i2c_wiinunchuck_data[5] & 0x01);
		WiiNunchuck.buttonC = ! ((_i2c_wiinunchuck_data[5] >> 1) & 0x01 );
		
		_i2c_wiinunchuck_sendZero();
	}
}

void _i2c_wiinunchuck_sendZero(void){
	I2C.start(0x52);
	I2C.send((T_UBYTE)0x00);
	I2C.end(1);	
	delay(5);
}

int _i2c_wiinunchuck_readAccelX(void){
	//return (int) _i2c_wiinunchuck_acc_data[0] - _I2C_WIINUNCHUCK_DEFAULT_ZERO_ACC_X;
	return (int) _i2c_wiinunchuck_acc_data[0];
}

int _i2c_wiinunchuck_readAccelY(void){
	 //return (int) _i2c_wiinunchuck_acc_data[1] - _I2C_WIINUNCHUCK_DEFAULT_ZERO_ACC_Y;
	 return (int) _i2c_wiinunchuck_acc_data[1];
}

int _i2c_wiinunchuck_readAccelZ(void){
	 //return (int) _i2c_wiinunchuck_acc_data[2] - _I2C_WIINUNCHUCK_DEFAULT_ZERO_ACC_Z;	
	 return (int) _i2c_wiinunchuck_acc_data[2];	
}

T_UBYTE _i2c_wiinunchuck_zPressed(void){
	return ( WiiNunchuck.buttonZ && ! _i2c_wiinunchuck_lastZ);
}

T_UBYTE _i2c_wiinunchuck_cPressed(void){
	return ( WiiNunchuck.buttonC && ! _i2c_wiinunchuck_lastC);	
}

void _i2c_wiinunchuck_calibrateJoystick(void){
	_i2c_wiinunchuck_zeroJoyX = _i2c_wiinunchuck_joyX;
	_i2c_wiinunchuck_zeroJoyY = _i2c_wiinunchuck_joyY;
}

int _i2c_wiinunchuck_readJoystickX(void){
	//return (int)(_i2c_wiinunchuck_joyX - _i2c_wiinunchuck_zeroJoyX);
	return (_i2c_wiinunchuck_joyX);
}

int _i2c_wiinunchuck_readJoystickY(void){
	//return (int)(_i2c_wiinunchuck_joyY - _i2c_wiinunchuck_zeroJoyY);
	return (_i2c_wiinunchuck_joyY);
}
