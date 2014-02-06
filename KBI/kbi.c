/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 kbi.h
** 	Description: OSWarrior Keyboard interruptions library
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

/*
** ===================================================================
** KBI includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/KBI/kbi.h"

/*
** ===================================================================
** KBI interrupt handlers
** ===================================================================
*/

T_P_FUNCTION_VOID _OSWarrior_kbi_handlers[MAX_KBI_CHANNELS];

static void (* near const _vect_KBI[])(void) @OSWarrior_KBIPort_ISR_Vector = {
		_OSWarrior_kbi_isr_handler
};

/*
** ===================================================================
** KBI Macros
** ===================================================================
*/



/*
** ===================================================================
** KBI Structure definition
** ===================================================================
*/

S_KBISTR KBI = {
	_OSWarrior_kbi_attachInterrupt,
	_OSWarrior_kbi_detachInterrupt,
	_OSWarrior_Dummy_Fnc
};

/*
** ===================================================================
**     Function  : _OSWarrior_kbi_enable
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          address: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_kbi_enable(void)
{
	KBI_ACK = (T_UBYTE)0x01;	//Keyboard interrupt acknowledge
	KBI_MOD = (T_UBYTE)0x00;	//Edge-only detection
	KBI_IE  = (T_UBYTE)0x01;	//Keyboard interrupt enabled
}

/*
** ===================================================================
**     Function : KBI.stop
**     Handler  : _OSWarrior_kbi_stop
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          address: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_kbi_disable(void)
{
	KBI_IE = (T_UBYTE)0x00;	
	KBI_EN = (T_UBYTE)0x00;
}

/*
** ===================================================================
**     Function : KBI.enable
**     Handler  : _OSWarrior_kbi_enable
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          address: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_kbi_attachInterrupt(int pin, void (*handler)(void))
{
	//KBI.onPress = handler;
	
	switch(pin)
	{
		#if ( 0 < MAX_KBI_CHANNELS)	
			case_kbiEnable(0);
		#endif
		#if ( 1 < MAX_KBI_CHANNELS)	
			case_kbiEnable(1);
		#endif
		#if ( 2 < MAX_KBI_CHANNELS)	
			case_kbiEnable(2);
		#endif
		#if ( 3 < MAX_KBI_CHANNELS)	
			case_kbiEnable(3);
		#endif
		#if ( 4 < MAX_KBI_CHANNELS)	
			case_kbiEnable(4);
		#endif
		#if ( 5 < MAX_KBI_CHANNELS)	
			case_kbiEnable(5);
		#endif
		#if ( 6 < MAX_KBI_CHANNELS)	
			case_kbiEnable(6);
		#endif
		#if ( 7 < MAX_KBI_CHANNELS)	
			case_kbiEnable(7);
		#endif
	}
	if(KBI_EN)	_OSWarrior_kbi_enable();
}

/*
** ===================================================================
**     Function : KBI.disable
**     Handler  : _OSWarrior_kbi_disable
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          address: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_kbi_detachInterrupt(int pin)
{
	
	switch(pin)
	{
		#if ( 0 < MAX_KBI_CHANNELS)	
			case_kbiDisable(0);
		#endif
		#if ( 1 < MAX_KBI_CHANNELS)	
			case_kbiDisable(1);
		#endif
		#if ( 2 < MAX_KBI_CHANNELS)	
			case_kbiDisable(2);
		#endif
		#if ( 3 < MAX_KBI_CHANNELS)	
			case_kbiDisable(3);
		#endif
		#if ( 4 < MAX_KBI_CHANNELS)	
			case_kbiDisable(4);
		#endif
		#if ( 5 < MAX_KBI_CHANNELS)	
			case_kbiDisable(5);
		#endif
		#if ( 6 < MAX_KBI_CHANNELS)	
			case_kbiDisable(6);
		#endif
		#if ( 7 < MAX_KBI_CHANNELS)	
			case_kbiDisable(7);
		#endif
	}
	if(!KBI_EN)	_OSWarrior_kbi_disable();
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_ISR_KBI
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          address: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

__interrupt void _OSWarrior_kbi_isr_handler(void)
{
	KBI_ACK = 1;
	KBI.onPress();
}
