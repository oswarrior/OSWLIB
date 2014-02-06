/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 math.h
**  Description: OSWarrior Mathematical library functions declarations
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Version 2.0 freeze (Integrated)
**	Date: 02/05/2013 - Map function fixed
**	Date: 02/05/2013 - Version 2.1 freeze (Tested)
**	Date: 03/05/2013 - Added Limit function
**	Date: 03/05/2013 - Added number_explode function for number print functions
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

#ifndef OSWARRIOR_MATH_H_
	#define OSWARRIOR_MATH_H_

	/*
    ** ===================================================================
    ** Math constants
    ** ===================================================================
    */

	#define PI 			3.14159
	#define HALF_PI 	1.57079
	#define TWO_PI 		6.28318
	#define DEG_TO_RAD 	0.01745
	#define RAD_TO_DEG 	57.29577
	#define EULER 		2.71828

	/*
    ** ===================================================================
    ** Math functions prototypes
    ** ===================================================================
    */

	int min(int x, int y);
	int max(int x, int y);
	int absvalue(int x);
	int limits(int x, int min, int max);
	int map(long x, long in_min, long in_max, long out_min, long out_max);
	
	// Print number functions
	void number_explode(T_SLONG number, void (*handler)(T_UBYTE), int num_digits);
	void number_explode_FloatNumbers(T_FLOAT Floatnumber, void (*handler)(T_UBYTE), int num_decimals);
	void dispatch_exploded_number(T_SLONG number, void (*handler)(T_UBYTE), int digits_count, int num_digits );

#endif /* OSWARRIOR_MATH_H_ */
