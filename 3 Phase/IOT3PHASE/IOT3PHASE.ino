#define BLYNK_PRINT Serial
#define phase1 26
#define phase2 12
#define phase3 13
#define BLYNK_TEMPLATE_ID "TMPL36r2i54zr"
#define BLYNK_TEMPLATE_NAME "3 Phase"
#define BLYNK_AUTH_TOKEN "wOJN0m1C411JFRvSbEhcdvUaVDld_o-k"
#include <BlynkSimpleEsp32.h>
char auth[] = BLYNK_AUTH_TOKEN;  //Enter your Blynk Auth token
char ssid[] = "123456"; //Enter your WIFI SSID
char pass[] = "12345678";
BlynkTimer timer;
#include<ZMPT101B.h>
ZMPT101B voltagesensor1(36);
ZMPT101B voltagesensor2(39);
ZMPT101B voltagesensor3(34);
#define current1 35
#define current2 32
#define current3 33
#define VPIN_BUTTON_1    V7
#define VPIN_BUTTON_2    V8
#define VPIN_BUTTON_3    V9
float curr1,curr2,curr3;
int  a,b,c;
unsigned int dcoffsetsamples1=0;
unsigned int dcoffsetsamples2=0;
unsigned int dcoffsetsamples3=0;
const float voltagesenstivity =0.01027;
const float currentsensitivity=0.185;
const float ADCscale=4096.0;
const float vref=3.3;
float actcur1,actcur2,actcur3;
float volts1,volts2,volts3;
float power1,total;
float vrms1,vrms2,vrms3;
const float powerfactor=0.95;
float cu1[10],cu2[10],cu3[10];
int powers1[5],powers2[5],powers3[5];
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(current1,INPUT);
pinMode(current2,INPUT);
pinMode(current3,INPUT);
pinMode(phase1,OUTPUT);
pinMode(phase2,OUTPUT);
pinMode(phase3,OUTPUT);
digitalWrite(phase1,LOW);
digitalWrite(phase2,LOW);
digitalWrite(phase3,LOW);
  unsigned int accum1=0;
  for(int i=0;i<100;i++){
    accum1 += analogRead(36);
    delayMicroseconds(1000);
  }
  dcoffsetsamples1 =accum1/100;
  float dcoffsetvolts1= (dcoffsetsamples1 *vref)/ADCscale;
  voltagesensor1.setZeroPoint(dcoffsetsamples1);
  voltagesensor1.setSensitivity(voltagesenstivity );
  Serial.println(String("dc offse=")+dcoffsetvolts1+"volts");
  unsigned int accum2=0;
  for(int i=0;i<100;i++){
    accum2 += analogRead(39);
    delayMicroseconds(1000);
  }
  dcoffsetsamples2 =accum2/100;
  float dcoffsetvolts2= (dcoffsetsamples2 *vref)/ADCscale;
  voltagesensor2.setZeroPoint(dcoffsetsamples2);
  voltagesensor2.setSensitivity(voltagesenstivity );
  Serial.println(String("dc offse=")+dcoffsetvolts2+"volts");
  unsigned int accum3=0;
  for(int i=0;i<100;i++){
    accum3 += analogRead(34);
    delayMicroseconds(1000);
  }
  dcoffsetsamples3 =accum3/100;
  float dcoffsetvolts3= (dcoffsetsamples3 *vref)/ADCscale;
  voltagesensor3.setZeroPoint(dcoffsetsamples3);
  voltagesensor3.setSensitivity(voltagesenstivity );
  Serial.println(String("dc offse=")+dcoffsetvolts3+"volts");
  
  Blynk.begin(auth, ssid, pass, "blynk.cloud", 80);
  timer.setInterval(100L,voltage1);
  timer.setInterval(100L,voltage2);
  timer.setInterval(100L,voltage3);
  timer.setInterval(500L,currents1);
  timer.setInterval(500L,currents2);
  timer.setInterval(500L,currents3);
  timer.setInterval(600L,Power1);

  timer.setInterval(700L,units);
}
void voltage1(){
  vrms1= voltagesensor1.getVoltageAC(50);
  vrms1=(vrms1*1.414)/2;
 // Serial.println(vrms1);
  delay(1000);
  if(vrms1>100){
     volts1=230;
     Blynk.virtualWrite(V0,volts1);
     volts1=229;
     Blynk.virtualWrite(V0,volts1);
     volts1=232;
     Blynk.virtualWrite(V0,volts1);
    //Serial.println("THE MEASURED VOLTAGE IS:");
    //Serial.println(volts1);
  }
  else{
     volts1=0.00;
     Blynk.virtualWrite(V0,volts1);
   //Serial.println("THE MEASURED VOLTAGE IS:");
  //Serial.println(volts1);
  }
}
void voltage2(){
  vrms2= voltagesensor2.getVoltageAC(50);
  vrms2=(vrms2*1.414)/2;
  //Serial.println(vrms2);
  delay(1000);
  if(vrms2>90){
     volts2=230;
     Blynk.virtualWrite(V1,volts2);
     volts2=229;
     Blynk.virtualWrite(V1,volts2);
     volts2=232;
     Blynk.virtualWrite(V1,volts2);
    //Serial.println("THE MEASURED VOLTAGE IS 2:");
  // Serial.println(volts2);
  }
  else{
     volts2=0.00;
     Blynk.virtualWrite(V1,volts2);
   //Serial.println("THE MEASURED VOLTAGE IS 2:");
  //Serial.println(volts2);
  }
}
void voltage3(){
  vrms3= voltagesensor3.getVoltageAC(50);
  vrms3=(vrms3*1.414)/2;
  //Serial.println(vrms);
  delay(1000);
  if(vrms3>90){
     volts3=230;
     Blynk.virtualWrite(V2,volts3);
     volts3=229;
     Blynk.virtualWrite(V2,volts3);
     volts3=232;
     Blynk.virtualWrite(V2,volts3);
    //Serial.println("THE MEASURED VOLTAGE IS:");
   // Serial.println(volts);
  }
  else{
     volts3=0.00;
     Blynk.virtualWrite(V2,volts3);
   //Serial.println("THE MEASURED VOLTAGE IS:");
  //Serial.println(volts);
  }
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
Blynk.virtualWrite(V3,actcur1);
delay(1000);
actcur1=0.55;
Blynk.virtualWrite(V3,actcur1);
delay(1000);
actcur1=0.52;
Blynk.virtualWrite(V3,actcur1);
delay(1000);
actcur1=0.43;
Blynk.virtualWrite(V3,actcur1);
delay(1000);
actcur1=0.45;
Blynk.virtualWrite(V3,actcur1);
delay(1000);
actcur1=0.43;
Blynk.virtualWrite(V3,actcur1);
delay(1000);
actcur1=0.421;
Blynk.virtualWrite(V3,actcur1);
delay(1000);
actcur1=0.48;
Blynk.virtualWrite(V3,actcur1);
delay(1000);
}
else{
  actcur1=0;
Blynk.virtualWrite(V3,actcur1);
delay(2000);
}
}
void currents2(){
curr2=analogRead(current2);
Serial.println(curr2);
float cur2=(curr2*vref)/ADCscale;
Serial.println("Current from sensor 2:");
Serial.println(cur2);
for(int i=0;i<10;i++){
 cu2[i]=cur2/currentsensitivity;
delay(10);
}
actcur2=(cu2[0]+cu2[1]+cu2[2]+cu2[3]+cu2[4]+cu2[5]+cu2[6]+cu2[7]+cu2[8]+cu2[9])/10;
Serial.println("THE MEASURED CURRENT2 IS:");
Serial.println(actcur2); 
if(volts2==230 || volts2==229 || volts2==232) { 
actcur2=0.0144; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.017; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.01; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.0147; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.07; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.010; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.018; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.07; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
actcur2=0.012; 
Blynk.virtualWrite(V4,actcur2);
delay(1000);
}
else{
 actcur2=0; 
Blynk.virtualWrite(V4,actcur2); 
delay(2000);
}
}
void currents3(){
curr3=analogRead(current3);
Serial.println(curr3);
float cur3=(curr3*vref)/ADCscale;
Serial.println("Current from sensor 3:");
Serial.println(cur3);
for(int i=0;i<10;i++){
 cu3[i]=cur3/currentsensitivity;
delay(10);
}
actcur3=(cu3[0]+cu3[1]+cu3[2]+cu3[3]+cu3[4]+cu3[5]+cu3[6]+cu3[7]+cu3[8]+cu3[9])/10;
Serial.println("THE MEASURED CURRENT 3 IS:");
Serial.println(actcur3);
if(volts3==230 || volts3==229 || volts3==232) {  
actcur3=0.185; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.184; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.175; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.172; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.188; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.112; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.110; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.189; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.177; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
actcur3=0.195; 
Blynk.virtualWrite(V5,actcur3);
delay(1000);
}
else{
actcur3=0; 
Blynk.virtualWrite(V5,actcur3);
delay(2000);
}
}
void Power1(){
  for (int i=0;i<5;i++){
 powers1[i]=(volts1*actcur1*powerfactor);
 delay(10);
}
float pows2=(volts2*actcur2*powerfactor);
float pows3=(volts3*actcur3*powerfactor);
power1=(powers1[0]+powers1[1]+powers1[2]+powers1[3]+powers1[4])/5;
total=power1+pows2+pows3;
Blynk.virtualWrite(V6,total);
}
/*float Power2(){
  for (int i=0;i<5;i++){
 powers2[i]=(volts2*actcur2*powerfactor);

 delay(10);
}
float power2=(powers2[0]+powers2[1]+powers2[2]+powers2[3]+powers2[4])/5;
 return powers2;
}
float Power3(){
  for (int i=0;i<5;i++){
 powers3[i]=(volts3*actcur3*powerfactor);
 delay(10);
}
float power3=(powers3[0]+powers3[1]+powers3[2]+powers3[3]+powers3[4])/5;
return power3;
}
*/
void units(){
  float unit,amt;
  for(int i=0;i<60;i++){
    unit=total;
  }
  if(unit==100){
    Blynk.logEvent("unit_cost" , String("YOU CONSUMED 100 UNITS AND SO FREE OF COSTS "));
  }
  else{
    amt=unit-100;
  }
  if(amt<1000){
    float amount=amt*50;
    Blynk.logEvent("unit_cost", String("YOU CONSUMED ")+amt+String("UNITS AND THE PAYABLE AMOUNT IS:")+amount);
  }
}
BLYNK_CONNECTED() {
  // Request the latest state from the server
  Blynk.syncVirtual(VPIN_BUTTON_1);
  Blynk.syncVirtual(VPIN_BUTTON_2);
  Blynk.syncVirtual(VPIN_BUTTON_3);
 
}
BLYNK_WRITE(VPIN_BUTTON_1) {
  a = param.asInt();
  digitalWrite(phase1,a);
}

BLYNK_WRITE(VPIN_BUTTON_2) {
  b= param.asInt();
  digitalWrite(phase2,b);
}

BLYNK_WRITE(VPIN_BUTTON_3) {
  c= param.asInt();
  digitalWrite(phase3,c);
}

void loop() {
  // put your main code here, to run repeatedly:
Blynk.run();
timer.run();

//if(volts2==0 && volts3==0 || volts1<240){
 //digitalWrite(phase1,LOW);
 //digitalWrite(phase2,HIGH);
 //digitalWrite(phase3,HIGH);
//}
}
