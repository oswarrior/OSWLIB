/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 i2c.h
**  Description: OSWarrior I2C library functions declarations
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**  Date: 27/03/2013 - 	Revision 1, planned for release 3.0.
**  Date: 08/05/2013 - 	Added interrupt vector declaration.
**  Date: 13/05/2013 - 	Added master mode capability.
**  Date: 14/05/2013 - 	Added OSWarrior data structure.
**  Date: 18/05/2013 - 	Removed interrupt vector declaration.
**  Date: 18/05/2013 - 	Added interrupt service function.
**  Date: 23/06/2013 - 	Library re-structured.
**  Date: 24/06/2013 - 	Typical IIC Interrupt Routine added.
**  Date: 28/07/2013 - 	Library backup for IIC interruption routine.
**  Date: 07/09/2013 - 	Fixed several errors in transmission, reception stills in development.
**  Date: 18/10/2013 -  Added enum typedef for the control variable I2C_STEP
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

#ifndef OSWARRIOR_I2C_H_

    #define OSWARRIOR_I2C_H_    

	#ifdef __OSWarrior_DK__
		#define I2C_STANDARD	0x59		/* 100 kbps */
		#define I2C_FAST		0x03		/* 400 kbps */
	#endif

	/* I2C parameters */
	#define I2C_BUFFER_SIZE		(50)
	#define I2C_TXRX			(2)
	#define I2C_TX				(0)
	#define	I2C_RX				(1)

	#define I2C_ST_COND			(2)
	#define I2C_SP_COND			(1)
	#define I2C_RS_COND			(0)

	#define I2C_ST_CMD			(I2C_MODE = I2C_MASTER)
	#define I2C_SP_CMD			(I2C_MODE = I2C_SLAVE)
	#define I2C_RS_CMD			(IIC1C_RSTA = 1)

	/* Driver-specific defines */
	// Use polling instead of interrupt-driven transfers
	#undef POLLING_MODE
	// Use debug prints to view byte level transfers via COM port
	#define DEBUG

    /*
	** ===================================================================
	** I2C type definitions
	** ===================================================================
	*/
	
	typedef enum
	{
		ERROR = 0,
		READY,
		HEADER_SENT,
		DATA_TRANSMISSION,
		DATA_SENT		
	}E_I2C_STATUS;	
	
	typedef struct{
		T_UBYTE address;
		void (*enable)(T_UBYTE);
		void (*mode)(T_UBYTE);
		void (*start)(T_UBYTE);
		void (*send)(T_UBYTE);
		void (*end)(T_BOOLEAN);
		void (*requestFrom)(T_UBYTE, T_UBYTE);
		T_UBYTE (*available)(void);
		T_UBYTE (*read)(void);
	}S_I2CSTR;
	
	typedef struct {
	    int tx_index;						/* TX index */
	    int rx_index;						/* RX index */
	    int data_present;					/* Data present flag */
	    T_ULONG length;						/* Length of the buffer in bytes */
	    T_UBYTE buf[I2C_BUFFER_SIZE];		/* Data buffer */
	} I2C_BUFFER;
    
    /*
    ** ===================================================================
    ** I2C related interrupt function handlers
    ** ===================================================================
    */
    
    PUBLIC_FCT __interrupt void _OSWarrior_ISR_i2c_main(void);
    
    /*
    ** ===================================================================
    ** I2C functions prototypes
    ** ===================================================================
    */
    
    PUBLIC_FCT void 	_OSWarrior_i2c_enable(T_UBYTE address);
    PUBLIC_FCT void 	_OSWarrior_i2c_mode(T_UBYTE mode);
    //PUBLIC_FCT T_UBYTE 	_OSWarrior_i2c_baud_calc(T_ULONG br);
    //PUBLIC_FCT T_UBYTE 	_OSWarrior_i2c_select_icr(T_UWORD SCLDivider);
    
    PUBLIC_FCT void _OSWarrior_i2c_start(T_UBYTE slv_adr);
    PUBLIC_FCT void _OSWarrior_i2c_send (T_UBYTE value);
    PUBLIC_FCT void _OSWarrior_i2c_end(T_BOOLEAN stop);

    PUBLIC_FCT void 	_OSWarrior_i2c_requestFrom(T_UBYTE slv_adr, T_UBYTE numberOfBytes);
    PUBLIC_FCT T_UBYTE 	_OSWarrior_i2c_available(void);
    PUBLIC_FCT T_UBYTE 	_OSWarrior_i2c_read(void);
    
    PUBLIC_FCT void _OSWarrior_i2c_onReceive(void (*handler)(void));
    PUBLIC_FCT void _OSWarrior_i2c_onRequest(void (*handler)(void));
    
    PUBLIC_FCT void _OSWarrior_i2c_master(void);
    PUBLIC_FCT void _OSWarrior_i2c_slave(void);
    
    /*
    ** ===================================================================
    ** I2C Structure declaration
    ** ===================================================================
    */

	PUBLIC_DATA S_I2CSTR I2C;

#endif	/* OSWARRIORMINI_I2C_H_ */
