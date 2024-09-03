#include <Servo.h>
Servo servo1;
const int trigPin = 12;
const int echoPin = 11;
long duration;
int distance=0;
int potPin = A0; //input pin
int soil=0;

void setup() 
{
  Serial.begin(9600);
//Serial.print("Humidity");
pinMode(trigPin, OUTPUT); 
pinMode(echoPin, INPUT); 
servo1.attach(8);
}
void loop() 
{

  
  int soil=0;
  for(int i=0;i<2;i++)
  {
digitalWrite(trigPin, LOW);
delayMicroseconds(7);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
delayMicroseconds(10);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2+distance;
delay(10);

  }
  distance=distance/2;
  Serial.println(distance);
if (distance <15 && distance>1)
{
  delay(1000);
for(int i=0;i<3;i++)
{
soil = analogRead(potPin) ;

delay(75);
}

Serial.println(soil);
Serial.print("%");
if(soil<800)
{delay(1000);
  Serial.print("WET ");
  servo1.write(180);
delay(3000);} 
else{ delay(1000);
  Serial.print("dry ");
servo1.write(0);
delay(3000);}

servo1.write(90);}
distance=0;
soil=0;delay(1000);
}