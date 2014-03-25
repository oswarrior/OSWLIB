/*
 * Full_Demo_functions.c
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#include "oswlib/Demos/Full_Demo/Full_Demo.h"

#include "oswlib/Demos/Full_Demo/Full_Demo_modules.h"
#include "oswlib/Demos/Full_Demo/Full_Demo_functions.h"

/*
** ===================================================================
** Auxiliar Variables	
** ===================================================================
*/

const int inst_user_led_0 = LED0;
//const int inst_user_led_1 = LED1;

const int inst_user_lcd_led = 12;

const int inst_potenciometer = A7;		//Digital Pin 22

const int inst_servo_0 	 = PWM2;		//Digital Pin 2

const int inst_blur_led  = PWM2;		//Digital Pin 8
const int inst_tone_pin  = PWM1;		//Digital Pin 8

const int inst_rgb_red	 = PWM3;		//Digital Pin 9
const int inst_rgb_green = PWM4;		//Digital Pin 10
const int inst_rgb_blue  = PWM5;		//Digital Pin 11

/*
** ===================================================================
** Function definitions	
** ===================================================================
*/

void demo_led_blinking(void){
	
	int timeLimit,i;
	const int duration = 10000;			/* Demo duration in milliseconds */	
	
	pinDirection(inst_user_led_0,OUTPUT);
	
	for( i = 0 ; i < 8 ; i++ )
	{
		writePin(inst_user_led_0, HIGH);
		delay(50);
		writePin(inst_user_led_0, LOW);
		delay(50);
	}

	writePin(inst_user_led_0, LOW);

	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
	{
		togglePin(inst_user_led_0);
		delay(500);
	}
	
	pinDirection(inst_user_led_0, INPUT);
}

void demo_analog_read(void){
	
	int timeLimit;
	const int duration = 20000;			/* Demo duration in milliseconds */	
	
	Analog.init();
	Analog.enable(inst_potenciometer);
	Analog.setResolution(10);
	
	Demo_Full_Serial->newLine();
	
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
	{
		Demo_Full_Serial->write(">> Analog read: ");
		Demo_Full_Serial->printDigits(Analog.read(inst_potenciometer),4);
		Demo_Full_Serial->writeChar(ASCII_CR);
		delay(10);
	}
	
	Analog.disable(inst_potenciometer);
}

void demo_lcd_demo(void){
		
	LCD.init(2, 16, 7, 6, 5, 4, 1, 0 );
	LCD.clear();

	LCD.setCursor(2,1);
	LCD.print("OSWarrior DK");
	LCD.setCursor(4,2);
	LCD.print("Demo LCD");		

}

void demo_pwm_rgb(void){
	int i,repQty;
	const int seqDelay = 5, stageDelay = 500;

	RGB.enable(inst_rgb_red, inst_rgb_green, inst_rgb_blue);
	
	RGB.setColor(255, 0, 0);	delay(stageDelay);
	RGB.setColor(0, 255, 0);	delay(stageDelay);
	RGB.setColor(0, 0, 255);	delay(stageDelay);
	RGB.setColor(255, 255, 0);	delay(stageDelay);
	RGB.setColor(0, 255, 255);	delay(stageDelay);
	RGB.setColor(255, 0, 255);	delay(stageDelay);
	
	for(i = 0; i < 256; i++)
	{
		RGB.setColor(i, 0, 0);
		delay(seqDelay);
	}
	delay(stageDelay);
	
	for(repQty = 0; repQty < 3; repQty++)
	{
		
		for(i = 0; i < 256; i++)
		{
			RGB.setColor((255-i), i, 0);
			delay(seqDelay);
		}
		delay(stageDelay);
		
		for(i = 0; i < 256; i++)
		{
			RGB.setColor(0, (255-i), i);
			delay(seqDelay);
		}
		delay(stageDelay);
		
		for(i = 0; i < 256; i++)
		{
			RGB.setColor(i, 0, (255-i));
			delay(seqDelay);
		}
		delay(stageDelay);

	}
	
	for(i = 0; i < 256; i++)
	{
		RGB.setColor((255-i), 0, 0);
		delay(seqDelay);
	}
	delay(stageDelay);

	RGB.disable();
}

void demo_tone(void)
{

	int noteDurations[] = { 4, 8, 8, 4, 4, 4, 4, 4};
	int melody[] = {NOTE_C4, NOTE_G3,NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4};	
	int currentNote;
	
	PWM.enable(inst_tone_pin);
	
	for (currentNote = 0; currentNote < sizeof(melody); currentNote++) 
	{
		PWM.freq(inst_tone_pin, melody[currentNote]);
		delay( 1500 / noteDurations[currentNote]);
		PWM.dutyCycle(inst_tone_pin, 0); 
		delay(noteDurations[currentNote]/ 4);
	}

	PWM.disable(inst_tone_pin);

	return;
}

void demo_tone_alarm(void)
{
	int noteDurations[] = {8};
	int melody[] = {NOTE_C2};
	int currentNote;
	
	PWM.enable(inst_tone_pin);
	
	for (currentNote = 0; currentNote < sizeof(melody); currentNote++) 
	{
		PWM.freq(inst_tone_pin, melody[currentNote]);
		delay( 1000 / noteDurations[currentNote]);
		PWM.dutyCycle(inst_tone_pin, 0); 
		delay(noteDurations[currentNote]/ 4);
	}

	PWM.enable(inst_tone_pin);

	return;
}

void demo_tone_mb_main(void)
{
	//Mario main theme melody
	int melody[] = 
	{
	  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
	  0, NOTE_C7, NOTE_E7, 0,
	  NOTE_G7, 0, 0,  0,
	  NOTE_G6, 0, 0, 0, 

	  NOTE_C7, 0, 0, NOTE_G6, 
	  0, 0, NOTE_E6, 0, 
	  0, NOTE_A6, 0, NOTE_B6, 
	  0, NOTE_AS6, NOTE_A6, 0, 

	  NOTE_G6, NOTE_E7, NOTE_G7, 
	  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
	  0, NOTE_E7, 0,NOTE_C7, 
	  NOTE_D7, NOTE_B6, 0, 0,

	  NOTE_C7, 0, 0, NOTE_G6, 
	  0, 0, NOTE_E6, 0, 
	  0, NOTE_A6, 0, NOTE_B6, 
	  0, NOTE_AS6, NOTE_A6, 0, 

	  NOTE_G6, NOTE_E7, NOTE_G7, 
	  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
	  0, NOTE_E7, 0,NOTE_C7, 
	  NOTE_D7, NOTE_B6, 0, 0
	};

	//Mario main theme tempo
	int noteDurations[] = 
	{
	  12, 12, 12, 12, 
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12, 

	  12, 12, 12, 12,
	  12, 12, 12, 12, 
	  12, 12, 12, 12, 
	  12, 12, 12, 12, 

	  9, 9, 9,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,

	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,

	  9, 9, 9,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	  12, 12, 12, 12,
	};
	
	int currentNote;
	
	PWM.enable(inst_tone_pin);
	
	for (currentNote = 0; currentNote < sizeof(melody); currentNote++) 
	{
		PWM.freq(inst_tone_pin, melody[currentNote]);
		delay( 1000 / noteDurations[currentNote]);
		PWM.dutyCycle(inst_tone_pin, 0); 
		delay(noteDurations[currentNote]/ 4);
	}

	PWM.enable(inst_tone_pin);

	return;
}

void demo_tone_mb_water(void)
{
	//Underworld melody
	int melody[] = 
	{
	  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
	  NOTE_AS3, NOTE_AS4, 0,
	  0,
	  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
	  NOTE_AS3, NOTE_AS4, 0,
	  0,
	  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	  NOTE_DS3, NOTE_DS4, 0,
	  0,
	  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
	  NOTE_DS3, NOTE_DS4, 0,
	  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
	  NOTE_CS4, NOTE_DS4, 
	  NOTE_DS4, NOTE_GS3,
	  NOTE_G3, NOTE_CS4,
	  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
	  NOTE_GS4, NOTE_DS4, NOTE_B3,
	  NOTE_AS3, NOTE_A3, NOTE_GS3,
	  0, 0, 0
	};
	
	//Underwolrd tempo
	int noteDurations[] = 
	{
	  12, 12, 12, 12,	12, 12, 6,	3,12, 12, 12, 12, 
	  12, 12, 6,
	  3, 
	  12, 12, 12, 12, 
	  12, 12, 6,
	  3,
	  12, 12, 12, 12, 
	  12, 12, 6,
	  6, 18, 18, 18,
	  6, 6,
	  6, 6,
	  6, 6,
	  18, 18, 18,18, 18, 18,
	  10, 10, 10,
	  10, 10, 10,
	  3, 3, 3
	};
	
	int currentNote;
	
	PWM.enable(inst_tone_pin);
	
	for (currentNote = 0; currentNote < sizeof(melody); currentNote++) 
	{
		PWM.freq(inst_tone_pin, melody[currentNote]);
		delay( 1000 / noteDurations[currentNote]);
		PWM.dutyCycle(inst_tone_pin, 0); 
		delay(noteDurations[currentNote]/ 4);
	}

	PWM.enable(inst_tone_pin);

	return;
}

void demo_tone_ode_to_joy(void)
{
	// notes in the melody:
	int melody[] = 
	{
	  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
	  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_E4, NOTE_D4, NOTE_D4,
	  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
	  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4,
	  NOTE_D4, NOTE_D4, NOTE_E4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_C4,
	  NOTE_D4, NOTE_E4, NOTE_F4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_D4, NOTE_A3,
	  NOTE_E4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_F4, NOTE_E4, NOTE_D4,
	  NOTE_C4, NOTE_C4, NOTE_D4, NOTE_E4, NOTE_D4, NOTE_C4, NOTE_C4 
	};

	// note durations: 4 = quarter note, 8 = eighth note, etc.:
	int noteDurations[] = 
	{
	  4,4,4,4,4,4,4,4,		4,4,4,4,3,6,2,		4,4,4,4,4,4,4,4,	4,4,4,4,3,6,2,	
	  4,4,4,4,4,8,8,4,4, 	4,8,8,4,4,4,4,2,	4,4,4,4,4,4,4,4,	4,4,4,4,3,6,2
	};
	int currentNote;
	
	PWM.enable(inst_tone_pin);
	
	for (currentNote = 0; currentNote < sizeof(melody); currentNote++) 
	{
		PWM.freq(inst_tone_pin, melody[currentNote]);
		delay( 1000 / noteDurations[currentNote]);
		PWM.dutyCycle(inst_tone_pin, 0); 
		delay(noteDurations[currentNote]/ 4);
	}

	PWM.enable(inst_tone_pin);

	return;
}

void demo_pwm_servo(void)
{
	int i;
	int repetitions;			/* Number of repetitions for this demo */	

	Servo.enable(inst_servo_0);
	Servo.setDegrees(inst_servo_0, 0);
	
	delay(1000);
	
	for(repetitions = 0; repetitions < 3; repetitions++)
	{
		for(i = 0; i < 181; i = i + 10)
		{
			Servo.setDegrees(inst_servo_0, i);
			delay(50);
		}
		for(i = 0; i < 181; i = i + 10)
		{
			Servo.setDegrees(inst_servo_0, (180 - i));
			delay(50);
		}
	}
	
	Servo.disable(inst_servo_0);
}

void demo_i2c_pcf8574(void)
{
	int counter = 0;	
	T_UBYTE PCF8574 = 0x21;   //IC PCF8574 - I2C to parallel converter Address
	
	I2C.enable(0x1F);				//Start I2C module with address 0x1F
	
	for(counter = 0; counter < 256; counter++)
	{
		I2C.start(PCF8574);
		I2C.send((T_UBYTE)counter);
		I2C.end();
		delay(50);
	} 
	/*
	for(i = 0; i < 20; i++)
	{
		I2C.requestFrom(PCF8574,1);
		Demo_Full_Serial->print("I2C Data Read: ");
		while(I2C.available())	
			Demo_Full_Serial->printNum(I2C.read());
		Demo_Full_Serial->newLine();
		delay(500);
	}
	*/
};

void demo_i2c_wii_nunchuck(void)
{
	int timeLimit;
	const int duration = 10000;			/* Demo duration in milliseconds */	
	
	pinDirection(inst_user_led_0, OUTPUT);
	
	WiiNunchuck.init();
	
	Demo_Full_Serial->newLine();
	
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
	{
		
		WiiNunchuck.update();
		
		Demo_Full_Serial->write(">> C:");
		Demo_Full_Serial->print(WiiNunchuck.buttonC);
		writePin(inst_user_led_0,WiiNunchuck.buttonC);
			
		Demo_Full_Serial->write(", Z:");
		Demo_Full_Serial->print(WiiNunchuck.zPressed());
		
		Demo_Full_Serial->write(" - JoyX:");
		Demo_Full_Serial->print(WiiNunchuck.joyX());
		Demo_Full_Serial->write(" JoyY:");
		Demo_Full_Serial->print(WiiNunchuck.joyY());
		
		Demo_Full_Serial->write(" - AccX:");
		Demo_Full_Serial->print(WiiNunchuck.readAccelX());
		Demo_Full_Serial->write("	AccY:");
		Demo_Full_Serial->print(WiiNunchuck.readAccelY());
		Demo_Full_Serial->write("	AccZ:");
		Demo_Full_Serial->print(WiiNunchuck.readAccelZ());
		
		Demo_Full_Serial->newLine();
	}
	writePin(inst_user_led_0,0);
	pinDirection(inst_user_led_0, INPUT);
}

void demo_analog_control_led(void)
{
	int timeLimit;
	const int duration = 10000;			/* Demo duration in milliseconds */	
	
	Analog.init();
	Analog.enable(inst_potenciometer);
	Analog.setResolution(8);
	
	PWM.enable(inst_blur_led);	
	
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
		PWM.dutyCycle(inst_blur_led, map(Analog.read(inst_potenciometer),0,255,0,100));
	
	Analog.disable(inst_potenciometer);
	PWM.disable(inst_blur_led);
}

void demo_analog_control_servo(void)
{
	
	int timeLimit;
	const int duration = 10000;			/* Demo duration in milliseconds */	
		
	Analog.init();
	Analog.enable(inst_potenciometer);
	Analog.setResolution(8);
	
	Servo.enable(inst_servo_0);
	Servo.setDegrees(inst_servo_0, 90);
	
	Demo_Full_Serial->newLine();
	delay(1000);
		
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
		Servo.setDegrees(inst_servo_0, map(Analog.read(inst_potenciometer),0,255,0,180));
	
	Analog.disable(inst_potenciometer);
	Servo.disable(inst_servo_0);
}

void demo_i2c_wii_nunchuck_servo(void)
{
	int timeLimit;
	const int duration = 30000;			/* Demo duration in milliseconds */	
	
	Servo.enable(inst_servo_0);
	Servo.setDegrees(inst_servo_0, 90);
	
	WiiNunchuck.init();
	
	Demo_Full_Serial->newLine();
	
	timeLimit = (int)millis() + duration;
	
	while( (int)millis() < timeLimit)
	{
		WiiNunchuck.update();
		Servo.setDegrees(inst_servo_0, map(WiiNunchuck.readAccelX(),320,735,0,180));
	}
	
	Servo.disable(inst_servo_0);
}

void demo_led_sequence_1(void)
{
	int i, rep, totalRep = 3;
	int seqDelay = 30;
	for(i = 0; i < 24; i++)		pinDirection(i,INPUT);	
	for(i = 0; i < 24; i++)		pinDirection(i,OUTPUT);	
	for(rep = 0; rep < totalRep; rep++){
		for(i = 0; i < 24; i++)
		{	
			writePin(i,HIGH);	
			delay(seqDelay);	
		}
		for(i; i >= 0; i--)
		{		
			writePin(i,LOW);	
			delay(seqDelay);	
		}	
	}
}

void demo_led_sequence_2(void)
{
	int i, rep, totalRep = 50;
	int seqDelay = 30;
	for(i = 0; i < 24; i++)		pinDirection(i,INPUT);	
	for(i = 0; i < 24; i++)		pinDirection(i,OUTPUT);	
	for(rep = 0; rep < totalRep; rep++)
	{
		for(i = 0; i < 8; i++)		writePin(i,HIGH);
		delay(seqDelay);	
		for(i; i >= 0; i--)			writePin(i,LOW);
		delay(seqDelay);
		for(i = 8; i < 16; i++)		writePin(i,HIGH);
		delay(seqDelay);
		for(i; i >= 8; i--)			writePin(i,LOW);
		delay(seqDelay);
		for(i = 16; i < 24; i++)	writePin(i,HIGH);
		delay(seqDelay);
		for(i; i >= 16; i--)		writePin(i,LOW);
		delay(seqDelay);
	}
}

void demo_led_sequence_3(void)
{
	int timeSqn;
	int i = 0;
	int rep, totalRep = 3;
	for(i = 0; i < 24; i++)		pinDirection(i,INPUT);	
	for(i = 0; i < 24; i++)		pinDirection(i,OUTPUT);	
	for(rep = 0; rep < totalRep; rep++)
	{
		for(i = 0; i < 25; i++)
		{
			writePin(i,HIGH);
			if(!(i < 1))
			{
				writePin(i-1,LOW);
				timeSqn = i*5;
				delay(timeSqn);					
			}
		}	
	}
}

void demo_kbi_demo(void)
{
	KBI.attachInterrupt(KBI3, demo_pwm_rgb);
	KBI.attachInterrupt(KBI0, demo_tone_alarm);

	KBI.onPress = demo_tone_alarm;
}

void demo_motors_demo(void)
{
	Demo_Full_Serial->println("|------------------------------------------|");
	Demo_Full_Serial->println("|            Motor Shield Test             |");
	Demo_Full_Serial->println("|------------------------------------------|");
	
	Motors.enable();
	Motors.stop();
	Motors.speed(50);
	
	Motors.forward();
	delay(1000);
	
	Motors.left();
	delay(1000);
	
	Motors.backward();
	delay(1000);
	
	Motors.right();
	delay(1000);		
}


void demo_dummy_car(void)
{
	T_UBYTE data;			//Save Data byte
	
	data = SCI1D;	
	Demo_Full_Serial->write("Char: ");
	Demo_Full_Serial->writeChar(data);
	
	switch(data){
		case(0x65):
			Motors.enable();
		break;
		case(0x64):
			Motors.disable();
		break;
		case(0x66):
			Motors.forward();
		break;
		case(0x62):
			Motors.backward();
		break;
		case(0x6C):
			Motors.left();
		break;
		case(0x72):
			Motors.right();
		break;
		case(0x73):
			Motors.stop();
		break;
	}
}

void demo_scheduler_demo(void)
{
	
	pinDirection(LED0, OUTPUT);
	pinDirection(9, OUTPUT);
	pinDirection(10, OUTPUT);
	
	writePin(LED0, HIGH);
	writePin(9, HIGH);
	writePin(10, HIGH);

	Scheduler.task(demo_Scheduler_Task_2, 100, 100);
	Scheduler.task(demo_Scheduler_Task_3, 200, 200);
	Scheduler.task(demo_Scheduler_Task_4, 500, 500);
	
	Scheduler.task(demo_Scheduler_Task_Millis, 1000, 1000);
	
	//Scheduler.task(demo_Scheduler_Task_Count_1s, 1000, 1000);
	
	Scheduler.start();	
	
	pinDirection(8, INPUT);
	pinDirection(9, INPUT);
	pinDirection(10, INPUT);
}

void demo_Scheduler_Task_1(void)
{
	togglePin(0);
}

void demo_Scheduler_Task_2(void)
{
	togglePin(LED0);
}

void demo_Scheduler_Task_3(void)
{
	togglePin(9);
}

void demo_Scheduler_Task_4(void)
{
	togglePin(10);
}

void demo_Scheduler_Task_Millis(void)
{
	static T_ULONG time = 0;
	Demo_Full_Serial->write("\r\n>> T(ms): ");
	Demo_Full_Serial->print(millis());
	if(millis() > 100000) Scheduler.end();
}

void demo_Scheduler_Task_Count_100ms(void)
{
	static T_ULONG time = 0;
	Demo_Full_Serial->write(">> T(ms): ");
	Demo_Full_Serial->print(time+=100);
	Demo_Full_Serial->writeChar(ASCII_CR);
}

void demo_Scheduler_Task_Count_1s(void)
{
	static T_ULONG time = 1;
	Demo_Full_Serial->write("\r\n>> T(s): ");
	Demo_Full_Serial->print(time++);
}

void demo_Scheduler_Task_Count_1m(void)
{
	static T_ULONG time = 1;
	Demo_Full_Serial->write("\r\n\t>> T(m): ");
	Demo_Full_Serial->print(time++);
}

void demo_Scheduler_Task_Count_1h(void)
{
	static T_ULONG time = 1;
	Demo_Full_Serial->write("\r\n\t\t>> T(h): ");
	Demo_Full_Serial->print(time++);
}

void demo_serial_getChar(void)
{

	Demo_Full_Serial->clear();

	{
		Demo_Full_Serial->write("\r\n\r\n*********************************************\r\n"); 
		Demo_Full_Serial->write("OSWarrior Serial Library - Get Char Test");
		Demo_Full_Serial->write("\r\n*********************************************\r\n"); 
	}
	
	Demo_Full_Serial->writeChar(Demo_Full_Serial->getChar());
}

void demo_serial_available(void)
{
		
	int i,total = 10;
	
	Demo_Full_Serial->clear();

	{
		Demo_Full_Serial->write("\r\n\r\n*********************************************\r\n"); 
		Demo_Full_Serial->write("OSWarrior Serial Library - Read Test");
		Demo_Full_Serial->write("\r\n*********************************************\r\n"); 
	}
	
	Demo_Full_Serial->write("Enter 10 characters: ");

	while(Demo_Full_Serial->available() < total);
	
	for(i = 0; i < total; i++)
	{
		Demo_Full_Serial->writeChar(Demo_Full_Serial->read());
		Demo_Full_Serial->write(",");
	}
		
}

void demo_serial_readString(void)
{
	T_UBYTE * pointerTemp;

	Demo_Full_Serial->clear();

	{
		Demo_Full_Serial->write("\r\n\r\n*********************************************\r\n"); 
		Demo_Full_Serial->write("OSWarrior Serial Library - Read String Test");
		Demo_Full_Serial->write("\r\n*********************************************\r\n"); 
	}
	
	Demo_Full_Serial->write("Type a string: ");
	pointerTemp = Demo_Full_Serial->readString();
	Demo_Full_Serial->write("Echo: ");
	Demo_Full_Serial->write(pointerTemp);	
	
}

void demo_serial_readNumber(void)
{

	int i;
	
	Demo_Full_Serial->clear();

	{
		Demo_Full_Serial->write("\r\n\r\n*********************************************\r\n"); 
		Demo_Full_Serial->write("OSWarrior Serial Library - Read/Print Number");
		Demo_Full_Serial->write("\r\n*********************************************\r\n"); 
	}
	
	Demo_Full_Serial->write("X = ");
	i = Demo_Full_Serial->readNumber();
	i *= 2; 
	Demo_Full_Serial->write("X*2 = ");
	Demo_Full_Serial->print(i);
}


void demo_stepper_driver(void)
{
	//Control Signals
	int CLK = 3, DIR = 0, EN = 7;
	int MS1 = 17, MS2 = 16, MS3 = 15;
	
	//Local Variables
	static int freq_signal = 0;
	static int step_res = STEP_FULL;
	static int step_qty = 0;
	static int i,a = 1;
	int CLK_Delay[2];
	int CLK_Delay_temp;
	
	//Configure Pin Direction
	pinDirection(DIR, OUTPUT);
	pinDirection(CLK, OUTPUT);

	writePin(DIR,LEFT);
	writePin(CLK, OFF);
	
	// Set Motor Step Resolution
	pinDirection(MS1, OUTPUT);
	pinDirection(MS2, OUTPUT);
	pinDirection(MS3, OUTPUT);
	
	writePin(MS1, (step_res & 0x04));
	writePin(MS2, (step_res & 0x02));
	writePin(MS3, (step_res & 0x01));	
	
	//Get Signal Frequency
	Demo_Full_Serial->write("\n\rFrequency (<= 500) = ");
	freq_signal = Demo_Full_Serial->readNumber();
	
//	CLK_Delay[0] = (unsigned int)(500/freq_signal);			//Units = uS
//	CLK_Delay[0] = (unsigned int)(CLK_Delay[0]*1000);		//Units = uS
	CLK_Delay[0] = (int)(500/freq_signal);				//Units = mS
	CLK_Delay[1] = (int)CLK_Delay[0]*4;
	CLK_Delay_temp = CLK_Delay[0];
				
	Demo_Full_Serial->print(CLK_Delay_temp);

	//Get Steps Quantity
	Demo_Full_Serial->write("\n\rSteps Qty (<=200) = ");
	step_qty = Demo_Full_Serial->readNumber();	
		
	for(;;)	
	{
		togglePin(DIR);
		for(i = 0; i < (step_qty*2); i++)
		{
			togglePin(CLK);   
			delay(CLK_Delay_temp);
		}
		CLK_Delay_temp -= 1;
		if(CLK_Delay_temp == 0) CLK_Delay_temp = CLK_Delay[0];
	}
	
	return;
}

