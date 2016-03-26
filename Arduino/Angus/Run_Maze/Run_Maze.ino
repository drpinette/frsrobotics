#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>



void setup() {
  pinMode(A5, INPUT);
  void runRoom1DoorA();
  void runRoom1DoorB();
  void runRoom2();
  void runRoom3();
  void runRoom4a();
  void runRoom4b();
  void runRoom4c();
  // put your setup code here, to run once:
  Serial.begin(57600);
  initialize();
  waitForPushButton();
  delay(1000);
  
  bool done;
  float distance3 = readSonarDistance(RIGHT_FRONT_PIN);
  if (distance3 > INTERSECTION_DISTANCE_THRESHOLD) {
    fullStop();
  }
  else{
    //turnLeft90(DEFAULT_SPEED);
    turnLeft90AlignLeft(DEFAULT_SPEED);
    
  }
 
  
  //explore the side
  //bool foundDog = moveUntilProximity(40);
  bool foundDog = readProximity();
  bool foundDoor = false;
  if (!foundDog) {
    // move out of intersection
    do {
      followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, DEFAULT_SPEED);
      float frontDistance = readSonarDistance(RIGHT_FRONT_PIN);
      done = frontDistance < INTERSECTION_DISTANCE_THRESHOLD;
    } while(!done);
    stop();
    if (readProximity()) {
      foundDog = true;
    }
    else {
      turnRightUntil(2);
      if (readProximity()) {
        foundDog = true;
      }
      else {
         turnLeftUntil(4);
         if (readProximity()) {
            foundDog = true;
         }
         else {
           turnRightUntil(2);
           foundDog = false;
         }
      }
    } 
    if (foundDog) { 
      turn180();
      move(15);
      stop();
      turnLeft90();
    }
    else{
    // look for door
      move(80);
      float frontDistance = readSonarDistance(RIGHT_FRONT_PIN);
      foundDoor = frontDistance > ROOM4_SIDE_CORRIDER_DISTANCE_THRESHOLD;
      if (foundDoor) {
        do {
          float rearDistance = readSonarDistance(RIGHT_BACK_PIN);
          done = rearDistance > ROOM4_SIDE_CORRIDER_DISTANCE_THRESHOLD;
        } while(!done);
        runRoom4c();
      }
      else{
        stop();
        turn180AlignRight(); 
        do {
           followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, DEFAULT_SPEED);
           float distance = readSonarDistance(LEFT_BACK_PIN);
           done = distance >  ROOM4_SIDE_CORRIDER_DISTANCE_THRESHOLD;  
           } while (!done);
           move(10);
         turnLeft90AlignRight();
      }
      do  {
          followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
          float distance = readSonarDistance(LEFT_BACK_PIN);
          done = distance < INTERSECTION_DISTANCE_THRESHOLD;
      } while (!done);  
      do  {
          followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
          float distance = readSonarDistance(LEFT_BACK_PIN);
          done = distance > INTERSECTION_DISTANCE_THRESHOLD;
      } while (!done);  
      move(10);
      turnLeft90AlignRight(); 
    }
  }
  else{
    turnRight90();
  }
  
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
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
  
  //move front out of intersection
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(RIGHT_FRONT_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
 
  //move rear out of intersection
  setMotorSpeed(EDGE_DETECT_SPEED,EDGE_DETECT_SPEED,FORWARD,FORWARD);
  bool isDoorA = false;
  do  {
   float backDistance = readSonarDistance(LEFT_BACK_PIN);
   done = backDistance < INTERSECTION_DISTANCE_THRESHOLD;
   float frontDistance = readSonarDistance(LEFT_FRONT_PIN);
   isDoorA |= frontDistance > INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  //digitalWrite(13,LOW); //debug, remove for actual competition
  
  //Check Room 1 Door A
 
  move(23);
  
  if (isDoorA){
    runRoom1DoorA();
    do {
        followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, DEFAULT_SPEED);
        float distance = readSonarDistance(RIGHT_BACK_PIN);
        done = distance >  INTERSECTION_DISTANCE_THRESHOLD;  
    } while (!done);
    move(17);
    stop();
    turnRight90AlignLeft();
  }
  else {
     do {
        done = followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, DEFAULT_SPEED);
     } while (!done);
     setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
     do {
        float distance = readSonarDistance(LEFT_BACK_PIN);
        done = distance >  INTERSECTION_DISTANCE_THRESHOLD;  
    } while (!done);
    runRoom1DoorB();
  }
  
   runRoom2(); 

  turnLeft90();
  
  //move past wall on right if any
  if (isDoorA) { 
    do {
       done = followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, DEFAULT_SPEED);
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
   done = followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, DEFAULT_SPEED); 
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
  turnLeft90();
  
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
   done = followRightWall2(DEFAULT_NEAR_THRESHOLD/2,DEFAULT_FAR_THRESHOLD/2);  
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
  move(10);
  if (readSonarDistance(LEFT_FRONT_PIN) > INTERSECTION_DISTANCE_THRESHOLD) {
    stop();
    runRoom4a();
  }  
 
 //move past room 4 
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
  
  turnLeft90AlignRight();
  
  //moving into room 4 doorway
  do {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, EDGE_DETECT_SPEED,15.0);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance <  LEAVING_INTERSECTION_DISTANCE_THRESHOLD;  
  } while (!done);
  //digitalWrite(13,HIGH); //debug, remove for actual competition
  
  move(10);
  
  runRoom4b(); 
  
  fullStop();
}

//Room Subroutines

void runRoom1DoorA() {
  // move- into doorway
  move(15,DEFAULT_SPEED);
  // entering room
  
  //Experiment with new parameter numTicks
  turnLeft90(150, 42);
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  bool done;
  do  {
   float distance = readSonarDistance(RIGHT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  move(15, DEFAULT_SPEED);
  //Look for candle
  stop();
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
  }
}

void runRoom1DoorB() {
  fullStop();
  // move into doorway
  move(23, DEFAULT_SPEED);
  // entering room
  stop();
  turnLeft90AlignRight();
  bool done;
  do  {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_FRONT_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  do  {
   followRightWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD);
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  move(15, DEFAULT_SPEED);
  //Look for candle
  stop();
  switch (locateCandle(CANDLE_LOCATE_SPEED,false)){
    case 1: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED,130); fullStop(); break;
    case 2: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED,0); fullStop(); break;
    case 3: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 72); fullStop(); break; 
    case 0: setMotorSpeed(100,100,FORWARD,FORWARD);
        do  {
           followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, EDGE_DETECT_SPEED);
           float distance = readSonarDistance(RIGHT_BACK_PIN);done = distance < INTERSECTION_DISTANCE_THRESHOLD;
           //Include variable to count odometry
        } while (!done);
        move (14);     
  }
}

void runRoom2(){
  //Move into room 2
  setMotorSpeed(100,100,FORWARD,FORWARD);
  bool done;
  /*do  {
   followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, EDGE_DETECT_SPEED);
   float distance = readSonarDistance(RIGHT_FRONT_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  delay(5);*/
  do  {
   followLeftWall2(DEFAULT_NEAR_THRESHOLD,DEFAULT_FAR_THRESHOLD, EDGE_DETECT_SPEED);
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
       move(13);
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
       move(30);
      stop();
      turnLeft90();
  }
  
}

void runRoom4a() {
  //move into room 4
  move(10);
  stop();
  turnLeft90();
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
    case 0: fullStop();  break; 
  }
  
}

void runRoom4b() {
  //move into room 4
  move(10);
  stop();
  turnLeft90();
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
    case 0: fullStop();  break; 
  }
}

void runRoom4c() {
  //move into room 4
  move(10);
  stop();
  turnRight90();
  bool done;
  setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
  do  {
   float distance = readSonarDistance(LEFT_BACK_PIN);
   done = distance < INTERSECTION_DISTANCE_THRESHOLD;
  } while (!done);
  move(15, DEFAULT_SPEED);
  //Look for candle
  stop();
  //look for candle
  switch (locateCandle(CANDLE_LOCATE_SPEED,true)){
    case 1: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 0); fullStop(); break;
    case 2: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 5); fullStop(); break;
    case 3: digitalWrite(13,HIGH); moveToCandle(CANDLE_MOVE_SPEED, 0); fullStop(); break;
    case 0: break; }
      setMotorSpeed(DEFAULT_SPEED,DEFAULT_SPEED,FORWARD,FORWARD);
      do  {
         float distance = readSonarDistance(RIGHT_BACK_PIN);
         done = distance > INTERSECTION_DISTANCE_THRESHOLD;
      }while (!done);
     
       move (15);
       turnLeft90AlignRight();
}



//===============================================================
void loop() {
  // put your main code here, to run repeatedly:

}
