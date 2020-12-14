/*
 * Atmega16_Blink_v7.c
 *
 * Created: 14-12-2020 18:57:34
 * Author : Siddharth
 */ 
#define  F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB = 0xFF;
	int temp;
	int blink_Arr[4] = {0x81,0x42,0x24,0x18};
	
	while(1){
		for (int i= 3; i >= 0; i--)
		{
			temp = blink_Arr[i];
			PORTB = temp;
			_delay_ms(500);
		}
	}

/*	Reverse Single	
	DDRB = 0xFF;
	int temp;
	int blink_Arr[8] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
		
	while(1){
		for (int i = 7; i >= 0; i--)
		{
			temp = blink_Arr[i];
			PORTB = temp;
			_delay_ms(500);
		}
	}*/
/*	Single Blink Start to End
	
	DDRB = 0xFF;
	int temp;
	int blink_Arr[8] = {0x1,0x2,0x4,0x8,0x10,0x20,0x40,0x80};
	
	while(1){
		for (int i= 0; i< 8; i++)
		{
			temp = blink_Arr[i];
			PORTB = temp;
			_delay_ms(500);
		}
	}*/
/*  End 2 Mid

	DDRB = 0xFF;
	int temp;
	int blink_Arr[4] = {0x81,0x42,0x24,0x18};
	
	while(1){
		for (int i= 0; i< 4; i++)
		{
			temp = blink_Arr[i];
			PORTB = temp;
			_delay_ms(500);
		}
	}*/
/*	Mid 2 End Blink

	DDRB = 0xFF;
	int temp;
	int blink_Arr[4] = {0x81,0x42,0x24,0x18};
	
	while(1){
		for (int i= 3; i >= 0; i--)
		{
			temp = blink_Arr[i];
			PORTB = temp;
			_delay_ms(500);
		}
	}
*/

/*	ALternate Blink
	DDRB = 0xFF;
	while(1){
		PORTB = 0x55;
		_delay_ms(500);
		PORTB = 0xAA;
		_delay_ms(500);
	}*/

/*	Full blink Code

	DDRB = 0xFF; //0b11111111//
	
	while(1){
		PORTB = 0xFF;
		_delay_ms(500);
		PORTB = 0x00;
		_delay_ms(500);
	}*/
}
