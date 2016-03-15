#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  
   Serial.begin(57600);
  initialize();
  delay(5000);
  bool done;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  
  move(14);
  turnLeft90AlignRight();
  //moving along outside of room 4
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD,DEFAULT_SPEED);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  
  
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  move(10);
  
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD,DEFAULT_SPEED);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  
  move(5);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  stop();
  
  turnLeft90(SLOW_SPEED);
  
  //moving into room 4 doorway
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, 127);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance <  LEAVING_INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  move(10);
  
  
  turnLeft90(SLOW_SPEED);
  
  fullStop();
}


void loop() {
  // put your main code here, to run repeatedly:

}
