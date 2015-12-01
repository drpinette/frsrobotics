#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  initialize();
  delay(2000);
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  turn180(SLOW_SPEED);
  digitalWrite(13,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
