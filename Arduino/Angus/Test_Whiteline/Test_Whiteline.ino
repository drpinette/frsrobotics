#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  initialize();

}

void loop() {
  int white = isWhiteLine();
  Serial.println(white);
  delay(1000);
}
