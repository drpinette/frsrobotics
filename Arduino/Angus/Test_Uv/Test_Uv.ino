#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize(); 
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  int right = analogRead(UV_RIGHT_PIN);
  int left = analogRead(UV_LEFT_PIN);
  Serial.print(left);Serial.print(" ");Serial.println(right);
  delay(1000);  
}
