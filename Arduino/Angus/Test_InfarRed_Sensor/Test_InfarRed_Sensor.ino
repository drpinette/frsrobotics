

void setup() {
  // put your setup code here, to run once:
  Serial.begin(57600);
  pinMode(A5, INPUT);
  pinMode(13, OUTPUT);
}

void loop() {
  delay(10);
  bool on = digitalRead(A5);
  digitalWrite(13, on);
  Serial.println(digitalRead(A5));
}
