/*
 * Full_Demo_functions.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Demo_3/Demo_3.h"

#include "oswlib/Demos/Demo_3/Demo_3_modules.h"
#include "oswlib/Demos/Demo_3/Demo_3_functions.h"

/*
** ===================================================================
** Auxiliar Variables	
** ===================================================================
*/

const int Demo_3_user_led_0 = LED0;
const int Demo_3_user_pwm_2 = PWM2;		//Digital Pin 2

/*
** ===================================================================
** Example 3.- Serial Functions
** ===================================================================
*/


void demo_serial_wASCII(void)
{
	int number;
	Demo_3_Serial->write("\f>>ASCII Table\r\n");

	for(number = 33; number < 127; number++)
	{
		Demo_3_Serial->write("CHR: ");
		Demo_3_Serial->writeChar((T_UBYTE)number);
		
		Demo_3_Serial->write("\t\tDEC: ");
		Demo_3_Serial->print(number);
		
		if(number < 100)	Demo_3_Serial->write("\t\tHEX: ");
		else Demo_3_Serial->write("\tHEX: ");
		Demo_3_Serial->write(dec_to_hexString(number));
		
		/*
		Demo_3_Serial->print(number);
		if(number < 100)	Demo_3_Serial->write("\t\tOCT: ");
		else Demo_3_Serial->write("\tOCT: ");
		Demo_3_Serial->write(dec_to_hexString(number));
		*/
		
		Demo_3_Serial->write("\r\n");
		delay(100);
	}
	
	delay(3000);

	return;
}

void demo_serial_wString(void)
{
	Demo_3_Serial->write("\n\r>>Bienvenidos a la presentacion de OSWarrior DK\r\n");
	
	delay(3000);
	return;
}

void demo_serial_wChar(void)
{
	int number;

	Demo_3_Serial->writeChar(ASCII_LF);				//LF - Line Feed
	Demo_3_Serial->writeChar(ASCII_CR);				//CR - Carriage return	
	
	for(number = 33; number < 127; number++)
	{
		Demo_3_Serial->writeChar((T_UBYTE)number);
		Demo_3_Serial->writeChar((T_UBYTE)0x20);		
	}
	
	delay(3000);
	return;
}

void demo_serial_wNumber(void)
{
	int number;

	for(number = 0; number < 255; number++)
	{
		Demo_3_Serial->print(number);
		Demo_3_Serial->write("\r\n");
		delay(10);
	}
	
	delay(3000);
	return;
}

void demo_serial_wDigits(void)
{	
	int number;
	
	for(number = 0; number < 10000; number++)
	{
		Demo_3_Serial->printDigits(number,4);
	}
	
	delay(3000);
	return;
}

void demo_serial_rAvailable(void)
{
	int i,total = 10;

	Demo_3_Serial->write("\f>>Enter 10 characters. ");

	while(Demo_3_Serial->available() < total);
	
	Demo_3_Serial->write("\r\n>>Echo: ");
	
	for(i = 0; i < total; i++)
	{
		Demo_3_Serial->writeChar(Demo_3_Serial->read());
		Demo_3_Serial->write(",");
	}	
	
	delay(3000);
}

void demo_serial_rString(void)
{
	T_UBYTE * pointerTemp;
	
	Demo_3_Serial->write("\f>>Type a string: ");
	pointerTemp = Demo_3_Serial->readString();
	Demo_3_Serial->write("\r\n>>Echo: ");
	Demo_3_Serial->write(pointerTemp);	

	delay(3000);	
}

void demo_serial_rChar(void)
{
	Demo_3_Serial->writeChar(Demo_3_Serial->getChar());

	delay(3000);
}

void demo_serial_rNumber(void)
{
	int i;

	Demo_3_Serial->write("\f>>X = ");
	i = Demo_3_Serial->readNumber();
	i *= 2; 
	Demo_3_Serial->write("\n\r>>X*2 = ");
	Demo_3_Serial->print(i);

	delay(3000);
}

/*
** ===================================================================
** Example 4.- I2C Functions
** ===================================================================
*/

void demo_i2c_rAccelerometer(void)
{
	int timeLimit;
	const int duration = 10000;			/* Demo duration in milliseconds */	
	T_UBYTE _i2c_MMA8451[10];
	T_UBYTE _i2c_MMA8451_byteCounter;
			
	Demo_3_Serial->write("\r\n>>MMA8451 Test\r\n");
	
	delay(1000);
	
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
	{
		
		I2C.start(0x1C);
		I2C.send((T_UBYTE)0x02);
		I2C.end();	
		delay(5);
		
		I2C.requestFrom(0x1C,1);
		
		while(I2C.available()){
			_i2c_MMA8451[_i2c_MMA8451_byteCounter] = I2C.read();
			_i2c_MMA8451_byteCounter++;
		}
		
		Demo_3_Serial->print((int)_i2c_MMA8451[0]);
		Demo_3_Serial->newLine();
		
		delay(5);
		
	}
	
	delay(3000);
	return;
}

void demo_i2c_rNunchuck(void)
{
	int timeLimit;
	const int duration = 10000;			/* Demo duration in milliseconds */	
	
	pinDirection(Demo_3_user_led_0, OUTPUT);

	Demo_3_Serial->write("\r\n>>Wii Nunchuck Test\r\n");

	WiiNunchuck.init();
	
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
	{
		delay(20);
		
		WiiNunchuck.update();
		
		Demo_3_Serial->write(">> C:");
		Demo_3_Serial->print(WiiNunchuck.buttonC);
		writePin(Demo_3_user_led_0,WiiNunchuck.buttonC);
			
		Demo_3_Serial->write(", Z:");
		Demo_3_Serial->print(WiiNunchuck.zPressed());
		
		Demo_3_Serial->write(" - JoyX:");
		Demo_3_Serial->print(WiiNunchuck.joyX());
		Demo_3_Serial->write(" JoyY:");
		Demo_3_Serial->print(WiiNunchuck.joyY());
		
		Demo_3_Serial->write(" - AccX:");
		Demo_3_Serial->print(WiiNunchuck.readAccelX());
		Demo_3_Serial->write("	AccY:");
		Demo_3_Serial->print(WiiNunchuck.readAccelY());
		Demo_3_Serial->write("	AccZ:");
		Demo_3_Serial->print(WiiNunchuck.readAccelZ());
		
		Demo_3_Serial->newLine();
	}
	writePin(Demo_3_user_led_0,0);
	pinDirection(Demo_3_user_led_0, INPUT);
}

void demo_i2c_rNunchuck_servo(void)
{
	int timeLimit;
	const int duration = 30000;			/* Demo duration in milliseconds */	
	
	Servo.enable(Demo_3_user_pwm_2);
	Servo.setDegrees(Demo_3_user_pwm_2, 90);
	
	WiiNunchuck.init();
	
	Demo_3_Serial->newLine();
	
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
	{
		WiiNunchuck.update();
		Servo.setDegrees(Demo_3_user_pwm_2, map(WiiNunchuck.readAccelX(),320,735,0,180));
	}
	
	Servo.disable(Demo_3_user_pwm_2);
	
	delay(3000);
}

void demo_i2c_wParallel(void)
{
	int counter = 0;	
	const T_UBYTE PCF8574 = 0x21;   //IC PCF8574 - I2C to parallel converter Address
	
	I2C.enable(0x1F);				//Start I2C module with address 0x1F
			
	for(counter = 0; counter <= 0xFF; counter++)
	{
		I2C.start(PCF8574);
		I2C.send((T_UBYTE)counter);
		I2C.end();
		delay(50);
	} 

	delay(3000);
};
