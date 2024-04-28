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

enum heater_enum {
    HEATER_TOP_RIGHT,
    HEATER_TOP_LEFT,
    HEATER_BOTTOM_RIGHT,
    HEATER_BOTTOM_LEFT,
    HEATER_SMALL_PLATE
};
enum thermistor_enum {
    THERMISTOR_TOP_RIGHT,
    THERMISTOR_TOP_LEFT,
    THERMISTOR_BOTTOM_RIGHT,
    THERMISTOR_BOTTOM_LEFT,
    THERMISTOR_SMALL_PLATE
};

thermistor_enum getThermistorPin(int i) {
    switch(i) {
        case 0:
            return THERMISTOR_TOP_RIGHT;
        case 1:
            return THERMISTOR_TOP_LEFT;
        case 2:
            return THERMISTOR_BOTTOM_RIGHT;
        case 3:
            return THERMISTOR_BOTTOM_LEFT;
        case 4:
            return THERMISTOR_SMALL_PLATE;
        default:
            return THERMISTOR_TOP_RIGHT; // Default to THERMISTOR_TOP_RIGHT
    }
}

heater_enum getHeaterPin(int i) {
    switch(i) {
        case 0:
            return HEATER_TOP_RIGHT;
        case 1:
            return HEATER_TOP_LEFT;
        case 2:
            return HEATER_BOTTOM_RIGHT;
        case 3:
            return HEATER_BOTTOM_LEFT;
        case 4:
            return HEATER_SMALL_PLATE;
        default:
            return HEATER_TOP_RIGHT; // Default to HEATER_TOP_RIGHT
    }
}

void setup() {
    Serial.begin(9600); // Serial Initialization at 9600 baud rate
}

void loop() {
    for(int i = 0; i < 5; i++) {
        float temp = readTemp(getThermistorPin(i)); // Get current temp
        if (temp < min_temp) {
            active_heater = i;
            min_temp = temp; // Corrected variable name
        }
    }
    if(min_temp < HIGH_TEMP) {
        digitalWrite(getHeaterPin(active_heater), HIGH); // Corrected function usage
    }
    delay(100);
    digitalWrite(getHeaterPin(active_heater), LOW); // Corrected function usage
}

float readTemp(thermistor_enum pin) { // Corrected function parameter type
    float analogData = analogRead(pin); // Read from thermistor pin
    float tempCelsius = ((analogData * 4.887586) - 500) * 0.05; // Conversion from analog data to Celsius
    return tempCelsius; // Return Celsius temperature
}
