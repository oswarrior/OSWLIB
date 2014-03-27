#ifndef OSWARRIOR_SERIAL_SerialPort1_H_
	
	#define OSWARRIOR_SERIAL_SerialPort1_H_

	/*
    ** ===================================================================
    ** Serial related interrupt function handlers
    ** ===================================================================
    */
	
	PUBLIC_FCT __interrupt void _OSWarrior_SerialPort1_ISR_Write(void);
	PUBLIC_FCT __interrupt void _OSWarrior_SerialPort1_ISR_Read(void);
	PUBLIC_FCT __interrupt void _OSWarrior_SerialPort1_ISR_Error(void);
	
    /*
    ** ===================================================================
    ** Serial functions prototypes
    ** ===================================================================
    */

	/* Control and Settings functions */ 
	
	PUBLIC_FCT void _OSWarrior_SerialPort1_Init(T_ULONG baudrate);
	PUBLIC_FCT void _OSWarrior_SerialPort1_setBaudRate(T_ULONG baudrate);
	PUBLIC_FCT void _OSWarrior_SerialPort1_End(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Clear(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_SerialPort1_Available(void);
	
	/* Print functions: Send numeric data trough the serial port */
	
	PUBLIC_FCT void _OSWarrior_SerialPort1_Print(T_SLONG number);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Print_Line(T_SLONG number);
	PUBLIC_FCT void _OSWarrior_SerialPort1_PrintDigits (T_SLONG number, int digits);
	PUBLIC_FCT void _OSWarrior_SerialPort1_PrintFloatNumber(T_FLOAT number, int decimals);

	/* Print functions: Send string and char data trough the serial port */

	PUBLIC_FCT void _OSWarrior_SerialPort1_Write(T_UBYTE *data);
	PUBLIC_FCT void _OSWarrior_SerialPort1_WriteChar(T_UBYTE data);

	/* Read functions */
	
	PUBLIC_FCT T_UBYTE _OSWarrior_SerialPort1_Peek(void);
	PUBLIC_FCT T_UBYTE _OSWarrior_SerialPort1_Read(void);
	PUBLIC_FCT T_UBYTE *_OSWarrior_SerialPort1_Read_String(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Read_Handler(void);
	PUBLIC_FCT int _OSWarrior_SerialPort1_ReadNumber(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_SerialPort1_GetChar(void);
	
	/* Functions for Enable/Disable Tx and Rx */
	
	PUBLIC_FCT void _OSWarrior_SerialPort1_Enable_Tx_Rx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Disable_Tx_Rx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Enable_Tx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Disable_Tx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Enable_Rx(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Disable_Rx(void);

	PUBLIC_FCT void _OSWarrior_SerialPort1_Enable_Tx_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Disable_Tx_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Enable_Tx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Disable_Tx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Enable_Rx_ISR(void);
	PUBLIC_FCT void _OSWarrior_SerialPort1_Disable_Rx_ISR(void);
				
#endif
