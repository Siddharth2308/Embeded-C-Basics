/*
 * Arduino_Tinkercad
 *
 * Created: 14-12-2020 18:57:34
 * Author : Siddharth
 * Task   : Blinking LED Patterns.
 */ 
int a;
int temp;
int blink_mid[4] = {0x81,0x42,0x24,0x18};
int test_array[8] = {0,1,2,3,4,5,6,7};
int alter1[4] = {0,2,4,6};
void setup()
{
  DDRD = 0xFF;
  for(int i = 0; i < 8; i++){
    a = test_array[i];
    pinMode(a, OUTPUT);
  }  
}
void loop()
{
  //Full Blink Code
  
  for(int i = 0; i < 8; i++){
    a = test_array[i];
    digitalWrite(a, HIGH);
  }
  delay(500);
  for(int i = 0; i < 8; i++){
    a = test_array[i];
    digitalWrite(a, LOW);
  }
  delay(1000);
  
  //Alternate Blink
  
  for(int i = 0; i < 8; i++){
    a = alter1[i];
    digitalWrite(a, HIGH);
  }
  delay(500);
  for(int i = 0; i < 8; i++){
    a = alter1[i];
    digitalWrite(a, LOW);
  }
  delay(1000);
  
  //Top to bottom single
  
  for(int i = 0; i < 8; i++){
    a = test_array[i];
    digitalWrite(a, HIGH);
    delay(500);
    digitalWrite(a, LOW);
  }
  delay(1000);
  
  //Bottom to Top Single
  
  for(int i = 7; i >= 0; i--){
    a = test_array[i];
    digitalWrite(a, HIGH);
    delay(500);
    digitalWrite(a, LOW);
  }
  delay(1000);
  
  //End to Mid
  
  for (int i= 3; i >= 0; i--)
  {
    temp = blink_mid[i];
    PORTD= temp;
    delay(500);
  }
  // Mid to End
  for (int i= 0; i < 4; i++)
  {
    temp = blink_mid[i];
    PORTD= temp;
    delay(500);
  }
}