/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 gsc_sch_core.h
**  Description: Scheduler Core
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

#ifndef GSC_SCH_CORE_H
	#define GSC_SCH_CORE_H

    /*
	** ===================================================================
	** I2C type definitions
	** ===================================================================
	*/
	
	typedef struct{
		void (*gsc_sch_task)(void); 
		T_ULONG gsc_sch_taskPeriod; 
		T_ULONG gsc_sch_taskDelay; 
	}S_SCHEDULER_TASK;
	
	typedef struct{
		void (*task)(void (*function)(void), T_ULONG delay, T_ULONG period);
		void (*start)(void); 
		void (*end)(void); 
	}S_SCHEDULER;
	
    /*
    ** ===================================================================
    ** Scheduler Core functions prototypes
    ** ===================================================================
    */
	
	PUBLIC_FCT void gsc_sch_core_stopTasks(void);
	PUBLIC_FCT void gsc_sch_core_dispatchTasks(void);
	PUBLIC_FCT void gsc_sch_core_createTask(void (*function)(void), T_ULONG delay, T_ULONG period);
		
    /*
    ** ===================================================================
    ** Scheduler Structure declaration
    ** ===================================================================
    */
	
	PUBLIC_DATA const S_SCHEDULER Scheduler;

#endif /* GSC_SCH_CORE_H */
