#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize(); 
  move(200,DEFAULT_SPEED);
  setMotorSpeed(0,0,BRAKE,BRAKE);
}

void loop() {
  // put your main code here, to run repeatedly:

}
