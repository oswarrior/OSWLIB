#ifndef OSWARRIOR_PCF8574_H_
	#define OSWARRIOR_PCF8574_H_


	/*
	** ===================================================================
	** Device addressing
	** ===================================================================
	*/	

	#define PCF8574_ADD0		    0x20	// Address if A2 = 0, A1 = 0 y A0 = 0
	#define PCF8574_ADD1		    0x21	// Address if A2 = 0, A1 = 0 y A0 = 1
	#define PCF8574_ADD2		    0x22	// Address if A2 = 0, A1 = 1 y A0 = 0
	#define PCF8574_ADD3		    0x23	// Address if A2 = 0, A1 = 1 y A0 = 1
	#define PCF8574_ADD4		    0x24	// Address if A2 = 1, A1 = 0 y A0 = 0
	#define PCF8574_ADD5		    0x25	// Address if A2 = 1, A1 = 0 y A0 = 1
	#define PCF8574_ADD6		    0x26	// Address if A2 = 1, A1 = 1 y A0 = 0
	#define PCF8574_ADD7		    0x27	// Address if A2 = 1, A1 = 1 y A0 = 1

	/*
	** ===================================================================
	** Function prototypes	
	** ===================================================================
	*/

	extern void _i2c_PCF8574_init(T_UBYTE);
	extern void _i2c_PCF8574_write(T_UBYTE);
	extern T_UBYTE _i2c_PCF8574_read(void);
	
	/*
	** ===================================================================
	** MCP4725 DAC Structure Definition
	** ===================================================================
	*/

	typedef struct{
		T_UBYTE address;
		void (*init)(T_UBYTE addr);	
		void (*write)(T_UBYTE);	
		T_UBYTE (*read)(void);	
	}PCF8574STR;	
	
	extern PCF8574STR PCF8574;

#endif
