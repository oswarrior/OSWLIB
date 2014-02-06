/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 gsc_sch_core_tick_isr.h
**  Description: Scheduler core tick counter interruptions
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							 LICENSE:
** =============================================================================
**  This library is free software; you can redistribute it and/or
**  modify it under the terms of the Attribution-ShareAlike
**  License as published by the Creative Commons Organization; either
**  version 3.0 of the License, or (at your option) any later version.
**  This library is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
**  See the Attribution-ShareAlike License for more details.
**  You should have received a copy of the Creative Commons Attribution-ShareAlike 
**  License along with this library; if not send a email to the library author.
** =============================================================================
*/

#ifndef GSC_SCH_CORE_TICK_ISR_H
	#define GSC_SCH_CORE_TICK_ISR_H

    /*
    ** ===================================================================
    ** Scheduler variables
    ** ===================================================================
    */

	PUBLIC_DATA T_BOOLEAN re_sch_mngExecflag;
	
    /*
    ** ===================================================================
    ** Scheduler function prototypes
    ** ===================================================================
    */

	extern void gsc_sch_tick_counter(void);


#endif /* GSC_SCH_CORE_TICK_ISR_H */
