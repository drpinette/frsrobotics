#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>



void setup() {
  void runDoor1A();
  void runRoom2();
  void runRoom3();
  void runRoom4a();
  // put your setup code here, to run once:
  Serial.begin(57600);
  initialize();
  delay(5000);
  
  //Move along wall
  bool done;
  do {
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  //Move into intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   //Serial.println(distance);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW); //debug, remove for actual competition
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
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  //stop();
  //delay(100);
  //move rear out of intersection

  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW); //debug, remove for actual competition
  
  //Check Room 1 Door A
  bool isDoorA;
  
  float distance = readSonarDistance(LEFT_FRONT_PIN);
  isDoorA = distance > INTERSECTION_DISTANCE_THRESHOLD;
  if (isDoorA) runRoom1DoorA();
  //NTS: If Door = A, Then we will enter Room 1
  //Move along right wall
  runRoom2();
  
  turnLeft90(SLOWMO_SPEED);
  
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
  //digitalWrite(13,LOW); //debug, remove for actual competition
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
  //digitalWrite(13,HIGH);
  stop();
  
  //turn for Door/Room 3
  turnLeft90(SLOW_SPEED);
  
  //Move out of intersection(Part 2)
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW);
 
  //Move to Room/Door 3
  do {
      done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
  } while (!done);
  //digitalWrite(13,HIGH);
  
  //Move into doorway for room three 
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW);
  //turn for Door/Room 4
  stop();
  turnRight90AlignLeft();
  
  runRoom3();
  
  //Move towards intersection
  do {
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  //Move into intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW);

  //Move nose out of intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_FRONT_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW);

  //Move butt out of intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   float distance2 = readSonarDistance(LEFT_BACK_PIN);
   done = distance <  LEAVING_INTERSECTION_DISTANCE_THRESHOLD || distance2 <  LEAVING_INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW);
  
  //check for room 4 door
  if (readSonarDistance(LEFT_FRONT_PIN) > INTERSECTION_DISTANCE_THRESHOLD) {
    stop();
    runRoom4a();
  }  
  fullStop();
 
 //move past room 4 
  do {
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  //Move into intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  
  turnLeft90(SLOW_SPEED);
  
  //moving along outside of room 4
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance <  INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance >  INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  stop();
  
  turnLeft90(SLOW_SPEED);
  
  //moving into room 4 doorway
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance <  LEAVING_INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  fullStop();
}

//Room Subroutines

void runRoom1DoorA() {
  // move into doorway
  move(23, DEFAULT_SPEED);
  // entering room
  stop();
  turnLeft90(ROOM_ENTER_SPEED);
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  bool done;
  do  {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  move(15, DEFAULT_SPEED);
  //Look for candle
  stop(500);
  switch (locateCandle(CANDLE_LOCATE_SPEED,true)){
    case 1: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED,16); fullStop(); break;
    case 2: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED,161); fullStop(); break;
    case 3: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 50); fullStop(); break; 
    case 0: setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
        do  {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  
  move (14);
  
  stop();
  turnLeft90AlignRight();
  
  
    do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance >  INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  
  move(17);
  
  stop();
  turnRight90AlignLeft();
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  /*
  //Move into doorway for room two 
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW); //debug, remove for actual competition
  //stop();
  
  //note may enter room 1 and go into room 2 here
  */
  //turnLeft90AlignRight(CANDLE_LOCATE_SPEED);
  }
}
void runRoom2(){
  //Move into room 2
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  bool done;
  do  {
   followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  move(15, DEFAULT_SPEED);
  //Look for candle
  stop();
  
  switch (locateCandle(CANDLE_LOCATE_SPEED,true)){
    case 1: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 25); fullStop(); break;
    case 2: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 94); fullStop(); break;
    case 3: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 78); fullStop(); break; 
    case 0: 
       setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
       bool done;
       do  {
       followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
       float distance = readSonarDistance(LEFT_BACK_PIN);
       done = distance < INTERSECTION_DISTANCE_THRESHOLD;
      } while (!done);
       move(10);
       stop();
      break;
  }
  
}

void runRoom3(){
  //Move into room 3
  bool done;
  do  {
   followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  move(15, DEFAULT_SPEED);
  //Look for candle
  stop();
  
  switch (locateCandle(CANDLE_LOCATE_SPEED,true)){
    case 1: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 61); fullStop(); break;
    case 2: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 72); fullStop(); break;
    case 3: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 6); fullStop(); break; 
    case 0: 
       setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
       bool done;
       do  {
       followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
       float distance = readSonarDistance(LEFT_BACK_PIN);
       done = distance < INTERSECTION_DISTANCE_THRESHOLD;
      } while (!done);
       move(10);
      stop();
      turnLeft90(SLOWMO_SPEED);
  }
  
}

void runRoom4a() {
  //move into room 4
  move(10);
  stop();
  turnLeft90(ROOM_ENTER_SPEED);
  bool done;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  move(15, DEFAULT_SPEED);
  //Look for candle
  stop();
  
  switch (locateCandle(CANDLE_LOCATE_SPEED,true)){
    case 1: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 0); fullStop(); break;
    case 2: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 5); fullStop(); break;
    case 3: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 0); fullStop(); break; 
    case 0: 
       setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
       bool done;
       do  {
       followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
       float distance = readSonarDistance(LEFT_BACK_PIN);
       done = distance < INTERSECTION_DISTANCE_THRESHOLD;
      } while (!done);
       move(10);
      stop();
      turnLeft90(SLOWMO_SPEED);
  }
  
}

//===============================================================
void loop() {
  // put your main code here, to run repeatedly:

}
