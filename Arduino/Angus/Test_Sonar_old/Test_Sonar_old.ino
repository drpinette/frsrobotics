#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>


void setup() {
    initialize();
    Serial.begin(9600);
    delay(3000);
    Serial.println("Start");
    int i;
    for (i = 0; i < 20000; i++) {
      float inches = readSonarDistance(RIGHT_FRONT_PIN);
  }
  Serial.println("End");
}

void loop() {
  // put your main code here, to run repeatedly:
  //float inches;
  //inches = readSonarDistance(RIGHT_FRONT_PIN);
  //inches = readSonarDistance(RIGHT_BACK_PIN);
  //inches = readSonarDistance(LEFT_FRONT_PIN);
  //inches = readSonarDistance(LEFT_BACK_PIN);
  //Serial.print(inches);
  //Serial.print("in,");
  //Serial.println();
  //delay(1);
}




