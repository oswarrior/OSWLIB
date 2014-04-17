#include "oswlib/settings.h"
#include "oswlib/I2C/i2c.h"
#include "oswlib/Sensors/MMA8451.h"

MMA8451STR MMA8451 = {
	MMA8451_SA0_GND,
	_i2c_MMA8451_init, 		  
	_i2c_MMA8451_ID, 		   
};

void _i2c_MMA8451_init(T_UBYTE addr)
{
	MMA8451.address = addr;
	I2C.enable(I2C.address);
	//I2C.mode(I2C_FAST);
}

T_UBYTE _i2c_MMA8451_ID( )
{
	T_UBYTE temp = 0;
	
	I2C.start(MMA8451.address);		
	I2C.send( (T_UBYTE) MMA8451_WHO_AM_I );	// Upper data bits          (D11.D10.D9.D8.D7.D6.D5.D4)
	I2C.end(0);
	
	//for(j = 0; j < 250; j++);
	
	I2C.requestFrom(MMA8451.address, 2);
	
	while(I2C.available())	temp = (T_UBYTE)I2C.read();
	
	return temp;
}


