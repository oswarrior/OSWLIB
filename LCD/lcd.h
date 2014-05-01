/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 lcd.h
** 	Description: OSWarrior library for Liquid Crystal Displays (LCD)
** =============================================================================
**  Author:		 Hugo Arganda (hugo.arganda@gmail.com)
**  Version:	 4.0
**  Status: 	 Integrated
** =============================================================================
**  							CHANGE LOG:
** =============================================================================
**	Date: 27/03/2013 - Version 2.0 freeze (Integrated)
**	Date: 02/05/2013 - Command function bug fixed
**	Date: 02/05/2013 - Added Clear function
**	Date: 02/05/2013 - Version 2.1 freeze (Tested)
**	Date: 03/05/2013 - Added control for rows and columns quantity on the initialization function
**	Date: 03/05/2013 - Added custom character creation function .customChar()
**	Date: 22/06/2013 - Function descriptions added
**	Date: 22/06/2013 - Version 3.0 freeze (Integrated)
**	Date: 14/08/2013 - Fixed bug on reset function
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

#ifndef OSWARRIOR_LCD_H_
	#define OSWARRIOR_LCD_H_
	
	/*
	** ===================================================================
	** LCD commands
	** ===================================================================
	*/

	#define LCD_CLR 			0x01	//Clears all display and returns the cursor to the home position (Address 0).
	#define LCD_HOME 			0x02	//Returns the cursor to the home position (Address 0). Returns display to its original state if it was shifted.

	#define LCD_MOVE_CURSOR_R 	0x14	//Shifts the cursor position to the right (Address Counter is incremented by 1)
	#define LCD_MOVE_CURSOR_L 	0x10	//Shifts the cursor position to the left (Address Counter is decremented by 1)  

	#define LCD_SCROLL_R 		0x1C	//Shifts the entire display to the left. The cursor follows the display shift
	#define LCD_SCROLL_L 		0x18	//Shifts the entire display to the right. The cursor follows the display shift  
	
	#define LCD_BLINK_MASK		1u
	#define LCD_CURSOR_MASK	 	2u
	#define LCD_DISPLAY_MASK	4u

	/*
	** ===================================================================
	** LCD type definitions
	** ===================================================================
	*/

	typedef struct{
		T_UBYTE d4;
		T_UBYTE d5;
		T_UBYTE d6;
		T_UBYTE d7;
		T_UBYTE en; 
		T_UBYTE rs;
		
		T_UBYTE	rows; 	
		T_UBYTE cols;	
	
		void (*init)(T_UBYTE rows, T_UBYTE cols, T_UBYTE rs, T_UBYTE en, T_UBYTE d4, T_UBYTE d5, T_UBYTE d6, T_UBYTE d7);		
		void (*reset)(void);
		void (*clear)(void);
		void (*clearRow)(int);

		void (*customChar)(T_UBYTE location, T_UBYTE *ptr);
		void (*command)(T_UBYTE cmd);
		
		void (*write)(char *str);	
		void (*writeChar)(T_UBYTE data);	
		
		void (*print)(T_SLONG number);	
		void (*printDigits)(T_SLONG number, int digits);
		void (*printFloat)(T_FLOAT number, int decimals);
		
		void (*setCursor)(int col, int row);
		
		void (*display)(int enable);
		void (*cursor)(int enable);
		void (*blink)(int enable);

		void (*scrollLeft)(void);
		void (*scrollRight)(void);
		
	}S_LCDSTR;
	
	/*
	** ===================================================================
	** LCD functions prototypes
	** ===================================================================
	*/

	PUBLIC_FCT void _OSWarrior_lcd_init(T_UBYTE cols, T_UBYTE rows, T_UBYTE RS, T_UBYTE EN, T_UBYTE d4, T_UBYTE d5, T_UBYTE d6, T_UBYTE d7);
	PUBLIC_FCT void _OSWarrior_lcd_reset(void);
	PUBLIC_FCT void _OSWarrior_lcd_push_enable(void);
	PUBLIC_FCT void _OSWarrior_lcd_clear(void);
	PUBLIC_FCT void _OSWarrior_lcd_clear_row(int);
	
	PUBLIC_FCT void _OSWarrior_lcd_build(T_UBYTE location, T_UBYTE *ptr);
	PUBLIC_FCT void _OSWarrior_lcd_cmd(T_UBYTE cmd);

	PUBLIC_FCT void _OSWarrior_lcd_write (T_UBYTE *str);
	PUBLIC_FCT void _OSWarrior_lcd_write_char (T_UBYTE data);
	
	PUBLIC_FCT void _OSWarrior_lcd_print (T_SLONG number);
	PUBLIC_FCT void _OSWarrior_lcd_print_digits (T_SLONG number, int digits);
	PUBLIC_FCT void _OSWarrior_lcd_print_float (T_FLOAT number, int decimals);

	PUBLIC_FCT void _OSWarrior_lcd_setCursor(int col, int row);
	PUBLIC_FCT void _OSWarrior_lcd_moveCursorRight(void);
	PUBLIC_FCT void _OSWarrior_lcd_moveCursorLeft(void);
	
	PUBLIC_FCT void _OSWarrior_lcd_display(int enable);
	PUBLIC_FCT void _OSWarrior_lcd_cursor(int enable);
	PUBLIC_FCT void _OSWarrior_lcd_blink(int enable);

	PUBLIC_FCT void _OSWarrior_lcd_scrollLeft(void);
	PUBLIC_FCT void _OSWarrior_lcd_scrollRight(void);

	/*
	** ===================================================================
	** LCD Structure Declaration
	** ===================================================================
	*/

	extern S_LCDSTR LCD;

#endif /* OSWARRIORMINI_LCD_H_ */
