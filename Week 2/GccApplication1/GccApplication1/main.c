#define F_CPU 8e6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

void opdracht1();
void opdracht2();
void opdracht3();

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
	
}


int main( void )
{
	//opdracht1();
	opdracht2();

	return 1;
}
