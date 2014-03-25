#include "oswlib/Demos/Demo_1/Demo_1.h"

#include "oswlib/Demos/Demo_1/Demo_1_commands.h"
#include "oswlib/Demos/Demo_1/Demo_1_functions.h"

#include <string.h>

S_SCISTR * Demo_1_Serial;

/*
** ===================================================================
** Function definitions	
** ===================================================================
*/

void Demo_1_main(S_SCISTR * userSerialPort, T_ULONG br)
{	
	Demo_1_Serial = userSerialPort;
	Demo_1_Serial->init(br);
}

void Demo_1_loop(void)
{	
	register T_UBYTE i;
	T_UBYTE * userSel;
	T_BOOLEAN CmdFound;
		
	/*
	** ===================================================================
	** Print Header
	** ===================================================================
	*/
	
	{
		Demo_1_Serial->write("\f\r\n****************************************\r\n"); 
		Demo_1_Serial->write("OSWarrior Example 1\r\n");
		Demo_1_Serial->write("Developed by: OSWarrior Team");
		Demo_1_Serial->write("\r\n****************************************\r\n"); 
		Demo_1_Serial->write("\r\nCommand List:\r\n");
		Demo_1_Serial->write("----------------------\r\n");
	}
	
	/*
	** ===================================================================
	** Print Command List
	** ===================================================================
	*/
	
	{
		for(i = 0; i < Demo_1_Total; i++)
		{
			Demo_1_Serial->write(" ");		
			Demo_1_Serial->write((T_UBYTE *)Demo_1_List[i].CommandString);		
			Demo_1_Serial->write(") ");		
			Demo_1_Serial->write((T_UBYTE *)Demo_1_List[i].function_name);		
			Demo_1_Serial->write("\r\n");		
		}
	}

	/*
	** ===================================================================
	** Wait for user input
	** ===================================================================
	*/	

	Demo_1_Serial->write("\r\nSelect function to execute: ");
	userSel = Demo_1_Serial->readString();	
	
	{
		CmdFound = FALSE;
		
		for(i=0; i < Demo_1_Total;i++)
		{           
			if(strcmp(userSel,Demo_1_List[i].CommandString) == 0)
			{
				Demo_1_Serial->write("\r\n>> Example Running: ");
				Demo_1_Serial->write((T_UBYTE *)Demo_1_List[i].function_name);		
				
				Demo_1_List[i].handler();
				
				CmdFound = TRUE;
				break;
			}             
		} 
		
		if(CmdFound == FALSE)
		{
			Demo_1_Serial->write("\r\n>> Please select a valid command.");
		}
	}
	
	delay(1000);
}
