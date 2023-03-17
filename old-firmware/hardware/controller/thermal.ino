#define FIVE_VOLTS 972.0
#define HEATER A5;
#define TEMP_SENSOR_1 A0;

float tempOne;


void setup() {
  Serial.begin(115200);
  pinMode(TEMP_SENSOR_1, INPUT);
  pinMode(HEATER, OUTPUT);
  
}

bool atTemp(int pin) {
  // Should change to <= because of schematic
  return (analogRead(pin) >= FIVE_VOLTS / 2.0);
}

void loop() {
  Serial.println(atTemp(TEMP_SENSOR_1));
  if (!atTemp(TEMP_SENSOR_1)) {
    digitalWrite(HEATER, HIGH);
  } else {
    digitalWrite(HEATER, LOW);
  }
}

float readTemp(int pin) {
  return (1.0 / (1.0/298.15 + 1.0/3950.0 * log(1023.0/float(analogRead(pin)) - 1.0)) - 273.15);
}
