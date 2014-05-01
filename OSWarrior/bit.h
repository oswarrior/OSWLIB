#ifndef OSWARRIOR_BIT_H_
	
	#define OSWARRIOR_BIT_H_
	
	extern T_BOOLEAN bitRead(T_UBYTE x, T_UBYTE  n);
	extern void bitWrite(T_UBYTE x, T_UBYTE  n, T_UBYTE  b);
	extern void bitSet(T_UBYTE x, T_UBYTE  n);
	extern void bitClear(T_UBYTE x, T_UBYTE  n);
	extern int bit(T_UBYTE n);
	
#endif
