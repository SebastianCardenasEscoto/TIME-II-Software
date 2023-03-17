/** 
Writes data to the datalog.txt in the following format:
S (status)
TODO: add temperature and whether the servos turned on or not
*/

#include <SPI.h>
#include <SD.h>

File log_file;

char current_packet[200];
char current_status = '@';

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  while (!SD.begin()) {
    ;
  }

  log_file = SD.open("datalog.txt", FILE_WRITE);
  if (log_file) {
    log_file.println("Writing...");
    log_file.close();
  }
}

void loop() {
  if (Serial.available()) {
    get_valid_packet();
    if (is_valid_packet()) {
      get_status();
      log_file = SD.open("datalog.txt", FILE_WRITE);
      if (log_file) {
        log_file.println(current_status);
        log_file.close();
      }
    }
  }
}

void get_valid_packet() {
  Serial.readStringUntil('\0').toCharArray(current_packet, 200);
}

bool is_valid_packet() {
  bool is_not_empty = (strlen(current_packet) > 0);
  bool has_valid_first = ('@' <= current_packet[0] && current_packet[0] <= 'J');
  return (is_not_empty && has_valid_first);
}

void get_status() {
  current_status = current_packet[0];
}
