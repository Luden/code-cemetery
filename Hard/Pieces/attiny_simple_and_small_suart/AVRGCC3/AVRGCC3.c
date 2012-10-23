#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#define UART_BAUD_RATE 9600

#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16l)-1)
 

void USART_Init( unsigned int baudrate );

unsigned char USART_Receive( void );

void USART_Transmit( unsigned char data );

 

int main( void ) //Главная функция

{

	USART_Init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); //Скорость соединения 19200 бит/с

	for(;;) 	    //Вечный цикл

	{

		USART_Transmit( USART_Receive() ); //Отправка принятого символа назад

	}

}

 

 

void USART_Init( unsigned int baudrate ) //Функция инициализации USART

{

	UBRRH = (unsigned char) (baudrate>>8);                  

	UBRRL = (unsigned char) baudrate;

	//UCSRA = (1<<U2X); //Удвоение скорости

	UCSRB = ( ( 1 << RXEN ) | ( 1 << TXEN ) ); //Разрешение на прием и н апередачу через USART

	UCSRC = (1<<USBS) | (3<<UCSZ0);

}

 

 

unsigned char USART_Receive( void ) //Функция приема данных

{

	while ( !(UCSRA & (1<<RXC)) ); 	//Ожидание приема символа

	return UDR; //Возврат символа

}

 

void USART_Transmit( unsigned char data ) //Функция отправки данных

{

	while ( !(UCSRA & (1<<UDRE)) ); //Ожидание опустошения буфера приема

	UDR = data; //Начало передачи данных			        

}
