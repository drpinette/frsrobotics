#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  //initialize();
  Serial.begin(9600);
  pinMode(FRONT_PROXIMITY_PIN1,INPUT_PULLUP);
  pinMode(FRONT_PROXIMITY_PIN2,INPUT_PULLUP);
  pinMode(FRONT_PROXIMITY_PIN3,INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
  //=====Test Code (17/03/2015) (DD/MM/YYYY)=====
  Serial.print(digitalRead(FRONT_PROXIMITY_PIN1));
  Serial.print(digitalRead(FRONT_PROXIMITY_PIN2));
  Serial.println(digitalRead(FRONT_PROXIMITY_PIN3));
  //else (digitalWrite(13,LOW));
  delay(10);
}
