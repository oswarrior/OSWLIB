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

