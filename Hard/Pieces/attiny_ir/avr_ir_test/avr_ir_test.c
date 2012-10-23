/*
 * avr_ir_test.c
 *
 * Created: 09.04.2012 1:05:28
 *  Author: Admin
 */ 

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

volatile char process = 0; 

void TimerInit()
{
	 // Set the Timer Mode to CTC
    TCCR1A |= (1 << WGM01);

	TCCR1B |= (1 << CS00);

    // Set the value that you want to count to
    OCR1A = 0x022B;

    TIMSK |= (1 << OCIE1A);    //Set the ISR COMPA vect

    sei(); //enable interrupts
}

char commandLength = 20;
char command[] = {0b00000000, 0b11111111, 0b11111111, 0b00000000, 0b01000101, 0b01000100, 0b00010001, 0b01010101, 0b00010101, 0b01010101, 0b01010100, 0b01000100, 0b01000100, 0b01000100, 0b01010101, 0b01010101, 0b01000100, 0b01000100, 0b01000100, 0b01000100};
volatile char curByte = 0;
volatile char curPos = 0;
volatile char curPulse = 0;

ISR (TIMER1_COMPA_vect) 
{
	if(process)
	{
		if(curPos>=8)
		{
			curPos = 0;
			curByte++;
		}
		
        if (curByte >= commandLength)
        {
			process = 0;
			curByte = 0;
		}
		
		if((command[curByte]) & (1 << curPos))
		{
			PORTB ^= (1 << PINB0);
		}
		else
		{
			PORTB &= (~(1 << PINB0));
		}
		
		curPulse++;
		if(curPulse >= 22)
		{
			curPulse = 0;
			curPos++;
		}
	}
}

int main(void)
{
	DDRB |= (1);	
	
	TimerInit();
	
    while(1)
    {
		process = 1;
		PORTB = 0;
		_delay_ms(1000);
    }
}