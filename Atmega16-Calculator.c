/*
 * Atmega16-Calculator.c
 *
 * Created: 25-12-2020 19:09:16
 * Author : Siddharth
 */ 

#define F_CPU 8000000UL
#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
//Macros for LCD.
#define Data_Dir DDRA
#define Cmd_Dir DDRB
#define Data_Port PORTA
#define Cmd_Port PORTB
#define RS PB7
#define Enable PB6
//Macros for keypad.
#define  clr_bit(reg,pos) reg &=~(1<<pos)

//Setting Up the LCD functions.
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

void LCD_String_xy (char row, char pos, char *str)/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	command((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	else if (row == 1 && pos<16)
	command((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	lcd_string(str);		/* Call LCD string function */
}

void lcd_clear()
{
	command(0x01);
	command(0x80);
}

void  key_init(void)
{
	DDRC = 0x0F; // PC0-PC3 outputs rows 	
}

//Key_scan final

unsigned char key_scan(void)
{
	unsigned char cnt, key;
	
	for ( cnt = 0; cnt < 4; ++cnt)
	{
		PORTC = 0xFF; //check rows one by one
		
		if ( cnt == 0)
			clr_bit(PORTC, 0); //first row
		if (cnt == 1)
			clr_bit(PORTC, 1); //second row
		if (cnt == 2)
			clr_bit(PORTC, 2); //third row
		if (cnt == 3)
			clr_bit(PORTC, 3); //fourth row
		key = PINC & 0xF0; //check if any key is pressed
		if (key != 0xF0)
		{
			while((PINC & 0xF0) != 0xF0);
			break;
		}
	}
	
	if (cnt == 4) //end of first scan loop
		return 0;
	switch (cnt) //scan columns
	{
		case 0: 	//case for first row
			switch ( key )
			{
				case 0xE0: //check if row 1 col1(7)
				return 0x07;
				break;
				
				case 0xD0: //check if row 1 col2(8)
				return 0x08;
				break;
				
				case 0xB0: //check if row 1 col3(9)
				return 0x09;
				break;
				
				case  0x70: // check if row1 col 4(A)
				return 0x0A; //0x0A
				break;
			}
		break;
		
		case 1: //case for second row
			switch( key )
			{
				case 0xE0: //check row  2 col 1 (4)
				return 0x04;
				break;
				
				case 0xD0: //check row 2 col 2 (5)
				return 0x05;
				break;
				
				case 0xB0: //check row 2 col 3 (6)
				return 0x06;
				break;
				
				case 0x70: //check row 2 col 4 (B)
				return 0x0B;
				break;				
			}
		break;
		
		case 2: //case  for third row
				
		switch ( key )
		{
			case 0xE0: //Check if row 3 col 1( 1 )
			return 0x01;
			break;
					
			case 0xD0: //Check if row 3 col 2 ( 2 )
			return 0x02;
			break;
					
			case 0xB0: //Check if row 3 col 3 ( 3 )
			return 0x03;
			break;
					
			case 0x70: //Check if row 3 col 4( C )
			return 0x0C;
			break;
		}
		break;
		
		case 3:						//case 3 for fourth row
		
		switch ( key )
		{
			case 0xE0:		//Check if row 4 col 1 --> ( F )
			return 0x0F;
			break;
			
			case 0xD0:		//Check if row 4 col 2 --> ( 0 )
			return '0';
			break;
			
			case 0xB0:		//Check if row 4 col 3 --> ( E )
			return 0x0E;
			break;
			
			case 0x70:		//Check if row 4 col 4 --> ( D )
			return 0x0D;
			break;
		}
		break;
	}
	return 0;
}

//variables for final code
static unsigned int key; //variable to store pressed key
static unsigned int op; //variable to store operation ID 
static char op_char; //op_char for operation model
long  int a, b; // variables to store two numbers of operation
long int result;
static char lcd_buffer[16]; // buffer array for conversion

void cal_init(void)
{
	key_init();
	lcd_init();
}

void cal_op(void)
{
	if ( key == 0x0D) // add
	{
		key = 0;
		op = 1;
		op_char = '+';
	}
	else if (key == 0x0C) //substraction
	{
		key = 0;
		op = 2;
		op_char = '-';
	}
	else if (key == 0x0B) //multiplication
	{
		key = 0;
		op = 3;
		op_char = 'x';
	}
	else if (key == 0x0A) //division
	{
		key = 0;
		op = 4;
		op_char = '/';
	}
	else if ( key == 0x0E) //execution
	{
		key = 0;
		op = 5;
	}
	else if (key == '0') //No idea but it worksss bugggggg
	{
		key = 0;
	}
	else if (key == 0x0F) // clear lcd
	{
		a = 0;
		b = 0;
		result = 0;
		op = 0;
		key = 0;
		lcd_clear();
	}
}

void cal_run(void)
{
	if (op == 0) //no operation selected store the number
	{
		//command(0x80);
		a = a * 10 + key; // storing n number of digits
		sprintf(lcd_buffer,"%1li",a);
		LCD_String_xy(0,0,lcd_buffer);
	}
	// If operation is selected start storing the second value
	else if (op == 1 || op == 2 || op == 3 || op == 4)
	{
		b = b * 10 + key;
		sprintf(lcd_buffer,"%1li%c%1li",a,op_char,b); // TO display both numbers at the same time through the array
		LCD_String_xy(0,0,lcd_buffer);
	}
	else if ( op == 5) //if = is selected
	{
		if ( op_char == '+')
			result = a + b;
		else if (op_char == '-')
			result = a - b;
		else if (op_char == 'x')
			result = a * b;
		else if (op_char == '/')
			result = a / b;
		//Result
		sprintf(lcd_buffer,"=%li",result);
		LCD_String_xy(1,0,lcd_buffer);
		//clear memory for next operation
		a = 0;
		b = 0;
		result = 0;
		op = 0;
	}
}

void calculator(void)
{
	key = key_scan();
	if (key != 0)
	{
		cal_op();
		cal_run();
		key = 0;		
	}
}

int main(void)
{
	cal_init();
	//lcd_string("Press any key");
	_delay_ms(50);

    while (1) 
    {
		calculator();
    }
}
