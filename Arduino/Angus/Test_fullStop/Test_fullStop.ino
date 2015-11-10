#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize(); 
  Serial.begin(9600);
}

void loop() {
  int speed = 1024;
  setMotorSpeed(speed, speed, FORWARD, FORWARD);
  delay(2000);//Let the robot get upto speed
  fullStop(speed); //Now Stop it
}
  
