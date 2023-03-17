void setup() {
  // put your setup code here, to run once:
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);
  for (int i = 0; i < 200; i++) {
    digitalWrite(6, HIGH);
    delayMicroseconds(500);
    digitalWrite(6, LOW);
    delayMicroseconds(500);
    delay(10);
  }
  digitalWrite(7, LOW);
  for (int i = 0; i < 200; i++) {
    digitalWrite(6, HIGH);
    delayMicroseconds(500);
    digitalWrite(6, LOW);
    delayMicroseconds(500);
    delay(10);
  }
}
