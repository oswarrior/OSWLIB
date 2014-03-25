/*
 * Full_Demo_commands.h
 *
 *  Created on: Nov 26, 2013
 *      Author: HuAr
 */

#ifndef FULL_DEMO_COMMANDS_H_
#define FULL_DEMO_COMMANDS_H_

	typedef struct{
		const T_UBYTE *CommandString;
		void (*handler)(void);
		const T_UBYTE * function_name;			
	}S_OSWARRIOR_DEMO_TYPE;

	PUBLIC_DATA const T_UBYTE Demo_3_Total;
	PUBLIC_DATA const S_OSWARRIOR_DEMO_TYPE Demo_3_List[];
	
#endif /* FULL_DEMO_COMMANDS_H_ */
