#include "oswlib/Demos/Demo_3/Demo_3.h"

#include "oswlib/Demos/Demo_3/Demo_3_commands.h"
#include "oswlib/Demos/Demo_3/Demo_3_functions.h"

#include <string.h>

S_SCISTR * Demo_3_Serial;

/*
** ===================================================================
** Function definitions	
** ===================================================================
*/

void Demo_3_main(S_SCISTR * userSerialPort, T_ULONG br)
{	
	Demo_3_Serial = userSerialPort;
	Demo_3_Serial->init(br);
}

void Demo_3_loop(void)
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
		Demo_3_Serial->write("\f\r\n****************************************\r\n"); 
		Demo_3_Serial->write("OSWarrior Example 3\r\n");
		Demo_3_Serial->write("Developed by: OSWarrior Team");
		Demo_3_Serial->write("\r\n****************************************\r\n"); 
		Demo_3_Serial->write("\r\nCommand List:\r\n");
		Demo_3_Serial->write("----------------------\r\n");
	}
	
	/*
	** ===================================================================
	** Print Command List
	** ===================================================================
	*/
	
	{
		for(i = 0; i < Demo_3_Total; i++)
		{
			Demo_3_Serial->write(" ");		
			Demo_3_Serial->write((T_UBYTE *)Demo_3_List[i].CommandString);		
			Demo_3_Serial->write(") ");		
			Demo_3_Serial->write((T_UBYTE *)Demo_3_List[i].function_name);		
			Demo_3_Serial->write("\r\n");		
		}
	}

	/*
	** ===================================================================
	** Wait for user input
	** ===================================================================
	*/	

	Demo_3_Serial->write("\r\nSelect function to execute: ");
	userSel = Demo_3_Serial->readString();	
	
	{
		CmdFound = FALSE;
		
		for(i=0; i < Demo_3_Total;i++)
		{           
			if(strcmp(userSel,Demo_3_List[i].CommandString) == 0)
			{
				Demo_3_Serial->write("\r\n>> Example Running: ");
				Demo_3_Serial->write((T_UBYTE *)Demo_3_List[i].function_name);		
				
				Demo_3_List[i].handler();
				
				CmdFound = TRUE;
				break;
			}             
		} 
		
		if(CmdFound == FALSE)
		{
			Demo_3_Serial->write("\r\n>> Please select a valid command.");
		}
	}
	
	delay(1000);
}
