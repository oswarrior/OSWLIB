#ifndef OSWARRIOR_SERIAL_SCIPORT_H_
	
	#define OSWARRIOR_SERIAL_SCIPORT_H_

	/*
    ** ===================================================================
    ** Serial related interrupt function handlers
    ** ===================================================================
    */

	PUBLIC_FCT __interrupt void _OSWarrior_SCIPort_ISR_Write(void);
	PUBLIC_FCT __interrupt void _OSWarrior_SCIPort_ISR_Read(void);
	PUBLIC_FCT __interrupt void _OSWarrior_SCIPort_ISR_Error(void);
	
    /*
    ** ===================================================================
    ** Serial functions prototypes
    ** ===================================================================
    */
		
	PUBLIC_FCT void 	_OSWarrior_SCIPort_Init(dword baudrate);
	PUBLIC_FCT void 	_OSWarrior_SCIPort_End(void);
	PUBLIC_FCT void 	_OSWarrior_SCIPort_Clear(void);
	PUBLIC_FCT void 	_OSWarrior_SCIPort_NewLine(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_SCIPort_Available(void);
	
	PUBLIC_FCT void 	_OSWarrior_SCIPort_Print(T_UBYTE *data);
	PUBLIC_FCT void		_OSWarrior_SCIPort_Print_Line(T_UBYTE *data);
	PUBLIC_FCT void 	_OSWarrior_SCIPort_PrintChar(T_UBYTE data);
	PUBLIC_FCT void 	_OSWarrior_SCIPort_PrintNum (T_SLONG number);
	PUBLIC_FCT void 	_OSWarrior_SCIPort_PrintDigits (T_SLONG number, int digits);
	PUBLIC_FCT void 	_OSWarrior_SCIPort_PrintFloatNumber(double number, int decimals);
	
	PUBLIC_FCT T_UBYTE *_OSWarrior_SCIPort_Read(void);
	PUBLIC_FCT int 		_OSWarrior_SCIPort_ReadNumber(void);
	PUBLIC_FCT T_UBYTE 	_OSWarrior_SCIPort_GetChar(void);
		
#endif /* OSWARRIORMINI_SERIAL_H_ */
