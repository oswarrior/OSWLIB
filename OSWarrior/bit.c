/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
** 	Filename: 	 bit.c
** 	Description: OSWarrior Bit functions library
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
** Bit includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/OSWarrior/bit.h"

T_BOOLEAN bitRead(T_UBYTE x, T_UBYTE  n)
{		
	return ( (x & (2^n)) >> n );
}

void bitWrite(T_UBYTE x, T_UBYTE  n, T_UBYTE  b)
{		
	x |= ( ( b & 1u ) << n ) ;
}

void bitSet(T_UBYTE x, T_UBYTE  n)
{		
	x |= ( 1u << n ) ;
}

void bitClear(T_UBYTE x, T_UBYTE  n)
{		
	x &= !( 1u << n ) ;	
}

int bit(T_UBYTE n)
{		
	return (2^n);	
}

