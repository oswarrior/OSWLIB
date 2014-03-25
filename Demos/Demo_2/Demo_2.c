#include "oswlib/Demos/Demo_2/Demo_2.h"

#include "oswlib/Demos/Demo_2/Demo_2_commands.h"
#include "oswlib/Demos/Demo_2/Demo_2_functions.h"

#include <string.h>

S_SCISTR * Demo_2_Serial;

/*
** ===================================================================
** Function definitions	
** ===================================================================
*/

void Demo_2_main(S_SCISTR * userSerialPort, T_ULONG br)
{	
	Demo_2_Serial = userSerialPort;
	Demo_2_Serial->init(br);
}

void Demo_2_loop(void)
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
		Demo_2_Serial->write("\f\r\n****************************************\r\n"); 
		Demo_2_Serial->write("OSWarrior Example 2\r\n");
		Demo_2_Serial->write("Developed by: OSWarrior Team");
		Demo_2_Serial->write("\r\n****************************************\r\n"); 
		Demo_2_Serial->write("\r\nCommand List:\r\n");
		Demo_2_Serial->write("----------------------\r\n");
	}
	
	/*
	** ===================================================================
	** Print Command List
	** ===================================================================
	*/
	
	{
		for(i = 0; i < Demo_2_Total; i++)
		{
			Demo_2_Serial->write(" ");		
			Demo_2_Serial->write((T_UBYTE *)Demo_2_List[i].CommandString);		
			Demo_2_Serial->write(") ");		
			Demo_2_Serial->write((T_UBYTE *)Demo_2_List[i].function_name);		
			Demo_2_Serial->write("\r\n");		
		}
	}

	/*
	** ===================================================================
	** Wait for user input
	** ===================================================================
	*/	

	Demo_2_Serial->write("\r\nSelect function to execute: ");
	userSel = Demo_2_Serial->readString();	
	
	{
		CmdFound = FALSE;
		
		for(i=0; i < Demo_2_Total;i++)
		{           
			if(strcmp(userSel,Demo_2_List[i].CommandString) == 0)
			{
				Demo_2_Serial->write("\r\n>> Example Running: ");
				Demo_2_Serial->write((T_UBYTE *)Demo_2_List[i].function_name);		
				
				Demo_2_List[i].handler();
				
				CmdFound = TRUE;
				break;
			}             
		} 
		
		if(CmdFound == FALSE)
		{
			Demo_2_Serial->write("\r\n>> Please select a valid command.");
		}
	}
	
	delay(1000);
}
