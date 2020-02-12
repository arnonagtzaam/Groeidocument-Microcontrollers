#define F_CPU 8e6

#include <avr/io.h>
#include <inttypes.h>
#include <util/delay.h>

#define RS PORTC2
#define EN PORTC3

#define LCD_Dir DDRC
#define LCD_Port PORTC

void init()
{
		LCD_Dir = 0xFF;						/* Make LCD command port direction as o/p */
		_delay_ms(20);						/* LCD Power ON delay always >15ms */
		
		LCD_Command(0x33);
		LCD_Command(0x32);		    		/* send for 4 bit initialization of LCD  */
		LCD_Command(0x28);              	/* Use 2 line and initialize 5*7 matrix in (4-bit mode)*/
		LCD_Command(0x0c);              	/* Display on cursor off*/
		LCD_Command(0x06);              	/* Increment cursor (shift cursor to right)*/
		LCD_Command(0x01);              	/* Clear display screen*/
		_delay_ms(2);
		LCD_Command (0x80);
}

void display_text(char *str)
{
		int i;
		for(i=0;str[i]!=0;i++)				/* Send each char of string till the NULL */
		{
			LCD_Char (str[i]);
		}
}

void LCD_Char( unsigned char data )
{
	LCD_Port = (LCD_Port & 0x0F) | (data & 0xF0); /* sending upper nibble */
	LCD_Port |= (1<<RS);				/* RS=1, data reg. */
	LCD_Port|= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (data << 4); /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

void set_cursor(int position)
{
	
}

void LCD_Command( unsigned char cmnd )
{
	LCD_Port = (LCD_Port & 0x0F) | (cmnd & 0xF0); /* sending upper nibble */
	LCD_Port &= ~ (1<<RS);				/* RS=0, command reg. */
	LCD_Port |= (1<<EN);				/* Enable pulse */
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);

	_delay_us(200);

	LCD_Port = (LCD_Port & 0x0F) | (cmnd << 4);  /* sending lower nibble */
	LCD_Port |= (1<<EN);
	_delay_us(1);
	LCD_Port &= ~ (1<<EN);
	_delay_ms(2);
}

