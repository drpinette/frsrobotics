#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize();
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  Serial.begin(9600);
  
}

void loop() {
  // put your main code here, to run repeatedly:
  
 followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, DEFAULT_SPEED);
}
