#include "oswlib/Examples/Full_Demo/Full_Demo.h"

#include "oswlib/Examples/Full_Demo/Full_Demo_commands.h"
#include "oswlib/Examples/Full_Demo/Full_Demo_functions.h"

#include <string.h>

S_SCISTR * Demo_Full_Serial;

/*
** ===================================================================
** Function definitions	
** ===================================================================
*/

void example_Full_Demo_main(S_SCISTR * userSerialPort, T_ULONG br)
{	
	Demo_Full_Serial = userSerialPort;
	Demo_Full_Serial->init(br);
}

void example_Full_Demo_loop(void)
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
		Demo_Full_Serial->print("\f\r\n****************************************\r\n"); 
		Demo_Full_Serial->print("OSWarrior Demo\r\n");
		Demo_Full_Serial->print("Developed by: OSWarrior Team");
		Demo_Full_Serial->print("\r\n****************************************\r\n"); 
		Demo_Full_Serial->print("\r\nCommand List:\r\n");
		Demo_Full_Serial->print("----------------------\r\n");
	}
	
	/*
	** ===================================================================
	** Print Command List
	** ===================================================================
	*/
	
	{
		for(i = 0; i < OSWarrior_Demo_Total; i++)
		{
			Demo_Full_Serial->print(" ");		
			Demo_Full_Serial->print((T_UBYTE *)OSWarrior_Demo_List[i].CommandString);		
			Demo_Full_Serial->print(") ");		
			Demo_Full_Serial->print((T_UBYTE *)OSWarrior_Demo_List[i].function_name);		
			Demo_Full_Serial->print("\r\n");		
		}
	}

	/*
	** ===================================================================
	** Wait for user input
	** ===================================================================
	*/	

	Demo_Full_Serial->print("\r\nSelect function to execute: ");
	userSel = Demo_Full_Serial->read();	
	
	{
		CmdFound = FALSE;
		
		for(i=0; i < OSWarrior_Demo_Total;i++)
		{           
			if(strcmp(userSel,OSWarrior_Demo_List[i].CommandString) == 0)
			{
				Demo_Full_Serial->print("\r\n>> Example Running: ");
				Demo_Full_Serial->print((T_UBYTE *)OSWarrior_Demo_List[i].function_name);		
				
				OSWarrior_Demo_List[i].handler();
				
				CmdFound = TRUE;
				break;
			}             
		} 
		
		if(CmdFound == FALSE)
		{
			Demo_Full_Serial->print("\r\n>> Please select a valid command.");
		}
	}
	
	delay(1000);
}
