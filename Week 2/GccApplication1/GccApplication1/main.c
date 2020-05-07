#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

void opdracht1();
void opdracht2();
void opdracht3();
void opdracht4();
void opdracht5();

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT pattern[] = {
	{0b00000001, 150}, {0b00000010, 150}, {0b01000000, 150}, {0b00100000, 150},
	{0b00000001, 150}, {0b00000010, 150},
		
	{0b00000100, 150}, {0b00001000, 150}, {0b00010000, 150}, {0b01000000, 150}, 
	{0b00000100, 150}, {0b00001000, 150}, {0b00010000, 150}, {0b00100000, 150},
		
	{0b00000001, 150}, {0b00000010, 150}, {0b00000100, 150}, {0b00001000, 150},
	{0b00010000, 150}, {0b00100000, 0}
};

const unsigned char
Numbers [16] =
{
	// dPgfe dcba
	0b00111111, // 0
	0b00000110, // 1
	0b01011011, // 2
	0b01001111, // 3
	0b01100110, // 4
	0b01101101, // 5
	0b01111101, // 6
	0b00000111, // 7
	0b01111111, // 8
	0b01101111, // 9
	0b01110111, // A
	0b01111100, // B
	0b00111001, // C
	0b01011110, // D
	0b01111001, // E
	0b01110001, // F



};

void wait( int ms )
{
	for (int i=0; i<ms; i++)
	{
		_delay_ms( 1 );		// library function (max 30 ms at 8MHz)
	}
}



ISR( INT0_vect )	
{
	if (PORTB & 0b10000000)
	{
		PORTB = 0b00000001;
	}
	else 
	{
		PORTB = PORTB << 1;
		
	}
}


ISR( INT1_vect )
{	
	if (PORTB & 0b00000001)
	{
		PORTB = 0b10000000;
	} 
	else 
	{
		PORTB = PORTB >> 1;
	}
}

void opdracht1()
{
	// Init I/O
	DDRD = 0xF0;			// PORTD(7:4) output, PORTD(3:0) input

	// Init Interrupt hardware
	EICRA |= 0x0B;			// INT1 falling edge, INT0 rising edge
	EIMSK |= 0x03;			// Enable INT1 & INT0
	
	// Enable global interrupt system
	//SREG = 0x80;			// Of direct via SREG of via wrapper
	sei();

	while (1)
	{
		PORTD ^= (1<<7);	// Toggle PORTD.7
		wait( 500 );
	}
	
}

void opdracht2()
{
	DDRB = 0xFF;
	DDRA = 0xFF;
	
	PORTB = 0b00000001;
	
	EICRA |= 0x0F;
	EIMSK |= 0x03;
	sei();
	
	while(1)
	{

		
	}
}

void opdracht3() 
{
	while(1){
		for (int i = 0; i < 16; i++)
		{
			display(i);
			wait(1000);
		}
	}
}

void opdracht4()
{
	DDRC = 0xFF;	while (1)
	{
		int index = 0;
		while( pattern[index].delay != 0 ) {
			PORTC = pattern[index].data;
			wait(pattern[index].delay);
			index++;
		}
	}
}

void opdracht5()
{
	init();
	display_text("test");
	set_cursor(3);
}

void display(int digit){	DDRC = 0xFF;	if (digit >= 0 && digit <= 15 )
	{
		PORTC = Numbers[digit];
	}
	else 
	{
		PORTC = Numbers[14];
	}}

int main( void )
{

	//opdracht1();
	/*opdracht2();*/
	//opdracht3();
	//opdracht4();
	opdracht5();
	while(1);
	return 1;
}
