/* =============================================================================
** 					OSWarrior - EMBEDDED SYSTEMS SOFTWARE            	  	  
** =============================================================================
**                       	OBJECT SPECIFICATION                                
** =============================================================================
**  Filename: 	 lcd.h
** 	Description: OSWarrior library for Liquid Crystal Displays (LCD)
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
** LCD includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/LCD/lcd.h"

/*
** ===================================================================
** LCD Structure definition
** ===================================================================
*/

S_LCDSTR LCD = {
	0,	//d4
	1,	//d5
	4,	//d6
	5,	//d7
	6,	//RS
	7,	//EN
	
	2, 	//2 Rows
	16, //16 Columns
	
	_OSWarrior_lcd_init, 
	_OSWarrior_lcd_reset,
	_OSWarrior_lcd_clear,
	
	_OSWarrior_lcd_build,
	_OSWarrior_lcd_cmd, 
	_OSWarrior_lcd_print_char, 
	_OSWarrior_lcd_print, 
	_OSWarrior_lcd_print_num, 
	_OSWarrior_lcd_print_digits, 
	_OSWarrior_lcd_print_float, 
	
	
	_OSWarrior_lcd_setCursor, 
	_OSWarrior_lcd_cursor,
	
	_OSWarrior_lcd_blink, 
	_OSWarrior_lcd_display,
};

/*
** ===================================================================
**     Function : LCD.init
**     Handler  : _OSWarrior_lcd_init
**
**     Description :
**         	This function initialize the specified pins to work as the
**         	LCD control signals. 
**     
**     Parameters  : 
**         	cols   : Specify the number of columns in the LCD 
**         	rows   : Specify the number of columns in the LCD
**         	RS     : Register select pin
**         	EN     : Enable pin
**         	d4     : Data pin 0 (Connected to D4 pin in the LCD)
**         	d5     : Data pin 1 (Connected to D5 pin in the LCD)
**         	d6     : Data pin 2	(Connected to D6 pin in the LCD)
**         	d7     : Data pin 3	(Connected to D7 pin in the LCD)
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_lcd_init(T_UBYTE cols, T_UBYTE rows, T_UBYTE RS, T_UBYTE EN, T_UBYTE d4, T_UBYTE d5, T_UBYTE d6, T_UBYTE d7){

	LCD.rows = rows;
	LCD.cols = cols;

	LCD.rs = RS;
	LCD.en = EN;
	
	LCD.d4 = d4;
	LCD.d5 = d5;
	LCD.d6 = d6;
	LCD.d7 = d7;
	
	pinDirection(EN, OUTPUT);
	pinDirection(RS, OUTPUT);
	
	pinDirection(d4, OUTPUT);
	pinDirection(d5, OUTPUT);
	pinDirection(d6, OUTPUT);
	pinDirection(d7, OUTPUT);
	
	LCD.reset();         		// Call LCD reset
	
	LCD.command(0x28);       	// 4-bit mode - 2 line - 5x7 font. 
	LCD.command(0x0C);       	// Display no cursor - no blink.
	LCD.command(0x06);       	// Automatic Increment - No Display shift.
	LCD.command(0x80);       	// Address DDRAM with 0 offset 80h.	
}

/*
** ===================================================================
**     Function : _OSWarrior_lcd_push_enable
**
**     Description :
**         	This function just push the enable signal on the LCD. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_lcd_push_enable(void)
{
	writePin(LCD.en, LOW);
	writePin(LCD.en, HIGH);
	writePin(LCD.en, LOW);
}

/*
** ===================================================================
**     Function : LCD.reset
**     Handler  : _OSWarrior_lcd_reset
**
**     Description :
**         	This function reset the LCD Display. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_reset(void)
{
	writePin(LCD.en, 1);
	writePin(LCD.rs, 1);
	writeNibble( 0x0F , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	delay(20);
	
	writeNibble( 0x03 , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
	delay(10);
	
	writeNibble( 0x03 , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
	delay(1);
	
	writeNibble( 0x03 , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
	delay(1);
	
	writeNibble( 0x02 , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
	delay(1);
}

/*
** ===================================================================
**     Function : LCD.command
**     Handler  : _OSWarrior_lcd_cmd
**
**     Description :
**         	This function executes a command on the LCD display. 
**     
**     Parameters  : 
**         	cmd    : command code to be executed 
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_cmd (T_UBYTE cmd)
{
	writePin(LCD.rs, 0);
	writeNibble( ((cmd >> 4) & NIBBLE_MASK ) , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
	writeNibble( (cmd & NIBBLE_MASK) , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
	delay(1);
}	

/*
** ===================================================================
**     Function : LCD.printChar
**     Handler  : _OSWarrior_lcd_print_char
**
**     Description :
**         	This function prints a single character in the LCD where
**         	is the cursor. 
**     
**     Parameters  : 
**         	data   : ASCII value to be printed
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_print_char(T_UBYTE data)
{
	if(!data) return;
	writeNibble( (data >> 4), LCD.d7, LCD.d6, LCD.d5, LCD.d4 );		//Write higher nibble
	writePin(LCD.rs, 1);
	_OSWarrior_lcd_push_enable();
	writeNibble( data, LCD.d7, LCD.d6, LCD.d5, LCD.d4 );			//Write lower nibble
	writePin(LCD.rs, 1);
	_OSWarrior_lcd_push_enable();
	delay(1);		
}

/*
** ===================================================================
**     Function : LCD.print
**     Handler  : _OSWarrior_lcd_print
**
**     Description :
**         	This function prints a character array to the LCD Display. 
**     
**     Parameters  : 
**         	str    : character array to be printed
**     
**     Returns     : Nothing
** ===================================================================
*/

void _OSWarrior_lcd_print(T_UBYTE *str)
{
	while (*str)
	{
		_OSWarrior_lcd_print_char(*str);
		str++;
	}
}

/*
** ===================================================================
**     Function : LCD.printNum
**     Handler  : _OSWarrior_lcd_print_num
**
**     Description :
**         	This function prints a number in the LCD Display.
**     
**     Parameters  : 
**         	number : number to send
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_print_num (int number)
{
	number_explode( number, _OSWarrior_lcd_print_char, 0);
}

/*
** ===================================================================
**     Function : LCD.printDigits
**     Handler  : _OSWarrior_lcd_print_digits
**
**     Description :
**         	This function prints a number in the LCD Display
**         	where the quantity of digits to display can be configured 
**         	by the user. 
**         	
**         	Example: for the number 75 and 3 digits this function 
**         	will print 075. 
**     
**     Parameters  : 
**         	number : number to send
**         	digits : the number of digits to be displayed
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_print_digits (int number, int digits)
{
	number_explode( number, _OSWarrior_lcd_print_char, digits);
}

/*
** ===================================================================
**     Function : LCD.printDigits
**     Handler  : _OSWarrior_lcd_print_digits
**
**     Description :
**         	This function prints a number in the LCD Display
**         	where the quantity of digits to display can be configured 
**         	by the user. 
**         	
**         	Example: for the number 75 and 3 digits this function 
**         	will print 075. 
**     
**     Parameters  : 
**         	number : number to send
**         	digits : the number of digits to be displayed
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_print_float (T_FLOAT number, int num_decimals)
{
	number_explode_FloatNumbers( number, _OSWarrior_lcd_print_char, num_decimals);
}

/*
** ===================================================================
**     Function : LCD.customChar
**     Handler  : _OSWarrior_lcd_build
**
**     Description :
**         	This function is able to create a custom character in the
**         	LCD Display DRAM memory. 
**     
**     Parameters  : 
**         	location  : sets the DRAM memory address to store 
**         				the custom character 
**         	ptr    	  : custom character data array 
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_build(T_UBYTE location, T_UBYTE *ptr)
{
	/*		
	T_UBYTE degree_symbol[8] = {0x1C,0x14,0x1C,0x00,0x00,0x00,0x00,0x00};
	*/
	register T_UBYTE i;
	if(location<8){
		LCD.command(0x40+(location*8));
		for(i=0;i<8;i++) _OSWarrior_lcd_print_char( ptr[ i ] );
	}
}

/*
** ===================================================================
**     Function : LCD.setCursor
**     Handler  : _OSWarrior_lcd_setCursor
**
**     Description :
**         	This function locates the LCD Display cursor to the
**         	specified location defined by the user. 
**     
**     Parameters  : 
**         	col    : column to locate the cursor (x-axis)
**         	row    : row to locate the cursor (y-axis)
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_setCursor (int col, int row) 
{
	//Position the LCD cursor; that is, set the location at which 
	//subsequent text written to the LCD will be displayed.
	int i=0;
	LCD.command(LCD_HOME);
	//if we are on a 1-line display, set line_num to 1st line, regardless of given
	if (row > LCD.rows) 	row = 1;
	//offset 40 chars for each row requested
	col += 40 * (int)(row-1);
	//advance the cursor to the right according to position. (second line starts at position 40).
	for (i=0; i<col; i++) 	_OSWarrior_lcd_moveCursorRight();
}

/*
** ===================================================================
**     Function : _OSWarrior_lcd_moveCursorRight
**
**     Description :
**         	This function moves the LCD Display cursor from his 
**         	current position one space to the right. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_moveCursorRight (void) 
{
	LCD.command(LCD_MOVE_CURSOR_R);
}

/*
** ===================================================================
**     Function : _OSWarrior_lcd_moveCursorLeft
**
**     Description :
**         	This function moves the LCD Display cursor from his 
**         	current position one space to the left. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_moveCursorLeft (void) 
{
	LCD.command(LCD_MOVE_CURSOR_L);
}

/*
** ===================================================================
**     Function : LCD.blink
**     Handler  : _OSWarrior_lcd_blink
**
**     Description :
**         	This function allows the LCD Display cursor to blink. 
**     
**     Parameters  : 
**         	enable : Enable or Disable the cursor blinking
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_blink(int enable)
{
	if(enable == 0) LCD.command(LCD_BLINK_OFF);
	if(enable == 1) LCD.command(LCD_BLINK_ON);
}

/*
** ===================================================================
**     Function : LCD.display
**     Handler  : _OSWarrior_lcd_display
**
**     Description :
**         	This function control if the data is displayed or not
**         	in the LCD Display. 
**     
**     Parameters  : 
**         	enable : Enable or Disable the LCD Display
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_display(int enable)
{
	if(enable == 0) LCD.command(LCD_DISPLAY_OFF);
	if(enable == 1) LCD.command(LCD_DISPLAY_ON);
}

/*
** ===================================================================
**     Function : LCD.cursor
**     Handler  : _OSWarrior_lcd_cursor
**
**     Description :
**         	This function allows the LCD Display cursor to 
**         	be displayed. 
**     
**     Parameters  : 
**         	enable : Enable or Disable the cursor display
**     
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_cursor(int enable)
{
	if(enable == 0) LCD.command(LCD_CURSOR_OFF);
	if(enable == 1) LCD.command(LCD_CURSOR_ON);
}

/*
** ===================================================================
**     Function : LCD.clear
**     Handler  : _OSWarrior_lcd_clear
**
**     Description :
**         	This function clears all data in the LCD display. 
**     
**     Parameters  : Nothing
**     Returns     : Nothing
** ===================================================================
*/
	
void _OSWarrior_lcd_clear(void)
{
	LCD.command(LCD_CLR);
	LCD.command(LCD_HOME);
}
