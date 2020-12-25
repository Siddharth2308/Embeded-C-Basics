/*
 * Atmega16-LCD-Basics.c
 *
 * Created: 24-12-2020 19:54:38
 * Author : Siddharth
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
//Macrosssssssssszzzz
#define Data_Dir DDRA
#define Cmd_Dir DDRB
#define Data_Port PORTA
#define Cmd_Port PORTB
#define RS PB7
#define Enable PB6

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

int main()
{
	lcd_init();
	while(1)
	{
		lcd_string("Hello World !!");
		command(0xC0);
		lcd_string("Test");
	}
}






/* --------------------------------------------------------------------------------------First Code-----------------------------------------------------------------------------------------
void command (unsigned char cmd){
	PORTB = 0b11000000;//0xC0; //Setting pin E(enable) of LCD high while RS is low.
	PORTA = cmd;
	PORTB = 0b00000000; //Clearing the entire PortB.
	_delay_ms(150);
}

void lcd_data(unsigned char data){
	PORTB = 0b01000000;//(1<<PB6) | (0<<PB7); //0xC0; //In order to display data I need to set both RS(Register Select) and E pins to High.
	PORTA = data;
	PORTB |= 0b00000000; //After passing the data disable the enable pin.
	_delay_ms(500);
	
}

void lcd_print(char *p){
	while(*p){
		lcd_data(*p++);
	}
}

int main(void)
{
	DDRB = 0xFF;
	DDRA = 0xFF; 
	command(0x38); //Activating 2 lines in 8-bit mode
	command(0x0F); //Turning on the display (Blinking cursor)
	command(0x01); //Clearing the display
	_delay_ms(150);
	
    while (1) 
    {
		command(0x80); //Sets the cursor to first position first line.
		lcd_print("Hello World !!");
		_delay_ms(150);
		command(0xC0);//Sets the cursor to first position second line.
		_delay_ms(150);
		lcd_print("TEST");
		_delay_ms(150);
		command(0x01); //Clearing the display.
		_delay_ms(150);
    }
}*/

