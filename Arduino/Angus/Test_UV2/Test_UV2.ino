#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize(); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(analogRead(A5));
  delay(100);  
}
