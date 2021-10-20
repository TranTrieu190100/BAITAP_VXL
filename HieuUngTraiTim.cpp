/*
 * TIM.cpp
 *
 * Created: 8/7/2021 10:21:47 PM
 * Author : KAITO
 */ 

#define F_LU 16MHz
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/delay.h>
unsigned char  Code7[] = {0x3F,0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // led 7 catode
unsigned int dem = 0;
unsigned char x,y,z,e, f;
ISR(INT1_vect) // ngat hai cho hieu ung
{
	dem ++;
	PORTC = Code7[dem];
}

void T1 () // CHOP TAT
{
	for(int i =0 ; i < 8 i++)
	{
	PORTA = 0XFF;
	PORTB = 0XFF;
	_delay_ms(200);
	PORTA = PORTB =0x00;
	_delay_ms(200);
	}
}

void T2() // 2/ CHAY QUA CHAY LAI 
{
	PORTA = 0B00000001;
	_delay_ms(200);
	for( int i = 0; i < 8; i ++ )
	{
		PORTB = PORTA = (PORTA << 1);
		_delay_ms(200);
	}
	PORTA = 0B10000000;
	_delay_ms(200);
	for(int i = 0; i < 8;i++)
	{
		PORTB = PORTA = (PORTA >> 1);
		_delay_ms(100);
	}
	// chay tu 1 den 16
	x = 0B00000001;
	_delay_ms(200);
	for( int i = 0; i < 8; i ++ ) // nua dau
	{
		x = (x << 1);
		PORTA = x;
		_delay_ms(200);
	}
	x = 0b00000001;
	for( int i = 0; i < 8; i ++ ) // nua s 
	{
		PORTB = x;
		_delay_ms(200);
		x = (x << 1);
	}
	PORTB =0;
	_delay_ms(200);	
	PORTA = 0B00000001;
	_delay_ms(200);
	PORTA = 0;
	_delay_ms(200);
	x = 0b10000000;
	for(int i = 0; i < 8;i++)
	{
		PORTB = x;
		_delay_ms(200);
		x = (x >> 1);	
	}
	PORTB = 0;
	PORTA = 0B10000000;
	_delay_ms(200);
	for(int i = 0; i < 8; i++)
	{
		PORTA = (PORTA >> 1);
		_delay_ms(200);
	}
}

void T3() // 2/ CHAY QUA CHAY LAI tang
{
	PORTA = 0B00000001;
	_delay_ms(200);
	for( int i = 0; i < 8; i ++ )
	{
		PORTB = PORTA = (PORTA << 1) + 0b00000001;
		_delay_ms(200);
	}
	PORTA = 0B10000000;
	_delay_ms(200);
	for(int i = 0; i < 8;i++)
	{
		PORTB = PORTA = (PORTA >> 1) + 0b10000000;
		_delay_ms(100);
	}
	// chay tu 1 den 16
	x = 0B00000001;
	PORTB = 0;
	_delay_ms(200);
	for( int i = 0; i < 8; i ++ ) // nua dau
	{
		
		PORTA = x;
		_delay_ms(200);
		x = (x << 1)+0B00000001;
	}
	x = 0b00000001;
	for( int i = 0; i < 8; i ++ ) // nua s
	{
		PORTB = x;
		_delay_ms(200);
		x = (x << 1)+0b00000001;
	}
	// chay 1 den 16
	PORTB = 0;
	_delay_ms(200);
	PORTA = 0B00000001;
	_delay_ms(200);
	x = 0b10000000;
	for(int i = 0; i < 8;i++)
	{
		PORTB = x;
		_delay_ms(200);
		x = (x >> 1) + 0b10000000;
		
	}
	//PORTA = 0B00000001;
	PORTA = 0B10000001;
	_delay_ms(200);
	for(int i = 0; i < 7; i++)
	{
		PORTA = (PORTA >> 1) + 0B10000001 ;
		_delay_ms(200);
	}
}

void T4() // SANG DON TU HAI BEN VAO
{
	z = 0; e = 0; // sang tu ngoai vao 
	for(int i = 8 ; i > 0; i--)
	{ 
		PORTA = z + 0b00000001; // sang PORT dau va cong them z de giua gia tra 
		_delay_ms(200);
		x = 0b00000010;
		y = 0b10000000;
		for(int j = 0; j < i; j++)
		{
			PORTA = x + z;
			PORTB = y + e;
			_delay_ms(200);
			x = (x << 1) ;
			y = (y >> 1) ;
		}
		z = PORTA;
		e = PORTB;
	}
	for(int i = 0; i < 3; i++ ) // cho led chop tat
	{
		PORTA = PORTB = 0b11111111;
		_delay_ms(500);
		PORTA = PORTB = 0;
		_delay_ms(500);
	}
	
	z = 0;e = 0;
	for(int i = 8; i > 0; i--) // sang nguoc lai tu duoi len 
	{
		PORTB = e + 0b00000001;
		_delay_ms(200);
		x = 0b10000000;
		y = 0b00000010;
		for(int j = 0; j < i; j++)
		{
			PORTA = x + z ;
			PORTB = y + e ;
			_delay_ms(200);
			x = (x >> 1);
			y = (y << 1);
		}
		z = PORTA;
		e = PORTB;
	}	
	for(int i = 0; i < 3; i++ ) // cho led chop tat
	{
	PORTA = PORTB = 0b11111111;
	_delay_ms(500);
	PORTA = PORTB = 0;
	_delay_ms(500);
	}
}

void T5()//  1 CON CHAY QUA HAI CON CHAY LAI
{ 
	{
		x =0b00000001;
		y =0b00000001;
		for(int i = 4; i > 0; i--) // cho chay 4 lan
		{
			for (int j =  0; j < 2*i; j ++) // chay qua 2*i chay lan dau 8 lan tuong ung 8 con s do 6 4 .
			{
				PORTA = x;
				_delay_ms(200);
				x = x << 1;
			}
			x = PORTA;
			x = ( x >> 1 ) + 0b10000000;
			for (int j =  0; j < 2*i; j ++) // chay qua 2*i chay lan dau 8 lan tuong ung 8 con s do 6 4 .
			{
				PORTB = y;
				_delay_ms(200);
				y = y << 1;
			}
			y = PORTB;
			y = ( y >> 1 ) + 0b10000000;
		
			for(int j = 0; j <2*i - 1; j++) // chay lai theo lan le 7 5 3 moi lan nhu vay dieu cong them bit
			{
				PORTB  = y;
				_delay_ms(200);
				y= y >> 1;
			}
			y = PORTB ;
			y = (y << 1)+ 0b00000001;
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
}
void T6()// DD
{
	x = 0b00000001;
	for(int i = 7; i >= 0; i --)
	{
		PORTB = PORTA = x ;
		_delay_ms(200);
		x = ( x << 1)+ 0b00000001 ;
	}
	//x =0b1111111;
	for(int i = 7; i >= 0; i --)
	{
		PORTB = PORTA = x ;
		_delay_ms(200);
		x = ( x << 1);
	}
}
int main(void)
{
  DDRA = 0xff; PORTA = 0; // 0xff khai bao la pora xuat vs gia tri ban dau 0
  DDRB = DDRC = 0xff; PORTB = PORTC = 0;
  
  DDRD = 0b11110111;// khai bao nhan gia tri tu ben ngoai Pina
  PORTD= 0b00001000; // cho xuat la 1

  GICR |=(1 << INT1); // chon ngat 0 ; PO va ngat 1 RTD.2
  MCUCR |= (1 << ISC11);  // chon che do tac dong ngat
  sei();  
    while (1) 
    {
		PORTC = Code7[dem];
		PORTA= PORTB = 0XFF;
		if(dem == 1 )
		{
			PORTD = 0b10001000;
			T1();
		}
		if(dem == 2 )
		{
			PORTD = 0b01001000;
			T2();
		}
		if(dem == 3 )
		{
			PORTD = 0b00101000;
			T3();
		}
		if(dem == 4 )
		{	PORTD = 0b00011000;
			T4();
		}
		if(dem == 5 )
		{
			PORTD = 0b00001100;
			T5();
		}
		if(dem == 6 )
		{
			PORTD = 0b00001010;
			T6();
		}
    }
}

