#include <avr/io.h>

#define VSYNC_LOW    PORTD &= ~_BV(6)
#define VSYNC_HIGH   PORTD |= _BV(6)

#define HSYNC_LOW    PORTD &= ~_BV(7)
#define HSYNC_HIGH   PORTD |= _BV(7)

#define RED_ON       PORTB |= _BV(4)
#define RED_OFF      PORTB &= ~_BV(4)

#define GREEN_ON     PORTB |= _BV(3)
#define GREEN_OFF    PORTB &= ~_BV(3)

#define BLUE_ON      PORTB |= _BV(2)
#define BLUE_OFF     PORTB &= ~_BV(2)
int i = 0;

void setup() {
  // put your setup code here, to run once:
  DDRB = 0xFF;
  DDRD = 0xFF;
}

void loop() {
  // put your main code here, to run repeatedly:
  i = 0;
  VSYNC_LOW;
  while(i < 200){
    RED_ON;
    delayMicroseconds(2);  
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    delayMicroseconds(20);    
    RED_OFF;    
    delayMicroseconds(1);
    i++;
    HSYNC_HIGH;
    delayMicroseconds(3);
    __asm__("nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t""nop\n\t");
    HSYNC_LOW;
    
    //26.4uS 
}
}
