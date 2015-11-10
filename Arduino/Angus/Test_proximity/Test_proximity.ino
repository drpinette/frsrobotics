#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

int i = 0;

void setup() {
  // put your setup code here, to run once:
  initialize;
  Serial.begin(9600);
  pinMode(12,INPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  setMotorSpeed(CANDLE_LOCATE_SPEED,CANDLE_LOCATE_SPEED, FORWARD, FORWARD);
  //=====Test Code (17/03/2015) (DD/MM/YYYY)=====
  if (readProximity() > 5) {
    digitalWrite(13,HIGH);
    stop();
  }
  else move(50);
  //else (digitalWrite(13,LOW));
  delay(1);
  i++;
}
