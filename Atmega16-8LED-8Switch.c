/*
 * Atmega16-Switch-LED.c
 *
 * Created: 18-12-2020 19:27:42
 * Author : Siddharth
 */ 

#define  F_CPU 8000000UL
#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>


int main(void)
{
	DDRB |= 0xFF;//Assigned as Output
	DDRC |= 0x00;//Assigned as Input
	
    while (1) 
    {
		for(int i = 0; i < 8; i++){
			if (bit_is_set(PINC,i))
			{
				PORTB |= 1<<i;
				_delay_ms(150);
			}
			else{ PORTB = 0x00; }
		}
		/*
		if (bit_is_set(PINC,6))//(PINC == 0x01)
		{
			PORTB |= 0x01;
		}
		 else{ PORTB = 0x00; }
			 */
    }
}

