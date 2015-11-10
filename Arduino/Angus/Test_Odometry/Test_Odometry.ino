#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  initialize();
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);

}

void loop() {
  int odom = checkOdometry();
  if (odom == 0) digitalWrite(13,HIGH);
  else digitalWrite(13,LOW);
  Serial.println(odom);
  delay(5);
}
