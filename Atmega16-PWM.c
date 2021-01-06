/*
 * Atmega16-PWM.c
 *
 * Created: 04-01-2021 17:07:25
 * Author : Siddharth
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

double cycle = 0;

int main(void)
{
	DDRD = (1 << PD5) | (1 << PD3);
	TCCR0 = (1 << COM01) | (1 << WGM01) | (1 << WGM00) | (1 << CS00);
	PORTB = (1 << PB3);
	
    while (1) 
    {
		//_delay_ms(100);
	    /* My logic- DOnt use refactoring for now
	    	OCR1A = (cycle/100)*255;
	    
		cycle += 10;
		if (cycle > 100)
		{
			cycle = 0;
		}*/
		
	    for(int i = 0; i < 255; i++)
	    {
		    OCR1A = i;
		    _delay_ms(500);
	    }
	    for(int i = 255; i > 1; i--)
	    {
		    OCR1A = i;
		    _delay_ms(500);
	    }
    }
}

