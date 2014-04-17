#ifndef OSWARRIOR_MMA8451_H_
	#define OSWARRIOR_MMA8451_H_

	#define MMA8451_SA0_GND		    0x1C	// Address if A0 is connected to GND or not connected
	#define MMA8451_SA0_VCC		    0x1D 	// Address if A0 is connected to VCC

	#define MMA8451_WHO_AM_I		0x0D	// Writes data to the DAC
	
	#define MMA8451_OUT_X_MSB		0x01	// Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
	#define MMA8451_OUT_X_LSB		0x02	// Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
	
	#define MMA8451_OUT_Y_MSB		0x03	// Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
	#define MMA8451_OUT_Y_LSB		0x04	// Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
	
	#define MMA8451_OUT_Z_MSB		0x05	// Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
	#define MMA8451_OUT_Z_LSB		0x06	// Writes data to the DAC and the EEPROM (persisting the assigned value after reset)
	
	/*
	** ===================================================================
	** Function prototypes	
	** ===================================================================
	*/

	extern void _i2c_MMA8451_init(T_UBYTE addr);
	extern T_UBYTE _i2c_MMA8451_ID(void);
	
	/*
	** ===================================================================
	** MCP4725 DAC Structure Definition
	** ===================================================================
	*/

	typedef struct{
		T_UBYTE address;
		void (*init)(T_UBYTE addr);	
		T_UBYTE (*queryID)(void);	
	}MMA8451STR;	
	
	extern MMA8451STR MMA8451;

#endif
