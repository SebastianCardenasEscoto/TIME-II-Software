/*  MP6500 Motor Driver
 *  Adjust to fit servo
*/


//Motor driver pins - assign later
const int STEP; //step input
const int DIR; //direction input
const int nSLEEP; //sleep mode input

void setup() {
  pinMode(STEP, INPUT);
  pinMode(DIR, INPUT);
  pinMode(nSLEEP, INPUT);
}

void loop(){
}

void activateMotor(){
  digitalWrite(nSLEEP, HIGH);
  for (int i = 0; i < distance; i++) {
    digitalWrite(STEP, HIGH);
    delay(500);
    digitalWrite(STEP, LOW);
    delay(500);
  }
}

