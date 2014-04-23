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

static void (* near const _vect_I2C[])(void) @OSWarrior_ISR_I2CPort_Vector = { _OSWarrior_ISR_i2c_main };

/*
** ===================================================================
** I2C variables declarations
** ===================================================================
*/

/* Globals to be shared throughout the project */
PRIVATE_DATA I2C_BUFFER i2c_tx_buffer;
PRIVATE_DATA I2C_BUFFER i2c_rx_buffer;

/* Globals for this file only */
PRIVATE_DATA T_UBYTE stop_condition;
PRIVATE_DATA T_UBYTE master_mode;
PRIVATE_DATA T_UBYTE master_tx_done;

PRIVATE_DATA T_UBYTE _OSWarrior_i2c_read_next = 0;

/*
** ===================================================================
** I2C Structure definition
** ===================================================================
*/

S_I2CSTR I2C = {
	0x1F, 
	_OSWarrior_i2c_enable,
	_OSWarrior_i2c_mode,
	_OSWarrior_i2c_start,
	_OSWarrior_i2c_send,
	_OSWarrior_i2c_end,
	_OSWarrior_i2c_requestFrom,
	_OSWarrior_i2c_available,
	_OSWarrior_i2c_read
};

void _OSWarrior_i2c_enable(T_UBYTE address)
{
	#ifdef __OSWarrior_DK__
	{
		I2C_EN = I2C_ENABLED;		//OK
		I2C.address = address;		//OK
		I2C_ADD = address;			//OK
		I2C_FREQ = I2C_STANDARD;	//OK
	}
	#endif
	
}

void _OSWarrior_i2c_mode(T_UBYTE mode)
{
	#ifdef __OSWarrior_DK__
	{
		I2C_FREQ = mode;			//OK
	}
	#endif
}

void _OSWarrior_i2c_start (T_UBYTE slv_adr)
{
	i2c_tx_buffer.tx_index = 0;		//OK
	i2c_tx_buffer.buf[i2c_tx_buffer.tx_index++] = slv_adr;		//OK
}

void _OSWarrior_i2c_send (T_UBYTE data)
{
	i2c_tx_buffer.buf[i2c_tx_buffer.tx_index++] = data;			//OK
}

void _OSWarrior_i2c_end(T_BOOLEAN stop)
{
	
	#ifdef __OSWarrior_DK__
	{
		
		//while (IIC1S & IIC1S_BUSY_MASK);
		
		stop_condition = (T_UBYTE)stop;		//OK
		
		master_mode = I2C_TX;
		//master_tx_done = FALSE;

		/* Reset index for TX and RX buffers */
		i2c_tx_buffer.length = i2c_tx_buffer.tx_index - 1;
		
		i2c_tx_buffer.tx_index = 0;
		
		I2C_EN = I2C_DISABLED;			
		I2C_EN = I2C_ENABLED;
		
		I2C_TMODE = I2C_TRANSMIT;
		I2C_ST_CMD;
		I2C_IE = I2C_IE_EN;
						
		/* Put target address into IBDR */
		IIC1D = ( 0 | (i2c_tx_buffer.buf[i2c_tx_buffer.tx_index++]<<1) | master_mode);
		
		/* Wait for I2SR[IBB] (bus busy) to be set */
		//while (!(IIC1S & IIC1S_BUSY_MASK));

		/* Wait for bus to become free before continuing */
		//while (IIC1S & IIC1S_BUSY_MASK);
		
		/* Restore module to it's idle (but active) state */
		//IIC1C |= IIC1C_IICIE_MASK;

		return;
		
	}
	#endif
}

void _OSWarrior_i2c_requestFrom(T_UBYTE slv_adr, T_UBYTE numberOfBytes)
{	
	T_UBYTE Temp;

	#ifdef __OSWarrior_DK__
	{
		stop_condition = 1;

		i2c_rx_buffer.length = numberOfBytes;
		
		master_mode = I2C_RX;
		master_tx_done = FALSE;

    	/* Reset index for TX and RX buffers */
		_OSWarrior_i2c_read_next = 0;
    	i2c_tx_buffer.tx_index = 0;
    	i2c_rx_buffer.rx_index = 0;

    	//while (IIC1S & IIC1S_BUSY_MASK);
    	
		/* Reset index for TX and RX buffers */
	
		I2C_EN = I2C_DISABLED;			
		I2C_EN = I2C_ENABLED;
		
		I2C_TMODE = I2C_TRANSMIT;
		
		I2C_ST_CMD;
		
		for(Temp=0;Temp<3;Temp++);				/* Small delay */	

		/* Put target address into IBDR */
		I2C_DATA = ((slv_adr<<1)&0xFE)|0x01;
		
		/* Wait for I2SR[IBB] (bus busy) to be set */
		//while (!(IIC1S & IIC1S_BUSY_MASK));

		/* Wait for bus to become free before continuing */
		//while (IIC1S & IIC1S_BUSY_MASK);
		
		/* Restore module to it's idle (but active) state */
		//IIC1C |= IIC1C_IICIE_MASK;
		
		return;
		
	}
	#endif
}

T_UBYTE _OSWarrior_i2c_available(void)
{
	delay(1);
	return ((i2c_rx_buffer.rx_index)>(0)?(TRUE):(FALSE));
}

T_UBYTE _OSWarrior_i2c_read(void)
{	
	T_UBYTE temp = i2c_rx_buffer.buf[_OSWarrior_i2c_read_next++];
	
	i2c_rx_buffer.rx_index--;

	if(i2c_rx_buffer.rx_index == 0) _OSWarrior_i2c_read_next = 0;
		
	return temp; 
}

void _OSWarrior_i2c_onReceive(void (*handler)(void))
{
	(*handler)();   
}

void _OSWarrior_i2c_onRequest(void (*handler)(void))
{
	(*handler)();   
}

__interrupt void _OSWarrior_ISR_i2c_main(void)
{    
	#ifdef __OSWarrior_DK__
	{
		
		 /* Clear the I2C Interrupt Flag. */
		//IIC1S &= (T_UBYTE) ~IIC1S_IICIF_MASK;
		
		(void)I2C_STATUS;         				/* ACK the interrupt                */
		I2C_IF = I2C_CLR_IF;
		
		if( IIC1C & IIC1C_MST_MASK )
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

void _OSWarrior_i2c_master(void)
{
	/*
	** ==============================================================
	**  MASTER MODE OPERATION
	** ==============================================================
	*/
	
	#ifdef __OSWarrior_DK__
	{

		/* Master Mode - Check if this device is in Transmit or Receive Mode. */
		if (IIC1C & IIC1C_TX_MASK)
		{
	   		/* Master Transmit Mode - Check if last byte was tranmitted. */
	    	if ( (i2c_tx_buffer.length == 0) && (master_mode != I2C_RX) )
	    	{
				if(stop_condition == 1) I2C_SP_CMD;	/* Generate a stop condition        */            
				else I2C_RS_CMD;						/* Generate a repeated start condition */
	    	}
	    	else
	    	{
				/* More bytes to be transmitted - Check if ACK received. */
				if (I2C_ACK == I2C_NO_ACK)
				{
		    		/* ACK not received - Generate STOP */
					I2C_SP_CMD;
				}
				else
				{
		    		/* Check if end of address cycle */
		    		if (master_mode == I2C_RX)
		    		{
		    			/* Switch to RX Mode */
		    			I2C_TMODE = I2C_RECEIVE;
		    			/* Dummy read from IICD */
		    			(void)I2C_DATA;
		    		}
		    		/* ACK received, send data */
		    		else
		    		{
						/* Not end of address cycle - Write next byte to MBDR */
		    			IIC1D = i2c_tx_buffer.buf[i2c_tx_buffer.tx_index++];
						i2c_tx_buffer.length--;
		    		}
				}
	    	} 
		}
		else
		{
	    	/* Master Receive Mode - Check if this is last byte to be read. */	    
	    	if (i2c_rx_buffer.length == 1)
	    	{
				/* Last byte to be read - 
				   Generate Stop signal by changing to Slave Mode. */
	    		I2C_SP_CMD;
	    	}
	    	else
	    	{
				/* Not last byte to be read - Check if second to last byte. */
				if (i2c_rx_buffer.length == 2)
				{
		    		/* Second to last byte to be read - Set Transmit Acknowledge Enable
		    		   bit so no ACK is sent after the next byte is received, which
		    		   indicates "end of data" to the slave. */
		    		I2C_TACK = I2C_NO_TACK;
				}
	    	}

	    	/* Store received data in RX buffer */
	    	i2c_rx_buffer.buf[i2c_rx_buffer.rx_index++] = I2C_DATA;
	    	i2c_rx_buffer.length--;
		} 
	}
	#endif
}

void _OSWarrior_i2c_slave(void)
{
	/*************************/
	/*  Slave Mode Operation */  
	/*************************/
	#ifdef __OSWarrior_DK_I2C_SLAVE__
	{	
		/* Slave Mode - Check if Arbitration Lost. */
				if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IAL)
				{
			    	#ifdef DEBUG
			         	printf("Arbitration Lost.\n");
		            #endif

			    	/* Clear IAL bit */
			    	MCF5282_I2C_I2SR &= ~MCF5282_I2C_I2SR_IAL;
			    
			    	/* Arbitration Lost - Check if this device is being addressed as slave.
			    	   (If not, nothing more needs to be done.) */
			    	if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IAAS)
			    	{
						/* Addressed as slave - 
						   Check if master was reading from slave or writing to slave. */
						if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_SRW)
						{
				    		/* Set tx_index to 0 */
				    		i2c_tx_buffer.tx_index = 0;
				    
				    		/* Master was reading from slave - Set Transmit Mode. */
				    		MCF5282_I2C_I2CR |= MCF5282_I2C_I2CR_MTX;
				    
				    		/* Write data to MBDR. */
				    		MCF5282_I2C_I2DR = i2c_tx_buffer.buf[i2c_tx_buffer.tx_index++];

				    		#ifdef DEBUG
				         		printf("Arbitration Lost: Addressed as slave - TX mode.\n");
		                    #endif
						}
						else
						{
				    		/* Set rx_index to 0 */
				    		i2c_rx_buffer.rx_index = 0;
				    
				    		/* Master was writing to slave - Set Receive Mode. */
				    		MCF5282_I2C_I2CR &= ~MCF5282_I2C_I2CR_MTX;
				    
				    		/* Dummy read from MBDR, to clear the ICF bit. */
				    		dummy_read = MCF5282_I2C_I2DR;
				    
				    		#ifdef DEBUG
				         		printf("Arbitration Lost: Addressed as slave - RX mode.\n");
		                    #endif
						}
			    	}	    
				}
				else
				{
			    	/* Arbitration Not Lost - Check if data byte is this devices's Slave Address byte. */
			    	if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_IAAS)
			    	{
						/* Data byte is Slave Address byte - Check Slave Read/Write bit. */
						if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_SRW)
						{
				    		/* Set tx_index to 0 */
				    		i2c_tx_buffer.tx_index = 0;
				    
				    		/* Master was reading from slave - Set Transmit Mode. */
				    		MCF5282_I2C_I2CR |= MCF5282_I2C_I2CR_MTX;
				    
				    		/* Write data to MBDR. */
				    		MCF5282_I2C_I2DR = i2c_tx_buffer.buf[i2c_tx_buffer.tx_index++];

				    		#ifdef DEBUG
				         		printf("Slave TX: First byte - 0x%02X\n",i2c_tx_buffer.buf[i2c_tx_buffer.tx_index-1]);
		                    #endif
						}
						else
						{
				    		/* Master has specified Slave Receive Mode.
				    		   Set Receive Mode.  (Writing to MBCR clears IAAS.) */
				    
				    		/* Set rx_index to 0 */
				    		i2c_rx_buffer.rx_index = 0;
				    
				    		MCF5282_I2C_I2CR &= ~MCF5282_I2C_I2CR_MTX;
				    
				    		/* Read address data from MBDR and store it. */
				    		dummy_read = MCF5282_I2C_I2DR;

				    		#ifdef DEBUG
				         		printf("Slave RX: Receive address.\n");
		                    #endif
						}
			    	}
			    	else
			    	{
						/* Data byte received is not Slave Address byte - 
				   		   Check if this device is in Transmit or Receive Mode. */
						if (MCF5282_I2C_I2CR & MCF5282_I2C_I2CR_MTX)
						{
				    		/* Last byte received? */
				    		if (MCF5282_I2C_I2SR & MCF5282_I2C_I2SR_RXAK)
				    		{
								MCF5282_I2C_I2CR &= ~MCF5282_I2C_I2CR_MTX;
								dummy_read = MCF5282_I2C_I2DR;

								#ifdef DEBUG
					     			printf("Slave TX: Last byte has been sent.\n");
		                        #endif
				    		}
				    		else
				    		{
								/* Write data to MBDR. */
								MCF5282_I2C_I2DR = i2c_tx_buffer.buf[i2c_tx_buffer.tx_index++];
								i2c_tx_buffer.length--;

								#ifdef DEBUG
					     			printf("Slave TX: Send byte - 0x%02X\n",i2c_tx_buffer.buf[i2c_tx_buffer.tx_index-1]);
		                        #endif
				    		}
						}
						else
						{
				    		/* Receive Mode - Read data from MBDR and store it. */
				    		i2c_rx_buffer.buf[i2c_rx_buffer.rx_index++] = MCF5282_I2C_I2DR;
				    		i2c_rx_buffer.length++;
				    		i2c_rx_buffer.data_present = TRUE;

				    		#ifdef DEBUG
				         		printf("Slave RX: Receive byte - 0x%02X\n",i2c_rx_buffer.buf[i2c_rx_buffer.rx_index-1]);
		                    #endif
						}
			    	}
				}
	}
	#endif
}
