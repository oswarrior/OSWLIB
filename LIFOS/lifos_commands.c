#include "oswlib/LIFOS/lifos_modules.h"
#include "oswlib/LIFOS/lifos_functions.h"
#include "oswlib/LIFOS/lifos_commands.h"

const S_LIFOS_CMD LIFOS_CMD_LIST[] = 
{
		/* CMD, 	TYPE,		LIFOS Function, 		Command Name */
	    { 0x0A,		ROM,		lifos_printCMDList, 	"Print LIFOS command List"	},

	    { 0x11,		WOM,		lifos_pinDirection, 	"Pin - Direction"			},
	    { 0x12,		ROM,		lifos_pinRead, 			"Pin - Read"				},
	    { 0x13,		WOM,		lifos_pinWrite, 		"Pin - Write"				},
	    { 0x14,		CFG,		lifos_pinToggle, 		"Pin - Toggle"				},
	    
	    { 0x30,		CFG,		lifos_analogInit, 		"Analog - Init"				},
	    { 0x31,		CFG,		lifos_analogEnable, 	"Analog - Enable Pin"		},
	    { 0x32,		CFG,		lifos_analogDisable, 	"Analog - Disable Pin"		},
	    { 0x33,		ROM,		lifos_analogRead, 		"Analog - Read Pin"			},
	    { 0x34,		WOM,		lifos_analogResolution, "Analog - Set resolution"	},
	    
	    { 0x40,		CFG,		lifos_servoEnable, 		"Servo - Enable Channel"	},
	    { 0x41,		CFG,		lifos_servoDisable, 	"Servo - Disable Channel"	},
	    { 0x42,		ROM,		lifos_servoRead, 		"Servo - Read Position"		},
	    { 0x43,		WOM,		lifos_servoWrite, 		"Servo - Write Position"	},
	    
	    { 0x50,		CFG,		lifos_pwmEnable, 		"PWM - Enable Channel"		},
	    { 0x51,		CFG,		lifos_pwmDisable, 		"PWM - Disable Channel"		},
	    { 0x52,		ROM,		lifos_pwmRead, 			"PWM - Read Duty Cycle"		},
	    { 0x53,		WOM,		lifos_pwmWrite, 		"PWM - Write Duty Cycle"	},
	    
	    /* NOTE: this list shall be updated according to S_LIFOS_CMD type! */
};

T_UBYTE LIFOS_CMD_LIST_LEN = (sizeof(LIFOS_CMD_LIST)/sizeof(S_LIFOS_CMD));
