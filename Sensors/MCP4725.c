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

#include "oswlib/settings.h"
#include "oswlib/I2C/i2c.h"
#include "oswlib/Sensors/MCP4725.h"

MCP4725STR MCP4725 = {
	MCP4725_A0_GND,
	_i2c_MCP4725_init, 		  
	_i2c_MCP4725_setVoltage, 		   
};

void _i2c_MCP4725_init(T_UBYTE addr)
{
	MCP4725.address = addr;
	I2C.enable(I2C.address);
	I2C.mode(I2C_FAST);
}

void _i2c_MCP4725_setVoltage( T_ULONG output, T_BOOLEAN writeEEPROM )
{
	I2C.start(MCP4725.address);	
	
	if (writeEEPROM)
	{
		//I2C.send(MCP4725_CMD_WRITEDACEEPROM);
	}
	else
	{
		//I2C.send(MCP4725_CMD_WRITEDAC);
	}
	
	I2C.send( (T_UBYTE)(0x000F & (output>>8)) );	// Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
	I2C.send( (T_UBYTE)(0x00FF & (output)) );  		// Lower data bits          (D3.D2.D1.D0.x.x.x.x)
	I2C.end();
}


