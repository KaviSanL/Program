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
#define vCalibration 83.3
#define currCalibration 0.50
#define VPIN_BUTTON_1 V3
 int a;
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
  Blynk.virtualWrite(V1, emon.Irms);

 }

 
void setup()
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(phase1,OUTPUT);
  digitalWrite(phase1,LOW);

  emon.voltage(35, vCalibration, 1.7);  // Voltage: input pin, calibration, phase_shift
  emon.current(34, currCalibration);    // Current: input pin, calibration.
 
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