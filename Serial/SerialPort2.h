#ifndef OSWARRIOR_SERIAL_SerialPort2_H_
	
	#define OSWARRIOR_SERIAL_SerialPort2_H_

	/*
    ** ===================================================================
    ** Serial related interrupt function handlers
    ** ===================================================================
    */
	
	PUBLIC_FCT __interrupt void _OSWarrior_SerialPort2_ISR_Write(void);
	PUBLIC_FCT __interrupt void _OSWarrior_SerialPort2_ISR_Read(void);
	PUBLIC_FCT __interrupt void _OSWarrior_SerialPort2_ISR_Error(void);
	
    /*
    ** ===================================================================
    ** Serial functions prototypes
    ** ===================================================================
    */

	/* Control and Settings functions */ 
	
	PUBLIC_FCT void _OSWarrior_SerialPort2_Init(T_ULONG baudrate);
	PUBLIC_FCT void _OSWarrior_SerialPort2_setBaudRate(T_ULONG baudrate);
	PUBLIC_FCT void _OSWarrior_SerialPort2_End(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Clear(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_SerialPort2_Available(void);
	
	/* Print functions: Send numeric data trough the serial port */
	
	PUBLIC_FCT void _OSWarrior_SerialPort2_Print(T_SLONG number);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Print_Line(T_SLONG number);
	PUBLIC_FCT void _OSWarrior_SerialPort2_PrintDigits (T_SLONG number, int digits);
	PUBLIC_FCT void _OSWarrior_SerialPort2_PrintFloatNumber(T_FLOAT number, int decimals);

	/* Print functions: Send string and char data trough the serial port */

	PUBLIC_FCT void _OSWarrior_SerialPort2_Write(T_UBYTE *data);
	PUBLIC_FCT void _OSWarrior_SerialPort2_WriteChar(T_UBYTE data);

	/* Read functions */
	
	PUBLIC_FCT T_UBYTE _OSWarrior_SerialPort2_Peek(void);
	PUBLIC_FCT T_UBYTE _OSWarrior_SerialPort2_Read(void);
	PUBLIC_FCT T_UBYTE *_OSWarrior_SerialPort2_Read_String(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Read_Handler(void);
	PUBLIC_FCT int _OSWarrior_SerialPort2_ReadNumber(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_SerialPort2_GetChar(void);
	
	/* Functions for Enable/Disable Tx and Rx */
	
	PUBLIC_FCT void _OSWarrior_SerialPort2_Enable_Tx_Rx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Disable_Tx_Rx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Enable_Tx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Disable_Tx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Enable_Rx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Disable_Rx(void);

	PUBLIC_FCT void _OSWarrior_SerialPort2_Enable_Tx_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Disable_Tx_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Enable_Tx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Disable_Tx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Enable_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort2_Disable_Rx_ISR(void);
				
#endif
