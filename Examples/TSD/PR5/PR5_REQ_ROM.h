/*
 * PR5_REQ_ROM.h
 *
 *  Created on: Nov 20, 2013
 *      Author: HuAr
 */

#ifndef PR5_REQ_ROM_H_
#define PR5_REQ_ROM_H_
	
	typedef struct{
		const T_UBYTE * CommandString;
		void (*handler)(void);
		const T_UBYTE * function_name;			
	}S_PR5_REQ_ROM_MENU_TYPE;
	
	/*
	** ===================================================================
	** Function declarations	
	** ===================================================================
	*/
	void PR5_REQ_ROM(void);	
	void PR5_REQ_ROM_Listener(void);
	void PR5_REQ_ROM_print_menu(void);
	void PR5_REQ_ROM_find_command(T_UBYTE * userSel);
	void PR5_REQ_ROM_ANALOG_Mode(void);




#endif /* PR5_REQ_ROM_H_ */
