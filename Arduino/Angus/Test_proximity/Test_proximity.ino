#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  //initialize();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  //=====Test Code (17/03/2015) (DD/MM/YYYY)=====
  bool ok = readProximity();
  if (ok) {
  digitalWrite(13, HIGH); }
  else{
  digitalWrite(13, LOW); }
  //else (digitalWrite(13,LOW));
  delay(50);
}
