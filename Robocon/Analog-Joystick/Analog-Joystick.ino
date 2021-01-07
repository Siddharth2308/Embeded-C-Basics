#define sw 6
#define screenWidth 600
#define screenHeight 300


int defultData;
int data;
int startTime = 0;
int TimeGap = 10;
int remap;

void setup()
{
  Serial.begin(9600);
  if (micros()-startTime >= TimeGap)
  {
    defultData = analogRead(0); 
  }
}
void loop()
{
  data = analogRead(A0);
  if(data < defultData + 1)
  {
    remap = map(data,0,defultData-1,255,0);        
  } else if(data >= defultData) {
    remap = map(data,defultData,1023,0,255);
  }
  Serial.println("Remapped Value: ");
  Serial.println("Default Value: ");
  Serial.println(defultData);
  delay(200);
}
/*
void setup() {
  Serial.begin(9600);
  pinMode(sw,INPUT_PULLUP);
}
 
void loop() {
  int x = analogRead(A0);
  int y = analogRead(A1);
  int xPos = map(x, 0, 1023,0,screenWidth);
  int yPos = map(y, 0, 1023,0,screenHeight); 
  int sStat = digitalRead(sw);

  Serial.print("X: ");
  Serial.print(xPos);

  Serial.print(" Y: ");
  Serial.println(yPos);
}*/
