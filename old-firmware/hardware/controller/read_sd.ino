/** 
Read from datalog.txt. Gives option to delete at the end.
*/

#include <SPI.h>
#include <SD.h>

File log_file;

void setup() {
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  while (!SD.begin()) {
    ;
  }

  log_file = SD.open("datalog.txt");
  if (log_file) {
    Serial.println("datalog.txt");
     while (log_file.available()) {
      Serial.write(log_file.read());
    }
    log_file.close();
  } else {
    Serial.println("error opening");
  }
  
  Serial.println();
  Serial.println("Delete? Y/N");
}

void loop() {
  if (Serial.available()) {
    int delete_file = Serial.read();
    if (delete_file == 'Y') {
      if (SD.remove("datalog.txt")) {
        Serial.println("Successfully deleted");
      }
    }
  }
}
