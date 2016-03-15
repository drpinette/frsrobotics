#ifndef ARGUS_LIB_H
#define ARGUS_LIB_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>

#define RIGHT_FRONT_PIN 11
#define FRONT_PROXIMITY_PIN 10
#define RIGHT_BACK_PIN 6
#define LEFT_FRONT_PIN 7
#define LEFT_BACK_PIN 5
#define WHITELINE_PIN 2
#define ODOMETRY_PIN 8
#define EXTINGUISHER_PIN 4

// analog pins
#define UV_LEFT_PIN 0
#define UV_RIGHT_PIN 1
//#define FRONT_PROXIMITY_PIN 2

#define WHITELINE_DIR INPUT_PULLUP
#define ODOMETRY_DIR INPUT_PULLUP
#define EXTINGUISHER_DIR OUTPUT

#define LEFT_MOTOR 3
#define RIGHT_MOTOR 4

#define MAX_MOTOR_SPEED 255
#define DEFAULT_SPEED 255
#define SLOW_SPEED 127
#define SLOWMO_SPEED 63
#define CANDLE_MOVE_SPEED 255
#define ROOM_ENTER_SPEED 150
#define CANDLE_LOCATE_SPEED 127
#define TURN_ALIGN_SPEED 100
#define EDGE_DETECT_SPEED 110
#define TURN_SPEED 150
#define TURN_ADJUST 30 //was 50 then 30 then 50 then 40 then 35

#define CANDLE_ADJUST_PCT 0.75 //was 0.85 then 0.95 then 0.90 then 0.85 then 0.80 
#define UV_THRESH 65 //was 200 then 60 then

#define INTERSECTION_DISTANCE_THRESHOLD 11.0 
#define LEAVING_INTERSECTION_DISTANCE_THRESHOLD 6.0 
#define DEFAULT_NEAR_THRESHOLD 2.0 // prev thres #define DEFAULT_NEAR_THRESHOLD 4.0
#define DEFAULT_FAR_THRESHOLD 4.0 // prev thres #define DEFAULT_FAR_THRESHOLD 6.0
#define FOLLOW_OFFSET 1.0
#define TURN45 15
#define TURN90 31
#define TURN180 63
#define MOVE 5 //was 3 then 

#define NO_CANDLE 0
#define STRAIGHT_AHEAD 1
#define KIDDIE_CORNER 2
#define TO_SIDE 3

// Code Starter
void initialize() ;
void startLedShow() ;

// Sensors/Detectors variables
int isWhiteLine() ;

int checkOdometry() ;

void readThermalArray(int* arr) ;

float readSonarDistance(int pingPin) ;

bool readProximity() ;

int readUv() ;

void moveToCandle(int speed, int maxDistance);

int locateCandle(int speed, bool turnRight);

// Begin Mechanical variables

void extinguish (int onOff) ;

void setMotorSpeed(int leftSpeed, int rightSpeed, int leftDir, int rightDir);

// Begin Movement variables

void move(int distance, int speed = DEFAULT_SPEED) ;

bool moveUntilProximity(int distance, int speed=DEFAULT_SPEED);

void moveBackwards() ;

bool followLeftWall(float nearDistance, float farDistance) ;

bool followLeftWall2(float nearDistance, float farDistance, int speed=DEFAULT_SPEED, float threshold=INTERSECTION_DISTANCE_THRESHOLD);

bool followRightWall(float nearDistance, float farDistance) ;

bool followRightWall2(float nearDistance, float farDistance, int speed=DEFAULT_SPEED, float threshold=INTERSECTION_DISTANCE_THRESHOLD); 

void turnLeft45(int speed = TURN_SPEED) ;

void turnRight45(int speed = TURN_SPEED) ;

void turnLeft90(int speed = TURN_SPEED) ;

void turnLeft90AlignLeft(int speed=TURN_ALIGN_SPEED) ;

void turnLeft90AlignRight(int speed=TURN_ALIGN_SPEED) ;

void turnRight90(int speed = TURN_SPEED) ;

void turnRight90AlignLeft(int speed=TURN_ALIGN_SPEED) ;

void turn180(int speed = TURN_SPEED) ;

void turn180AlignRight(int speed=TURN_ALIGN_SPEED) ;

void turnLeftUntil(int distance, int speed = TURN_SPEED) ; 

void turnRightUntil(int distance, int speed = TURN_SPEED) ; 

void alignLeftWall() ;

void alignRightWall() ; 

void stop(int pause=100); 

void fullStop();

void move();

#endif
