#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  //initialize();
  Serial.begin(9600);
}
bool ok = false;
void loop() {
  if (!ok) {
    move (12);
    stop();
    ok = checkForDog(4);
  }
  
}
