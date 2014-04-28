/*
 * lifos_available_commands.c
 *
 *  Created on: Nov 23, 2013
 *      Author: HuAr
 */

#ifndef LIFOS_AVAILABLE_COMMANDS_C_
#define LIFOS_AVAILABLE_COMMANDS_C_

	typedef enum{
		ROM,
		WOM,
		CFG
	}E_LIFOS_CMD_TYPE;
	
	typedef struct{
		const T_UBYTE CMD;					//CMD - Command
		const E_LIFOS_CMD_TYPE TYPE;		//Function Type
		int (*FNC)(T_UBYTE, int);			//Function Handler
		const T_UBYTE * CMD_NAME;			//CMD Name
	}S_LIFOS_CMD;
	
	extern T_UBYTE LIFOS_CMD_LIST_LEN;
	
	extern const S_LIFOS_CMD LIFOS_CMD_LIST[];
	
#endif /* LIFOS_AVAILABLE_COMMANDS_C_ */
