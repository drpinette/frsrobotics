#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize();
  Serial.begin(9600);
  
}

bool done = false;

void loop() {
  // put your main code here, to run repeatedly:
  
  if (!done && !followLeftWall2(DEFAULT_FAR_THRESHOLD,DEFAULT_NEAR_THRESHOLD)){
   done = true;
   setMotorSpeed(0,0, BRAKE, BRAKE);
  }
  delay(25);
  
}
