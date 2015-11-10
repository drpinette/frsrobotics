#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  initialize();
  setMotorSpeed(MAX_MOTOR_SPEED,MAX_MOTOR_SPEED,FORWARD,FORWARD);
  delay (4000);
  setMotorSpeed(0,0,BRAKE,BRAKE);
}

void loop() {
  

}
