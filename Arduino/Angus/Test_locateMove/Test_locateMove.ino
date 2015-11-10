#include <Adafruit_MotorShield.h>
#include <Wire.h>
#include <Angus_Lib.h>

void setup() {
  // put your setup code here, to run once:
  initialize();
  digitalWrite(13,HIGH);
  delay(1000);
  digitalWrite(13,LOW);
  delay(2000); 
  Serial.begin(9600);
  locateCandle(CANDLE_LOCATE_SPEED, true);
  digitalWrite(13,HIGH);
//  delay(1000);
//  digitalWrite(13,LOW);
//  delay(1000);
  moveToCandle(CANDLE_MOVE_SPEED, 10000);
}

void loop() {
  // put your main code here, to run repeatedly:

}
