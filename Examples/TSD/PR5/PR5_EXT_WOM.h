/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 lifos.h
**  Description: LabVIEW Interface for OSWarrior functions declarations
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Revision 1, stills in development.
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

#ifndef OSWARRIORMINI_P5_H_
	#define OSWARRIORMINI_P5_H_

	/*
	** ===================================================================
	** LIFOS constants
	** ===================================================================
	*/

	#define PR5_PKG_SIZE 		3u

	#define EXT_WOM_RX_SYNC		0xA5		
	#define EXT_WOM_CAL_OFF		0x80		


	/*
	** ===================================================================
	** LIFOS type definitions
	** ===================================================================
	*/
	
	typedef enum{
		MODE_OFF = 0x10,
		MODE_SEQ,
		MODE_ANALOG,
		SET_COLOR_RED = 0x0A,
		SET_COLOR_GREEN,
		SET_COLOR_BLUE,
		CAL_COLOR = 0x80
	}E_EXT_WOM_CMD;
	
	typedef enum{
		SYNC_FRAME,
		CMD_FRAME,
		CHK_FRAME
	}E_EXT_WOM_FRAME;
	
	typedef enum{
		RGB_NO_COLOR = 0x00,
		RGB_COLOR_RED = 0x01,
		RGB_COLOR_GREEN = 0x02,
		RGB_COLOR_BLUE = 0x04
	}E_RGB_Colors;

	
	#define SYNC_FRAME_ID	0xA5
	
	typedef struct{
		T_UBYTE			SYNC;
		E_EXT_WOM_CMD	CMD;
		T_UBYTE			CHK;
	}S_EXT_WOM_PKG;

	/*
    ** ===================================================================
    ** LIFOS functions prototypes
    ** ===================================================================
    */

	PUBLIC_FCT  void PR5_EXT_WOM_Listener(void);
	PUBLIC_FCT  void PR5_S2_Event_Listener(void);
	PUBLIC_FCT  void PR5_Toggle_Ext_Mode(void);
	PRIVATE_FCT void EXT_WOM_pkg_decode(void);
	
	/*
	** ===================================================================
	** LIFOS Structure declaration
	** ===================================================================
	*/
	
	PUBLIC_DATA S_EXT_WOM_PKG EXT_WOM_pkg;
	
	PUBLIC_DATA E_RGB_Colors RGB_Color_Selected;
	
	PUBLIC_DATA T_UBYTE PR5_current_Color_R;
	PUBLIC_DATA T_UBYTE PR5_current_Color_G;
	PUBLIC_DATA T_UBYTE PR5_current_Color_B;
	
	PUBLIC_DATA T_BOOLEAN EXT_Mode_Active;


#endif
