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
	
	TCCR0 = (1 << COM01) | (1 << WGM01) | (1 << WGM00);
	TIMSK = (1 << TOIE1);
	
	OCR1A = (cycle/100)*255;
	
	sei();
	
	TCCR1B = (1 << CS10);

    while (1) 
    {
		//_delay_ms(100);
		
		PORTD |= (1 << PD5);
		PORTD &=~ (1 << PD3);
	 
		cycle += 10;
		if (cycle > 100)
		{
			cycle = 0;
		}
    }
}

ISR(TIMER0_OVF_vect)
{
		OCR1A = (cycle/100)*255;
}

