#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize();
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(4000); 
  Serial.begin(9600);
  moveToCandle(MAX_MOTOR_SPEED, 10000);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
