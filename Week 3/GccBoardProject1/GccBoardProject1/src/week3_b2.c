#define F_CPU 8E6
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include "lcd.h"

int volatile msCount = 0;

void wait(int ms)
{ // Wait methode
	for (int i = 0; i < ms; i++)
	_delay_ms(1);
}

ISR(TIMER2_COMP_vect) // Wordt getriggered bij een overflow.
{
	msCount++;
	if (msCount % 40 == 0) // periodetijd is 40ms
	{
		PORTD |= 1 << 7;
	}
	else if (msCount % 40 == 15) // periodetijd is 40ms
	{
		PORTD &= 0b00000000;
	}
}

void timerInitialize(void) // Initialiseren van de timer.
{
	OCR2 = 250; // Timer initialiseren op 0 (er is immers nog geen Overflow opgetreden).
	TIMSK |= 1 << 7; // TIMSK Overflow Interrupt Enable (pagina 162)
	TCCR2 = 0b00001011; // prescaler instellen
	sei(); // Interrupts enablen.
}

int main(void)
{
	DDRD = 0xFF; // Output mode.
	timerInitialize(); // Initialiseren van Timer.

	while (1)
	{
		// do something
		wait(10); // Korte delay van ongeveer 10 ms.
	}

	return 0;
}