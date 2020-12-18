/*
 * Atmega16_Blink_v7.c
 *
 * Created: 14-12-2020 18:57:34
 * Author : Siddharth
 * Task   : Blinking LED Patterns.
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF; //0b11111111// Sets All pins on portB to Output.
	int temp;
	int blink_mid[4] = {0x81,0x42,0x24,0x18};
	int blink_reverse[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};
	
	while(1){
		//Full blink Code
		
		PORTB = 0xFF;//Turns all pins on port B to high.
		_delay_ms(500);
		PORTB = 0x00;//Turns all pins on port B to Low.
		_delay_ms(1000);
		
		//Alternate Blink
		
		PORTB = 0x55;// Turns alternate pins high. //0b00101010
		_delay_ms(500);
		PORTB = 0x00;//Turns All pins low
		_delay_ms(500);
		PORTB = 0xAA;// Vice versa
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
		
		//Reverse Single
		
		for (int i = 7; i >= 0; i--)
		{
			temp = blink_reverse[i];
			PORTB = temp;
			_delay_ms(500);			
		}
		PORTB = 0x00;
		_delay_ms(1500);
		
		// Top To Bottom Single
		
		for (int i = 0; i < 8; i++){
			temp = blink_reverse[i];
			PORTB = temp;
			_delay_ms(500);
		}
		PORTB = 0x00;
		_delay_ms(1500);
		
		// End to Mid
		
		for (int i = 0; i < 4; i++){
			temp = blink_mid[i];
			PORTB = temp;
			_delay_ms(500);
		}
		PORTB = 0x00;
		_delay_ms(1500);
		
		//Mid to End
		
		for (int i= 3; i >= 0; i--)
		{
			temp = blink_mid[i];
			PORTB = temp;
			_delay_ms(500);
		}
	}
}

