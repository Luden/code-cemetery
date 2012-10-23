#ifndef F_CPU
#define F_CPU 16000000UL
#endif

#include <stdlib.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include <avr/pgmspace.h>
#include <avr/eeprom.h>
#include <util/delay.h>

#include "uart.h"
#include "lcd.h"
#include "keyboard.h"

#define IsDigit(x) (x>='0' && x<='9')
#define Digit(x) x-'0'

/* 9600 baud */
#define UART_BAUD_RATE 9600

#define SERV_PORT PORTD
#define ENABLE_GEN1 7
#define ENABLE_GEN2 1
#define DISABLE_GEN1 2
#define DISABLE_GEN2 3
#define ENABLE_COUNT 4

#define GEN1_PIN 5
#define GEN2_PIN 6

#define GEN1_ENABLED (((PIND & (1<<ENABLE_GEN1)) == 0) && ((PIND & (1<<DISABLE_GEN1)) != 0))
#define GEN2_ENABLED (((PIND & (1<<ENABLE_GEN2)) == 0) && ((PIND & (1<<DISABLE_GEN2)) != 0))
#define COUNTER_ENABLED ((PIND & (1<<ENABLE_COUNT)) == 0)

volatile unsigned int counter = 0;			// счетчик
volatile unsigned int tickCount = 0;		// счетчик тиков
volatile unsigned int generator1 = 300;		// top генератора 1
volatile unsigned int generator2 = 300;		// top генератора 2
volatile unsigned int curGen1 = 0;			// текущий импульс генератора 1
volatile unsigned int curGen2 = 0;			// текущий импульс генератора 2
volatile unsigned int halfPeriod1 = 100;	// полупериод/делитель счетчика по таймеру генератора 1
volatile unsigned int halfPeriod2 = 100;	// полупериод/делитель счетчика по таймеру генератора 2
volatile unsigned int curHalfPeriod1 = 0;	// текущий импульс делителя счетчика по таймеру первого генератора
volatile unsigned int curHalfPeriod2 = 0;	// текущий импульс делителя счетчика по таймеру второго генератора
volatile char gen1Pause = 0;				// софтварная пауза первого генератора
volatile char gen2Pause = 0;				// софтварная пауза второго генератора
volatile char even1 = 0;
volatile char even2 = 0;
volatile char cycle1 = 0;
volatile char cycle2 = 0;

void Save()
{
	eeprom_write_word((uint16_t *)100, generator1);
	eeprom_write_word((uint16_t *)100, generator1);
	eeprom_write_word((uint16_t *)108, generator2);
	eeprom_write_word((uint16_t *)116, halfPeriod1);
	eeprom_write_word((uint16_t *)124, halfPeriod2);
	eeprom_write_byte((uint8_t *)132, cycle1);
	eeprom_write_byte((uint8_t *)136, cycle2);
}

void Load()
{
	generator1 = eeprom_read_word((uint16_t *)100);
	generator1 = eeprom_read_word((uint16_t *)100);
	generator2 = eeprom_read_word((uint16_t *)108);
	halfPeriod1 = eeprom_read_word((uint16_t *)116);
	halfPeriod2 = eeprom_read_word((uint16_t *)124);
	cycle1 = eeprom_read_byte((uint8_t *)132);
	cycle2 = eeprom_read_byte((uint8_t *)136);
	
	curHalfPeriod1 = 0;
	curHalfPeriod2 = 0;
	curGen1 = generator1;
	curGen2 = generator2;
	gen1Pause = 1;
	gen2Pause = 1;
}

void lcd_print(int number)
{
	char buff[10];
	itoa(number, buff, 10);
	lcd_puts(buff);
}

void lcd_printstat(const char * prefix, int number)
{
	lcd_clrscr();
	lcd_puts(prefix);
	lcd_getnewline();
	lcd_print(number);
}

void TimerInit()
{
	 // Set the Timer Mode to CTC
    TCCR0 |= ((1 << CS01) | (1 << CS00) | (1 << WGM01));

    // Set the value that you want to count to
    OCR0 = 25;

    TIMSK |= (1 << OCIE0);    //Set the ISR COMPA vect

    sei(); //enable interrupts
}

ISR(INT2_vect)
{
	counter++;
}

ISR (TIMER0_COMP_vect)  // timer0 overflow interrupt
{
	tickCount++; // общее число тиков
	
	// зацикливаем если нужно
	if((curGen1 == 0) && (cycle1)) curGen1 = generator1;
	if((curGen2 == 0) && (cycle2)) curGen2 = generator2;
	
	if ((curGen1 != 0) && (GEN1_ENABLED) && (!gen1Pause)) // если генератор включен
	{
		curHalfPeriod1++; // число импульсов за текущий полупериод
		if (curHalfPeriod1 >= halfPeriod1) // если отсчитали достаточное количество
		{
			curHalfPeriod1 = 0; // новый полупериод
			
			if(even1) // количество импульсов генератора декрементируется один раз за период (2 полупериода)
				curGen1--;
			even1 = 1 - even1;
			
			SERV_PORT ^= (1<<GEN1_PIN);
		}
	}
	else if (even1) // сброс четности импульса, если генератор выключен
		even1 = 0;
	
	if ((curGen2 != 0) && (GEN2_ENABLED) && (!gen2Pause) && (!COUNTER_ENABLED))
	{
		curHalfPeriod2++;	
		if (curHalfPeriod2 >= halfPeriod2)
		{
			curHalfPeriod2 = 0;
			
			if(even2)
				curGen2--;
			even2 = 1 - even2;
			
			SERV_PORT ^= (1<<GEN2_PIN);
		}
	}
	else if (even2)
		even2 = 0;
}

int InputNumber(char firstChar, char * endChar, const char * prefix)
{
	int result = 0;
	if(!IsDigit(firstChar))
		return 0;
		
	char currentKey = 0;	
	result += Digit(firstChar);
	
	lcd_printstat(prefix, result);
	
	do 
	{
		KEYB_ScanKeyboard();
		currentKey = KEYB_GetKey();		
		if (currentKey != 0)
		{
			if(IsDigit(currentKey))
			{
				result = result * 10 + Digit(currentKey);				
				lcd_printstat(prefix, result);
			}
			else
			{
				*endChar = currentKey;
				return result;
			}
		}
	} while (1);
}

char GetKey()
{
	char subKey = 0;
	while (!subKey)
	{
		KEYB_ScanKeyboard();
		subKey = KEYB_GetKey();
	}
	return subKey;
}

int main(void)
{
	// инициализация портов
	DDRD = 96; // порт D 11000000, старшие биты - генераторы
	PORTD = 159; // подтянутый
	
	DDRB = 0; // порт B вход
	PORTB = 0xff; // подтянутый
	
	GICR |= (1<<5); // INT2 enable

    unsigned int c;
    char buffer[10];
	
    //uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
    sei();
	
	int num = 0;
	
	KEYB_Init();
	lcd_init(LCD_DISP_ON);
	TimerInit();
	
	lcd_puts("Hello");
	
	Load(); // загрузка настроек
	
	// инициализация меню
	char menu[4][8];
	strcpy(menu[0], "полупер");
	strcpy(menu[1], "цикл");
	strcpy(menu[2], "сохр");
	strcpy(menu[3], "загр");
	
	char menuLenght = 4;
	
	// loop main menu
	while(1)
	{
		KEYB_ScanKeyboard();
		char key = KEYB_GetKey();
		char mode = '*';
		char curMenuItem = 0;
		char exitFlag = 0;
		unsigned int result = 0;
		if (key != 0) // меню здесь
		{
			switch(key)
			{
				lcd_clrscr();
				case '*': // сброс первого генератора
					curGen1 = generator1;
					gen1Pause = 1 - gen1Pause;
					break;
				
				case '#': // сброс второго генератора / счетчика
					curGen2 = generator2;
					gen2Pause = 1 - gen2Pause;
					counter = 0;
					break;
					
				case '0': // 0 меню доп функций
					while(!exitFlag)
					{
						lcd_clrscr();
						
						char acceptFlag = 0;
						lcd_putc('-');
						lcd_puts(menu[curMenuItem]);
						char nextMenuItem = curMenuItem + 1;
						if (nextMenuItem < menuLenght)
						{
							lcd_getnewline();
							lcd_putc(' ');
							lcd_puts(menu[nextMenuItem]);
						}							
							
						char subKey = GetKey();							
						switch(subKey)
						{
							case '*':
								acceptFlag = 1;
								break;
							case '0':
								exitFlag = 1;
								break;
							case '2':
								if (curMenuItem > 0)
									curMenuItem--;
								break;
							case '8':
								if (curMenuItem < menuLenght - 1)
									curMenuItem++;
								break;
							default:
								continue;
						}
							
						if(exitFlag)
							break;
								
						if(!acceptFlag)
							continue;
								
						// собственно обработка кнопок подменю
						char cChar = 0;
						switch(curMenuItem)
						{
							case 0: // полупер
								result = InputNumber(key, &mode, "Полупер:");
								if (result == 0) break;
								if(mode=='*') // от того чем закончился ввод зависит какой генератор настраиваем
									halfPeriod1 = result;
								else halfPeriod2 = result;
								exitFlag = 1;
								break;
								
							case 1: // цикл								
								while(!cChar)
								{
									lcd_clrscr();
									
									if(cycle1)
										lcd_puts("цкл1 вкл");
									else lcd_puts("цкл1 отк");
									
									lcd_getnewline();
									
									if(cycle2)
										lcd_puts("цкл2 вкл");
									else lcd_puts("цкл2 отк");								
									
									cChar = GetKey();
									if(cChar == '1')
									{
										if(cycle1)
											cycle1 = 0;
										else cycle1 = 1;
										cChar = 0;
									}
									if(cChar =='2')
									{
										if(cycle2)
											cycle2 = 0;
										else cycle2 = 1;
										cChar = 0;
									}									
								}
								
								break;
							
							case 2: // сохр
								lcd_clrscr();
								lcd_puts("Saving");
								Save();
								break;
							
							case 3: // загр
								lcd_clrscr();
								lcd_puts("Loading");
								Load();
								break;								
						}
					}
					break;
					
				default: // цифра 1-9
					result = InputNumber(key, &mode, "Кол.имп:");
					if(mode=='*') // от того чем закончился ввод зависит какой генератор настраиваем
					{
						generator1 = result;
						curGen1 = result;
					}						
					else 
					{
						generator2 = result;
						curGen2 = result;
					}						
					break;
			}			
		}
		
		// генераторы всегда останавливаются в нулевом положении
		if((!GEN1_ENABLED)||(gen1Pause)||(curGen1==0))
			SERV_PORT &= (~(1<<GEN1_PIN));
			
		if((!GEN2_ENABLED)||(gen2Pause)||(curGen2==0))
			SERV_PORT &= (~(1<<GEN2_PIN));
		
		// отображение не чаще чем раз в 1000 тиков
		if(tickCount > 1000)
		{
			tickCount = 0;		
			// первый генератор всегда отображается		
			char buff1[5];
			itoa(curGen1,buff1,10);
			lcd_clrscr();
			if(gen1Pause)
				lcd_puts("G1.");
			else lcd_puts("G1:");
			lcd_puts(buff1);
			lcd_getnewline();
		
			if (COUNTER_ENABLED) // счетчик
			{	
				char buff2[5];
				itoa(counter,buff2,10);
				lcd_puts("С1:");
				lcd_puts(buff2);
			}
			else // второй генератор
			{
				char buff2[5];
				itoa(curGen2,buff2,10);
				if(gen2Pause)
					lcd_puts("G2.");
				else lcd_puts("G2:");
				lcd_puts(buff2);
			}
		}		
		
	}
}