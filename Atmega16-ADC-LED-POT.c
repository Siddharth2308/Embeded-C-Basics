/*
 * Atmega328p-ADC.c
 *
 * Created: 05-01-2021 21:11:26
 * Author : Siddharth
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>


void ADC_Init()
{
    DDRA = 0x00;
    ADCSRA = 0x87;
    ADMUX = 0x40;
}

void ADC_Read( char channel)
{
    ADMUX = ADMUX | (channel & 0x0f);
    ADCSRA |= (1 << ADSC);
    while((ADCSRA & (1 << ADIF))==0);
    _delay_us(10);
}
int main()
{
    DDRB = 0xff;
    PORTB = (1 << PB3);
    TCCR0 = (1 << COM01) | (1 << WGM01) | (1 << WGM0) | (1 << CS00);
    ADC_Init();

    while(1)
    {
        ADC_Read(5);
        OCR0 = ADC/4;
    }
}
