#include <avr/io.h>

#ifndef F_CPU
#define F_CPU 20000000UL
#endif

#define UART_BAUD_RATE 9600

#define UART_BAUD_SELECT(baudRate,xtalCpu) ((xtalCpu)/((baudRate)*16l)-1)
 

void USART_Init( unsigned int baudrate );

unsigned char USART_Receive( void );

void USART_Transmit( unsigned char data );

 

int main( void ) //������� �������

{

	USART_Init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) ); //�������� ���������� 19200 ���/�

	for(;;) 	    //������ ����

	{

		USART_Transmit( USART_Receive() ); //�������� ��������� ������� �����

	}

}

 

 

void USART_Init( unsigned int baudrate ) //������� ������������� USART

{

	UBRRH = (unsigned char) (baudrate>>8);                  

	UBRRL = (unsigned char) baudrate;

	//UCSRA = (1<<U2X); //�������� ��������

	UCSRB = ( ( 1 << RXEN ) | ( 1 << TXEN ) ); //���������� �� ����� � � ��������� ����� USART

	UCSRC = (1<<USBS) | (3<<UCSZ0);

}

 

 

unsigned char USART_Receive( void ) //������� ������ ������

{

	while ( !(UCSRA & (1<<RXC)) ); 	//�������� ������ �������

	return UDR; //������� �������

}

 

void USART_Transmit( unsigned char data ) //������� �������� ������

{

	while ( !(UCSRA & (1<<UDRE)) ); //�������� ����������� ������ ������

	UDR = data; //������ �������� ������			        

}
