/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 oswarrior.c
* 	Description: OSWarrior Main library
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
** =============================================================================
**  							 LICENSE:
** =============================================================================
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the Attribution-ShareAlike
**  License as published by the Creative Commons Organization; either
**  version 3.0 of the License, or (at your option) any later version.
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
**  See the Attribution-ShareAlike License for more details.
**  You should have received a copy of the Creative Commons Attribution-ShareAlike 
**  License along with this library; if not send a email to the library author.
** =============================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/OSWarrior/oswarrior.h"
#include "oswlib/OSWarrior/delay.h"

#if defined(__OSWarrior_Micro__) || defined(__OSWarrior_DK__)

	/*
	** ===================================================================
	**     Function : COMPort_DefaultOnReceive
	**
	**     Description :
	**         This function is a dummy, only for avoid errors on Rx handler
	**     
	**     Parameters  : Nothing
	**     Returns     : Nothing
	** ===================================================================
	*/
	
	void OSWarrior_Clock_Settings(void)
	{
	
		#ifdef __OSWarrior_DK__
							
			/* Common initialization of the write once registers */			
			SOPT = (T_UBYTE)0x53U;
			SPMSC1 = (T_UBYTE)0x1CU;
			SPMSC2 = (T_UBYTE)0x00U;
			
			/* Enable Master Clock Output */
			SMCLK |= (T_UBYTE)0x14U;  			/* MCLK frequency = Bus Clock frequency / 4 */
			
			/*  System clock initialization */
			
			/* FEE Mode: External Crystal = 4 MHz, Bus Frequency = 20 MHz - Tested */
			ICGC1 = (T_UBYTE)0x78;   
			ICGC2 = (T_UBYTE)0x30;		
			
			/*  Self clock initialisation */
			//ICGC1 = 0x44U;	ICGC2 = 0x01U;	//ICGFLT = 0x0200U;		
			
			/* FEI Mode: No External Crystal Connection, 5.4MHz Bus Frequency - Tested */
			//ICGC1 = 0x28U;	ICGC2 = 0x31U;   
			
			/* FEI Mode: No External Crystal Connection, 15MHz Bus Frequency - Tested */
			//ICGC1 = 0x08U;	ICGC2 = 0x50U;  

			if (*(T_UBYTE*)0xFFBEU != 0xFFU)	/* Test if the device trim value is stored on the specified address */ 
				ICGTRM = *(T_UBYTE*)0xFFBEU;	/* Initialize ICGTRM register from a non volatile memory */
			
			while(ICGS1_LOCK == 0U) {}
			
		#endif
				
		oswarrior_enableDelays();
		
		__asm CLI;
	} 
		
#endif

/*
** ===================================================================
**     Function : COMPort_DefaultOnReceive
**
**     Description :
**         This function is a dummy, only for avoid errors on Rx handler
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/
	
void main(void)
{
	OSWarrior_Clock_Settings();
	setup();
	for(;;)	loop();
}

/*
** ===================================================================
**     Function : COMPort_DefaultOnReceive
**
**     Description :
**         This function is a dummy, only for avoid errors on Rx handler
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_Dummy_Fnc(void){
	return;
}
