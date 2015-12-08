#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  initialize();
  delay(5000);
  
  //Move along wall
  bool done;
  do {
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);  
  } while (!done);
  digitalWrite(13,HIGH); //debug, remove for actual competition
  
  //Move into intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   //Serial.println(distance);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW); //debug, remove for actual competition
  //stop();
  //delay(3000);
  /*move(13);
  stop();*/
  //return;
  //move front out of intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(RIGHT_FRONT_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,HIGH); //debug, remove for actual competition
  //stop();
  //delay(100);
  //move rear out of intersection
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  }
  digitalWrite(13,LOW); //debug, remove for actual competition
  
  //Check Room 1 Door A
  bool isDoorA;
  {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   isDoorA = distance > INTERSECTION_DISTANCE_THRESHOLD;
  }
  //NTS: If Door = A, Then we will enter Room 1
  
  
  //stop();
  //return;
  //delay(500);
  //Move along right wall
  done = false;
  while (!done){
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
  }
  digitalWrite(13,HIGH); //debug, remove for actual competition
  
  //Move into doorway for room two 
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW); //debug, remove for actual competition
  //stop();
  
  //note may enter room 1 and go into room 2 here
  
  
  //turn around
  stop();
  turn180(SLOW_SPEED);
  
  //move past wall on right if any
  if (isDoorA) {
    do {
       done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
    } while (!done);
  }
  
  //move to left wall
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW); //debug, remove for actual competition
  //fullStop();
  
  //Move back along wall
  do {
   done = followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD); 
  } while (!done);
  //fullStop();
  
  //Move into intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,HIGH);
  stop();
  
  //turn for Door/Room 3
  turnLeft90(SLOW_SPEED);
  
  //Move out of intersection(Part 2)
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW);
 
  //Move to Room/Door 3
  do {
      done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
  } while (!done);
  digitalWrite(13,HIGH);
  
  //Move into doorway for room three 
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW);
  //turn for Door/Room 4
  stop();
  turn180(SLOW_SPEED);
  
  //Move towards intersection
  followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
  
  //Move into intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW);

  //Move nose out of intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_FRONT_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW);

  //Move butt out of intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance <  LEAVING_INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  digitalWrite(13,LOW);
 
 //move past room 4 
  do {
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);  
  } while (!done);
  digitalWrite(13,HIGH); //debug, remove for actual competition
  
  //Move into intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  
  stop();
  
  turnLeft90(SLOW_SPEED);
  
  //moving along outside of room 4
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance <  INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  digitalWrite(13,HIGH); //debug, remove for actual competition
  
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance >  INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  digitalWrite(13,HIGH); //debug, remove for actual competition
  
  stop();
  
  turnLeft90(SLOW_SPEED);
  
  //moving into room 4 doorway
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance <  LEAVING_INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  digitalWrite(13,HIGH); //debug, remove for actual competition
  
  fullStop();
}
//===============================================================
void loop() {
  // put your main code here, to run repeatedly:

}
