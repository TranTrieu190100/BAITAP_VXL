/*
 * TRAITIMTHANG.cpp
 *
 * Created: 8/6/2021 9:34:16 PM
 * Author : KAITO
 */ 
/*
 * main.c
 *
 * Created: 8/6/2021 9:01:22 PM
 *  Author: KAITO
 */ 

#define F_CPU 8000000UL // cung tan so
#include <avr/io.h>
#include <avr/interrupt.h>// khai bao thu vien su dung ngat
#include <util/delay.h>
#include <stdio.h>

unsigned char  Code7[] = {0x3F,0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // led 7 catode
	
int dem = 0;
unsigned char x,y,z;

ISR(INT0_vect) // ngat 0 cho nut nhan 1 nap nhap nhay 10 lan
{	
	for (int i = 0; i < 10;i++)
	{
		PORTA = 0XFF;
		PORTB = Code7[i];
		_delay_ms(500);
		PORTA = 0;
		_delay_ms(100);
	}
}

ISR(INT1_vect) // ngat hai cho hieu ung
{
	dem ++;
} 

void HU1() // led chay qua chay lai 
{
	PORTA = 0B00000001;
	_delay_ms(100);
	for( int i = 0; i < 8; i ++ )
	{
		PORTA = (PORTA << 1);
		_delay_ms(100);	
	}
	PORTA = 0B10000000;
	_delay_ms(100);
	for(int i = 0; i < 8;i++)
	{
		PORTA = (PORTA >> 1);
		_delay_ms(100);
	}
}

void HU2() // led chay tang dan tat dan 
{
	PORTA = 0B00000001;
	_delay_ms(600);
	for( int i = 0; i < 8; i ++ )
	{
		PORTA = (PORTA << 1) + 0b00000001;
		_delay_ms(500);
		
	}
	PORTA = 0b10000000;
	_delay_ms(500);
	for(int i = 0; i < 8;i++)
	{
		PORTA = (PORTA >> 1) + 0b10000000;
		_delay_ms(500);
	}
}

void HU3() // SANG TU HAI BEN VAO 
{
	PORTA = 0; // SANG HAI BEN VAO TUNG CON 
	x= 0b10000000;
	y= 0b00000001;
	_delay_ms(500);
	for(int i = 0 ; i < 8; i ++ )
	{
		PORTA = y + x;
		_delay_ms(500);
		y = (y << 1) ;
		x = (x >> 1) ;	
	}
	x= 0b10000000; // SANG DAN TU HAI BEN VAO 
	y= 0b00000001;
	_delay_ms(500);
	for(int i = 0 ; i < 4; i ++ )
	{
		PORTA = y + x;
		_delay_ms(500);
		y = (y << 1) + 0b00000001;
		x = (x >> 1) + 0b10000000;
		
	}
	x = 0b11110000; // SANG TU TRONG RA 
	y = 0b00001111;
	for(int i = 0 ; i < 4; i ++ )
	{
		PORTA = y + x;
		_delay_ms(500);
		y = (y >> 1) ;
		x = (x << 1) ;
		
	}	
}

void HU4() // SANG DON TRAI SANG PHAI_PHAI SANG TRAI 
{
	 y = 0;
	
	for (int i= 8 ;i > 0 ; i --)			// chay 8 lan nhung bat dau tu 8 
	{	 
		x = 0b00000001;						// cho bien x chay tu pit 0 -> 8 ( trai sang phai )
		for (int j = 0 ;  j < i ; j++ )
		{				
			PORTA = x  + y ;				// de luu gia tri cuoi 
			x = x << 1;						// dich sang trai 1 bit <=> dich phai ben ngoai phan cung 
			_delay_ms(500); 
		}
		y = PORTA ;							// y luu lai gia tri cua cua PORT de cong vao 
	}
	// chay nguoc lai tu phai sang trai 
	y = 0;
		for (int i= 8 ;i > 0 ; i --)			
	{
		x = 0b10000000;						
		for (int j = 0 ;  j < i ; j++ )
		{
			PORTA = x  + y ;				
			x = x >> 1;						
			_delay_ms(500);
		}									
		y = PORTA ;							
	}
}

void HU5() // SANG DON TU HAI BEN VAO 
{
	z = 0;
	for(int i = 4 ; i > 0; i--)
	{
		x = 0b00000001;
		y = 0b10000000;
		for(int j = 0; j < i; j++)
		{
			PORTA = x + y + z ;
			x = x << 1;
			y = y >> 1 ;
			_delay_ms(200);
		}
		z = PORTA;
	}
	z = 0;
	for(int i = 4 ; i > 0; i--)
	{
		x = 0b0010000;
		y = 0b0001000;
		for(int j = 0; j < i; j++)
		{
			PORTA = x + y + z ;
			x = x << 1;
			y = y >> 1 ;
			_delay_ms(200);
		}
		z = PORTA;
	}
}

void HU6() //  1 CON CHAY QUA HAI CON CHAY LAI 
{
	x =0b00000001;
	for(int i = 4; i > 0; i--) // cho chay 4 lan 
	{
		for (int j =  0; j < 2*i; j ++) // chay qua 2*i chay lan dau 8 lan tuong ung 8 con s do 6 4 .
		{
			PORTA = x;
			_delay_ms(200);
			x = x << 1;
		}
		x =PORTA;
		x = ( x >> 1 ) + 0b10000000;
		for(int j = 0; j <2*i -1; j++) // chay lai theo lan le 7 5 3 moi lan nhu vay dieu cong them bit
		{
			PORTA  = x ;
			_delay_ms(200);
			x = x >> 1;
		}
		x =PORTA ;
		x = (x << 1)+ 0b00000001;
	}
}

int main(void)
{
	
	DDRA = 0xff; PORTA = 0; // 0xff khai bao la pora xuat vs gia tri ban dau 0
	DDRB = 0xff; PORTB = 0;
	
	DDRD = 0xff;// khai bao nhan gia tri tu ben ngoai Pina
	PORTD = 0xff; // cho xuat la 1

	GICR |=(1 << INT0) ; GICR |=(1 << INT1); // chon ngat 0 ; PO va ngat 1 RTD.2
	MCUCR |= (1 << ISC01 ) | (1 << ISC11);  // chon che do tac dong ngat 
	sei();
    while(1)
    {
			PORTB = Code7[0];			
				if(dem == 1)
				{
					PORTB = Code7[dem];
					HU1();
				}
				else if(dem == 2)
				{
					PORTB = Code7[dem];
					HU2();
				}
				else if(dem == 3)
				{
					PORTB = Code7[dem];
					HU3();
				}
				else if(dem == 4)
				{
					PORTB = Code7[dem];
					HU4();
				}
				else if(dem == 5)
				{
					PORTB = Code7[dem];
					HU5();
				}
				else if(dem == 6)
				{
					PORTB = Code7[dem];
					HU6();
				}
    }
}
