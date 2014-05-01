/*
** ===================================================================
** LCD includes
** ===================================================================
*/

#include "oswlib/settings.h"
#include "oswlib/LCD/lcd.h"

PRIVATE_DATA T_UBYTE LCD_DISPLAY = 0x0F;

/*
** ===================================================================
	** LCD Structure Definition
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
	_OSWarrior_lcd_clear_row,
	
	_OSWarrior_lcd_build,
	_OSWarrior_lcd_cmd, 
	
	_OSWarrior_lcd_write, 
	_OSWarrior_lcd_write_char, 
	
	_OSWarrior_lcd_print, 
	_OSWarrior_lcd_print_digits, 
	_OSWarrior_lcd_print_float, 
	
	_OSWarrior_lcd_setCursor, 
	
	_OSWarrior_lcd_display,
	_OSWarrior_lcd_cursor,
	_OSWarrior_lcd_blink, 
	
	_OSWarrior_lcd_scrollLeft, 
	_OSWarrior_lcd_scrollRight, 
};


/*
** ===================================================================
** LCD functions definition
** ===================================================================
*/

void _OSWarrior_lcd_init(T_UBYTE rows, T_UBYTE cols, T_UBYTE RS, T_UBYTE EN, T_UBYTE d4, T_UBYTE d5, T_UBYTE d6, T_UBYTE d7){

	LCD.rows = rows;
	LCD.cols = cols;

	LCD.rs = RS;
	LCD.en = EN;
	
	LCD.d4 = d4;
	LCD.d5 = d5;
	LCD.d6 = d6;
	LCD.d7 = d7;
	
	pinMode(EN, OUTPUT);
	pinMode(RS, OUTPUT);
	
	pinMode(d4, OUTPUT);
	pinMode(d5, OUTPUT);
	pinMode(d6, OUTPUT);
	pinMode(d7, OUTPUT);
	
	LCD.reset();         		// Call LCD reset
	
	LCD.command(0x28);       	// 4-bit mode - 2 line - 5x7 font. 
	//LCD.command(0x0C);       	// Display no cursor - no blink.
	LCD.command(0x06);       	// Automatic Increment - No Display shift.
	LCD.command(0x80);       	// Address DDRAM with 0 offset 80h.	

	LCD.command(LCD_DISPLAY);	// Display default configurations, Display ON, Cursor ON and Blink ON.	
}

void _OSWarrior_lcd_push_enable(void)
{
	digitalWrite(LCD.en, LOW);
	digitalWrite(LCD.en, HIGH);
	digitalWrite(LCD.en, LOW);
}

void _OSWarrior_lcd_reset(void)
{
	writeNibble( 0x0F , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	digitalWrite(LCD.en, 1);
	digitalWrite(LCD.rs, 1);
	delay(20);
	
	
	digitalWrite(LCD.rs, 0);
	
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
	
	LCD.command(0x02);
	
}
	
void _OSWarrior_lcd_cmd (T_UBYTE cmd)
{
	digitalWrite(LCD.rs, 0);
	
	writeNibble( ((cmd >> 4) & NIBBLE_MASK ) , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
	
	writeNibble( (cmd & NIBBLE_MASK) , LCD.d7, LCD.d6, LCD.d5, LCD.d4 );
	_OSWarrior_lcd_push_enable();
		
	delay(1);
}	

void _OSWarrior_lcd_write_char(T_UBYTE data)
{
	//if(!data) return;
	writeNibble( (data >> 4), LCD.d7, LCD.d6, LCD.d5, LCD.d4 );		//Write higher nibble
	digitalWrite(LCD.rs, 1);
	_OSWarrior_lcd_push_enable();
	writeNibble( data, LCD.d7, LCD.d6, LCD.d5, LCD.d4 );			//Write lower nibble
	_OSWarrior_lcd_push_enable();
	delay(1);		
}

void _OSWarrior_lcd_write(T_UBYTE *str)
{
	while (*str)
	{
		_OSWarrior_lcd_write_char(*str);
		str++;
	}
}
	
void _OSWarrior_lcd_print (T_SLONG number)
{
	number_explode( number, _OSWarrior_lcd_write_char, 0);
}
	
void _OSWarrior_lcd_print_digits (T_SLONG number, int digits)
{
	number_explode( number, _OSWarrior_lcd_write_char, digits);
}
	
void _OSWarrior_lcd_print_float (T_FLOAT number, int num_decimals)
{
	number_explode_FloatNumbers( number, _OSWarrior_lcd_write_char, num_decimals);
}

void _OSWarrior_lcd_build(T_UBYTE location, T_UBYTE *ptr)
{
	/*		
	T_UBYTE degree_symbol[8] = {0x1C,0x14,0x1C,0x00,0x00,0x00,0x00,0x00};
	*/
	register T_UBYTE i;
	if(location<8){
		LCD.command(0x40+(location*8));
		for(i=0;i<8;i++) _OSWarrior_lcd_write_char( ptr[ i ] );
	}
}

void _OSWarrior_lcd_setCursor (int col, int row) 
{
	//Position the LCD cursor; that is, set the location at which 
	//subsequent text written to the LCD will be displayed.
		 
	unsigned int position = 0x80; 	//0x80; offset inicial
	if(row > LCD.rows) row = 0;		//if we are on a 1-line display, set line_num to 1st line, regardless of given
	if(col > LCD.cols) col = 15;	
	position += (64 * row) + col;	//Calculate the command to set cursor  
	LCD.command((char)position);	//Set the cursor position 
}

void _OSWarrior_lcd_moveCursorRight (void) 
{
	LCD.command(LCD_MOVE_CURSOR_R);
}

void _OSWarrior_lcd_moveCursorLeft (void) 
{
	LCD.command(LCD_MOVE_CURSOR_L);
}

void _OSWarrior_lcd_display(int enable)
{
	if(enable)	LCD_DISPLAY |= LCD_DISPLAY_MASK;
	else		LCD_DISPLAY = (T_UBYTE)(LCD_DISPLAY & ~LCD_DISPLAY_MASK);
	LCD.command(LCD_DISPLAY);
}

void _OSWarrior_lcd_cursor(int enable)
{
	if(enable)	LCD_DISPLAY |= LCD_CURSOR_MASK;
	else		LCD_DISPLAY = (T_UBYTE)(LCD_DISPLAY & ~LCD_CURSOR_MASK);
	LCD.command(LCD_DISPLAY);
}

void _OSWarrior_lcd_blink(int enable)
{
	if(enable)	LCD_DISPLAY |= LCD_BLINK_MASK;
	else		LCD_DISPLAY = (T_UBYTE)(LCD_DISPLAY & ~LCD_BLINK_MASK);
	LCD.command(LCD_DISPLAY);
}
	
void _OSWarrior_lcd_clear(void)
{
	LCD.command(LCD_CLR);
	LCD.command(LCD_HOME);
}

void _OSWarrior_lcd_scrollRight(void)
{
	LCD.command(LCD_SCROLL_R);
}

void _OSWarrior_lcd_scrollLeft(void)
{
	LCD.command(LCD_SCROLL_L);
}

void _OSWarrior_lcd_clear_row(int row)
{
	register int i = 0;
	_OSWarrior_lcd_setCursor(0,row);
	for(i=0;i<LCD.cols;i++)
		_OSWarrior_lcd_write_char(0x20);	//Prints blank space
}
