// APSSR PSat code 2020
// Header file for the SD card
#include <SPI.h>
#include <SD.h>

// Set the pins used
#define chipSelect 10

File data_file;
char filename[10];

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(13, HIGH);
      delay(100);
      digitalWrite(13, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}

// This line is not needed if you have Adafruit SAMD board package 1.6.2+
//   #define Serial SerialUSB

void SD_setup() {
  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }
  Serial.println("SD Card Initialised");
  

  strcpy(filename, "APSSR00.csv");
  // Renames filename to have sequential numbering
  for (uint8_t i = 0; i < 100; i++) {
    filename[5] = '0' + i/10;
    filename[6] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      Serial.println("Making file: ");
      Serial.println(filename);
      File data_file = SD.open(filename, FILE_WRITE);
      data_file.close();
      return filename;
      break;
    }
  }
}

void SD_write(String to_write, String filename){
  File data_file = SD.open(filename, FILE_WRITE);
  if (data_file) {
    data_file.println(to_write);
    data_file.close();
    // Also print to the serial port
    Serial.println(to_write);
  }
  else {
    Serial.println("Error opening file");
    Serial.println(filename);
  }
}
