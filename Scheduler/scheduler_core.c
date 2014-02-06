/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 gsc_sch_core.c
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

/*
** ===================================================================
** Scheduler Core includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/scheduler/scheduler.h"
#include "oswlib/scheduler/scheduler_core.h"
#include "oswlib/scheduler/scheduler_core_tick_isr.h"

/*
** ===================================================================
** Scheduler Core variables declarations
** ===================================================================
*/

S_SCHEDULER_TASK gsc_sch_tasks[SCH_MAX_TASKS];
static T_UBYTE gsc_sch_tasks_qty;
static T_BOOLEAN re_sch_mngEnabledScheduler;

/*
** ===================================================================
** Scheduler Core Structure definition
** ===================================================================
*/

const S_SCHEDULER Scheduler = {
		gsc_sch_core_createTask,
		gsc_sch_core_dispatchTasks,
		gsc_sch_core_stopTasks
};

/*
** ===================================================================
**     Function : Scheduler.task
**     Handler  : gsc_sch_core_createTask
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void gsc_sch_core_createTask(void (*function)(void), T_ULONG delay, T_ULONG period)
{
	static T_UBYTE index = 0;
	gsc_sch_tasks[index].gsc_sch_task = function;
	gsc_sch_tasks[index].gsc_sch_taskPeriod = period;
	gsc_sch_tasks[index].gsc_sch_taskDelay = delay + 1;
	gsc_sch_tasks_qty = ++index;
}

/*
** ===================================================================
**     Function : Scheduler.start
**     Handler  : gsc_sch_core_dispatchTasks
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void gsc_sch_core_dispatchTasks(void)
{
	register T_UWORD i;
	
	_OSWarrior_tickISR_handler = gsc_sch_tick_counter;
	
	gsc_sch_enable_interrupts();
	
	re_sch_mngEnabledScheduler = TRUE;
	
	while(re_sch_mngEnabledScheduler)
	{
		if(re_sch_mngExecflag)
		{
			re_sch_mngExecflag = FALSE;
			for ( i = 0; i < gsc_sch_tasks_qty; i++) 
			{
				if (--gsc_sch_tasks[i].gsc_sch_taskDelay == 0) 
				{
					gsc_sch_tasks[i].gsc_sch_taskDelay = gsc_sch_tasks[i].gsc_sch_taskPeriod;						
					gsc_sch_tasks[i].gsc_sch_task();
				}
			}
		}
	}
}

/*
** ===================================================================
**     Function : Scheduler.start
**     Handler  : gsc_sch_core_dispatchTasks
**
**     Description :
**          Initialise the OSWarrior I2C library and set the device
**          address when used as slave, this function must me called
**          only once.
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void gsc_sch_core_stopTasks(void)
{
	re_sch_mngEnabledScheduler = FALSE;
	
	/* Write here you code for disable the scheduler function enabler */
	
	_OSWarrior_tickISR_handler = _OSWarrior_Dummy_Fnc;
}
