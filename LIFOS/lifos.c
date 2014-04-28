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

S_SCISTR * LIFOS_Port;

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

void LIFOS(S_SCISTR * userSerialPort, T_ULONG br, E_FNC_METHOD method )
{
	LIFOS_Port = userSerialPort;
	LIFOS_Port->begin(br);
	if(method == ISR)	LIFOS_Port->onReceive = &LIFOS_eventListener;
}

/* Metodo por interrupcion en el puerto serial, llamar a LIFOS.ejecutar dentro de la funcion loop*/

void LIFOS_ISR_Listener(void)
{
	LIFOS_rx_pkg[LIFOS_rx_nxt] = LIFOS_Port->data;		//Save Data T_UBYTE
	LIFOS_rx_nxt++;										//Increment Counters						
	if(LIFOS_rx_nxt >= LIFOS_PKG_SIZE)					//Full Data Package Received
	{			
		LIFOS_pkg_decode(LIFOS_rx_pkg);					//Decode Data
		LIFOS_rx_nxt = 0;
	}
}

/* Metodo por polling del puerto serial, ejecutar dentro de la funcion loop*/

void LIFOS_POL_Listener(void)
{
	while(LIFOS_Port->available < LIFOS_PKG_SIZE);
	for(LIFOS_rx_nxt = 0; LIFOS_rx_nxt < LIFOS_PKG_SIZE; LIFOS_rx_nxt++)
	{
		LIFOS_rx_pkg[LIFOS_rx_nxt] = LIFOS_Port->read;
	}
	LIFOS_pkg_decode(LIFOS_rx_pkg);						//Decode Data
	LIFOS_rx_nxt = 0;
}

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

				LIFOS_pkg.CMD = package[1];							//CMD
				LIFOS_pkg.CH  = package[2] - 0x30;					//Channel
								
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
					/*	
					 * STATUS: OK 
					 * Action: Send Positive Response 
					 */
					LIFOS_pkg_encode(LIFOS_TX_DID, RSP_POSITIVE, (0xFF - LIFOS_pkg.CMD), readed_value);	
				}
				else
				{
					/*	
					 * STATUS: ERROR - Command not found 
					 */
					LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_CMD_NOTFOUND, 0);	
				}
			}
			else
			{
				/*	
				 * 	STATUS: ERROR - Checksum mismatch
				 * 	Action: Request message re-send 
				 */
				LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_CHK_MISM, 0);
			}
		}
		else
		{
			/*	
			 * 	STATUS: ERROR - Device ID Received incorrectly.
			 * 	Action: Clear buffer for error and request package re-send. 
			 */
			LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_WRNG_DID, 0);
		}		
	}
	else
	{
		/*	
		 * STATUS: ERROR - Slave Busy.
		 * Action: Send "Slave Busy" Message.
		 */
		LIFOS_pkg_encode(LIFOS_TX_DID, RSP_NEGATIVE, ERROR_SLV_BUSY, 0);
	}
	
}

void LIFOS_pkg_encode(T_UBYTE did, T_UBYTE rsp, T_UBYTE ack, int value_to_send)
{

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
	
	LIFOS_Port->write(LIFOS_tx_pkg);	
	
	LIFOS_busy = FALSE;								//Release Slave		
}
