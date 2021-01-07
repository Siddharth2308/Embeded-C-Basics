#include <SoftwareSerial.h>
#define tx 2
#define rx 3

SoftwareSerial configbt(rx, tx);

void setup() {
  Serial.begin(38400);
  configbt.begin(38400);
  pinMode(tx, OUTPUT);
  pinMode(rx, INPUT);
}

void loop() {
  Serial.println("Setup Complete");
  if(configbt.available())
  {
    Serial.println(configbt.readString());    
  }
  if(Serial.available())
  {
    configbt.write(Serial.read());
  }
}
