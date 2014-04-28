#include "oswlib/LIFOS/lifos.h"
#include "oswlib/LIFOS/lifos_modules.h"
#include "oswlib/LIFOS/lifos_functions.h"
#include "oswlib/LIFOS/lifos_commands.h"

int lifos_printCMDList(T_UBYTE Channel, int Value)
{
	int i;
	(void) Value;
	(void) Channel;
	/* Insert print code here */
	for(i=0; i < LIFOS_CMD_LIST_LEN; i++)
	{     
		LIFOS_Port->write((T_UBYTE *)LIFOS_CMD_LIST[i].CMD_NAME);
		LIFOS_Port->write("\r\n");
	}
	return 0;
}

int lifos_pinDirection(T_UBYTE Channel, int Value)
{
	pinMode(Channel, Value);
	return 0;
}
int lifos_pinRead(T_UBYTE Channel, int Value)
{
	(void) Value;
	return digitalRead(Channel);
}
int lifos_pinWrite(T_UBYTE Channel, int Value)
{
	digitalWrite(Channel, Value);
	return 0;	
}
int lifos_pinToggle(T_UBYTE Channel, int Value)
{
	(void) Value;
	digitalToggle(Channel);	
	return 0;
}

int lifos_analogInit(T_UBYTE Channel, int Value)
{
	(void) Channel;
	(void) Value;
	Analog.init();
	Analog.setResolution(8);	
	return 0;
}
int lifos_analogEnable(T_UBYTE Channel, int Value)
{
	(void) Value;	
	Analog.enable(Channel);	
	return 0;
}
int lifos_analogDisable(T_UBYTE Channel, int Value)
{
	(void) Value;
	Analog.disable(Channel);	
	return 0;
}
int lifos_analogRead(T_UBYTE Channel, int Value)
{
	(void) Value;
	return Analog.read(Channel);	
}
int lifos_analogResolution(T_UBYTE Channel, int Value)
{
	(void) Channel;
	Analog.setResolution((T_UBYTE)Value);	
	return 0;
}

int lifos_servoEnable(T_UBYTE Channel, int Value)
{
	(void) Value;
	Servo.enable(Channel);	
	return 0;
}
int lifos_servoDisable(T_UBYTE Channel, int Value)
{
	(void) Value;
	Servo.disable(Channel);	
	return 0;
}
int lifos_servoRead(T_UBYTE Channel, int Value)
{
	(void) Value;
	return Servo.channel_pos[Channel];
}
int lifos_servoWrite(T_UBYTE Channel, int Value)
{
	Servo.setDegrees(Channel, Value);
	return 0;
}

int lifos_pwmEnable(T_UBYTE Channel, int Value)
{
	(void) Value;
	PWM.enable(Channel);
	return 0;
}

int lifos_pwmDisable(T_UBYTE Channel, int Value)
{
	(void) Value;
	PWM.disable(Channel);
	return 0;
}

int lifos_pwmRead(T_UBYTE Channel, int Value)
{
	(void) Value;
	return PWM.readDutyCycle(Channel);
}

int lifos_pwmWrite(T_UBYTE Channel, int Value)
{
	PWM.dutyCycle(Channel, Value);
	return 0;
}
