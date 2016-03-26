#include <Angus_Lib.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

void setup() {
  initialize();
  extinguish(1);
  delay(1000);
  extinguish(0);

}

void loop() {

}
