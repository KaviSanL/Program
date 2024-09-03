#include <Wire.h>
#include <Adafruit_BMP280.h>
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <MPU6050.h>
#include <BlynkSimpleEsp8266.h>
#define BMP_SCK  (13)
#define BMP_MISO (12)
#define BMP_MOSI (11)
#define BMP_CS   (10)
#define REPORTING_PERIOD_MS     1000
Adafruit_BMP280 bmp; 
char auth[] = "AGp7XPF93kYr_z9_0XOSndb47MF1YzRk";  //Enter your Blynk Auth token
char ssid[] = "123456";  //Enter your WIFI SSID
char pass[] = "12345678";  //Enter your WIFI Password
BlynkTimer timer;
MPU6050 sensor ;
int16_t ax, ay, az ;
int16_t gx, gy, gz ;
void setup() {
  Serial.begin(9600);
  Wire.begin ( );
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  Serial.println  ( "Initializing the sensor" ); 
  sensor.initialize ( ); 
  Serial.println (sensor.testConnection ( ) ? "Successfully Connected" : "Connection failed"); 
  delay (1000); 
  Serial.println ( "Taking Values from the sensor" );
  delay (1000);
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
    pinMode(D5,OUTPUT);
  }
  /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */
  
Blynk.virtualWrite(V0, bmp.readTemperature());
Blynk.virtualWrite(V1, bmp.readPressure());


}

void loop() {
  Blynk.run();
   sensor.getMotion6 (&ax, &ay, &az, &gx, &gy, &gz);
  ax = map (ax, -17000, 17000, 0, 180) ;
  Serial.println (ax);
  Blynk.virtualWrite(V2,ax);
  if(ax > 130)
  {
    digitalWrite(D5,HIGH);

  }
  else
  {
    digitalWrite(D5,LOW);
  }
  Serial.print(F("Temperature = "));
    Serial.print(bmp.readTemperature());
    Serial.println(" *C");

    Serial.print(F("Pressure = "));
    Serial.print(bmp.readPressure());
    Serial.println(" Pa");

    Serial.print(F("Approx altitude = "));
    Serial.print(bmp.readAltitude(1013.25)); /* Adjusted to local forecast! */
    Serial.println(" m");

    Serial.println();
    delay(2000);

}
