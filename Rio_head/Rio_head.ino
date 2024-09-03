#include <Servo.h>
#include <SoftwareSerial.h>
#include<JQ6500_Serial.h>
SoftwareSerial mySerial(3,4); 
JQ6500_Serial mp3(mySerial);
Servo myservo1;   //Eye
Servo myservo2;   //Head
Servo myservo3;   //Jaw
int d;
int pos1,pos2,pos3,pos4; 
int trigPin = 8;    
int echoPin = 9; 
long duration, dist, average;
long aver[3]; 
int var=0; 
int a;
void setup() {
  // put your setup code here, to run once:
 Serial.begin(9600); 
 myservo1.attach(5);//eyes
 myservo2.attach(6);//head
 myservo3.attach(10);//Jaw
 pinMode(trigPin, OUTPUT);  
 pinMode(echoPin, INPUT); 
  mySerial.begin(9600);
  mp3.reset();
  mp3.setVolume(50);
  mp3.setLoopMode(MP3_LOOP_NONE);
  mp3.play();
}
/*int measure(void)
{  
  for (int i=0;i<=2;i++) 
    {   
    digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(15);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin, INPUT);
    duration = pulseIn(echoPin, HIGH);
    dist = (duration/2) / 29.1;    //obtain distance
    aver[i]=dist;            
    delay(10);              //delay between measurements
  }
   dist=(aver[0]+aver[1]+aver[2])/3;
   return(dist);
}
*/
void measure() {  
 digitalWrite(10,HIGH);
digitalWrite(trigPin, LOW);
delayMicroseconds(5);
digitalWrite(trigPin, HIGH);
delayMicroseconds(15);
digitalWrite(trigPin, LOW);
pinMode(echoPin, INPUT);
duration = pulseIn(echoPin, HIGH);
dist = (duration/2) / 29.1;    //obtain distance
}

void play()
{
  Serial.println("Audio");
  mp3.setVolume(50);
  mp3.play();
  myservo3.write(180);
  mp3.playFileByIndexNumber(1);
  myservo3.write(0);
  delay(15000);
  mp3.reset();
  
}

void loop() {
  // put your main code here, to run repeatedly:
 //d=measure();
//Serial.println("DISTANCE:");
//Serial.print(d);
//delay(2000);

  myservo1.write(90);
  myservo2.write(125);
  
   for (int i=0;i<=2;i++) {   //average distance
    measure();               
   aver[i]=dist;            
    delay(10);              //delay between measurements
  }
 dist=(aver[0]+aver[1]+aver[2])/3;    

   if (dist<50)
   {
    play();
    moves();
  }
  Serial.println(dist);
}
void moves(){
  movement1();
delay(2000);
  Serial.println("movement1 finished");
movement2();
delay(2000);
  Serial.println("movement2 finished");
movement3();
 delay(2000); 
  Serial.println("movement3 finished");
  movement4();
  delay(2000);
  Serial.println("movement4 finished ");

}
void movement1(){
  for(pos1=90;pos1>=0;pos1--){
    myservo1.write(pos1);
    //interrupt();
    delay(35);
  }
  delay(500);
  for(pos1=125;pos1>=70;pos1--){
    myservo2.write(pos1);
    //interrupt();
    delay(35);
  }
}
void movement2(){
  for(pos2=0;pos2<=90;pos2++){
    myservo1.write(pos2);
    //interrupt();
    delay(35);
  }
  delay(500);
  for(pos2=70;pos2<=125;pos2++){
    myservo2.write(pos2);
    //interrupt();
    delay(35);
  }
}

void movement3(){
  Serial.println("movement3");
  for(pos3=90;pos3<=180;pos3++){
    myservo1.write(pos3);
   // interrupt();
    delay(35);
  }
  delay(500);
  for(pos3=125;pos3<=165;pos3++){
    Serial.println("movement3a");
    myservo2.write(pos3);
    //interrupt();
    delay(35);
  }
  
}
void movement4(){
  Serial.println("movement4");
  for(pos4=180;pos4>=90;pos4--){
    myservo1.write(pos4);
   // interrupt();
    delay(35);
  }
  delay(500);
  for(pos4=165;pos4>=125;pos4--){
    Serial.println("movement4a");
    myservo2.write(pos4);
    //interrupt();
    delay(35);
  }
  
}
/*void interrupt(){
  if(d<=50){
      for(pos1=0;pos1<=90;pos1++){
    myservo1.write(pos1);
    delay(35);
  }
  for(pos1=0;pos1<=90;pos1++){
    myservo2.write(pos1);
    delay(35);
  }
    play();
  }
  return loop();
}
*/