#define BLYNK_TEMPLATE_ID "TMPL3pyQUdKYs"
#define BLYNK_TEMPLATE_NAME "Fire fighting robot"
#define BLYNK_AUTH_TOKEN "M6lJXyrKufWKkJW7Z2wwAg8qqupTWxBY"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

//Motor PINs
//#define ENA D0
#define IN1 D1
#define IN2 D2
#define IN3 D3
#define IN4 D4
//#define ENB D5
BlynkTimer timer;
bool forward = 0;
bool backward = 0;
bool left = 0;
bool right = 0;
//int Speed;
int a;
char auth[] = BLYNK_AUTH_TOKEN ; 
char ssid[] = "123456"; 
char pass[] = "12345678"; 
#define Relay D6 // relay pin
#define RELAY_BUTTON V5
#define fire D7 // flame sensor out
void setup() {
  Serial.begin(9600);
 // pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
 // pinMode(ENB, OUTPUT);
  Blynk.begin(auth, ssid, pass);
  timer.setInterval(100L,fireSensor);

}

BLYNK_WRITE(V0) {
  forward = param.asInt();
}

BLYNK_WRITE(V1) {
  backward = param.asInt();
}

BLYNK_WRITE(V2) {
  left = param.asInt();
}

BLYNK_WRITE(V3) {
  right = param.asInt();
}
/*
BLYNK_WRITE(V4) {
  Speed = param.asInt();
}
*/
BLYNK_CONNECTED() {

  Blynk.syncVirtual(RELAY_BUTTON);

 
}
BLYNK_WRITE(RELAY_BUTTON) {
  a = param.asInt();
  digitalWrite(Relay,a);
}
void fireSensor(){
int fireValue = digitalRead(fire);
Blynk.virtualWrite(V6, fireValue);
}



void smartcar() {
  if (forward == 1) {
    Forward();
    Serial.println("Forward");
  } else if (backward == 1) {
    Backward();
    Serial.println("Backward");
  } else if (left == 1) {
    Left();
    Serial.println("Left");
  } else if (right == 1) {
    Right();
    Serial.println("Right");
  } else if (forward == 0 && backward == 0 && left == 0 && right == 0) {
    Stop();
    Serial.println("Stop");
  }
}

void loop() {

  Blynk.run();
  timer.run();
  smartcar();
}

void Forward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Backward() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Left() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
}
void Right() {
  analogWrite(ENA, Speed);
  analogWrite(ENB, Speed);
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
}
void Stop() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}