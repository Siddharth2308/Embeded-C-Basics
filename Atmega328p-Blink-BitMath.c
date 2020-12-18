/*
 * Atmega328p-Bit-Blink.c
 * Author : Siddharth
 */ 

#define  F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#define  BLINK_MS 150

int main(void)
{
	//DDRB |= 0x20;//0b00100000; This is a trial to set a particular bit to high
	//DDRB |= _BV(PORTB) - Alternative method
	DDRB |= 0xFF; //ALl pins are intentionally set to high to test out patterns(Don't really need a bitwise or hear)
	int temp;
	int blink_mid[4] = {0x81,0x42,0x24,0x18};
	int blink_reverse[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};

    while (1) 
    {
		//Full blink code

		PORTB ^= 0xFF;//instead of on/off a  toggle logic
		_delay_ms(BLINK_MS);

		//Reverse single
		PORTB = 0x00;
		for (int i = 7; i >= 0; i--)
		{
			temp = blink_reverse[i];
			PORTB = 0x00;
			PORTB |= temp;
			_delay_ms(15);
		}
	

		// Top to bottom Single
		PORTB = 0x00;
		for (int i = 0; i < 8; i++){
			PORTB = 0b00000001<<i;
			_delay_ms(15);
		}
		//Mid to end
		PORTB = 0x00;
		for (int i= 3; i >= 0; i--)
		{
			PORTB = 0x00;
			temp = blink_mid[i];
			PORTB |= temp;
			_delay_ms(50);
		}
		
		//End to Mid
		PORTB = 0x00;
		for (int i = 0; i < 4; i++){
			PORTB = 0x00;
			temp = blink_mid[i];
			PORTB |= temp;
			_delay_ms(50);
		}

		// Alternate Blink
		PORTB = 0x00;
		PORTB ^= 0x55; //0b01010100
		_delay_ms(BLINK_MS);				
		
    }
}

