/*
 * DONGHO.cpp
 *
 * Created: 8/9/2021 4:09:45 PM
 * Author : KAITO
 */ 
#define F_LU 8MHz
#include <avr/io.h>
#include <avr/delay.h>
#include <avr/interrupt.h>

unsigned char  Code7[] = {0x3F,0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F}; // led 7 catode
unsigned long b,c;
unsigned long dem = 0; // kieu long cho no nhieu 

void HienThiGiay(unsigned int a)
{
	int chuc,dv;
	chuc = a/10; // lay hang chuc
	dv = a%10; // lay hang dv
	PORTB =0b00000100; // cho led tat truoc
	PORTB = 0X00; // rui cho le bat 
	PORTD = Code7[dv]; // hien led cho sang  
	_delay_ms(10);
	
	
	PORTB =0b00001000;
	PORTB = 0X00;
	PORTD = Code7[chuc];
	_delay_ms(10);
	
	
	
}

void HienThiPhut(unsigned int a)
{
	int chuc,dv;
	chuc = a/10; // lay hang chuc
	dv = a%10; // lay hang dv
	PORTB = 0b00010000;
	PORTB = 0X00 ;
	PORTC = Code7[dv];
	_delay_ms(10);
	
	PORTB = 0b00100000;
	PORTB =0X00;
	PORTC = Code7[chuc];
	_delay_ms(10);
	
	
}

void HienThiGio(unsigned int a)
{
	int chuc,dv;
	chuc = a/10; // lay hang chuc
	dv = a%10; // lay hang dv
	PORTB = 0b01000000;
	PORTB = 0X00;
	PORTA = Code7[dv];
	_delay_ms(10);
	
	PORTB = 0b10000000;
	PORTB =0X00;
	PORTA = Code7[chuc];
	_delay_ms(10);
	
	
}


ISR(TIMER0_OVF_vect) // CHON MODE NORMAL NEN OVF
{
	TCNT0 = 130;
	dem ++;
}

int main(void)
{
	unsigned int k = 22, z = 50, i = 50;
	DDRA = DDRC = DDRD = 0XFF; //KHAI BAO XUAT DE HIEN LEN LED 7
	PORTA = PORTC = PORTD = 0;
	DDRB = 0b11111100;
	PORTB = 0xff;
	//PORTB = 0B00000011; // cho tat ca po b = 0 neu kia xuat 1 no se snag 
	// khai bao timer0 va su dung dem thoi gian (ngat tran)
    TCCR0 = (1 << CS01)|(1 <<CS00); // CHON MODE NORMAL
	TCNT0 = 130; // THANH GHI TAO LUU TRU
	TIMSK |=(1 << TOIE0); // THANH GHI BAO NGAT
	
	sei();
	
    while (1) 
    {	
		HienThiGio(k);
	    HienThiPhut(z);		
		HienThiGiay(i);
			
	    if(dem >= 1000 )// 1 s thuc nhung sai so co the chinh cho gaN DUNG NHAT
		{
			i++;
			dem = 0; 
			if(i < 60)
			{
			HienThiGiay(i);
			}
			else  
			{
				i = 50;
				HienThiGiay(i);
				z++;
				if(z < 60)
				{					
					HienThiPhut(z);
				}	
				else
				{
					z = 50;
					HienThiPhut(z);
					k++;
					if(k < 24)
					{
						HienThiGio(k);
					}
					else
					{
						k = 0;
					}
				}
			}
		}

    }
}

