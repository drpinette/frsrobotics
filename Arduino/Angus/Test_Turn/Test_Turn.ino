++#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  initialize();
  delay(4000);
}

void loop() {
  //turnLeft90(MAX_MOTOR_SPEED/2);
  turn180(MAX_MOTOR_SPEED/2);
  //turnRight90(MAX_MOTOR_SPEED/2);
  delay (4000);

}
