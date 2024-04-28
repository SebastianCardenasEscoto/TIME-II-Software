#include <SPI.h>
#include <SD.h>

#define H_TOP_RIGHT 3
#define H_TOP_LEFT 6
#define H_BOTTOM_RIGHT 5
#define H_BOTTOM_LEFT 11
#define H_SMALL_PLATE 10
#define T_TOP_RIGHT A1
#define T_TOP_LEFT A2
#define T_BOTTOM_RIGHT A3
#define T_BOTTOM_LEFT A4
#define T_SMALL_PLATE A5

#define CRITICAL_TEMP 30
#define HIGH_TEMP 35


int active_heater = -1;
float min_temp = 0;

enum heater_pin_mappings {
	H_TOP_RIGHT,
	H_TOP_LEFT,
	H_BOTTOM_RIGHT,
	H_BOTTOM_LEFT ,
	H_SMALL_PLATE 
}
enum thermistor_pin_mappings {
	T_TOP_RIGHT,
	T_TOP_LEFT,
	T_BOTTOM_RIGHT,
	T_BOTTOM_LEFT ,
	T_SMALL_PLATE 
}

void setup() {
  Serial.begin(9600); // Serial Initialization at 9600 baud rate

}

void loop() {
  for(int i = 0; i < 5; i++) {
		float temp = readTemp(thermistor_pin_mappings[i]); // Get current temp
		if (temp < min_temp) {
			active_heater = i;
			temp = min_temp;
		}
	}
	if(min_temp < HIGH_TEMP) {
		digitalWrite(heater_pin_mappings[i], HIGH);
	}
	delay(100);
	digitalWrite(heater_pin_mappings[i], LOW);
}

float readTemp(int pin) {
  float analogData = analogRead(pin); // Read from A2(temp sensor pin)
  tempCelsius = ((analogData * 4.887586) - 500) * 0.05; // Conversion from analog data to Celsius  // ((analogData/1024.0) * 4876 / 10) - 273.15;
  return tempCelsius; // Printing Celsius temperature to9 serial
}
