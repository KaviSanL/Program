#define BLYNK_TEMPLATE_ID "TMPL3bVQS8poU"
#define BLYNK_TEMPLATE_NAME "Drone"
#define BLYNK_AUTH_TOKEN "uD0bTZd84um_EyXCxXnpSnpJmOBfGGMq"
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>

char auth[] =BLYNK_AUTH_TOKEN;
char ssid[] = "123456"; 
char pass[] = "12345678";  

DHT dht(D4, DHT11);
BlynkTimer timer;


#define Smoke A0   
#define fire D5

void checkPhysicalButton();
int relay1State = LOW;

#define RELAY_PIN_1       D3   
#define VPIN_BUTTON_1    V1 


double T, P;
char status;



void setup() {
  Serial.begin(9600);


 pinMode(RELAY_PIN_1, OUTPUT);
 digitalWrite(RELAY_PIN_1, LOW);

  digitalWrite(RELAY_PIN_1, relay1State);


  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  dht.begin();


  timer.setInterval(100L, SmokeSensor);
  //timer.setInterval(100L, DHT11sensor);
  timer.setInterval(100L, fireSensor);
  
}

/*
void DHT11sensor() {
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Blynk.virtualWrite(V0, t);
  Blynk.virtualWrite(V1, h);


}

*/
void SmokeSensor() {
  int value = analogRead(Smoke);
  value = map(value, 0, 1024, 0, 100);
  value = (value - 100) * -1;

  Blynk.virtualWrite(V3, value);

}
void fireSensor(){
int fireValue = digitalRead(fire);
Blynk.virtualWrite(V0, fireValue);
}




BLYNK_CONNECTED() {

  Blynk.syncVirtual(VPIN_BUTTON_1);
}

BLYNK_WRITE(VPIN_BUTTON_1) {
  relay1State = param.asInt();
  digitalWrite(RELAY_PIN_1, relay1State);
}



void loop() {
   


     
      
  Blynk.run();
  timer.run();

  }
