/*
 * Atmega328p-ADC.c
 *
 * Created: 05-01-2021 21:11:26
 * Author : Siddharth
 */ 

#define F_CPU	16000000

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>

long dutyCycle = 0;

//LCD
#define Data_Dir DDRB
#define Cmd_Dir DDRD
#define Data_Port PORTB
#define Cmd_Port PORTD
#define RS PD7
#define Enable PD6

//--------------------------------------------------------------------------------------Final Code-----------------------------------------------------------------------------------------

void command(unsigned char cmd)
{
	Data_Port = cmd;
	Cmd_Port &= ~(1<<RS); // RS = 0.
	Cmd_Port |= (1<<Enable); // Enable E = 0. RW connected to gnd so 0.
	_delay_us(1);
	Cmd_Port &= ~(1<<Enable);
	_delay_ms(3);
}

void lcd_init(void)
{
	Cmd_Dir = 0xFF;
	Data_Dir = 0xFF;
	_delay_ms(20);
	// Same Initializing sequence from the first code.
	command(0x38);
	command(0x0C);
	command(0x06);
	command(0x01);
	command(0x80);
}

void lcd_char(unsigned char char_data)
{
	Data_Port = char_data;
	Cmd_Port |= (1<<RS);
	Cmd_Port |= (1<<Enable);
	_delay_us(1);
	Cmd_Port &= ~(1<<Enable);
	_delay_ms(1);
}

void lcd_string(char *str)
{
	int i;
	for(i=0;str[i]!=0;i++)
	{
		lcd_char(str[i]);
	}
}

void lcd_string_xy(char row, char pos, char *str)
{
	if (row == 0 && pos<16 )
	{
		command((pos & 0x0F) | 0x80);
	} else if (row == 1 && pos<16)
	{
		command((pos & 0x0F) | 0xC0);
		lcd_string(str);
	}
}

void lcd_clear()
{
	command(0x01);
	command(0x80);
}

//ADC 

void ADC_Convert()
{
	ADCSRA |= (1 << ADSC);
}

void Setup_ADC()
{
	ADMUX = (1 << REFS0) | (1 << MUX0) | (1 << MUX1); // Page 217 of datasheet MUX0 and 2 define where the pins are connected
	//ADCSRA is the control status register
	ADCSRA = (1 << ADEN) | (1 << ADIE) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2); // ADPS sets the prescaler to 128 most reliable page 219
	DIDR0 = ( 1 << ADC5D); // Digital Input buffer
	ADC_Convert();
}

char lcd_buffer[16];

int main(void)
{
	TCCR0A = (1 << COM0A1) | (1 << WGM00) | (1 << WGM01);
	TIMSK0 = (1 << TOIE0);
	
	Setup_ADC();
	lcd_init();
	sprintf(lcd_buffer,"%1li",dutyCycle);
	lcd_string(lcd_buffer);
	
	sei(); //set external interrupt
	
	TCCR0B = (1 << CS00) | (1 << CS02);
	
	while(1)
	{
		//TODO:: Please write your application code
		
	}
}

ISR(TIMER0_OVF_vect)
{
	OCR0A = dutyCycle; //refer pwm code
}

ISR(ADC_vect)
{
	dutyCycle = ADC*0.249266;//10bit to 8 bit cross if 255 : 1023 X : ? 
	ADC_Convert();
}
