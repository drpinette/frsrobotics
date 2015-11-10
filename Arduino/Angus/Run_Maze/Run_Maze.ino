#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  initialize();
  delay(7500);
  
  //Move along wall
  bool done = false;
  while (!done){
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
  }
  digitalWrite(13,HIGH);
  
  //Move into intersection
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   //Serial.println(distance);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  }
  digitalWrite(13,LOW);
  //stop();
  //delay(3000);
  /*move(13);
  stop();*/
  //return;
  //move front out of intersection
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(RIGHT_FRONT_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  }
  digitalWrite(13,HIGH);
  //stop();
  //delay(100);
  //move rear out of intersection
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  }
  digitalWrite(13,LOW);
  
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
  digitalWrite(13,HIGH);
  
  //Move into doorway for room two
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  }
  digitalWrite(13,LOW);
  //stop();
  
  //note may enter room 1 and go into room 2 here
  
  //turn around
  turn180(SLOW_SPEED);
  //delay(500);
  stop();
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,BRAKE,BRAKE);
  //move past wall on right if any
  if (isDoorA) {
     while (!done){
       done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
    }
  }
  
   
  //moe to left wall
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  }
  digitalWrite(13,LOW);
  //stop();
  

  //Move back along wall
  done = false;
  while (!done){
   done = followLeftWall(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD); 
  } 
  
  //Move into intersection
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  }
  stop;
  delay(5000);
  
  //turn for Door/Room 3
  turnLeft90;
  
  //Move out of intersection(Part 2)
  done = false;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  while (!done){
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  }
  
  //Move to Room/Door 3
  while (true){
       float distance = readSonarDistance(RIGHT_BACK_PIN);
       if (distance > INTERSECTION_DISTANCE_THRESHOLD) break;
       followLeftWall(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
  }
  
  //turn for Door/Room 4
  turn180;
  followRightWall(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
  stop;
}

//===============================================================
void loop() {
  // put your main code here, to run repeatedly:

}
