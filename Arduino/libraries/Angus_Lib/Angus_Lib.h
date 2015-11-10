#ifndef ARGUS_LIB_H
#define ARGUS_LIB_H

#include <Arduino.h>
#include <Adafruit_MotorShield.h>

#define RIGHT_FRONT_PIN 11
#define RIGHT_BACK_PIN 6
#define LEFT_FRONT_PIN 7
#define LEFT_BACK_PIN 5
#define WHITELINE_PIN 2
#define ODOMETRY_PIN 8
#define EXTINGUISHER_PIN 4

// analog pins
#define UV_LEFT_PIN 0
#define UV_RIGHT_PIN 1
#define FRONT_PROXIMITY_PIN 2

#define WHITELINE_DIR INPUT_PULLUP
#define ODOMETRY_DIR INPUT_PULLUP
#define EXTINGUISHER_DIR OUTPUT

#define LEFT_MOTOR 3
#define RIGHT_MOTOR 4

#define MAX_MOTOR_SPEED 1023
#define DEFAULT_SPEED 1023
#define SLOW_SPEED 511
#define SLOWMO_SPEED 255
#define CANDLE_MOVE_SPEED 255
#define CANDLE_LOCATE_SPEED 127
#define TURN_ADJUST 30 //was 50 then 30 then 50 then 40 then 35

#define CANDLE_ADJUST_PCT 0.75 //was 0.85 then 0.95 then 0.90 then 0.85 then 0.80 
#define UV_THRESH 75 //was 200 then 60 then

#define INTERSECTION_DISTANCE_THRESHOLD 11.0 //was 13.0
#define DEFAULT_NEAR_THRESHOLD 2.0 // prev thres #define DEFAULT_NEAR_THRESHOLD 4.0
#define DEFAULT_FAR_THRESHOLD 4.0 // prev thres #define DEFAULT_FAR_THRESHOLD 6.0
#define FOLLOW_OFFSET 1.0
#define TURN90 31
#define TURN180 64
#define MOVE 5 //was 3 then 

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

bool locateCandle(int speed, bool turnRight);

// Begin Mechanical variables

void extinguish (int onOff) ;

void setMotorSpeed(int leftSpeed, int rightSpeed, int leftDir, int rightDir);

// Begin Movement variables

void move(int distance, int speed = DEFAULT_SPEED) ;

void moveBackwards() ;

bool followLeftWall(float nearDistance, float farDistance) ;

bool followLeftWall2(float nearDistance, float farDistance);

bool followRightWall(float nearDistance, float farDistance) ;

bool followRightWall2(float nearDistance, float farDistance); 

void turnLeft90(int speed) ;

void turnRight90(int speed) ;

void turn180(int speed) ;

void turnLeftUntil(int speed, int distance) ; 

void turnRightUntil(int speed, int distance) ; 

void alignLeftWall() ;

void alignRightWall() ; 

void stop();

void move();

#endif
