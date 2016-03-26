#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  initialize();
  waitForPushButton();
  delay(1000);
}

void loop() {
  //turnLeft90(MAX_MOTOR_SPEED/2);
  //turn180(MAX_MOTOR_SPEED/2);
  turnLeft90(MAX_MOTOR_SPEED/2);
  delay (3000);

}
