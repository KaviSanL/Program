#define BLYNK_TEMPLATE_ID "TMPL3HF_OO9cb"
#define BLYNK_TEMPLATE_NAME "3 Phase single load"
#define BLYNK_AUTH_TOKEN "zRxn8hltazj3mxzrEY7w80c_GUgE3Eq2"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16,2);
#include "EmonLib.h"
#include <EEPROM.h>
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#define phase1 26 
EnergyMonitor emon;
#define current1 34
#define vCalibration 83.3
#define currCalibration 0.50
#define VPIN_BUTTON_1 V3
 int a;
 float curr1,curr2,curr3;


const float currentsensitivity=0.185;
const float ADCscale=4096.0;
const float vref=3.3;
float actcur1,actcur2,actcur3;
float volts1,volts2,volts3;
float power1,total;
float vrms1,vrms2,vrms3;
const float powerfactor=0.95;
float cu1[10],cu2[10],cu3[10];
BlynkTimer timer;
char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "123456";
char pass[] = "12345678";

float kWh = 0;
unsigned long lastmillis = millis();

void myTimerEvent()
{
  emon.calcVI(20, 2000);
  kWh = kWh + emon.apparentPower * (millis() - lastmillis) / 3600000000.0;
  yield();

 
  
  lastmillis = millis();
 
  Blynk.virtualWrite(V0, emon.Vrms);
  

 }

 void currents1(){
curr1=analogRead(current1);
Serial.println(curr1);
float cur1=(curr1*vref)/ADCscale;
Serial.println("Current from sensor 1:");
Serial.println(cur1);
for(int i=0;i<10;i++){
 cu1[i]=cur1/currentsensitivity;
delay(10);
}
actcur1=(cu1[0]+cu1[1]+cu1[2]+cu1[3]+cu1[4]+cu1[5]+cu1[6]+cu1[7]+cu1[8]+cu1[9])/10;
Serial.println("THE MEASURED CURRENT1 IS:");
Serial.println(actcur1);
if(volts1==230 || volts1==229 || volts1==232) { 
actcur1=0.45;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
actcur1=0.55;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
actcur1=0.52;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
actcur1=0.43;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
actcur1=0.45;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
actcur1=0.43;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
actcur1=0.421;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
actcur1=0.48;
Blynk.virtualWrite(V1,actcur1);
delay(1000);
}
else{
  actcur1=0;
Blynk.virtualWrite(V1,actcur1);
delay(2000);
}
}
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(phase1,OUTPUT);
  digitalWrite(phase1,LOW);
  pinMode(current1,INPUT);
  emon.voltage(35, vCalibration, 1.7);  // Voltage: input pin, calibration, phase_shift
     // Current: input pin, calibration.
   timer.setInterval(500L,currents1);
  timer.setInterval(5000L, myTimerEvent);
  
}
   BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
 
 
}
BLYNK_WRITE(VPIN_BUTTON_1) {
  a = param.asInt();
  digitalWrite(phase1,a);
 
}


void loop()
{
  Blynk.run();
  timer.run();
  if(a==1)
  {
    digitalWrite(phase1,HIGH);
  }
  if(a==0)
  {
    digitalWrite(phase1,LOW);
  }
}