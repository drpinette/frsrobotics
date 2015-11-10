#include <Angus_Lib>

void setup() {
   initialize();
    
    // todo: add soundstart
    
    // checking what direction the robot is facing
    int dist = readSonarDistance(RIGHT_FRONT_PIN);
    if (dist < INTERSECTION_DISTANCE_THRESHOLD) {
      //explore left corridor 
      turnLeft90();
      alignLeftWall();
    } 
    
    //robot facing left corridor
    
    if (readProximity()==0) {
      scoot(35);
    }
    if (readProximity()==1) {
      
}

void loop() {
  // put your main code here, to run repeatedly:

}





