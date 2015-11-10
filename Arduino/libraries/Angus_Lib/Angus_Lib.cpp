#include <Angus_Lib.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

// initlize motor 
Adafruit_MotorShield AFMS = Adafruit_MotorShield(); 
Adafruit_DCMotor* leftMotor = AFMS.getMotor(LEFT_MOTOR);
Adafruit_DCMotor* rightMotor = AFMS.getMotor(RIGHT_MOTOR);

// returns 1 if whiteline, else 0
int isWhiteLine() {
    return digitalRead(WHITELINE_PIN);
}

//retuns 1 if white, else 0 
int checkOdometry() {
    return digitalRead(ODOMETRY_PIN);
}

//return distance in units of .1 inches
//sensor is sensor id
float readSonarDistance(int pingPin) {
  //unsigned long duration, inches; //was float distance;
  float duration, inches;
  
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);//was 2
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);
  
  // convert the time into a distance
   // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return duration / 74 / 2;
}

bool readProximity() {
  if (analogRead(FRONT_PROXIMITY_PIN) > 70) return true;  //... > value was 10 then 20 then 15
  else return false;
}

//returns value of uv detector 
int readUv()
{
	return analogRead(UV_LEFT_PIN);
}

//turns extinguisher on if onOff is 1, else turns off if 0
void extinguish (int onOff) {
}

//arr[0] has ambient temperature
//other elememets have temperature readings
// arr[1] is on left
void readThermalArray(int* arr) {
}

//Movement Subroutine

void move(int distance, int speed) {
	setMotorSpeed(speed,speed, FORWARD, FORWARD);
	int prevVal = checkOdometry();
	while (distance > 0){
		int val = checkOdometry();
		if (prevVal != val){
			distance--;
			prevVal = val;
		}
	}
} 

void turnRight90(int speed) { 
	int distance = TURN90;
	setMotorSpeed(speed,speed, FORWARD, BACKWARD);
	int prevVal = checkOdometry();
	while (distance > 0){
		int val = checkOdometry();
		if (prevVal != val){
			distance--;
			prevVal = val;
		}
	}
	setMotorSpeed(speed, speed, BRAKE, BRAKE);
}

void turnLeft90(int speed) { 
	int distance = TURN90;
	setMotorSpeed(speed,speed, BACKWARD, FORWARD);
	int prevVal = checkOdometry();
	while (distance > 0){
		int val = checkOdometry();
		if (prevVal != val){
			distance--;
			prevVal = val;
		}
	}
	setMotorSpeed(speed, speed, BRAKE, BRAKE);
}

void turnLeftUntil(int speed, int distance) { 
	setMotorSpeed(speed,speed, BACKWARD, FORWARD);
	int prevVal = checkOdometry();
	while (distance > 0){
		int val = checkOdometry();
		if (prevVal != val){
			distance--;
			prevVal = val;
		}
	}
}

void turnRightUntil(int speed, int distance) { 
	setMotorSpeed(speed,speed, FORWARD, BACKWARD);
	int prevVal = checkOdometry();
	while (distance > 0){
		int val = checkOdometry();
		if (prevVal != val){
			distance--;
			prevVal = val;
		}
	}
}

void turn180(int speed) { 
	int distance = TURN180;
	setMotorSpeed(speed,speed, BACKWARD, FORWARD);
	int prevVal = checkOdometry();
	while (distance > 0){
		int val = checkOdometry();
		if (prevVal != val){
			distance--;
			prevVal = val;
		}
	}
	setMotorSpeed(speed, speed, BRAKE, BRAKE);
}


bool followLeftWall(float nearDistance, float farDistance) {
	float backDist = readSonarDistance(LEFT_BACK_PIN);
	if (backDist > INTERSECTION_DISTANCE_THRESHOLD) return 1;
	float frontDist = readSonarDistance(LEFT_FRONT_PIN);
	float distance = (backDist + frontDist) / 2;
    if (backDist > frontDist ) {
         setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED-TURN_ADJUST,
				FORWARD, FORWARD);
    }
    else if (backDist < frontDist ){
        setMotorSpeed(DEFAULT_SPEED-TURN_ADJUST, DEFAULT_SPEED,
                FORWARD, FORWARD);
    }
    else {
        setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED,
                FORWARD, FORWARD);
    } 
	return backDist < INTERSECTION_DISTANCE_THRESHOLD;
}
/*
bool followLeftWall2(float nearDistance, float farDistance){
    float backDist = readSonarDistance(LEFT_BACK_PIN); 
    if (backDist > INTERSECTION_DISTANCE_THRESHOLD) return false;
    float frontDist = readSonarDistance(LEFT_FRONT_PIN); 
    float distance = (backDist + frontDist) / 2;
	float offset;
	if (distance < nearDistance) offset = FOLLOW_OFFSET;
	else if (distance > farDistance) offset = 0;
	else offset = 1-(distance-nearDistance)/(farDistance-nearDistance);
	}
	/*
	Serial.print("frontDist "); Serial.print(frontDist); Serial.print("\n");
	Serial.print("backDist "); Serial.print(backDist); Serial.print("\n");
	Serial.print("offset "); Serial.print(offset); Serial.print("\n");
	Serial.print("nearDistance "); Serial.print(nearDistance); Serial.print("\n");
	Serial.print("farDistance "); Serial.print(farDistance); Serial.print("\n\n");
	/
    if ((backDist - frontDist) > offset ) {
         setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED-TURN_ADJUST,
				FORWARD, FORWARD);
    }
    else if ((backDist - frontDist)< -offset ){
        setMotorSpeed(DEFAULT_SPEED-TURN_ADJUST, DEFAULT_SPEED,
                FORWARD, FORWARD);
    }
    else {
        setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED,
                FORWARD, FORWARD);
    }
	return true;
}
*/

bool followRightWall(float nearDistance, float farDistance){
    float frontDist = readSonarDistance(RIGHT_FRONT_PIN); 
    if (frontDist > INTERSECTION_DISTANCE_THRESHOLD) return 1;
    float backDist = readSonarDistance(RIGHT_BACK_PIN); 
    float distance = (frontDist + backDist) / 2;
    if (frontDist > backDist ) {
         setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED-TURN_ADJUST,
				FORWARD, FORWARD);
    }
    else if (frontDist < backDist ){
        setMotorSpeed(DEFAULT_SPEED-TURN_ADJUST, DEFAULT_SPEED,
                FORWARD, FORWARD);
    }
    else {
        setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED,
                FORWARD, FORWARD);
    } 
	return frontDist < INTERSECTION_DISTANCE_THRESHOLD;
}

bool followRightWall2(float nearDistance, float farDistance){
    float frontDist = readSonarDistance(RIGHT_FRONT_PIN); 
    if (frontDist > INTERSECTION_DISTANCE_THRESHOLD) return true;
    float backDist = readSonarDistance(RIGHT_BACK_PIN); 
    float distance = (frontDist + backDist) / 2;
	float offset;
	if (distance < nearDistance) offset = FOLLOW_OFFSET;
	else if (distance > farDistance) offset = 0;
	else offset = 1-(distance-nearDistance)/(farDistance-nearDistance);
	

	Serial.print("frontDist "); Serial.print(frontDist); Serial.print("\n");
	Serial.print("backDist "); Serial.print(backDist); Serial.print("\n");
	Serial.print("offset "); Serial.print(offset); Serial.print("\n");
//	Serial.print("nearDistance "); Serial.print(nearDistance); Serial.print("\n");
//	Serial.print("farDistance "); Serial.print(farDistance); Serial.print("\n\n");
	
	
    if ((frontDist - backDist) > offset ) {
		Serial.print("Right_Turn "); Serial.print(frontDist-backDist); Serial.print("\n");
         setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED-TURN_ADJUST,
				FORWARD, FORWARD);
    }
    else if ((frontDist - backDist)< offset ){ 
	   Serial.print("Left_Turn "); Serial.print(frontDist-backDist); Serial.print("\n");
		setMotorSpeed(DEFAULT_SPEED-TURN_ADJUST, DEFAULT_SPEED,
                FORWARD, FORWARD);
    }
    else {
	   Serial.print("No_Turn "); Serial.print(frontDist-backDist); Serial.print("\n");
        setMotorSpeed(DEFAULT_SPEED, DEFAULT_SPEED,
                FORWARD, FORWARD);
    }
	
	return false;
}



void stop() {
 setMotorSpeed(0,0, BRAKE, BRAKE);
 //delay(100); nts: removed for test only
}


void initialize() {
 //initialize
    pinMode(WHITELINE_PIN, WHITELINE_DIR);
    pinMode(ODOMETRY_PIN, ODOMETRY_DIR);
    pinMode(EXTINGUISHER_PIN, EXTINGUISHER_DIR);
//	pinMode(FRONT_PROXIMITY_PIN, FRONT_PROXIMITY_DIR);
    AFMS.begin();  // create with the default frequency 1.6KHz
}




void setMotorSpeed(int leftSpeed, int rightSpeed, int leftDir, int rightDir) {
	  //Serial.print(leftSpeed); Serial.print(" "); Serial.print (rightSpeed); Serial.print("\n\n");
      leftMotor->setSpeed(leftSpeed);
      leftMotor->run(leftDir);
      rightMotor->setSpeed(rightSpeed);
      rightMotor->run(rightDir);
}

/* Begin "Basement"

void alignLeftWall() {
}

void alignRightWall() {
}

void alignBothWalls() {
}

void moveBackwards(int distance){
}
End "Basement"*/

void moveToCandle(int speed, int maxDistance) {
	int prevVal = checkOdometry();
	while (maxDistance > 0) {
		// Serial.print("proximity ");Serial.println(readProximity());
		if (readProximity()) break;
		// Serial.print("Check_Odometry ");Serial.println(maxDistance);
		int val = checkOdometry();
		if (prevVal != val){
			maxDistance--;
			prevVal = val;
		}
		int left = analogRead(UV_LEFT_PIN);
		int right = analogRead(UV_RIGHT_PIN);
		int rightSpeed = speed;
		int leftSpeed = speed;
		if (left > right) {
			leftSpeed *= CANDLE_ADJUST_PCT;
		}
		else if (right > left) {
			rightSpeed *= CANDLE_ADJUST_PCT;
		}
		// Serial.println("Setting Speed");
		setMotorSpeed(leftSpeed,rightSpeed,FORWARD,FORWARD);
		delay(5);
	}
	// Serial.println("Fullstop Stop");
	stop();
}

bool locateCandle(int speed, bool turnRight) {
	int found = 0;
	int distance = TURN90;
	int maxVal = 0;
	int angleAtMaxVal;
	if (turnRight) {
		setMotorSpeed(speed,speed, FORWARD, BACKWARD);
	}
	else{
		setMotorSpeed(speed,speed, BACKWARD, FORWARD);
	}
	int prevVal = checkOdometry();
	while (distance > 0){
		if(turnRight) {
			int val = analogRead(UV_RIGHT_PIN);
			if(val > maxVal){ 
				maxVal = val;
				angleAtMaxVal = distance;
			}
		}
		else {
			int val = analogRead(UV_LEFT_PIN);
			if(val > maxVal){ 
				maxVal = val;
				angleAtMaxVal = distance;
			}
		}
		int val = checkOdometry();
		if (prevVal != val){
			distance--;
			prevVal = val;
		}
	}
	if (maxVal < UV_THRESH) {
		if (turnRight) turnRight90(speed);
		else turnLeft90(speed);
		return false;
	}
	stop();
	//reverse direction
	if (turnRight) {
		turnLeftUntil(speed,angleAtMaxVal);
	}
	else{
		turnRightUntil(speed,angleAtMaxVal);
	}
	// put candle in middle of sensors
	while (true) {
		if(turnRight) {
			Serial.print("turnRight ");Serial.print(analogRead(UV_LEFT_PIN));Serial.print(" ");Serial.println(analogRead(UV_RIGHT_PIN));
			if (analogRead(UV_RIGHT_PIN)>= analogRead(UV_LEFT_PIN)) {
				break;
			}
		}
		else {
			Serial.print("turnLeft ");Serial.print(analogRead(UV_LEFT_PIN));Serial.print(" ");Serial.println(analogRead(UV_RIGHT_PIN));
			if (analogRead(UV_LEFT_PIN)>= analogRead(UV_RIGHT_PIN)) {
				break;
			}
		}
	}
	stop();
	return true;
}

void startLedShow() {
	digitalWrite(13,HIGH);
	delay(100);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(100);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(100);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(200);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(200);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(200);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(100);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(100);
	digitalWrite(13,LOW);
	delay(150);
	digitalWrite(13,HIGH);
	delay(100);
	digitalWrite(13,LOW);
}