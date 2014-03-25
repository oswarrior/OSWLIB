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

#include "oswlib/settings.h"
#include "oswlib/OSWarrior/string.h"

PRIVATE_DATA const T_UBYTE hex_digits[] =  {"0123456789ABCDEF"};

T_UBYTE strlength_ptr(T_UBYTE *str)
{
	T_UBYTE length = 0;
	while(*(str++)) ++length;
	return length;
};

T_UBYTE strsub(T_UBYTE string[],T_UBYTE sub_min,T_UBYTE sub_max)
{
	int i;
	T_UBYTE subString[STRING_MAX_LENGTH];
	for(i = sub_min; i <sub_max; i++) subString[i] = string[i];
	return *subString;		
};

int str_to_int(T_UBYTE *str)
{
	int result = 0;
	switch(strlength_ptr(str))
	{
		case 1:
			result = (int)*str - 48;
		break;
		case 2:
			result = ((int)*str - 48)*10;
			str++;
			result += ((int)*str - 48);
		break;
		case 3:
			result = ((int)*str - 48)*100;
			str++;
			result += ((int)*str - 48)*10;
			str++;
			result += ((int)*str - 48);
		break;
		case 4:
			result = ((int)*str - 48)*1000;
			str++;
			result += ((int)*str - 48)*100;
			str++;
			result += ((int)*str - 48)*10;
			str++;
			result += ((int)*str - 48);
		break;
	}	
	return result;
}

T_UBYTE * dec_to_hexString(unsigned int dec)
{
	T_UBYTE * hex_base = "0x";
	
	char hex_temp[2];
	char hex[80];
	
	unsigned int residuo;
	unsigned int cociente;	
	
	(void) strcpy(hex, hex_base );

	cociente = (unsigned int)dec/16;
	hex_temp[0] = hex_digits[cociente];		
	
	residuo = (unsigned int)dec%16;
	hex_temp[1] = hex_digits[residuo];		
	
	(void) strcat(hex,hex_temp);	
	
	return hex;
}
