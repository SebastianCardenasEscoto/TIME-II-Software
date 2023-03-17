#include <SPI.h>
#include <SD.h>

File myFile;

int temp_sensorPin = A2; // Pin for temp sensor
int heater_pin = 2; // Pin for heater
float tempCelsius;
const int chipSelect = 10;

void setup() {
  Serial.begin(9600); // Serial Initialization at 9600 baud rate
  
  // SD Card Initialization
  if (SD.begin()) {
    Serial.println("SD card is ready to use.");
  } else {
    Serial.println("SD card initialization failed");
    return;
  }

  // Create/Open file 
  myFile = SD.open("data.txt", FILE_WRITE);

  // Reading the file
  /*
  myFile = SD.open("data.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
    Serial.println("Closed");
  }
  else {
    Serial.println("error opening data.txt");
  }*/

}

void loop() {
  float temp = readTemp(); // Get current temp
  int i = 0;
  while (i < 10) {
    // if the file opened okay, write to it:
    if (myFile) {
      Serial.println("Writing to file...");
      // Write to file
      myFile.println(temp);
      // myFile.close(); // close the file
      // Serial.println("Done.");
    }
    // if the file didn't open, print an error:
    else {
      Serial.println("error opening data.txt");
    }
    // digitalWrite(heater_pin, LOW); 
    delay(1000);
    i++;
  }
  myFile.close();
  Serial.println("Done");

  // Reading the file
  myFile = SD.open("data.txt");
  if (myFile) {
    Serial.println("Read:");
    // Reading the whole file
    while (myFile.available()) {
      Serial.write(myFile.read());
    }
    myFile.close();
    Serial.println("Closed");
  }
  else {
    Serial.println("error opening data.txt");
  }

  exit(0);
}

float readTemp() {
  float analogData = analogRead(temp_sensorPin); // Read from A2(temp sensor pin)
  tempCelsius = ((analogData * 4.887586) - 500) * 0.05; // Conversion from analog data to Celsius  // ((analogData/1024.0) * 4876 / 10) - 273.15;
  return tempCelsius; // Printing Celsius temperature to9 serial
}
