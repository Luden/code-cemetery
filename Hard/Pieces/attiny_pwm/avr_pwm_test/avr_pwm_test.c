/*
 * avr_pwm_test.c
 *
 * Created: 08.04.2012 16:08:44
 *  Author: Admin
 */ 

#ifndef F_CPU
#define F_CPU 20000000UL
#endif


#include <avr/io.h>
#include <util/delay.h>

void InitPWM()
{
	// для attiny2313
   TCCR0A|=(1<<WGM00)|(1<<WGM01)|(1<<COM0A1); // быстрый pwm, включен без инверсии
   TCCR0B|=(1<<CS00); // предделитель 1
   DDRB|=(1<<PB2); // выход 0C0A
}

void SetPWMOutput(uint8_t duty)
{
   OCR0A=duty;
}

int main()
{
   uint8_t brightness=0;

   //Initialize PWM Channel 0
   InitPWM();

   //Do this forever

   while(1)
   {
      //Now Loop with increasing brightness

      for(brightness=0;brightness<255;brightness++)
      {
         //Now Set The Brighness using PWM

         SetPWMOutput(brightness);

         //Now Wait For Some Time
         _delay_ms(1);
      }

      //Now Loop with decreasing brightness

      for(brightness=255;brightness>0;brightness--)
      {
         //Now Set The Brighness using PWM

         SetPWMOutput(brightness);

         //Now Wait For Some Time
         _delay_ms(1);
      }
   }
}