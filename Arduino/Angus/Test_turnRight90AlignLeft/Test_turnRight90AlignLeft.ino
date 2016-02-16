#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  initialize();
  delay(5000);
  
  turnRight90AlignLeft(100);
}

void loop() {
  // put your main code here, to run repeatedly:

}
