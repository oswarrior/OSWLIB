#include "oswlib/settings.h"
#include "oswlib/I2C/i2c.h"
#include "oswlib/Sensors/PCF8574.h"

PCF8574STR PCF8574 = {
	PCF8574_ADD0,
	_i2c_PCF8574_init, 		  
	_i2c_PCF8574_write, 		   
	_i2c_PCF8574_read, 		   
};

void _i2c_PCF8574_init(T_UBYTE addr)
{
	PCF8574.address = addr;
	I2C.enable(I2C.address);
	//I2C.mode(I2C_FAST);
}

void _i2c_PCF8574_write(T_UBYTE data)
{
	I2C.start(PCF8574.address);		
	I2C.send(data);
	I2C.end(1);
	return;
}

T_UBYTE _i2c_PCF8574_read( )
{

	I2C.requestFrom(PCF8574.address, 1);		
	
	if(I2C.available())
		return I2C.read();
	else
		return 0;
}


