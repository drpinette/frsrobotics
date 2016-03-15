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

bool done = false;

void loop() {
  // put your main code here, to run repeatedly:
  
 followLeftWall2(DEFAULT_FAR_THRESHOLD,DEFAULT_NEAR_THRESHOLD, DEFAULT_SPEED);
}
