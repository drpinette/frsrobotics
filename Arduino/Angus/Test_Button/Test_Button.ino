#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  pinMode(A3, INPUT);
  Serial.begin(57600);
  initialize();
  delay(1000);
  if();
    digitalWrite(13, HIGH);
    delay(500);
    digitalWrite(13, LOW);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
