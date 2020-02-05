/**
* \file
*
* \brief Empty user application template
*
*/

/**
* \mainpage User Application template doxygen documentation
*
* \par Empty user application template
*
* Bare minimum empty user application template
*
* \par Content
*
* -# Include the ASF header files (through asf.h)
* -# "Insert system clock initialization code here" comment
* -# Minimal main function that starts with a call to board_init()
* -# "Insert application code here" comment
*
*/

/*
* Include header files for all drivers that have been imported from
* Atmel Software Framework (ASF).
*/
/*
* Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
*/

#define F_CPU 8e6

#include <asf.h>
#include <inttypes.h>
#include <util/delay.h>
#include <stdbool.h>

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>


void wait(int ms)
{
	for (int i = 0; i<ms; i++)
	{
		_delay_ms(1);
	}
}

typedef struct {
	unsigned char data;
	unsigned int delay ;
} PATTERN_STRUCT;

PATTERN_STRUCT newPattern[] = {
	{0xF0,100}, {0x0F, 100}, {0xF0,100}, {0x0F, 100}, {0xF0,100}, {0x0F, 100} 
};

void display(int waitTime);

void s1(void);
void s2(void);
void s3(void);
void end(void);
void start(void);

typedef enum { D7, D6, D5 } ENUM_EVENTS;
typedef enum { START, STATE_1, STATE_2, STATE_3, END } ENUM_STATES;

typedef struct {
	void (*finit)(void);
	void (*fbody)(void);
	void (*fexit)(void);
	ENUM_STATES nextState;
} STATE_TRANSITION_STRUCT;

STATE_TRANSITION_STRUCT fsm[5][3] = {
	{ {s1,   NULL,  NULL, START}, 	{NULL, s1, NULL, STATE_1},		{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START},	{NULL, NULL, NULL, STATE_1},	{NULL, s2, NULL, STATE_2} },
	{ {NULL, start, NULL, START}, 	{NULL, s1, NULL, STATE_1}, 		{NULL, s3, NULL, STATE_3} },
	{ {NULL, NULL,  NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} },
	{ {NULL, start, NULL, START},	{NULL, end, NULL, END}, 		{NULL, end, NULL, END} }
};

ENUM_STATES state = START;

void handleEvent(ENUM_EVENTS event)
{
	// Call EXIT function old state
	if( fsm[state][event].fexit != NULL) {
		fsm[state][event].fexit() ;
	}
	
	// Set new state, -1 means
	state = fsm[state][event].nextState;

	// Call INIT function
	if( fsm[state][event].finit != NULL) {
		fsm[state][event].finit() ;
	}

	// Call BODY function
	if( fsm[state][event].fbody != NULL) {
		fsm[state][event].fbody() ;
	}
}

void s1(void){
	printf("s1\n");
}

void s2(void){
	printf("s2\n");
}

void s3(void){
	printf("s3\n");
}

void start(void){
	printf("start\n");
}

void end(void){
	printf("end\n");
}

int main (void)
{
	board_init();
	
	// OPDRACHT B.2
	
// 	DDRD = 0b11111111;
// 	
// 	while (1)
// 	{
// 		if(PORTD & 0b10000000)
// 		{
// 			PORTD = 0b01000000;
// 		}
// 		else
// 		{
// 			PORTD = 0b10000000;
// 		}
// 		wait(500);
// 	}
	
	
	// OPDRACHT B.3
	
// 	DDRD = 0b10000000;
// 	DDRC = 0b11111110;
// 	
// 	while (1)
// 	{
// 		if(PINC & 0b00000001)
// 		{
// 			PORTD = 0b10000000;
// 		wait( 500 );				
// 		PORTD = 0b00000000;
// 		wait( 500 );
// 		} 
// 		else
// 		{
// 			PORTD = 0b00000000;
// 		}
// 	}

//	OPDRACHT B.4
	
	DDRD = 0b11111111;
	
	while (1)
	{
		int bit = 0b10000000;
		for (int i = 0; i < 8; i++)
		{
			PORTD = bit >> i;
			wait(500);
		}
	}
	
	// OPDRACHT B.5
	
// 	DDRD = 0b11111111;
// 	while (1)
// 	{
// 		int index = 0;
//  		while( 1 ) 
// 		 {
// 			PORTD = newPattern[index].data;
// 			wait(newPattern[index].delay);
// 			index++;
// 		}
// 	}
// 	return 1;

	//	OPDRACHT B.6

// 	DDRD = 0b10000000;
// 	DDRC = 0b00000001;	
// 	while (1)
// 	{
// 		if(PORTC & 0b00000001)
// 		{
// 			state = !state;
// 		}
// 		
// 		if(state)	
// 		{
// 			display(1000);
// 		}
// 		else
// 		{
// 			display(250);		
// 		}
// 		
// 	}

// 	DDRD = 0b00001111;
// 	handleEvent(D6);
// 	handleEvent(D5);
// 	handleEvent(D5);
// 
// 	while (1)
// 	{
// 	}



	return 1;
}

void display(int waitTime) 
{
	PORTD ^= 0b10000000;
	wait(waitTime);
}
