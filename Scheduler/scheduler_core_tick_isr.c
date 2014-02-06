/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 gsc_sch_core_tick_isr.c
**  Description: Scheduler core tick counter interruptions
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
** Scheduler includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/scheduler/scheduler_core_tick_isr.h"

/*
** ===================================================================
** Scheduler variables declarations
** ===================================================================
*/

T_BOOLEAN re_sch_mngExecflag = FALSE;

/*
** ===================================================================
**     Function : gsc_sch_tick_counter
**
**     Description :
**          This interruption is programmed to run every time a 
**          millisecond happens. 
**     
** ===================================================================
*/

void gsc_sch_tick_counter(void){    
	re_sch_mngExecflag = TRUE;
}
