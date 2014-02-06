/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 math.c
**  Description: OSWarrior Mathematical library functions declarations
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
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

/*
** ===================================================================
** Math includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/OSWarrior/math.h"

/*
** ===================================================================
** Math constants declarations
** ===================================================================
*/

PRIVATE_DATA const T_UBYTE digits[] =  {"0123456789-."};

/*
** ===================================================================
**     Function : min
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

int min(int x, int y){
	return ((x)<(y)?(x):(y));
}

/*
** ===================================================================
**     Function : max
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

int max(int x, int y){
	return ((x)>(y)?(x):(y));
}

/*
** ===================================================================
**     Function : limits
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

int limits(int x, int min, int max){
	return ((x)<(min)?(min):(((x)>(max))?(max):(x)));
}

/*
** ===================================================================
**     Function : absvalue
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

int absvalue(int x){
	return ((x)>0?(x):-(x));
}


/*
** ===================================================================
**     Function : map
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

int map(long x, long in_min, long in_max, long out_min, long out_max){
  return (int)((((x - in_min) * (out_max - out_min))/ (in_max - in_min)) + out_min);
}

/*
** ===================================================================
**     Function : number_explode
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

void number_explode(T_SLONG number, void (*handler)(T_UBYTE), int num_digits)
{	
	T_SLONG aux_number;
	int count = 0;
	if(number < 0)
	{
		(*handler)(digits[10]);
		number = -number;
	}
	aux_number = number;
	while(aux_number /= 10)	count++;
	if(num_digits > count) count = num_digits - 1;
	dispatch_exploded_number(number, handler, count, num_digits );
}

void number_explode_FloatNumbers(T_FLOAT Floatnumber, void (*handler)(T_UBYTE), int num_decimals)
{	
	T_SLONG number, aux_number, dec_base = 1;
	int i, count = 0;
	if(Floatnumber < 0)
	{
		(*handler)(digits[10]);
		Floatnumber = -Floatnumber;
	}
	number = (T_SLONG)Floatnumber;
	aux_number = number;
	while(aux_number /= 10)	count++;
	dispatch_exploded_number(number, handler, count, 0 );
	if(num_decimals)
	{
		(*handler)(digits[11]);
		Floatnumber = Floatnumber - number;
		for(i = 0; i < num_decimals; i++)	Floatnumber *= 10;
		number = (T_SLONG)Floatnumber;
		dispatch_exploded_number(number, handler, num_decimals - 1, 0 );
	}
}

void dispatch_exploded_number(T_SLONG number, void (*handler)(T_UBYTE), int digits_count, int num_digits )
{
	T_UBYTE digit;
	T_SLONG dec_base = 1;
	T_BOOLEAN prev_digit = FALSE;
	int i;
	for(i = 0; i < digits_count; i++)	dec_base *= 10;
	for(i = digits_count; i >= 0; i--)
	{
		digit = (T_UBYTE)(number/dec_base);
		if(digit || number == 0) prev_digit = TRUE;
		number = (T_ULONG)(number%dec_base);
		if( digit || prev_digit || num_digits >=i )
			(*handler)(digits[digit]);
		dec_base /= 10;
	}
}
