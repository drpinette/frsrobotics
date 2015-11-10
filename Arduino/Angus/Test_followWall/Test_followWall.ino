#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize(); 
  Serial.begin(9600);
  digitalWrite(13,HIGH);
  delay(500);
  digitalWrite(13,LOW);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
 digitalWrite(13,HIGH);
 followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
 /*float inches = readSonarDistance(RIGHT_BACK_PIN);
 Serial.print("right_Back");
 Serial.print(inches);
 Serial.println();
 delay(250);*/
}
