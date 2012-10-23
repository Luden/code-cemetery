/*
 * AVRGCC1.c
 *
 * Created: 24.11.2011 22:27:11
 *  Author: Admin
 */ 

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

#ifndef F_CPU
#define F_CPU 1600000
#endif

int speed;

void delay_ms( int ms ) 
 { 
    for (int i = 0; i < ms; i++) 
    { 
       _delay_ms(1); 
    } 
 }

int main(void)
{
	DDRD = 0xFF;
	DDRB = 0x00;
	PORTB = 0xFF;
	
	char working = 0;
	char working2 = 0;
	speed = 20;
	
    //PCMSK |= (1 << PCINT3);  // set PCINT0 to trigger an interrupt on state change 
	//GIMSK  |= (1<<PCIE);
	//sei(); 
	
	char lastPinState = 1;
	
    while(1)
    {
		if(!(PINB & (1<<PINB6))) // B6 низкий - кран нормально открытый (высокий сигнал == закрыт)
		{
			if((working)&&(!(PINB & (1<<PINB2)))) // надо лить и сигнал низкий (кран открыт) - льЄм
			{
				PORTD |= (1<<6); // льЄм по D6 если сигнал B2
			}
			if((working2)&&(!(PINB & (1<<PINB4)))) // льЄм по D5 если сигнал по B4
			{
				PORTD |= (1<<5);
			}
			delay_ms(speed);
			
			//if((working)&&(!(PINB & (1<<PINB2))))
			if(working)
			{
				PORTD &=~(1<<6);
			}
			if(working2)//&&(!(PINB & (1<<PINB4))))
			{
				PORTD &=~(1<<5);				
			}
			delay_ms(speed);
		}
		else // Ѕ6 высокий - кран нормально закрытый
		{
			if((working)&&(PINB & (1<<PINB2))) // надо лить и сигнал высокий (кран открыт) - льЄм
			{
				PORTD |= (1<<6);
			}
			if((working2)&&(PINB & (1<<PINB4)))
			{
				PORTD |= (1<<5);
			}							
			delay_ms(speed);				
		
			if(working)//&&(PINB & (1<<PINB2))) // надо лить и сигнал высокий (кран открыт) - льЄм
			{
				PORTD &=~(1<<6);
			}
			if(working2)//&&(PINB & (1<<PINB4)))
			{			
				PORTD &=~(1<<5);
			}			
			delay_ms(speed);						
		}
		
		if(!(PINB & (1<<PINB5)))
		{
			working2 = 1;			
		}
		
		if(!(PINB & (1<<PINB1)))
		{
			working = 1;			
		}
		
		if(!(PINB & (1<<PINB0)))
		{
			working = 0;
			working2 = 0;
			
			PORTD &=~(1<<6);
			PORTD &=~(1<<5);
		}
		if ((PINB & (1<<PINB3)) != lastPinState)
		{
			delay_ms(20);
			if((PINB & (1<<PINB3)) != lastPinState)
			{
				if(!(PINB & (1<<PINB3)))
				{
					if(speed == 5) speed = 40;
					else if(speed == 40) speed=20;
					else if(speed == 20) speed=10;
					else if(speed == 10) speed=5;
				}					
				lastPinState = (PINB & (1<<PINB3));
			}
		}
    }
}

//SIGNAL(SIG_PCINT)
//{
//	if(!(PINB & (1<<PINB3)))
//	{
//		
//	}
//}