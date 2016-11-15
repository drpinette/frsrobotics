#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>
/*
#define RIGHT_FRONT_PIN 11
#define RIGHT_BACK_PIN 8
#define LEFT_FRONT_PIN 7
#define LEFT_BACK_PIN 5

unsigned long t1;
unsigned long t2;
unsigned long t3;
unsigned long t4;
unsigned long t5;

bool initialized = false;

unsigned long sumDuration = 0;

unsigned long d1 = 0;
unsigned long d2 = 0;
unsigned long d3 = 0;
unsigned long d4 = 0;
unsigned long d5 = 0;

float readSonarDistance(int pingPin) {
  t1 = micros();
  unsigned long duration;
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  t2 = micros();
  pinMode(pingPin, INPUT);
  t3 = micros();
  duration = pulseIn(pingPin, HIGH);
  sumDuration += duration;
  t4 = micros();
  return ((float) duration) / 74.0 / 2.0;
}
*/


void setup() {
    initialize();
 /*   Serial.begin(9600);
    delay(4000);
    digitalWrite(13,HIGH);
    d1 = 0;
    d2 = 0;
    d3 = 0;
    d4 = 0;
    d5 = 0;
    t5 = micros();
    for(int i = 0; i < 100; i++) {
      float inches = readSonarDistance(RIGHT_BACK_PIN); 
      t5 = micros();
      if (initialized) d1 += t1 - t5;
      d2 += t2 - t1;
      d3 += t3 - t2;
      d4 += t4 - t3;
      d5 += t5 - t4;
      initialized = true;
    }
    Serial.print("avg d1 ");Serial.println(((float)d1) / 99.0);
    Serial.print("avg d2 ");Serial.println(((float)d3) / 100.0);
    Serial.print("avg d3 ");Serial.println(((float)d3) / 100.0);
    Serial.print("avg d4 ");Serial.println(((float)d4) / 100.0);
    Serial.print("avg duration ");Serial.println(((float)sumDuration) / 100.0);
    Serial.print("avg d5 ");Serial.println(((float)d5) / 100.0);
    */
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(readSonarDistance(RIGHT_BACK_PIN));
  Serial.print("     Right back pin\n");
  /*Serial.print(readSonarDistance(LEFT_BACK_PIN));
  Serial.print("     Left back pin\n");
  Serial.print(readSonarDistance(LEFT_FRONT_PIN));
  Serial.print("     Left front pin\n");
  Serial.print(readSonarDistance(RIGHT_FRONT_PIN));
  Serial.print("     Right front pin\n");*/
  Serial.println();
  delay(1000);
}




