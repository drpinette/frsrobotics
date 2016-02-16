#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  //Serial.begin(57600);
  initialize();
  delay(5000);
  
  //Serial.println(CANDLE_LOCATE_SPEED);
  turnLeft90AlignRight(CANDLE_LOCATE_SPEED);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
