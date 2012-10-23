#define F_CPU 20000000L

#include <inttypes.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#ifndef __AVR_ATtiny2313__
#define __AVR_ATtiny2313__
#endif

#define UART_BAUD_RATE 9600

#include "USI_I2C.h"
#include "uart.h"

// CONSTANTS
#define DS1307		0x68

uint8_t BCD2DEC(uint8_t bcd) {
	return (bcd & 0xF) + ((bcd >> 4) * 10);
}

uint8_t DEC2BCD(uint8_t dec) {
	return (dec % 10) | ((dec / 10) << 4);
}

typedef struct Time 
{
	uint8_t year;
	uint8_t month;
	uint8_t day;
	uint8_t dayOfWeek;
	uint8_t hour;
	uint8_t minute;
	uint8_t second;
} _Time;

void SetTime(_Time * time)
{
	uint8_t buf[9];
	buf[0] = (DS1307 << 1) | 0;	// установка адреса | 0 писать/ 1 читать
	buf[1] = 0;
	buf[2] = DEC2BCD(time->second);
	buf[3] = DEC2BCD(time->minute);
	buf[4] = DEC2BCD(time->hour);
	buf[5] = time->dayOfWeek;
	buf[6] = DEC2BCD(time->day);
	buf[7] = DEC2BCD(time->month);
	buf[8] = DEC2BCD(time->year);
	I2C_xfer(buf, 9);
}

void GetTime(_Time * time)
{
	uint8_t buf[8];
	buf[0] = (DS1307 << 1) | 0;
	buf[1] = 0x00;
	I2C_xfer(buf, 2);
	buf[0] |= 1;
	I2C_xfer(buf, 8);
	time->second = BCD2DEC(buf[1]);
	time->minute = BCD2DEC(buf[2]);
	time->hour = BCD2DEC(buf[3]);
	time->dayOfWeek = BCD2DEC(buf[4]);
	time->day = BCD2DEC(buf[5]);
	time->month = BCD2DEC(buf[6]);
	time->year = BCD2DEC(buf[7]);
}

void GetTimeString(_Time * time)
{
	uint8_t tempBuf[6];
	itoa(time->day, tempBuf, 10);	
	uart_puts(tempBuf);
	uart_putc('.');
	itoa(time->month, tempBuf, 10);	
	uart_puts(tempBuf);
	uart_putc('.');
	itoa(time->year, tempBuf, 10);	
	uart_puts(tempBuf);
	uart_putc(' ');
	
	itoa(time->hour, tempBuf, 10);	
	uart_puts(tempBuf);
	uart_putc(':');
	itoa(time->minute, tempBuf, 10);	
	uart_puts(tempBuf);
	uart_putc(':');
	itoa(time->second, tempBuf, 10);	
	uart_puts(tempBuf);
	uart_puts("\r\n");
}


int main(void)
{
	_Time time;
	time.year = 12;
	time.month = 12;
	time.day = 31;
	time.dayOfWeek = 2;
	time.hour = 23;
	time.minute = 59;
	time.second = 50;	
	
	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU));
	I2C_init();
	sei();
		
	uart_puts("\r\nHell low\r\n");
	
	SetTime(&time);

	while (1) 
	{
		GetTime(&time);
		GetTimeString(&time);
		_delay_ms(250);
	}	
}