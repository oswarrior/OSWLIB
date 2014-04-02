/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 oswarrior_mini.h
** 	Description: OSWarrior Micro pin-out definition
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Version 2.0 freeze
**	Date: 28/03/2012 - PWM status and control registers bug fixed
**	Date: 24/06/2013 - Pin-out updated
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

/***
 	 	
 	 	***************************************************************************
 	 	************************** 	  OSWARRIOR MICRO	***************************
 	 	************************** 		PIN DIAGRAM		***************************
 	 	***************************************************************************

 	 	 	 	 	 		---------------------------------------
							!									  !	
 		D0 	[Rx1]		----! PTE1							PTD2  !----	D23	[A7] [KBI5]
		D1 	[Tx1]		----! PTE0							PTD3  !----	D22	[A6] [KBI4]
		D2	[PWM0]		----! PTE2							PTD1  !----	D21	[A5]
		D3	[PWM1]		----! PTE3							PTD0  !----	D20	[A4]
		D4	[SS]		----! PTE4							PTB3  !----	D19	[A3]
		D5	[MISO]		----! PTE5							PTB2  !----	D18	[A2]
		D6	[MOSI]		----! PTE6							PTB1  !----	D17	[A1] [PWM6]
		D7	[SCK]		----! PTE7							PTB0  !----	D16	[A0] [PWM7]
							!									  !	
		D8	[PWM2]		----! PTF0								  !	
		D9	[PWM3]		----! PTF1							N/C	  !----	VIN
		D10	[PWM4]		----! PTF4							GND	  !----	GND
		D11	[PWM5][LED0]----! PTF5							GND	  !----	GND
		D12	[KBI0]		----! PTG0							VDD	  !----	5V
		D13	[KBI1]		----! PTG1							N/C	  !----	3.3V
		VREFL			----! VREFL							RESET !----	RESET
		VREFH			----! VREFH							VDDAD !----	VDDAD
		D14 [SCL]		----! PTC0							VSSAD !----	VSSAD
		D15 [SDA]		----! PTC1								  !
							!									  !	
 	 	 	 	 	 		!  		!-------!					  !
 	 	 	 	 	 		!		!		!					  !
 	 	 	 	 	 		!		! USB-B	!					  !
 	 	 	 	 	 		--------!		!----------------------
 	 	 	 	 	 				---------

***/

#ifdef __OSWarrior_Micro__ 

#ifndef OSWARRIOR_MICRO_PINOUT_H_
	#define OSWARRIOR_MICRO_PINOUT_H_

	/*
	** ===================================================================
	** OSWarrior Micro - I/O mapping
	** ===================================================================
	*/

	#include <oswlib/OSWarrior/pinout/variants/mc9s08ac48.h>

	/*
	** ===================================================================
	** OSWarrior Micro - Device Parameters
	** ===================================================================
	*/
	
	#define DEVICE_ID                 34
	#define MAX_DIGITAL_PINS 	      24
	#define MAX_ANALOG_PINS 	       8
	#define MAX_ONBOARD_LEDS 	       1
	#define MAX_PWM_CHANNELS 		   8
	#define MAX_BUSFREQ			20000000	//20MHz - Max Bus Frequency
	#define BUSCLOCK			 4000000	//4MHz - Bus Frequency
	#define BUSSPEED			 8000000	//8MHz - Bus Speed

	/*
	** ===================================================================
	** Digital pin macro definitions
	** ===================================================================
	*/
	
	#define	D0 		PTED_PTED1		//Digital pin 0	 [SCI1 - Tx]
	#define	D1 		PTED_PTED0		//Digital pin 1	 [SCI1 - Rx]
	#define	D2 		PTED_PTED2		//Digital pin 2	 [PWM0]
	#define	D3		PTED_PTED3		//Digital pin 3	 [PWM1]
	#define	D4 		PTED_PTED4		//Digital pin 4	 [SPI - SS signal]
	#define	D5 		PTED_PTED5		//Digital pin 5	 [SPI - MISO signal]
	#define	D6 		PTED_PTED6		//Digital pin 6	 [SPI - MOSI signal]
	#define	D7 		PTED_PTED7		//Digital pin 7	 [SPI - SCK signal]
	
	#define	D8 		PTFD_PTFD0		//Digital pin 8	 [PWM2]
	#define	D9 		PTFD_PTFD1		//Digital pin 9	 [PWM3]
	#define	D10 	PTFD_PTFD4		//Digital pin 10 [PWM4]
	#define	D11 	PTFD_PTFD5		//Digital pin 11 [PWM5]
	#define	D12 	PTGD_PTGD0		//Digital pin 12 [KBI0]
	#define	D13 	PTGD_PTGD1		//Digital pin 13 [KBI1]
	#define	D14 	PTCD_PTCD0		//Digital pin 14 [KBI2]
	#define	D15 	PTCD_PTCD1		//Digital pin 15 [KBI3]

	#define	D16 	PTBD_PTBD0		//Digital pin 16 [*PWM7]
	#define	D17 	PTBD_PTBD1		//Digital pin 17 [*PWM6]
	#define	D18 	PTBD_PTBD2		//Digital pin 18
	#define	D19		PTBD_PTBD3		//Digital pin 19
	#define	D20 	PTDD_PTDD0		//Digital pin 20
	#define	D21 	PTDD_PTDD1		//Digital pin 21
	#define	D22 	PTDD_PTDD3		//Digital pin 22 [KBI5]
	#define	D23 	PTDD_PTDD2		//Digital pin 23 [KBI6]

	/*
	** ===================================================================
	** Digital pin data direction macro definitions
	** ===================================================================
	*/

	#define	D0_DD 	PTEDD_PTEDD1	//Digital pin 0 data direction
	#define	D1_DD 	PTEDD_PTEDD0	//Digital pin 1 data direction
	#define	D2_DD 	PTEDD_PTEDD2	//Digital pin 2 data direction
	#define	D3_DD	PTEDD_PTEDD3	//Digital pin 3 data direction
	#define	D4_DD 	PTEDD_PTEDD4	//Digital pin 4 data direction
	#define	D5_DD 	PTEDD_PTEDD5	//Digital pin 5 data direction
	#define	D6_DD 	PTEDD_PTEDD6	//Digital pin 6 data direction
	#define	D7_DD 	PTEDD_PTEDD7	//Digital pin 7 data direction

	#define	D8_DD 	PTFDD_PTFDD0	//Digital pin 8 data direction
	#define	D9_DD 	PTFDD_PTFDD1	//Digital pin 9 data direction
	#define	D10_DD 	PTFDD_PTFDD4	//Digital pin 10 data direction
	#define	D11_DD 	PTFDD_PTFDD5	//Digital pin 11 data direction
	#define	D12_DD 	PTGDD_PTGDD0	//Digital pin 12 data direction
	#define	D13_DD 	PTGDD_PTGDD1	//Digital pin 13 data direction
	#define	D14_DD 	PTCDD_PTCDD0	//Digital pin 14 data direction
	#define	D15_DD 	PTCDD_PTCDD0	//Digital pin 15 data direction
	
	#define	D16_DD 	PTBDD_PTBDD0	//Digital pin 16 data direction
	#define	D17_DD 	PTBDD_PTBDD1	//Digital pin 17 data direction
	#define	D18_DD 	PTBDD_PTBDD2	//Digital pin 18 data direction
	#define	D19_DD	PTBDD_PTBDD3	//Digital pin 19 data direction
	#define	D20_DD 	PTDDD_PTDDD0	//Digital pin 20 data direction
	#define	D21_DD 	PTDDD_PTDDD1	//Digital pin 21 data direction
	#define	D22_DD 	PTDDD_PTDDD3	//Digital pin 22 data direction
	#define	D23_DD 	PTDDD_PTDDD2	//Digital pin 23 data direction

	/*
	** ===================================================================
	** Digital pin pull-up enable macro definitions
	** ===================================================================
	*/

	#define	D0_PE 	PTEPE_PTEPE1	//Digital pin 0 Pull-Up Enable
	#define	D1_PE 	PTEPE_PTEPE0	//Digital pin 1 Pull-Up Enable
	#define	D2_PE 	PTEPE_PTEPE2	//Digital pin 2 Pull-Up Enable
	#define	D3_PE	PTEPE_PTEPE3	//Digital pin 3 Pull-Up Enable
	#define	D4_PE 	PTEPE_PTEPE4	//Digital pin 4 Pull-Up Enable
	#define	D5_PE 	PTEPE_PTEPE5	//Digital pin 5 Pull-Up Enable
	#define	D6_PE 	PTEPE_PTEPE6	//Digital pin 6 Pull-Up Enable
	#define	D7_PE 	PTEPE_PTEPE7	//Digital pin 7 Pull-Up Enable
	
	#define	D8_PE 	PTFPE_PTFPE0	//Digital pin 8 Pull-Up Enable
	#define	D9_PE 	PTFPE_PTFPE1	//Digital pin 9 Pull-Up Enable
	#define	D10_PE 	PTFPE_PTFPE4	//Digital pin 10 Pull-Up Enable
	#define	D11_PE 	PTFPE_PTFPE5	//Digital pin 11 Pull-Up Enable
	#define	D12_PE 	PTGPE_PTGPE0	//Digital pin 12 Pull-Up Enable
	#define	D13_PE 	PTGPE_PTGPE1	//Digital pin 13 Pull-Up Enable
	#define	D14_PE 	PTCPE_PTCPE0	//Digital pin 14 Pull-Up Enable
	#define	D15_PE 	PTCPE_PTCPE0	//Digital pin 15 Pull-Up Enable
	
	#define	D16_PE 	PTBPE_PTBPE0	//Digital pin 16 Pull-Up Enable
	#define	D17_PE 	PTBPE_PTBPE1	//Digital pin 17 Pull-Up Enable
	#define	D18_PE 	PTBPE_PTBPE2	//Digital pin 18 Pull-Up Enable
	#define	D19_PE	PTBPE_PTBPE3	//Digital pin 19 Pull-Up Enable
	#define	D20_PE 	PTDPE_PTDPE0	//Digital pin 20 Pull-Up Enable
	#define	D21_PE 	PTDPE_PTDPE1	//Digital pin 21 Pull-Up Enable
	#define	D22_PE 	PTDPE_PTDPE3	//Digital pin 22 Pull-Up Enable
	#define	D23_PE 	PTDPE_PTDPE2	//Digital pin 23 Pull-Up Enable
	
	/**
	** ===================================================================
	**	NOTE: 	
	**	The PWM channels 6 and 7 are only available if not using the 
	**	delay library or LCD library (this due to the LCD library uses 
	**	delay functions).
	**	In order to use the PWM channels 6 or/and 7 execute the function 
	**	oswarrior_disableDelays() before and be sure to dont use delays 
	**	after that or the PWM channels will be unconfigured.
	** ===================================================================
	**/
	/*
	** ===================================================================
	** LEDx - Onboard Digital Output-Only LEDs - Macro Definitions
	** ===================================================================
	*/

	#define ONBOARDLED_OFFSET	100
	#define	LED0 				100				//Onboard LED0 - Pin ID
	#define	LED0_R 				D11				//Onboard LED0	
	#define	LED0_DD				D11_DD			//Onboard LED0 data direction
	
	/*
	** ===================================================================
	** Analog to Digital Converter (ADC) Configuration Registers
	** ===================================================================
	*/

	#define ADC_LOW_PWR			0x90			//ADC Low Power Mode
	#define ADC_HIGH_SPEED		0x00			//ADC High Speed Mode

	#define ADC_RES_10			0x08			//ADC 10-Bits Resolution
	#define ADC_RES_8			0x00			//ADC 8-Bits Resolution

	#define ADC_CFG				ADC1CFG			//ADC Configuration Register
	#define ADC_CH_SEL			ADC1SC1_ADCH	//ADC Channel Select
	#define ADC_COCO			ADC1SC1_COCO	//ADC Conversion Complete Flag
	#define ADC_VALUE			ADC1R			//ADC Conversion Complete Flag
	
	enum ADC_CHANNELS{ A0 = 0, A1 = 1, A2 = 2, A3 = 3, A4 = 4, A5 = 5, A6 = 6, A7 = 7 };
	
	const uint8_t ADC_CH[8] = {
		0,	// A0		D16		PTB0		AD1P0
		1,	// A1		D17		PTB1		AD1P1	
		2,	// A2		D18		PTB2		AD1P2	
		3,	// A3		D19		PTB3		AD1P3
		8,	// A4		D20		PTD0		AD1P8	
		9,	// A5		D21		PTD1		AD1P9	
		10,	// A6		D22		PTD2		AD1P10
		11	// A7		D23		PTD3		AD1P11
	};

	/*
	** ===================================================================
	** Pulse Width Modulation (PWM) Configuration Registers
	** ===================================================================
	*/
		
	#define	PWM0		0		//PWM Port - Channel 0
	#define PWM1		1		//PWM Port - Channel 1
	#define PWM2		2		//PWM Port - Channel 2
	#define PWM3		3		//PWM Port - Channel 3
	#define PWM4		4		//PWM Port - Channel 4
	#define PWM5		5		//PWM Port - Channel 5
	#define PWM6		6		//PWM Port - Channel 6
	#define PWM7		7		//PWM Port - Channel 7
	#define NO_PWM		0xFF	//Not a PWM Port
	
	#define	PWM0_V		TPM1C0V		//PWM Port - Channel 0 - Value Register
	#define PWM1_V		TPM1C1V		//PWM Port - Channel 1 - Value Register
	#define PWM2_V		TPM1C2V		//PWM Port - Channel 2 - Value Register
	#define PWM3_V		TPM1C3V		//PWM Port - Channel 3 - Value Register
	#define PWM4_V		TPM2C0V		//PWM Port - Channel 4 - Value Register
	#define PWM5_V		TPM2C1V		//PWM Port - Channel 5 - Value Register
	#define PWM6_V		TPM3C1V		//PWM Port - Channel 6 - Value Register
	#define PWM7_V		TPM3C0V		//PWM Port - Channel 7 - Value Register

	#define PWM0_SC		TPM1C0SC	//PWM Port - Channel 0 - Status and Control Register
	#define PWM1_SC		TPM1C1SC	//PWM Port - Channel 0 - Status and Control Register
	#define PWM2_SC		TPM1C2SC	//PWM Port - Channel 0 - Status and Control Register
	#define PWM3_SC		TPM1C3SC	//PWM Port - Channel 0 - Status and Control Register
	#define PWM4_SC		TPM2C0SC	//PWM Port - Channel 0 - Status and Control Register
	#define PWM5_SC		TPM2C1SC	//PWM Port - Channel 0 - Status and Control Register
	#define PWM6_SC		TPM3C1SC	//PWM Port - Channel 0 - Status and Control Register
	#define PWM7_SC		TPM3C0SC	//PWM Port - Channel 0 - Status and Control Register

	#define TPM0_SC		TPM1SC		//PWM Port - Channel 0 - Module Status and Control Register
	#define TPM1_SC		TPM1SC		//PWM Port - Channel 0 - Module Status and Control Register
	#define TPM2_SC		TPM1SC		//PWM Port - Channel 0 - Module Status and Control Register
	#define TPM3_SC		TPM1SC		//PWM Port - Channel 0 - Module Status and Control Register
	#define TPM4_SC		TPM2SC		//PWM Port - Channel 0 - Module Status and Control Register
	#define TPM5_SC		TPM2SC		//PWM Port - Channel 0 - Module Status and Control Register
	#define TPM6_SC		TPM3SC		//PWM Port - Channel 0 - Module Status and Control Register
	#define TPM7_SC		TPM3SC		//PWM Port - Channel 0 - Module Status and Control Register

	#define TPM0_MOD 	TPM1MOD		//PWM Port - Channel 0 - Modulo Register
	#define TPM1_MOD 	TPM1MOD		//PWM Port - Channel 1 - Modulo Register
	#define TPM2_MOD 	TPM1MOD		//PWM Port - Channel 2 - Modulo Register
	#define TPM3_MOD 	TPM1MOD		//PWM Port - Channel 3 - Modulo Register
	#define TPM4_MOD 	TPM2MOD		//PWM Port - Channel 4 - Modulo Register
	#define TPM5_MOD 	TPM2MOD		//PWM Port - Channel 5 - Modulo Register
	#define TPM6_MOD 	TPM3MOD		//PWM Port - Channel 6 - Modulo Register
	#define TPM7_MOD 	TPM3MOD		//PWM Port - Channel 7 - Modulo Register

	/*
	** ===================================================================
	** Inter-Integrated Circuit (I2C) Configuration Registers
	** ===================================================================
	*/
	
	#define	I2C_SDA 	PTCD_PTCD0		//I2C - SDA Signal
	#define	I2C_SCL 	PTCD_PTCD1		//I2C - SCL Signal
	
	#define I2C_ADD		IIC1A_AD		//I2C Address	
	#define I2C_DATA	IIC1D			//I2C Address
	#define I2C_FREQ	IIC1F			//I2C Clock Rate
	#define I2C_ICR		IIC1F_ICR		//I2C Clock Rate
	#define I2C_MULT	IIC1F_ICR		//I2C Multiplier factor
	#define I2C_CTRL	IIC1C1			//I2C Control register
	
	//	7  | 6  | 5   | 4  | 3    |  2    | 1 | 0  
	//--------------------------------------------
	//	EN | IE | MST | TX | TXAK | *RSTA | X | X
	
	#define I2C_EN		IIC1C_IICEN		//I2C Control register - I2C Enable
	#define I2C_DISABLED	0x00		// 0: I2C is not enabled
	#define I2C_ENABLED 	0x01		// 1: I2C is enabled

	#define I2C_IE		IIC1C_IICIE		//I2C Control register - I2C Interrupt Enable
	#define I2C_NO_IE 		0x00		// 0: I2C interrupt request not enabled
	#define I2C_IE_EN 		0x01		// 1: I2C interrupt request enabled
	
	#define I2C_MODE	IIC1C_MST		//I2C Control register - Master mode select
	#define I2C_SLAVE		0x00		// 0: Slave Mode
	#define I2C_MASTER		0x01		// 1: Master Mode
	
	#define I2C_TMODE	IIC1C_TX		//I2C Control register - Transmit mode select
	#define I2C_RECEIVE	 	0x00		// 0: Receive
	#define I2C_TRANSMIT 	0x01		// 1: Transmit
	
	#define I2C_TACK	IIC1C_TXAK		//I2C Control register - Transmit acknowledge enable
	#define I2C_TACK_EN 	0x00		// 0: An acknowledge signal is sent after bus receives data
	#define I2C_NO_TACK		0x01		// 1: No acknowledge signal is sent		
	
	#define I2C_STATUS	IIC1S
	
	//	7   |    6  |   5  |   4   |  3  |  2  |   1    |  0  
	//------------------------------------------------------
	//	TCF | *IAAS | BUSY | *ARBL |  X  | SRW | *IICIF | RXAK
	
	#define I2C_TCF		IIC1S_TCF		//I2C - Transfer complete flag
	#define I2C_TC_PRG		0x00		// 0: Transfer in progress
	#define I2C_TC_CPL		0x01		// 1: Transfer complete
	
	#define I2C_IF		IIC1S_IICIF		//I2C - Interruption Flag
	#define I2C_IF_SET		0x00		// 0: Transfer in progress
	#define I2C_CLR_IF		0x01		// 1: Transfer complete
	
	#define I2C_ARBL	IIC1S_ARBL		//I2C - Interruption Flag
	#define I2C_ARBL_OK		0x00		// 0: Transfer in progress
	#define I2C_ARBL_LOST	0x01		// 1: Transfer complete
	
	#define I2C_BUSY	IIC1S_BUSY		//I2C - Bus busy
	#define I2C_BUS_IDLE	0x00		// 0: Bus is idle
	#define I2C_BUS_BUSY	0x01		// 1: Bus is busy
	
	#define I2C_SRW		IIC1S_SRW		//I2C - Slave R/W
	#define I2C_SLV_RX		0x00		// 0: Slave Receive (Master writing to slave)
	#define I2C_SLV_TX		0x01		// 1: Slave Transmit (Master reading from slave)
	
	#define I2C_ACK		IIC1S_RXAK		//I2C - Receive Acknowledge
	#define I2C_ACK_R		0x00		// 0: Acknowledge Received
	#define I2C_NO_ACK		0x01		// 1: No Acknowledge Received
	
	#define I2C_IAAS	IIC1S_IAAS		//I2C - Is addressed as Slave
	#define I2C_IAAS_NA		0x00		// 0: Not addressed as Slave
	#define I2C_IAAS_AD		0x01		// 1: Is addressed as Slave
	
	/*
	** ===================================================================
	** COMPort (SCI Embedded Comport) Configuration Registers
	** ===================================================================
	*/

	#define	COMPort_TX 		PTCD_PTCD3		//COMport - Tx Signal
	#define	COMPort_RX 		PTCD_PTCD5		//COMport - Rx Signal

	/*
	** ===================================================================
	** Interrupt Vectors (Memory address asigments)
	** ===================================================================
	*/
	
	#define ISR_COMPort_Vector		0xFFD4
	#define ISR_SCIPort_Vector		0xFFDA
	#define ISR_I2C_Vector			0xFFCE
	
#endif /* MINI_PINOUT_H_ */

#endif
