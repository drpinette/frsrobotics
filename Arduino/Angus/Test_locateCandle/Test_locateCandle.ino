#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize(); 
  Serial.begin(9600);
  delay(3000);
  locateCandle(CANDLE_LOCATE_SPEED, true);
}

void loop() {
  // put your main code here, to run repeatedly:
  
}
