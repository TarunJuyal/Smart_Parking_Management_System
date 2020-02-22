#include <ESP8266WiFi.h>
#include <ESP8266WiFiType.h>
#include <Servo.h>
#include <timer.h>
#include <BlynkSimpleEsp8266.h>

Servo motor;
int angle;
int maxSlotFilled=0;
int status1 = 0;
int status2 = 0;
int status3 = 0;
int status4 = 0;
const int iRPin1=5;         //D1
const int iRPin2=4;         //D2
const int iRPin3=0;         //D3
const int iRPin4=2;         //D4
const int iRPin5=14;        //D5
const int iRPin6=12;        //D6
const int motorPin=13;      //D7
const int piezoPin=15;      //D8 

char auth[]="";
char ssid[]="";
char pass[]="";

SimpleTimer timer;

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(iRPin1,INPUT);
  pinMode(iRPin2,INPUT);
  pinMode(iRPin3,INPUT);
  pinMode(iRPin4,INPUT);
  pinMode(iRPin5,INPUT);
  pinMode(iRPin6,INPUT);
  motor.attach(motorPin);
  timer.setInterval(1000L,slot1);
  timer.setInterval(1000L,slot2);
  timer.setInterval(1000L,slot3);
  timer.setInterval(1000L,slot4);
  timer.setInterval(1000L,entrySide);
  timer.setInterval(1000L,exitSide);
}
void loop() {
  Blynk.run();
  timer.run();
}
//Function to see if all slots are filled
int checkFilled(){                                               
  maxSlotFilled=status1*status3;
  return maxSlotFilled;
}
//function to opening and closing of the gate
void motorRun(){    
  for(angle = 40; angle < 140; angle += 1)   
  { motor.write(angle); 
    delay(5);                                       
  } 
  delay(1000);
  for(angle = 140  ; angle>=40; angle-=1)    
  { motor.write(angle);
  delay(5);                                     
  } 
  delay(1000);
}
//slot functions are made to demonstrate empty parking slots.
void slot1(){
if(digitalRead(iRPin1)==HIGH){
  Blynk.virtualWrite(V1,255);
  status1=1;
  }
if(digitalRead(iRPin1)==LOW){
  Blynk.virtualWrite(V1,0);
  status1=0;;
  }  
}
void slot2(){
if(digitalRead(iRPin2)==HIGH){
  Blynk.virtualWrite(V2,255);
  status2=1;  }
if(digitalRead(iRPin2)==LOW){
  Blynk.virtualWrite(V2,0);
  status2=0;;
  }  
}
void slot3(){
if(digitalRead(iRPin3)==HIGH){
  Blynk.virtualWrite(V3,255);
  status3=1;
  }
if(digitalRead(iRPin3)==LOW){
  Blynk.virtualWrite(V3,0);
  status3=0;
  }  
}
void slot4(){
if(digitalRead(iRPin4)==HIGH){
  Blynk.virtualWrite(V4,255);
  status4=1;
  }
if(digitalRead(iRPin4)==LOW){
  Blynk.virtualWrite(V4,0);
  status4=0;
  }  
}
//entrySide and exitSide functions are made for opening and closing of gate.
void entrySide(){
if(digitalRead(iRPin5)==HIGH){
   if(!checkFilled()){
    motorRun();
    }
  else if(checkFilled()){
    tone(piezoPin,1000,3000);
    delay(500);
    noTone(piezoPin);
    }  
  }
  else{
    Serial.print("gate is empty ..");
    }
}
void exitSide(){
if(digitalRead(iRPin6)==HIGH){
  motorRun();
  }  
  else{
    Serial.print("gate is empty ..");
    }
}
