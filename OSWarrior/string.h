/*
*
* 	Filename: math.h
* 
* 	Actual Version: 2.0
* 	Status: Integrated
* 
* 	Description: OSWarrior String Functions
*
* 	Author: Hugo Arganda (hugo.arganda@gmail.com)
* 
* 	Created on: 27/03/2013
*
*	Change Log:
*	Date: 27/03/2013 - Version 2.0 freeze
* 
*/

#ifndef OSWARRIOR_STRING_H_
	
	#define OSWARRIOR_STRING_H_
	
	#define STRING_MAX_LENGTH	32
	
	PUBLIC_FCT T_UBYTE strlength_ptr(T_UBYTE *str);
	PUBLIC_FCT T_UBYTE strsub(T_UBYTE  string[],T_UBYTE  sub_min,T_UBYTE  sub_max);
	PUBLIC_FCT int str_to_int(T_UBYTE *str);
	T_UBYTE * dec_to_hexString(unsigned int dec);

	
#endif
