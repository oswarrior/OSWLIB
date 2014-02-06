#include "oswlib/settings.h"

#include "oswlib/PWM/PWM.h"
#include "oswlib/RGB/RGB.h"
#include "oswlib/Analog/analog.h"
#include "oswlib/Serial/serial.h"
#include "oswlib/scheduler/scheduler.h"

#include "oswlib/Examples/TSD/PR5/PR5_UART.h"

#include "oswlib/Examples/TSD/PR5/PR5_REQ_ROM.h"
#include "oswlib/Examples/TSD/PR5/PR5_EXT_WOM.h"

E_PR5_MODE PR5_current_Mode = PR5_MODE_OFF;

void (*functionHandler)(void);

/* Instruments */

int S1 = 12;
int S2 = 15;

int Lr = PWM2;
int Lg = PWM3;
int Lb = PWM4;

int Pr = A4;
int Pg = A3;
int Pb = A2;

int ADC_Value_r = 0;
int ADC_Value_g = 0;
int ADC_Value_b = 0;

void PR5_main(void)
{
	functionHandler = PR5_Mode_OFF;		//Mode off at power up		
	
	Serial.init(9600);
	
	PR5_Print_Header();					//Print header
	
	RGB.enable(Lr, Lg, Lb);				//Enable RGB LED
	
	pinDirection(S1,INPUT_PULLUP);		//Set S1
	pinDirection(S2,INPUT_PULLUP);		//Set S2
	
	Analog.enable(Pr);					//Enable ADC R Channel
	Analog.enable(Pg);					//Enable ADC G Channel
	Analog.enable(Pb);					//Enable ADC B Channel
	
	Scheduler.task(PR5_S1_Event_Listener, 5, 5);		//Schedule Function - S1 Listener
	Scheduler.task(PR5_S2_Event_Listener, 5, 5);		//Schedule Function - S2 Listener
	
	Scheduler.task(PR5_Analog_Read, 30, 30);			//Schedule Function - ADC read
	Scheduler.task(PR5_Function_handler, 100, 100);		//Schedule Function - Periodic User Function
	
	PR5_REQ_ROM();				//Enable external requests (ROM)
	//PR5_EXT_WOM();			//Enable external commands (WOM)

	Analog.init();				//Start ADC
	Scheduler.start();			//Run the scheduler

}

void PR5_Print_Header(void)
{
	Serial.print("\f"); 
	Serial.print("******************************************\r\n"); 
	Serial.print(" TOPICOS SELECTOS EN SISTEMAS DIGITALES\r\n");
	Serial.print(" Practica #5 - Interfaz UART\r\n");
	Serial.print("******************************************\r\n"); 	
}

void PR5_S1_Event_Listener(void)
{
	PRIVATE_DATA T_UWORD luw_tick_counter = 0;
	int luw_buttonStatus;
	luw_buttonStatus = readPin(S1);
	if(luw_buttonStatus == 0)
	{		 								//Push Button is ON
		luw_tick_counter++;					//Count ticks
	}
	else
	{										//Push Button is OFF
		if(luw_tick_counter != 0)			//Wait for counter change
		{																
			PR5_Mode_handler();
			luw_tick_counter = 0; 			//Reset Counter
		}
	}	
}

void PR5_Mode_handler(void)
{	
	switch(PR5_current_Mode)
	{
		case(PR5_MODE_OFF):						//Current
			PR5_Set_SEQ_Mode();
		break;
		case(PR5_MODE_SEQ):						//Current
			PR5_Set_ANALOG_Mode();
		break;
		case(PR5_MODE_ANALOG):					//Current	
			PR5_Set_OFF_Mode();
		break;
	}
}

void PR5_Analog_Read(void)
{
	static int nextChannel = 0;
	if(PR5_current_Mode == PR5_MODE_ANALOG)
	{
		switch(nextChannel)
		{
			case (0):
				ADC_Value_r = Analog.read(Pr);
				nextChannel	= 1;
			break;
			case (1):
				ADC_Value_g = Analog.read(Pg);
				nextChannel	= 2;
			break;
			case (2):
				ADC_Value_b = Analog.read(Pb);
				nextChannel	= 0;
			break;
		}
	}
}

void PR5_Mode_OFF(void)
{
	RGB.setColor(0,0,0);
}

void PR5_Mode_SEQ(void)
{
	static int nextSequence = 10;
	switch(nextSequence)
	{
		case (10):
			RGB.setColor(255,0,0);
			nextSequence++;
		break;
		case (20):
			RGB.setColor(255,255,0);
			nextSequence++;
		break;
		case (30):
			RGB.setColor(0,255,0);
			nextSequence++;
		break;
		case (40):
			RGB.setColor(0,255,255);
			nextSequence++;
		break;
		case (50):
			RGB.setColor(0,0,255);
			nextSequence++;
		break;
		case (60):
			RGB.setColor(255,0,255);
			nextSequence = 0;
		break;
		default:
			nextSequence++;
	}
}

void PR5_Mode_ANALOG(void)
{
	if(!EXT_Mode_Active)
	{
		RGB.setColor(ADC_Value_r,ADC_Value_g,ADC_Value_b);
	}
}

void PR5_Function_handler(void)
{
	(*functionHandler)();
}

void PR5_Set_OFF_Mode(void)
{
	Serial.print("\r\n\r\nFunction Mode: Off \r\n\r\n>> ");
	functionHandler = PR5_Mode_OFF;
	PR5_current_Mode = PR5_MODE_OFF;
}

void PR5_Set_SEQ_Mode(void)
{
	Serial.print("\r\n\r\nFunction Mode: Sequence \r\n\r\n>> ");
	functionHandler = PR5_Mode_SEQ;
	PR5_current_Mode = PR5_MODE_SEQ;
}

void PR5_Set_ANALOG_Mode(void)
{
	Serial.print("\r\n\r\nFunction Mode: Analog \r\n\r\n>> ");
	functionHandler = PR5_Mode_ANALOG;
	PR5_current_Mode = PR5_MODE_ANALOG;
}

void PR5_Clear_Screen(void)
{
	PR5_Print_Header();
	Serial.print("\r\n>> ");								//Wait for command
}
