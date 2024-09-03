#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include <Adafruit_BMP280.h>
#include <MPU6050.h>
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define REPORTING_PERIOD_MS     1000

LiquidCrystal_I2C lcd(0x27, 16, 2);
PulseOximeter pox;
uint32_t tsLastReport = 0;
Adafruit_BMP280 bmp; 
MPU6050 sensor ;
int16_t ax, ay, az ;
int16_t gx, gy, gz ;
void setup()
{
  //Pressure
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  Wire.begin ( );
  while ( !Serial ) delay(100);   // wait for native usb
  Serial.println(F("BMP280 test"));
  unsigned status;
  //status = bmp.begin(BMP280_ADDRESS_ALT, BMP280_CHIPID);
  status = bmp.begin(0x76);
  if (!status) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring or "
                      "try a different address!"));
    Serial.print("SensorID was: 0x"); Serial.println(bmp.sensorID(),16);
    Serial.print("        ID of 0xFF probably means a bad address, a BMP 180 or BMP 085\n");
    Serial.print("   ID of 0x56-0x58 represents a BMP 280,\n");
    Serial.print("        ID of 0x60 represents a BME 280.\n");
    Serial.print("        ID of 0x61 represents a BME 680.\n");
    while (1) delay(10);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
    // accelero meter
   Serial.println  ( "Initializing the sensor" ); 
   sensor.initialize ( ); 
   Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 
   delay (1000); 
   Serial.println ( "Taking Values from the sensor" );
   delay (1000);
   // pulse
   if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } else {
    Serial.println("SUCCESS");
  }
  pox.setIRLedCurrent(MAX30100_LED_CURR_7_6MA);

  pox.setOnBeatDetectedCallback(onBeatDetected);
}
void onBeatDetected()
{

  Serial.println("Beat!!!");

}
void loop()
{
  //spo2
  pox.update();
  

    lcd.clear();
    lcd.setCursor(0 , 0);
    lcd.print("BPM : ");
    lcd.print(pox.getHeartRate());
    lcd.setCursor(0 , 1);
    lcd.print("Sp02: ");
    lcd.print(pox.getSpO2());
    lcd.print("%");
    tsLastReport = millis();
    
    
  
  delay(2000);
  
  //Accellerometer
  sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);
  ax = map (ax, -17000, 17000, 0, 180) ;
 // Serial.println (ax);
   //Print
   //lcd.clear();
   //lcd.setCursor(0,0);
   //lcd.print("Temp : ");
   //lcd.print(bmp.readTemperature());
  //lcd.print(" *C");
  //lcd.setCursor(0,1);
  //lcd.print("Pressure : ");
  //lcd.print(bmp.readPressure());
  //lcd.print(" Pa");
  //delay(2000);
  //lcd.clear();
  //lcd.print("Tilt : ");
  //lcd.print(ax);
  //delay(2000);
}