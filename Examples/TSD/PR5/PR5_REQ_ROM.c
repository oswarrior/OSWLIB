#include "oswlib/settings.h"

#include "oswlib/Serial/serial.h"

#include "oswlib/Examples/TSD/PR5/PR5_UART.h"
#include "oswlib/Examples/TSD/PR5/PR5_REQ_ROM.h"

#include <string.h>

/*
** ===================================================================
** List of commands
** ===================================================================
*/

S_PR5_REQ_ROM_MENU_TYPE PR5_REQ_ROM_menu_list[] = {
	{"OFF", PR5_Set_OFF_Mode, "Select Off Mode"},
	{"SEQ", PR5_Set_SEQ_Mode, "Select Sequence Mode" },
	{"ANALOG", PR5_REQ_ROM_ANALOG_Mode, "Select Analog Mode" },
	{"CLS", PR5_Clear_Screen, "Clear Screen" }
};

#define PR5_MENU_TOTAL  (sizeof(PR5_REQ_ROM_menu_list)/sizeof(S_PR5_REQ_ROM_MENU_TYPE))

/*
** ===================================================================
** Init function
** ===================================================================
*/

void PR5_REQ_ROM(void)
{
	Serial.init(9600);
	Serial.onReceive = PR5_REQ_ROM_Listener;				//Add Event listener
	Serial.print("\r\n>> ");								//Wait for command
}

/*
** ===================================================================
** PR5 Listener
** ===================================================================
*/

PRIVATE_DATA T_UBYTE PR5_REQ_ROM_rx_pkg[16];
PRIVATE_DATA T_UBYTE PR5_REQ_ROM_rx_nxt = 0;

void PR5_REQ_ROM_Listener(void)
{	
	if(Serial.data == 'R')
	{
		Serial.printChar(Serial.data);							//Echo Char
		PR5_REQ_ROM_print_menu();								//Print Menu
		Serial.print("\r\n>> ");								//Wait for command
	}
	else if(Serial.data == '\b')
	{
		Serial.printChar(Serial.data);							//Echo Char
		PR5_REQ_ROM_rx_nxt--;
	}
	else if(Serial.data != '\r')
	{
		Serial.printChar(Serial.data);							//Echo Char
		PR5_REQ_ROM_rx_pkg[PR5_REQ_ROM_rx_nxt] = Serial.data;	//Save Char
		PR5_REQ_ROM_rx_nxt++;
	}
	else
	{
		PR5_REQ_ROM_rx_pkg[PR5_REQ_ROM_rx_nxt] = 0x00;			//Array End
		PR5_REQ_ROM_find_command(PR5_REQ_ROM_rx_pkg);			//Decode Command
		PR5_REQ_ROM_rx_nxt = 0;
	}
}

/*
** ===================================================================
** Print Command List
** ===================================================================
*/

void PR5_REQ_ROM_print_menu(void)
{
	register T_UBYTE i;
	
	Serial.print("\r\n\r\n******************************************\r\n"); 
	Serial.print(" Command List\r\n");
	Serial.print("******************************************\r\n\r\n"); 
	
	for(i = 0; i < PR5_MENU_TOTAL; i++)
	{
		Serial.print("");		
		Serial.print((T_UBYTE *)PR5_REQ_ROM_menu_list[i].CommandString);		
		Serial.print("\t --> ");		
		Serial.println((T_UBYTE *)PR5_REQ_ROM_menu_list[i].function_name);		
	}
}

/*
** ===================================================================
** Find function to execute
** ===================================================================
*/

void PR5_REQ_ROM_find_command(T_UBYTE * userSel)
{	
	register T_UBYTE i;
	T_BOOLEAN CmdFound;

	CmdFound = FALSE;
	
	for(i=0; i < PR5_MENU_TOTAL; i++)
	{     
		if(strcmp(userSel, PR5_REQ_ROM_menu_list[i].CommandString) == 0)
		{
			PR5_REQ_ROM_menu_list[i].handler();						//Execute Command
			CmdFound = TRUE;
			break;
		}             
	}               
	
	if(CmdFound == FALSE)
	{
		Serial.print("\r\n\r\n>> Please select a valid command. \r\n\r\n>> ");
	}
}

void PR5_REQ_ROM_ANALOG_Mode(void)
{
	PR5_Set_ANALOG_Mode();
	
	Serial.print("\r --> Lr D.C. = ");
	Serial.printNum(map(ADC_Value_r,0,255,0,100));
	Serial.println("%");
	
	Serial.print(" --> Lg D.C. = ");
	Serial.printNum(map(ADC_Value_g,0,255,0,100));
	Serial.println("%");
	
	Serial.print(" --> Lb D.C. = ");
	Serial.printNum(map(ADC_Value_b,0,255,0,100));
	Serial.println("%");
	
	Serial.print("\r\n>> ");								//Wait for command
}
