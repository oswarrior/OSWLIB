/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 lifos.c
**  Description: LabVIEW Interface for OSWarrior functions definitions
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
** =============================================================================
**  							 LICENSE:
** =============================================================================
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the Attribution-ShareAlike
**  License as published by the Creative Commons Organisation; either
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
** LIFOS includes
** ===================================================================
*/

#include "oswlib/settings.h"

#include "oswlib/LIFOS/lifos_modules.h"
#include "oswlib/LIFOS/lifos_functions.h"
#include "oswlib/LIFOS/lifos_commands.h"

#include "oswlib/LIFOS/lifos.h"

/*
** ===================================================================
** LIFOS variables declarations
** ===================================================================
*/

PRIVATE_DATA const T_UBYTE digits[] =  {"0123456789-"};

PRIVATE_DATA T_UBYTE	LIFOS_rx_pkg[LIFOS_PKG_SIZE];
PRIVATE_DATA T_UBYTE  	LIFOS_tx_pkg[(LIFOS_PKG_SIZE + 1)];

PRIVATE_DATA T_UBYTE  	LIFOS_rx_nxt = 0;
PRIVATE_DATA T_BOOLEAN 	LIFOS_busy = FALSE;

/*
** ===================================================================
** I2C Structure definition
** ===================================================================
*/

S_LIFOS_RX_PKG LIFOS_pkg = {0, 0, 0, 0, 0, 0, 0, 0 };

S_SCISTR * LIFOS_Serial;

/*
** ===================================================================
**     Function : LIFOS
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void LIFOS(S_SCISTR * userSerialPort, T_ULONG br)
{
	LIFOS_Serial = userSerialPort;
	LIFOS_Serial->begin(br);
	LIFOS_Serial->write("\fNew LIFOS Library test - T3");
	LIFOS_Serial->onReceive = &LIFOS_eventListener;
}

/*
** ===================================================================
**     Function : LIFOS
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void LIFOS_eventListener(void)
{
	LIFOS_rx_pkg[LIFOS_rx_nxt] = LIFOS_Serial->data;	//Save Data T_UBYTE
	LIFOS_rx_nxt++;										//Increment Counters						
		
	if(LIFOS_rx_nxt >= LIFOS_PKG_SIZE)					//Full Data Package Received
	{			
		LIFOS_pkg_decode(LIFOS_rx_pkg);					//Process Data
		LIFOS_rx_nxt = 0;
	}
}

/*
** ===================================================================
**     Function : LIFOS_pkg_decode
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          package: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

void LIFOS_pkg_decode(T_UBYTE package[])
{
	
	register T_UBYTE i = 0;
	register T_UBYTE LIFOS_rx_clc_chk = 0;							//CHK - Checksum (Calculated)
	
	T_BOOLEAN CmdFound = FALSE;
	int write_value = 0;	
	int readed_value = 0;		
		
	if(!LIFOS_busy)
	{
		LIFOS_busy = TRUE;											//Make Slave Busy														
		
		LIFOS_pkg.DID = package[0];									//DID - PKG[0]
		
		if(LIFOS_pkg.DID == LIFOS_RX_DID)							// DID correct
		{							

			LIFOS_pkg.CHK = package[7];								//Received CHK - PKG[7]
			for(i = 0; i < 7;i++)	
				LIFOS_rx_clc_chk += package[i];						//Calculated CHK
			
			if(LIFOS_rx_clc_chk == LIFOS_pkg.CHK)					//CHK Correct
			{				

				LIFOS_pkg.CMD = package[1];			//CMD
				LIFOS_pkg.CH = package[2] - 0x30;					//Channel
								
				for(i=0; i < LIFOS_CMD_LIST_LEN; i++)
				{     
					if( LIFOS_pkg.CMD == LIFOS_CMD_LIST[i].CMD )
					{
						if(LIFOS_CMD_LIST[i].TYPE == WOM)
						{
							LIFOS_pkg.Data3 = package[3] - 0x30;	//Value bytes
							LIFOS_pkg.Data2 = package[4] - 0x30;
							LIFOS_pkg.Data1 = package[5] - 0x30;
							LIFOS_pkg.Data0 = package[6] - 0x30;
							write_value += LIFOS_pkg.Data0;			//Value calculation
							write_value += LIFOS_pkg.Data1 * 10;
							write_value += LIFOS_pkg.Data2 * 100;
							write_value += LIFOS_pkg.Data3 * 1000;							
						}
						
						readed_value = LIFOS_CMD_LIST[i].FNC(LIFOS_pkg.CH, write_value);	//Execute Command
						CmdFound = TRUE;
						break;
					}             
				} 
				
				if(CmdFound == TRUE)
				{
					/*	OK, Action: Send Positive Response */
					LIFOS_pkg_encode(LIFOS_TX_DID, RSP_POSITIVE, (0xFF - LIFOS_pkg.CMD), readed_value);	
				}
				else
				{
					/*	ERROR, Action: Send Command not found Message */
					LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_CMD_NOTFOUND, 0);	
				}
			}
			else
			{
				/*	ERROR: Checksum mismatch, Action: Request message re-send */
				LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_CHK_MISM, 0);
			}
		}
		else
		{
			/*	ERROR: Device ID Received incorrectly, Action: Clear buffer for error and request package re-send */
			LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_WRNG_DID, 0);
		}		
	}
	else
	{
		/*	ERROR: The slave is busy, Action: Send "Slave Busy" Message */
		LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_SLV_BUSY, 0);
	}
	
}

/*
** ===================================================================
**     Function : LIFOS_pkg_encode
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : 
**          value_to_send	: Device address when used as slave
**     
**     Returns     : Nothing
** ===================================================================
*/

void LIFOS_pkg_encode(T_UBYTE did, T_UBYTE rsp, T_UBYTE ack, int value_to_send){

	register int i = 0;
	T_UBYTE th = 0, h = 0, t = 0, u = 0, aux_h = 0, aux_t = 0;
	
	T_UBYTE LIFOS_tx_pkg_chk;			//CHK - Calculated TX Checksum		

	if(value_to_send != 0)				//Calculate value to send
	{				
		th = (T_UBYTE)(value_to_send/1000);
		aux_h = (T_UBYTE)(value_to_send%1000);
		h = (T_UBYTE)(aux_h/100);
		aux_t = (T_UBYTE)(aux_h%100);
		t = (T_UBYTE)(aux_t/10);
		u = (T_UBYTE)(aux_t%10);
	}
		
	LIFOS_tx_pkg[0] = did;		//DID - Device Identifier
	LIFOS_tx_pkg[1] = rsp;		//RSP - Response
	LIFOS_tx_pkg[2] = ack;		//ARC - Acknowledge for Requested Checksum
	LIFOS_tx_pkg[3] = digits[th];	//Data to send
	LIFOS_tx_pkg[4] = digits[h];
	LIFOS_tx_pkg[5] = digits[t];
	LIFOS_tx_pkg[6] = digits[u];
		
	for(LIFOS_tx_pkg_chk = 0; i < 7; i++)	LIFOS_tx_pkg_chk += LIFOS_tx_pkg[i];	

	LIFOS_tx_pkg[7] = LIFOS_tx_pkg_chk;
	LIFOS_tx_pkg[8] = ASCII_NULL;
	
	LIFOS_Serial->write(LIFOS_tx_pkg);	
	
	LIFOS_busy = FALSE;								//Release Slave	
	
}
