#include <SoftwareSerial.h>

SoftwareSerial g_bluetooth(6, 7);
namespace {
  const int buttonPin = 2;
  const int ledPin =    3;
  const int sindou =    4;
  const int AVERAGE_NUM = 10;
  const int BASE_X      = 530;
  const int BASE_Y      = 519;
  const int BASE_Z      = 545;
  const int UPDOWN      = 250;
  const int UPDOWNS      = 20;
}
void setup()
{
  //g_bluetooth.begin(115200);
  g_bluetooth.begin(9600);
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(ledPin, INPUT_PULLUP);
  pinMode(sindou, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
}
void SendSignal()
{
  int sw1 = 0,sw2 = 0;
  int ax = 0, ay = 0, az = 0;
  int up = 0, down = 0, right = 0,left = 0;
  int push = 0,LR=0,UD=0;
  for (int i = 0; i < AVERAGE_NUM; ++i) {
    ax += analogRead(0);
    ay += analogRead(1);
    az += analogRead(2);
    push += analogRead(5);
  }
  ax /= AVERAGE_NUM;
  ay /= AVERAGE_NUM;
  az /= AVERAGE_NUM;
  push /= AVERAGE_NUM;
  LR = analogRead(4);
  UD = analogRead(3);
  const int angleX = atan2(ax - BASE_X, az - BASE_Z) / PI * 180;
  const int angleY = atan2(ay - BASE_Y, az - BASE_Z) / PI * 180;
  if(digitalRead(buttonPin) == LOW)
  {
    sw1 = 0;
  }else{
    sw1 = 1;
  }
  if(digitalRead(ledPin) == LOW)
  {
    sw2 = 0;
  }else{
    sw2 = 1;
  }
  g_bluetooth.print(ax);
  g_bluetooth.print("\t");
  g_bluetooth.print(ay);
  g_bluetooth.print("\t");
  g_bluetooth.print(az);
  g_bluetooth.print("\t");
  g_bluetooth.print(angleX);
  g_bluetooth.print("\t");
  g_bluetooth.print(angleY);
  g_bluetooth.print("\t");
  g_bluetooth.print(push);
  g_bluetooth.print("\t");
  g_bluetooth.print(sw1);
  g_bluetooth.print("\t");
  g_bluetooth.print(sw2);
  g_bluetooth.print("\t");
  g_bluetooth.print(UD);
  g_bluetooth.print("\t");
  g_bluetooth.print(LR);
  g_bluetooth.println("");
  
}
void readAccelermeter(){
  if ( g_bluetooth.available() ) {
    char mode = g_bluetooth.read();
    switch (mode) {
      case '0' : digitalWrite(sindou, LOW);  break;
      case '1' : digitalWrite(sindou, HIGH); break;
    }
  }
}
void loop()
{
  readAccelermeter();
  SendSignal();
}





