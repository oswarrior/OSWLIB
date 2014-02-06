/*
** 	Filename: hc-sr04.h
** 	Description: Ultrasonic Distance Sensor HC-SR04 library
**
**	Author: Hugo Arganda (e.arganda.salazar@gmail.com)
** 	Current Version: 3.0
** 	Status: Development
**
**	CHANGE LOG:
**	Date: 05/08/2013 - Library created
**	
** 	LICENSE:
** 	This library is free software; you can redistribute it and/or
** 	modify it under the terms of the Attribution-ShareAlike
** 	License as published by the Creative Commons Organization; either
** 	version 3.0 of the License, or (at your option) any later version.
** 	This library is distributed in the hope that it will be useful,
** 	but WITHOUT ANY WARRANTY; without even the implied warranty of
** 	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  
** 	See the Attribution-ShareAlike License for more details.
** 	You should have received a copy of the Creative Commons Attribution-ShareAlike 
** 	License along with this library; if not send a email to the library author.
*/

#ifndef OSWARRIOR_HCSR04_H_
	#define OSWARRIOR_HCSR04_H_

	/*
	** ===================================================================
	** Function prototypes	
	** ===================================================================
	*/

	void hcsr04_init(int trig, int echo);
	int hcsr04_read(void);

	/*
	** ===================================================================
	** HC-SR04 Sensor Structure Definition
	** ===================================================================
	*/
	
	typedef struct{
		void (*init)(int trig, int echo);	/*** HC-SR04 - Initialization function ***/
		int (*read)(void);					/*** HC-SR04 - Read Function ***/
	}HCSR04STR;	
	
	extern volatile HCSR04STR HCSR04 = {
		hcsr04_init, 		  
		hcsr04_read		
	};
	
	/*
	** ===================================================================
	**     Function : HCSR04.init
	**     Handler  : hcsr04_init
	**
	**     Description :
	**         Configure the pins to be used by the HC-SR04 sensor,
	**         the Echo pin must be a PWM pin.
	**         
	**     Parameters  : 
	**         trig    : digital pin to trigger the distance read
	**         echo    : PWM pin to measure the echo of the sensor
	**      
	**     Returns     : Nothing
	** ===================================================================
	*/
	
	void hcsr04_init(int trig, int echo){

	}

	/*
	** ===================================================================
	**     Function : HCSR04.read
	**     Handler  : hcsr04_read
	**
	**     Description :
	**         Reads the distance measured by the HC-SR04 sensor. 
	**     
	**     Parameters  : Nothing 
	**     
	**     Returns     : Distance measured in centimeters
	** ===================================================================
	*/
	
	int hcsr04_read(void){
		
	}
	
#endif