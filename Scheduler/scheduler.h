/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 gsc_sch_settings.h
**  Description: Scheduler Core Settings
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
** =============================================================================
**  							 LICENSE:
** =============================================================================
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the Attribution-ShareAlike
**  License as published by the Creative Commons Organisation; either
**  version 3.0 of the License, or (at your option) any later version.
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
**  See the Attribution-ShareAlike License for more details.
**  You should have received a copy of the Creative Commons Attribution-ShareAlike 
**  License along with this library; if not send a email to the library author.
** =============================================================================
*/

#ifndef GSC_SCH_CORE_CFG_H
	
	#define GSC_SCH_CORE_CFG_H
	
    /*
    ** ===================================================================
    ** Scheduler settings includes
    ** ===================================================================
    */

	#include "oswlib/settings.h"
	#include "oswlib/scheduler/scheduler_core.h"
	#include "oswlib/scheduler/scheduler_core_tick_isr.h"

    /*
    ** ===================================================================
    ** Scheduler variables
    ** ===================================================================
    */

	#define SCH_MAX_TASKS 10

    /*
    ** ===================================================================
    ** Scheduler functions prototypes
    ** ===================================================================
    */

	PUBLIC_FCT void gsc_sch_enable_interrupts(void);
	PUBLIC_FCT void gsc_sch_disable_interrupts(void);

#endif /* GSC_SCH_CORE_CFG_H */
