#ifndef OSWARRIOR_SERIAL_COMPORT_H_
	
	#define OSWARRIOR_SERIAL_COMPORT_H_

	/*
    ** ===================================================================
    ** Serial related interrupt function handlers
    ** ===================================================================
    */
	
	PUBLIC_FCT __interrupt void _OSWarrior_COMPort_ISR_Write(void);
	PUBLIC_FCT __interrupt void _OSWarrior_COMPort_ISR_Read(void);
	PUBLIC_FCT __interrupt void _OSWarrior_COMPort_ISR_Error(void);
	
    /*
    ** ===================================================================
    ** Serial functions prototypes
    ** ===================================================================
    */

	PUBLIC_FCT void _OSWarrior_COMPort_Init(T_ULONG baudrate);
	PUBLIC_FCT void _OSWarrior_COMPort_setBaudRate(T_ULONG baudrate);
	PUBLIC_FCT void _OSWarrior_COMPort_End(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Clear(void);
	PUBLIC_FCT void _OSWarrior_COMPort_NewLine(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_COMPort_Available(void);
	
	/* Print functions */
	
	PUBLIC_FCT void _OSWarrior_COMPort_Print(T_UBYTE *data);
	PUBLIC_FCT void _OSWarrior_COMPort_Print_Line(T_UBYTE *data);
	PUBLIC_FCT void _OSWarrior_COMPort_PrintChar(T_UBYTE data);
	PUBLIC_FCT void _OSWarrior_COMPort_PrintNum (T_SLONG number);
	PUBLIC_FCT void _OSWarrior_COMPort_PrintDigits (T_SLONG number, int digits);
	PUBLIC_FCT void _OSWarrior_COMPort_PrintFloatNumber(T_FLOAT number, int decimals);
	
	/* Read functions */
	
	PUBLIC_FCT T_UBYTE *_OSWarrior_COMPort_Read(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Read_Handler(void);
	PUBLIC_FCT int _OSWarrior_COMPort_ReadNumber(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_COMPort_GetChar(void);
	
	/* Functions for Enable/Disable Tx and Rx */
	
	PUBLIC_FCT void _OSWarrior_COMPort_Enable_Tx_Rx(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Disable_Tx_Rx(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Enable_Tx(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Disable_Tx(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Enable_Rx(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Disable_Rx(void);

	PUBLIC_FCT void _OSWarrior_COMPort_Enable_Tx_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Disable_Tx_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Enable_Tx_ISR(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Disable_Tx_ISR(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Enable_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_COMPort_Disable_Rx_ISR(void);
				
#endif
