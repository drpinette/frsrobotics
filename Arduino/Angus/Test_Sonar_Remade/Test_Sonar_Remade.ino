#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>


void setup() {
    initialize();
    Serial.begin(57600);
    digitalWrite(13,HIGH);
    delay(500);
    digitalWrite(13,LOW);
    delay(1000);
}

void loop() {
  //put your main code here, to run repeatedly:
  float inches = readSonarDistance(RIGHT_FRONT_PIN);
  delay(5);
  //float inches3 = readSonarDistance(LEFT_FRONT_PIN);
  float inches2 = readSonarDistance(RIGHT_BACK_PIN);
  //float inches4 = readSonarDistance(LEFT_BACK_PIN);
  Serial.print("Right_Front ");
  Serial.print(inches);
  Serial.print("Inches, Right_Back ");
  Serial.print(inches2);
  /*Serial.print("Inches, Left_Front ");
  Serial.print(inches3);
  Serial.print("Inches, Left_Back ");
  Serial.print(inches4);
  //Serial.print("Inches");*/
  Serial.println();
  delay(5);
}
