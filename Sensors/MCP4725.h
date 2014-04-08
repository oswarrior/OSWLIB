/*
** 	Filename: WiiNunchuck.h
** 	Description: I2C communication with the Wii Nunchuck sensors
**
**	Author: Hugo Arganda (e.arganda.salazar@gmail.com)
** 	Current Version: 1.0
** 	Status: Development
**
**	CHANGE LOG:
**	Date: 10/09/2013 - Library created
**	
** 	LICENSE:
** 	This library is free software; you can redistribute it and/or
** 	modify it under the terms of the Attribution-ShareAlike
** 	License as published by the Creative Commons Organization; either
** 	version 3.0 of the License, or (at your option) any later version.
** 	This library is distributed in the hope that it will be useful,
** 	but WITHOUT ANY WARRANTY; without even the implied warranty of
** 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
** 	See the Attribution-ShareAlike License for more details.
** 	You should have received a copy of the Creative Commons Attribution-ShareAlike 
** 	License along with this library; if not send a email to the library author.
*/

#ifndef OSWARRIOR_MCP4725_H_
	#define OSWARRIOR_MCP4725_H_


	#define MCP4725_A0_GND		            0x62	// Address if A0 is connected to GND or not connected
	#define MCP4725_A0_VCC		            0x63 	// Address if A0 is connected to VCC

	#define MCP4725_CMD_WRITEDAC            0x40	// Writes data to the DAC
	#define MCP4725_CMD_WRITEDACEEPROM      0x60	// Writes data to the DAC and the EEPROM (persisting the assigned value after reset)

	/*
	** ===================================================================
	** Function prototypes	
	** ===================================================================
	*/

	extern void _i2c_MCP4725_init(T_UBYTE addr);
	extern void _i2c_MCP4725_setVoltage(T_ULONG output, T_BOOLEAN writeEEPROM);
	
	/*
	** ===================================================================
	** MCP4725 DAC Structure Definition
	** ===================================================================
	*/

	typedef struct{
		T_UBYTE address;
		void (*init)(T_UBYTE addr);	
		void (*setVoltage)( T_ULONG output, T_BOOLEAN writeEEPROM );	
	}MCP4725STR;	
	
	extern MCP4725STR MCP4725;

#endif
