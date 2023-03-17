#include <SPI.h>
#include <SD.h>
#include "definitions.h"

#define NONE '@'
#define LIFTOFF 'A'
#define MECO 'B '
#define SEPARATION 'C'
#define COAST_START 'D'
#define APOGEE 'E'
#define COAST_END 'F'
#define UNDERCHUTES 'G'
#define LANDING 'H'
#define SAFING 'I'
#define FINISHED 'J'
#define ALTITUDE 3
#define MICRO_WARN 17
#define FIVE_VOLTS 972.0
#define HEATER A5;
#define TEMP_SENSOR_1 A0;

typedef enum {
    PREFLIGHT,
    MICROG,
    POSTFLIGHT
} STATES;

char current_packet[200];

File log_file;
/**Motor pins */
const int STEP; //step input
const int DIR; //direction input
const int nSLEEP; //sleep mode input

//TODO
//Create generic function that will work with any motor type
void run_motors(void) {}

String extract_data(int num) {
    char delim = ',';
    String data = "";
    for (size_t i = 0; i < 200; i++) {
        if (num == 0) {
            size_t j = i;
            char curr = current_packet[j];
            while (curr != delim) {
                data.concat(curr);
                j++;
                curr = current_packet[j];
            }
            break;
        } else if (current_packet[i] == delim)
            num--;
    }
    return data;
}

bool temp_reg(void) {
    // Should change to <= because of schematic
    bool state_ok = (analogRead(TEMP_SENSOR_1) >= FIVE_VOLTS / 2.0);
    if (!state_ok) 
    digitalWrite(HEATER, HIGH);
    else 
    digitalWrite(HEATER, LOW);
}


float read_temp(void) {
  return (1.0 / (1.0/298.15 + 1.0/3950.0 * log(1023.0/float(analogRead(TEMP_SENSOR_1)) - 1.0)) - 273.15);
}


void read_packet(void) {
    if (Serial.available()) {
        Serial.readStringUntil('\0').toCharArray(current_packet, 200);
    } 
}


void setup_sd(void) {
    while (!SD.begin()) {}
    log_file = SD.open("datalog.txt", FILE_WRITE);
     if (log_file) {
    log_file.println("FILE OK!!\n");
    log_file.close();
  }
}


void write_sd(char* packet) {
    if (!new_data)
        return;
    log_file = SD.open("datalog.txt", FILE_WRITE);
      if (log_file) {
        
        log_file.write(packet, 200);
        log_file.print("temperature,");
        log_file.println(read_temp());
        log_file.print("gravity");
        log_file.println(calc_g(extract_data(ALTITUDE)));
        log_file.close();
      }
      Serial.println("Writing...");
      Serial.println(packet, 200);
      Serial.println(read_temp());
}

void motor_setup(int STEP, int DIR, int nSLEEP) {
  pinMode(STEP, INPUT);
  pinMode(DIR, INPUT);
  pinMode(nSLEEP, INPUT);
}


void setup(void) {
    Serial.begin(115200);
    STATES flight_status = PREFLIGHT;
    setup_sd();
    //Thermal Setup
    pinMode(TEMP_SENSOR_1, INPUT);
    pinMode(HEATER, OUTPUT);


}

void loop(void) {
    switch(flight_status) {
        case PREFLIGHT:
            Serial.println("In PREFLIGHT!");
            read_packet()
            temp_reg();
            write_sd(current_packet);
            /*if (current_packet[0] == COAST_START)
                flight_status = MICROG;
                Moving experiment to warning stage.*/
            if (extract_data(MICRO_WARN))
                flight_status = MICROG;
        break;

        case MICROG:
            Serial.println("In MICROG!");
            read_packet()
            temp_reg();
            write_sd(current_packet);
            if (current_packet[0] == COAST_END)
                flight_status = MICROG;
        break;

        case POSTFLIGHT:
            Serial.println("In POSTFLIGHT!");
            read_packet()
            temp_reg();
            write_sd(current_packet);
        break;
    }
}