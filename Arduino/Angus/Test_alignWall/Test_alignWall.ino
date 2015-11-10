#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  initialize();
  Serial.begin(9600);

}

void loop() {
  float inches = readSonarDistance(0);
  Serial.print(inches);
  Serial.print("in,");
  Serial.println();
  delay(1000);

}
  //NTS: Ask Dr. Pinnette to help so we can get a reading from 2 
  //sonars instead of 1.
