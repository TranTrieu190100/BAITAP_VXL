/*
 * BAI1_8LED_UART.cpp
 *
 * Created: 10/16/2021 3:37:08 PM
 * Author : TRIEU
 */ 
// bai tap 1: thu giao tiep c# vs phan men protues dieu khien don gian 
#define F_CPU 8000000UL // cung tan so 
#include <avr/io.h>
#include <avr/interrupt.h>// khai bao thu vien su dung ngat 
#include <util/delay.h>
#include <stdio.h>

//  cac ham giao tiep URAT 
void UART_Init()
{
	// set baud: 9600 va tan sao f =8MHz
	UBRRH =0;
	UBRRL = 51;
	UCSRA = 0X00;
	UCSRC =(1 << URSEL)|(1<<UCSZ1)|(1<<UCSZ0); // SET UP DATA FRAME 1 BIT STRAR_ 1BIT STOP_NO PARITY_8BIT FRAME
	UCSRB =(1<<RXEN)|(1<<TXEN)|(1<<RXCIE); // ENABLE RX+TX :KICH HOAT NGAT VA TRUYEN DU LIEU
	sei();
}
// nhan data
unsigned char usart_getchar()
{
	while(!(UCSRA &(1<<RXC))); // BIT RXC TREN UCDRA CHO BIET QUA TRINH NHAN KET THUC HAY CHUA 
	return UDR;
}
// Gui data
void usart_putchar(char data)
{
	/* wait for empty transmit buffer*/
	while(!(UCSRA &(1<<UDRE))) // CHECK UDRE tren thanh UCRA co bang khong hay chua neu khac 0 trar ve 0 thoat while
	;
	/* Put data into buffer, sends the data */
	UDR = data; // ghi gia tri len thanh ghi du lieu 
}
// gui s string 
void usart_write(char*string)
{
	int i = 0;
	for (i = 0; i < 255; i++)
	{
		if(string[i] != 0)
		{
			usart_putchar(string[i]);
		}
		else 
		{
			break;
		}
	}
}
// nhan a string 
void usart_read(char*string)
{
	char ch;
	int i = 0;
	for(i = 0; i < 9; i++)
	{
		ch = usart_getchar();
		*string = ch;
		string++;
	}
	
}

int main(void)
{
   UART_Init();
   DDRB =0xFF;
   PORTB = 0xFF;
   while (1) 
    { 
		// PORTB =0B111111110;
    }
}

ISR (USART_RXC_vect)
{
	char pc = UDR;
	switch (pc)
	{
		case '8':
		PORTB =0b11111110; // sang led 8
		break;
		case '7':
		PORTB =0b11111101;
		break;
		case '6':
		PORTB =0b11111011;
		break;
		case '5':
		PORTB =0b11110111;
		break;
		case '4':
		PORTB =0b11101111;
		break;
		case '3':
		PORTB =0b11011111;
		break;
		case '2':
		PORTB =0b10111111;
		break;
		case '1':
		PORTB =0b01111111; // sang led 1
		break;
		case '9':
		PORTB =0b101010101;
		break;
		case '0':
		PORTB =0b010101010;
		break;
		case 'a':
		{
			for(int i = 0; i < 10; i++) // cho led sang chop tat
			{
				PORTB =0b101010101;
				_delay_ms(100);
				PORTB =0b010101010;
				_delay_ms(100);
				
			}
			break;
			
			
		}
		
	}
}
