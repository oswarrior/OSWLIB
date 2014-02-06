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

/*
** ===================================================================
** Scheduler Core Settings includes
** ===================================================================
*/

#include "oswlib/scheduler/scheduler.h"

/*
** ===================================================================
**     Function : _OSWarrior_gsc_sch_enable_interrupts
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

void gsc_sch_enable_interrupts(void){
	
	/* Write your interruption enable code here */
	oswarrior_enableDelays();
}

/*
** ===================================================================
**     Function : _OSWarrior_gsc_sch_disable_interrupts
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
void gsc_sch_disable_interrupts(void){	
	/* Write your interruption disable code here */
	oswarrior_disableDelays();
}
