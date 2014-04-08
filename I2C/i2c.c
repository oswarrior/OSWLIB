/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 i2c.c
**  Description: I2C library functions definitions
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
** I2C includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/I2C/i2c.h"

/*
** ===================================================================
** I2C interrupt handlers
** ===================================================================
*/

static void (* near const _vect_I2C[])(void) @OSWarrior_ISR_I2CPort_Vector = {
		_OSWarrior_ISR_i2c_main
};

/*
** ===================================================================
** I2C variables declarations
** ===================================================================
*/

PRIVATE_DATA E_I2C_STATUS 	_OSWarrior_i2c_ctrl_step;	
PRIVATE_DATA E_DATA_DIR 	_OSWarrior_i2c_ctrl_direction; 		
PRIVATE_DATA T_UBYTE 		_OSWarrior_i2c_ctrl_dataLength;     

PRIVATE_DATA T_UBYTE 		_OSWarrior_i2c_write_index;
PRIVATE_DATA T_UBYTE 		_OSWarrior_i2c_write_buffer[16];

PRIVATE_DATA T_UBYTE 		_OSWarrior_i2c_read_index;
PRIVATE_DATA T_UBYTE 		_OSWarrior_i2c_read_next;
PRIVATE_DATA T_UBYTE 		_OSWarrior_i2c_read_buffer[16];

#ifdef __OSWarrior_DK__
	PRIVATE_DATA const int _OSWarrior_i2c_SCLdivider[64] = 
	{
		  20,   22,   24,   26,   28,   30,   34,   40,   28,   32,   36,   40,   44,   48,   56,   68,
		  48,   56,   64,   72,   80,   88,  104,  128,   80,   96,  112,  128,  144,  160,  192,  240,
		 160,  192,  224,  256,  288,  320,  384,  480,  320,  384,  448,  512,  576,  640,  768,  960,  
		 640,  768,  896, 1024, 1152, 1280, 1536, 1920, 1280, 1536, 1792, 2048, 2304, 2560, 3072, 3840
	};	
#endif
	
/*
** ===================================================================
** I2C Structure definition
** ===================================================================
*/

S_I2CSTR I2C = {
	0x1F, 
	100000,
	_OSWarrior_i2c_enable,
	_OSWarrior_i2c_start,
	_OSWarrior_i2c_send,
	_OSWarrior_i2c_end,
	_OSWarrior_i2c_requestFrom,
	_OSWarrior_i2c_available,
	_OSWarrior_i2c_read
};

/*
** ===================================================================
**     Function : I2C.enable
**     Handler  : _OSWarrior_i2c_enable
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

void _OSWarrior_i2c_enable(T_UBYTE address)
{
	#ifdef __OSWarrior_DK__
	{
		static T_UBYTE Freq;
		I2C_EN = I2C_ENABLED;		// Enable I2C
		I2C.address = address;		// IIC Address to structure
		I2C_ADD = address;			// IIC Address
		Freq = _OSWarrior_i2c_baud_calc(I2C.baudRate);	
		//I2C_FREQ = 0x4C;	
		I2C_FREQ = Freq;	
		_OSWarrior_i2c_ctrl_step = READY;
		I2C_IE = I2C_IE_EN;			// Enable IIC interrupts    
	}
	#endif
	
}

/*
** ===================================================================
**     Function : _OSWarrior_i2c_baud_calc
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
** 		Example: 
** 			BUSCLOCK = 4MHz, BR = 50kbps, mul = 2
** 			
**			( mul * SCLdivider ) =  4MHz / 50kbps
**			( mul * SCLdivider ) =  80
**			
**			SCLdivider = 80 / mul = 80 / 2
**			SCLdivider = 40
**			
**			SCLdivider = 40 ( ICR  = 0x07 ) --> 2 x 40 = 80 : IIC1F = 0x47
**			SCLdivider = 40 ( ICR  = 0x0B ) --> 2 x 40 = 80 : IIC1F = 0x4B
**     
**     Parameters  : 
**          address: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

T_UBYTE _OSWarrior_i2c_baud_calc(T_ULONG br)
{
	#ifdef __OSWarrior_DK__	
	{
		const T_UBYTE MULT = 0x01;
		const T_UBYTE mul = 2;
		register T_UBYTE ICR;
		T_UWORD SCLDivider = (T_UWORD)((BUSCLOCK/br)/mul);
		ICR = _OSWarrior_i2c_select_icr(SCLDivider);	
		return ((MULT << 6)|ICR);
	}
	#endif
}

/*
** ===================================================================
**     Function  : _OSWarrior_i2c_select_icr
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

T_UBYTE _OSWarrior_i2c_select_icr(T_UWORD SCLDivider)
{
	#ifdef __OSWarrior_DK__
	{
		register T_UBYTE i, I2C_SCLdivider_index = 0;
		int I2C_SCLdivider_diference_Array[64], I2C_SCLdivider_lastValue = 1000;
		
		for(i = 0; i < 64; i++)	
			I2C_SCLdivider_diference_Array[i] = absvalue(_OSWarrior_i2c_SCLdivider[i] - SCLDivider);
			
		for(i = 0; i < 64; i++)
		{
			if(I2C_SCLdivider_diference_Array[i] <= I2C_SCLdivider_lastValue)
			{
				I2C_SCLdivider_index = i;
				I2C_SCLdivider_lastValue = I2C_SCLdivider_diference_Array[i];
			}
		}
		return	I2C_SCLdivider_index;			
	}
	#endif
}

/*
** ===================================================================
**     Function : I2C.start
**     Handler  : _OSWarrior_i2c_start
**
**     Description :
**          Starts the transmission to the I2C slave device with the
**          given address, this function only send the start sequence
**          and the address byte, to add data to the message you must
**          use the send() function and the end() to complete the data 
**          transfer. 
**     
**     Parameters  : Nothing
**          slv_adr: Slave address to transmit data
**      
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_i2c_start (T_UBYTE slv_adr)
{
	_OSWarrior_i2c_write_index = 0;
	_OSWarrior_i2c_write_buffer[_OSWarrior_i2c_write_index] = slv_adr;
	_OSWarrior_i2c_write_index++;
}
	
/*
** ===================================================================
**     Function : I2C.send
**     Handler  : _OSWarrior_i2c_send
**
**     Description :
**          Adds a value to the message initiated by the start()
**          function, to complete the data transmission you must use
**          the end() function. 
**     
**     Parameters  : 
**          data   : A value to send as a single byte
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_i2c_send (T_UBYTE data)
{
	_OSWarrior_i2c_write_buffer[_OSWarrior_i2c_write_index] = data;
	_OSWarrior_i2c_write_index++;
}
				
/*
** ===========================================================================
**     Function : I2C.end
**     Handler  : _OSWarrior_i2c_end
**
**     Description :
**          Ends a transmission to a slave device that was begun by the 
**          start() function and transmit the bytes added by the send()
**          function. 
**     
**     Parameters  : Nothing
**     
**     Returns     : byte, which indicates the status of the transmission
** ===========================================================================
*/

void _OSWarrior_i2c_end(void)
{
	T_UBYTE Temp;
	_OSWarrior_i2c_ctrl_dataLength = _OSWarrior_i2c_write_index;
	_OSWarrior_i2c_write_index = 0;
	_OSWarrior_i2c_ctrl_step = HEADER_SENT;
	_OSWarrior_i2c_ctrl_direction = TRANSMIT;

	#ifdef __OSWarrior_DK__
	{
		I2C_EN = I2C_DISABLED;
		I2C_EN = I2C_ENABLED;
		Temp = I2C_STATUS;                                          /* Clear any pending interrupt */
		I2C_IF = I2C_CLR_IF;
		I2C_MODE = I2C_SLAVE;
		I2C_SRW = I2C_SLV_RX;
		I2C_TMODE = I2C_TRANSMIT;
		I2C_MODE = I2C_MASTER;                                      /* Select Master Mode (Send Start Bit) */
		for(Temp=0;Temp<3;Temp++);                                  /* Small delay */
		I2C_DATA = (_OSWarrior_i2c_write_buffer[_OSWarrior_i2c_write_index]<<1)&0xFE;   /* Send selected slave address */
		_OSWarrior_i2c_write_index++;
	}
	#endif
}

/*
** ===================================================================
**     Function : I2C.requestFrom
**     Handler  : _OSWarrior_i2c_requestFrom
**
**     Description :
**          This function is used by the master device to request 
**          bytes from a slave device.
**          The bytes will be retrieved with the available() and
**          read() functions.
**     
**     Parameters  : 
**          slv_adr: Slave device address to request bytes from
**          qty    : the number of bytes requested
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_i2c_requestFrom(T_UBYTE slv_adr, T_UBYTE numberOfBytes)
{
	T_UBYTE Temp;

	_OSWarrior_i2c_ctrl_dataLength = numberOfBytes;
	_OSWarrior_i2c_read_index = 0;
	_OSWarrior_i2c_read_next = 0;
	_OSWarrior_i2c_ctrl_step = HEADER_SENT;
	_OSWarrior_i2c_ctrl_direction = RECEIVE;

	#ifdef __OSWarrior_DK__
	{
		I2C_EN = I2C_DISABLED;
		I2C_EN = I2C_ENABLED;
		Temp = I2C_STATUS;                  	/* Clear any pending interrupt  */
		I2C_IF = I2C_CLR_IF;
		I2C_TMODE = I2C_TRANSMIT;
		I2C_MODE = I2C_MASTER;   
		for(Temp=0;Temp<3;Temp++);				/* Small delay */	
		I2C_DATA = ((slv_adr<<1)&0xFE)|0x01;  	/* Send selected slave address */
	}
	#endif
}

/*
** ===================================================================
**     Function : I2C.available
**     Handler  : _OSWarrior_i2c_available
**
**     Description :
**          This function returns the number of bytes available for 
**          retrieval with the I2C.read() function. 
**          This should be called on a master device after a call 
**          to requestFrom() or on a slave inside the 
**          I2C.onReceive() handler. 
**     
**     Parameters  : Nothing
**     
**     Returns     : The number of bytes available for reading
** ===================================================================
*/

T_UBYTE _OSWarrior_i2c_available(void)
{
	delay(5);
	return ((_OSWarrior_i2c_read_index)>(0)?(TRUE):(FALSE));
}

/*
** ===================================================================
**     Function : I2C.read
**     Handler  : _OSWarrior_i2c_read
**
**     Description :
**         Reads a byte that was requested by the request() function. 
**         
**     Parameters  : Nothing
**     
**     Returns     : The next byte received
** ===================================================================
*/

T_UBYTE _OSWarrior_i2c_read(void)
{
	T_UBYTE Temp;
	Temp = _OSWarrior_i2c_read_buffer[_OSWarrior_i2c_read_next];
	_OSWarrior_i2c_read_next++;
	_OSWarrior_i2c_read_index--;
	return Temp;
}
		
/*
** ===========================================================================
**     Function : I2C.onReceive
**     Handler  : _OSWarrior_i2c_onReceive
**
**     Description :
**          Registers a function to be called when a slave device 
**          receives a transmission from a master. 
**     
**     Parameters  :
**          handler: the function to be called when the slave receives data
**
**     Returns     : Nothing
** ===========================================================================
*/

void _OSWarrior_i2c_onReceive(void (*handler)(void))
{
	(*handler)();   
}
			
/*
** ===================================================================
**     Function : I2C.onRequest
**     Handler  : _OSWarrior_i2c_onRequest
**
**     Description :
**          Register a function to be called when a master requests 
**          data from this slave device. 
**     
**     Parameters  :  
**          handler: the function to be called
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_i2c_onRequest(void (*handler)(void))
{
	(*handler)();   
}

/*
** ===================================================================
**     Interrupt : _OSWarrior_ISR_i2c_main
**
**     Description :
**          An interruption from the IIC is generated when any of the
**          next three events occur:
**          1.- Complete 1-byte transfer
**          2.- Match of receiving call address
**          3.- Arbitration lost
**          The interrupt type can be determinate by reading the 
**          status register. 
**     
** ===================================================================
*/

__interrupt void _OSWarrior_ISR_i2c_main(void)
{    
	T_UBYTE Temp;     
	
	#ifdef __OSWarrior_DK__
	{
		Temp = I2C_STATUS;              
		I2C_IF = I2C_CLR_IF;
		if( I2C_ARBL == I2C_ARBL_LOST )			// Verify the Arbitration lost status  
		{        
			I2C_ARBL= 1;
			I2C_MODE = I2C_SLAVE;            	//Generate Stop Signal
			_OSWarrior_i2c_ctrl_step = ERROR;
			return;     
		}
		if( I2C_MODE == I2C_MASTER )
		{   
			_OSWarrior_i2c_master();         	//I2C as Master      
		}
		else
		{
			_OSWarrior_i2c_slave();				//I2C as Slave
		}	
	}
	#endif
}

/*
** ===================================================================
**     Function : _OSWarrior_i2c_master
**
**     Description :
**          Handle interruption vector when the device is configured
**          as master. 
**         
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_i2c_master(void)
{
	#ifdef __OSWarrior_DK__
	{

		/*
		** ==============================================================
		**  MASTER MODE OPERATION
		** ==============================================================
		*/
		T_UBYTE Temp;
	
		if( I2C_ACK == I2C_NO_ACK ){                    /* Verify if byte sent was ACK */    
			I2C_MODE = I2C_SLAVE;                       //Generate Stop Signal
			_OSWarrior_i2c_ctrl_step = ERROR;
			return;
		}
		/*
		** ==============================================================
		**  HEADER SENT STATUS
		** ==============================================================
		*/
		if( _OSWarrior_i2c_ctrl_step == HEADER_SENT ){       /* Header Sent */
			
			I2C_TMODE = (T_UBYTE)_OSWarrior_i2c_ctrl_direction;
			_OSWarrior_i2c_ctrl_step = DATA_TRANSMISSION; 
			
			if( I2C_TMODE == I2C_RECEIVE ){                         /* If we are reading data clock in first slave byte */
				Temp = I2C_DATA;
				return;
			}
		}
		/*
		** ==============================================================
		**  DATA TRANSMISSION STATUS
		** ==============================================================
		*/
		if( _OSWarrior_i2c_ctrl_step == DATA_TRANSMISSION ){             /* If byte transmission is in progress.*/
			
			if( I2C_TMODE == I2C_TRANSMIT ){
				/*
				** ==============================================================
				**  MASTER SENDING DATA TO SLAVE
				** ==============================================================
				*/
				
				//Serial.println("MASTER MODE OPERATION - SENDING DATA TO SLAVE");
				
				I2C_DATA = _OSWarrior_i2c_write_buffer[_OSWarrior_i2c_write_index];     /* Send the next byte */
				_OSWarrior_i2c_write_index++;
				if(_OSWarrior_i2c_ctrl_dataLength <= _OSWarrior_i2c_write_index){               
					_OSWarrior_i2c_ctrl_step = DATA_SENT;    /* Mark we are done sending Bytes */      
				}
				return; 
	
			}else{  
				/*
				** ==============================================================
				**  MASTER READING DATA FROM SLAVE
				** ==============================================================
				*/
							
				if( ( _OSWarrior_i2c_read_index ) == _OSWarrior_i2c_ctrl_dataLength )	I2C_TACK = I2C_NO_TACK;
				_OSWarrior_i2c_read_buffer[_OSWarrior_i2c_read_index] = I2C_DATA;     /* Send the next byte */
				_OSWarrior_i2c_read_index++;  
				if( _OSWarrior_i2c_ctrl_dataLength <= _OSWarrior_i2c_read_index ){                 
					_OSWarrior_i2c_ctrl_step = DATA_SENT;    /* Mark we are done sending Bytes */      
				}   
				return;                                 /* Return until next byte is read */
			}     
		}
		/*
		** ==============================================================
		**  DATA SENT STATUS
		** ==============================================================
		*/  
		if( _OSWarrior_i2c_ctrl_step == DATA_SENT )			/* We are done with the transmition.*/ 
		{         
			
			_OSWarrior_i2c_ctrl_step = READY;            	/* Reset our status flag            */
			Temp = I2C_STATUS;         		/* ACK the interrupt                */
			I2C_IF = I2C_CLR_IF;
			I2C_TMODE = (T_UBYTE)RECEIVE;
			I2C_SRW = I2C_SLV_RX;
			I2C_MODE = I2C_SLAVE;       	/* Generate a stop condition        */            
			return;
			
		}
	}
	#endif
}

/*
** ===================================================================
**     Function : _OSWarrior_i2c_slave
**
**     Description :
**          Handle interruption vector when the device is configured
**          as slave. 
**         
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_i2c_slave(void){
	/*************************/
	/*  Slave Mode Operation */  
	/*************************/
	#ifdef __OSWarrior_DK__
	{	
		T_UBYTE Temp;
	
		if(_OSWarrior_i2c_ctrl_step <= READY) 				/* If it is the first byte transmitted */
		{              
			_OSWarrior_i2c_ctrl_step = DATA_TRANSMISSION;
			I2C_TMODE = I2C_SRW;                        	/* Set the transmission reception status */
			_OSWarrior_i2c_write_index = 0;
			
			if( I2C_TMODE == I2C_RECEIVE )					/* If we are receiving data read IIC1D to get free bus and get the next byte */
			{
				Temp = I2C_DATA;
				return;
			}
		}
		
		if( I2C_TCF == I2C_TC_CPL )							/* Transmission complete */
		{                
			if( I2C_TMODE == I2C_RECEIVE )					/* If data is received store it on the buffer */
			{                       
				//I2C_DATA_BUFFER[_OSWarrior_i2c_write_index] = I2C_DATA;
				_OSWarrior_i2c_write_index++;
				return;          
			}
			else											/* Data sent by the slave */              
			{                                  
				if( I2C_ACK == I2C_NO_ACK )					/* Check for ACK */
				{        
					I2C_TMODE = I2C_RECEIVE;
					Temp = I2C_DATA;
					_OSWarrior_i2c_ctrl_step = READY;
					return;
				}
				//I2C_DATA = I2C_DATA_BUFFER[_OSWarrior_i2c_write_index];
				_OSWarrior_i2c_write_index++;
				return;          
			}
		}
	}
	#endif
}
