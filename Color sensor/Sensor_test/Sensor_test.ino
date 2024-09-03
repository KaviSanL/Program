#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
//I2C pins declaration
LiquidCrystal_I2C lcd(0x27, 16,2); 
// TCS230 or TCS3200 pins wiring to Arduino
#define S0 4
#define S1 5
#define S2 6
#define S3 7
#define sensorOut 8

// Stores frequency read by the photodiodes
int red = 0;
int green = 0;
int blue = 0;

void setup() {
  lcd.init();
  lcd.backlight();
  // Setting the outputs
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  
  // Setting the sensorOut as an input
  pinMode(sensorOut, INPUT);
  
  // Setting frequency
//scaling to 20%
  digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
}

void loop(){
   lcd.setCursor(0,0);
   lcd.print("Color detected");
   color();

   if(red<blue && red<green && red<40){
      lcd.setCursor(0,1);
      lcd.print("    RED     ");
      delay(1000);
   }
   else if(blue < red && blue < green) {
      lcd.setCursor(0,1);
      lcd.print("    BLUE    ");
      delay(1000);
   }
   else if (green < red && green < blue) {
      lcd.setCursor(0,1);
      lcd.print("    GREEN   ");
      delay(1000);
   }  
   else {
 lcd.setCursor(0,0);
      lcd.print("   NO COLOR   ");
      lcd.setCursor(0,1); 
      lcd.print("   DETECTED   ");
     delay(5000);
  }
  
}

void color() {
  // Setting RED (R) filtered photodiodes to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,LOW);
  // Reading the output frequency
  red = pulseIn(sensorOut, LOW);
  delay(100);
  
  // Setting GREEN (G) filtered photodiodes to be read
  digitalWrite(S2,HIGH);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  green = pulseIn(sensorOut, LOW);
  delay(100);
 
  // Setting BLUE (B) filtered photodiodes
//to be read
  digitalWrite(S2,LOW);
  digitalWrite(S3,HIGH);
  // Reading the output frequency
  blue = pulseIn(sensorOut, LOW);
  delay(100);
}
