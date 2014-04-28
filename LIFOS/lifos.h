#ifndef OSWARRIORMINI_LIFOS_H_
	#define OSWARRIORMINI_LIFOS_H_

	#include "oswlib/settings.h"
	#include "oswlib/LIFOS/lifos_modules.h"

	/*
	** ===================================================================
	** LIFOS constants
	** ===================================================================
	*/

	#define LIFOS_PKG_SIZE 		8u

	#define LIFOS_RX_DID		0x23		//DID - Device Receive Identifier  (0x35 ~ #)
	#define LIFOS_TX_DID		0x40		//DID - Device Receive Identifier  (0x40 ~ @)

	#define ERROR_SLV_BUSY 		0x41
	#define ERROR_WRNG_DID 		0x42
	#define ERROR_CHK_MISM 		0x43
	#define ERROR_CMD_NOTFOUND	0x44

	#define RSP_POSITIVE 		0x2B
	#define RSP_NEGATIVE 		0x2D

	/*
	** ===================================================================
	** LIFOS type definitions
	** ===================================================================
	*/

	typedef struct{
		T_UBYTE	DID;		//DID - Device Identifier
		T_UBYTE CMD;		//FC  - Function Code
		T_UBYTE	CH;			//CH  - Channel selected
		T_UBYTE	Data3;		//D3  - Data byte 3
		T_UBYTE	Data2;		//D2  - Data byte 2
		T_UBYTE	Data1;		//D1  - Data byte 1
		T_UBYTE	Data0;		//D0  - Data byte 0
		T_UBYTE	CHK;		//CHK - Checksum
	}S_LIFOS_RX_PKG;

	/*
    ** ===================================================================
    ** LIFOS functions prototypes
    ** ===================================================================
    */

	PUBLIC_FCT void LIFOS(S_SCISTR * userSerialPort, T_ULONG br);
	PUBLIC_FCT void LIFOS_ISR_Listener(void);
	PUBLIC_FCT void LIFOS_POL_Listener(void);
	PRIVATE_FCT void LIFOS_pkg_decode(T_UBYTE package[]);
	PRIVATE_FCT void LIFOS_pkg_encode(T_UBYTE did, T_UBYTE rsp, T_UBYTE ack, int value_to_send);
	
	/*
	** ===================================================================
	** LIFOS Structure declaration
	** ===================================================================
	*/
	PUBLIC_DATA S_SCISTR * LIFOS_Serial;
	PUBLIC_DATA S_LIFOS_RX_PKG LIFOS_pkg;

#endif
