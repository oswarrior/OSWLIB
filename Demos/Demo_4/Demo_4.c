#include "oswlib/Demos/Demo_4/Demo_4.h"

#include "oswlib/Demos/Demo_4/Demo_4_commands.h"
#include "oswlib/Demos/Demo_4/Demo_4_functions.h"

#include <string.h>

S_SCISTR * Demo_4_Serial;

/*
** ===================================================================
** Function definitions	
** ===================================================================
*/

void Demo_4_main(S_SCISTR * userSerialPort, T_ULONG br)
{	
	Demo_4_Serial = userSerialPort;
	Demo_4_Serial->init(br);
}

void Demo_4_loop(void)
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
		Demo_4_Serial->write("\f\r\n****************************************\r\n"); 
		Demo_4_Serial->write("OSWarrior Example 4\r\n");
		Demo_4_Serial->write("Developed by: OSWarrior Team");
		Demo_4_Serial->write("\r\n****************************************\r\n"); 
		Demo_4_Serial->write("\r\nCommand List:\r\n");
		Demo_4_Serial->write("----------------------\r\n");
	}
	
	/*
	** ===================================================================
	** Print Command List
	** ===================================================================
	*/
	
	{
		for(i = 0; i < Demo_4_Total; i++)
		{
			Demo_4_Serial->write(" ");		
			Demo_4_Serial->write((T_UBYTE *)Demo_4_List[i].CommandString);		
			Demo_4_Serial->write(") ");		
			Demo_4_Serial->write((T_UBYTE *)Demo_4_List[i].function_name);		
			Demo_4_Serial->write("\r\n");		
		}
	}

	/*
	** ===================================================================
	** Wait for user input
	** ===================================================================
	*/	

	Demo_4_Serial->write("\r\nSelect function to execute: ");
	userSel = Demo_4_Serial->readString();	
	
	{
		CmdFound = FALSE;
		
		for(i=0; i < Demo_4_Total;i++)
		{           
			if(strcmp(userSel,Demo_4_List[i].CommandString) == 0)
			{
				Demo_4_Serial->write("\r\n>> Example Running: ");
				Demo_4_Serial->write((T_UBYTE *)Demo_4_List[i].function_name);		
				
				Demo_4_List[i].handler();
				
				CmdFound = TRUE;
				break;
			}             
		} 
		
		if(CmdFound == FALSE)
		{
			Demo_4_Serial->write("\r\n>> Please select a valid command.");
		}
	}
	
	delay(1000);
}
