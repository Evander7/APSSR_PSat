// APSSR PSat code 2020
// Header file for the SD card

// Includes
#include <SPI.h>
#include <SD.h>

// Set the pins used
#define cardSelect 4
#define SDPin 13

File logfile;

// blink out an error code
void error(uint8_t errno) {
  while(1) {
    uint8_t i;
    for (i=0; i<errno; i++) {
      digitalWrite(SDPin, HIGH);
      delay(100);
      digitalWrite(SDPin, LOW);
      delay(100);
    }
    for (i=errno; i<10; i++) {
      delay(200);
    }
  }
}



void SD_setup() {
  // connect at 115200 so we can read the GPS fast enough and echo without dropping chars
  // also spit it out
  Serial.println("\r\nSD Card started");
  pinMode(SDPin1, OUTPUT);


  // see if the card is present and can be initialized:
  if (!SD.begin(cardSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }
  char filename[15];
  strcpy(filename, "/ANALOG00.TXT");
  for (uint8_t i = 0; i < 100; i++) {
    filename[7] = '0' + i/10;
    filename[8] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      break;
    }
  }

  logfile = SD.open(filename, FILE_WRITE);
  if( ! logfile ) {
    Serial.print("Couldnt create "); 
    Serial.println(filename);
    error(3);
  }
  Serial.print("Writing to "); 
  Serial.println(filename);

  pinMode(SDPin, OUTPUT);
  pinMode(8, OUTPUT);
  Serial.println("Ready!");
}

//uint8_t i=0; dunno what this does, it was just here

void SD_write(String data) {
  digitalWrite(8, HIGH);
  
  logfile.println(data);
  
  digitalWrite(8, LOW);
  
  delay(100);
}
