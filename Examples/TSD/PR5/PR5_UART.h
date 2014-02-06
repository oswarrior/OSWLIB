/*
 * PR5_UART.h
 *
 *  Created on: Nov 19, 2013
 *      Author: HuAr
 */

#ifndef PR5_UART_H_
#define PR5_UART_H_

	extern int S1;
	extern int S2;
	
	extern int Lr;
	extern int Lg;
	extern int Lb;
	
	extern int Pr;
	extern int Pg;
	extern int Pb;
	
	extern int ADC_Value_r;
	extern int ADC_Value_g;
	extern int ADC_Value_b;

	typedef enum{
		PR5_MODE_OFF = 0x01,
		PR5_MODE_SEQ = 0x02,
		PR5_MODE_ANALOG = 0x04
	}E_PR5_MODE;
	
	extern E_PR5_MODE PR5_current_Mode;
	
	extern void (*functionHandler)(void);
	
	extern void PR5_main(void);
	extern void PR5_S1_Event_Listener(void);
	extern void PR5_Mode_handler(void);
	extern void PR5_Analog_Read(void);
	
	extern void PR5_Mode_OFF(void);
	extern void PR5_Mode_SEQ(void);
	extern void PR5_Mode_ANALOG(void);
	
	extern void PR5_Set_OFF_Mode(void);
	extern void PR5_Set_SEQ_Mode(void);
	extern void PR5_Set_ANALOG_Mode(void);
	
	extern void PR5_Clear_Screen(void);
	extern void PR5_Print_Header(void);
	
	extern void PR5_Function_handler(void);



#endif /* PR5_UART_H_ */
