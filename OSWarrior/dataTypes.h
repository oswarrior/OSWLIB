/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 dataTypes.h
**  Description: OSWarrior data type definitions
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - dataTypes.h Version 2.0 freeze
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

#ifndef OSWARRIOR_DATATYPES_H_
	
	#define OSWARRIOR_DATATYPES_H_

	//-----------------------------------------------------------------------------------------------

	#define BIT_MASK	0x01u
	#define NIBBLE_MASK	0x0Fu
	#define BYTE_MASK	0xFFu

	//-----------------------------------------------------------------------------------------------

	/* Basic Scalar types */	
	typedef unsigned char	T_UBYTE;		/* value range: 0...........................255	*/
	typedef unsigned short	T_UWORD;		/* value range: 0.........................65535	*/
	typedef unsigned long	T_ULONG;		/* value range: 0....................4294967294	*/
	
	typedef signed char		T_SBYTE;		/* value range: -127........................127	*/
	typedef signed short	T_SWORD;		/* value range: -32767....................32767	*/
	typedef signed long		T_SLONG;		/* value range: -2147483647..........2147483647	*/

	typedef double			T_FLOAT;		/* value range: -2147483647..........2147483647	*/
	
	//-----------------------------------------------------------------------------------------------

	/* Pointer to void function */
	typedef void(*T_P_FUNCTION_VOID)(void);

	//-----------------------------------------------------------------------------------------------

	/* basic type pointers */
	typedef T_UBYTE * PTR_UBYTE;
	typedef T_UWORD * PTR_UWORD;
	typedef T_ULONG * PTR_ULONG;
	typedef T_SBYTE * PTR_SBYTE;
	typedef T_SWORD * PTR_SWORD;
	typedef T_SLONG * PTR_SLONG;
	
	//-----------------------------------------------------------------------------------------------

	/* Carrier of 8 bits */
	typedef struct {
		unsigned int	bit7:1;
		unsigned int	bit6:1;
		unsigned int	bit5:1;
		unsigned int	bit4:1;
		unsigned int	bit3:1;
		unsigned int	bit2:1;
		unsigned int	bit1:1;
		unsigned int	bit0:1;
	}T_BITFLD8;

	//-----------------------------------------------------------------------------------------------

	/* Carrier of 16 bits */
	typedef struct {
		unsigned int	bit15:1;
		unsigned int	bit14:1;
		unsigned int	bit13:1;
		unsigned int	bit12:1;
		unsigned int	bit11:1;
		unsigned int	bit10:1;
		unsigned int	bit9:1;
		unsigned int	bit8:1;
		unsigned int	bit7:1;
		unsigned int	bit6:1;
		unsigned int	bit5:1;
		unsigned int	bit4:1;
		unsigned int	bit3:1;
		unsigned int	bit2:1;
		unsigned int	bit1:1;
		unsigned int	bit0:1;
	}T_BITFLD16;

	//-----------------------------------------------------------------------------------------------

	/* Carrier of 32 bits */
	typedef struct {
		unsigned int	bit31:1;
		unsigned int	bit30:1;
		unsigned int	bit29:1;
		unsigned int	bit28:1;
		unsigned int	bit27:1;
		unsigned int	bit26:1;
		unsigned int	bit25:1;
		unsigned int	bit24:1;
		unsigned int	bit23:1;
		unsigned int	bit22:1;
		unsigned int	bit21:1;
		unsigned int	bit20:1;
		unsigned int	bit19:1;
		unsigned int	bit18:1;
		unsigned int	bit17:1;
		unsigned int	bit16:1;
		unsigned int	bit15:1;
		unsigned int	bit14:1;
		unsigned int	bit13:1;
		unsigned int	bit12:1;
		unsigned int	bit11:1;
		unsigned int	bit10:1;
		unsigned int	bit9:1;
		unsigned int	bit8:1;
		unsigned int	bit7:1;
		unsigned int	bit6:1;
		unsigned int	bit5:1;
		unsigned int	bit4:1;
		unsigned int	bit3:1;
		unsigned int	bit2:1;
		unsigned int	bit1:1;
		unsigned int	bit0:1;
	}T_BITFLD32;

	//-----------------------------------------------------------------------------------------------

	/* Word with msb and lsb handling */
	typedef union{
		T_UWORD	wo;
		struct{
			T_UBYTE	msb;
			T_UBYTE	lsb;
		}by;
	}T_BYTEFLD;

	//-----------------------------------------------------------------------------------------------

	/* Long with word and byte handling */
	typedef union{
		T_ULONG lo;
	    struct {
	             T_UBYTE highword_msb;
	             T_UBYTE highword_lsb;
	             T_UBYTE lowword_msb;
	             T_UBYTE lowword_lsb;
	            } by;
	        
	    struct {
	             T_UWORD highword;
	             T_UWORD lowword;
	           } wo;
	               
	}T_BYTEFLD32;

	//-----------------------------------------------------------------------------------------------

	/* Carrier of 8 bits with byte handling */
	typedef union {
		T_UBYTE by;
		T_BITFLD8 bi;
	}T_FLAG8;

	//-----------------------------------------------------------------------------------------------

	/* Carrier of 16 bits with word or byte (msb & lsb) carrier handling */
	typedef union {
		T_BYTEFLD cr;
		T_BITFLD16 bi;
	}T_FLAG16;

	//-----------------------------------------------------------------------------------------------

	/* Carrier of 32 bits with word or byte (msb & lsb) carrier handling */
	typedef union {
		T_BYTEFLD32 cr;
		T_BITFLD32 bi;
	}T_FLAG32;

	//-----------------------------------------------------------------------------------------------

	typedef enum{
		LOW = 0u,
		HIGH
	}E_LEVEL;

	//-----------------------------------------------------------------------------------------------

	typedef enum{
		FALSE = 0u,
		TRUE
	}T_BOOLEAN;

	//-----------------------------------------------------------------------------------------------

	typedef enum{
		INPUT = 0u,
		OUTPUT,
		INPUT_PULLUP
	}E_PIN_DIRECTION;

	//-----------------------------------------------------------------------------------------------

	typedef enum{
		OFF = 0u,
		ON
	}E_LEVEL_LOGIC;

	//-----------------------------------------------------------------------------------------------

	typedef enum
	{
		RIGHT = 0u,
		LEFT,
		BACKWARD,
		FORWARD	
	}E_DIRECTION;
	
	//-----------------------------------------------------------------------------------------------

	typedef enum
	{
		RECEIVE = 0u,
		TRANSMIT
	}E_DATA_DIR;

	//-----------------------------------------------------------------------------------------------

	#define NEAR_FCT                        /* near function definition */
	#define FAR_FCT                         /* far function definition */
	#define INLINE_FCT                      /* inline function definition */ 

	#define PRIVATE_DATA static             /* static data definition */
	#define PRIVATE_FCT  static             /* private function definition */
	
	#define PUBLIC_DATA extern              /* Public (extern) data definition */
	#define PUBLIC_FCT  extern              /* Public (extern) function definition */
	
	//-----------------------------------------------------------------------------------------------
		
#endif /* DATATYPES_H_ */
