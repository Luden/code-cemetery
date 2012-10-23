/*
 * tiny_timer_3h.c
 *
 * Created: 03.09.2012 0:41:33
 *  Author: Admin
 */ 

#ifndef F_CPU
#define F_CPU 9600000UL
#endif

#include <avr/io.h>
#include <avr/interrupt.h>

volatile unsigned long counter = 0;			// счетчик
volatile unsigned char working = 1;

void TimerInit()
{
	 // 1024 prescaler
    TCCR0B |= ((1 << CS02) | (1 << CS00));

    TIMSK0 |= (1 << TOIE0);  // enable overflow vector (8bit timer overflows every 256 ticks)

    sei(); //enable interrupts
}

ISR (TIM0_OVF_vect)  // timer0 overflow interrupt
{
	if(working)
	{
		counter++;
		if(counter % 395508 == 0) // (9600000гц / 1024 / 256) * 3600c * 3 = переполнений таймера за 3 часа
		{
			PORTB &= ~(1<<PB4);  // выключили реле
			working = 0; // и счетчик
		}			
	}
}

int main(void)
{
	DDRB = 1<<DDB4;
	TimerInit();
	
	PORTB |= 1<<PB4; // включили реле
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}