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

void setup() {
  Serial.begin(9600);
  while(!Serial){;}
//  Serial.println("\r\nAnalog logger test");
//  pinMode(13, OUTPUT);


  // see if the card is present and can be initialized:
  if (!SD.begin(chipSelect)) {
    Serial.println("Card init. failed!");
    error(2);
  }
  Serial.println("SD Card Initialised");
  

  strcpy(filename, "test00.txt");
  // Renames filename to have sequential numbering
  for (uint8_t i = 0; i < 100; i++) {
    filename[4] = '0' + i/10;
    filename[5] = '0' + i%10;
    // create if does not exist, do not open existing, write, sync after write
    if (! SD.exists(filename)) {
      Serial.println("Making file: ");
      Serial.println(filename);
      File data_file = SD.open(filename, FILE_WRITE);
      data_file.close();
      break;
    }
  }
//
//  logfile = SD.open(filename, FILE_WRITE);
//  if( ! logfile ) {
//    Serial.print("Couldnt create "); 
//    Serial.println(filename);
//    error(3);
//  }
//  Serial.print("Writing to "); 
//  Serial.println(filename);
//
//  pinMode(13, OUTPUT);
//  pinMode(8, OUTPUT);
//  Serial.println("Ready!");
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


uint8_t i=0;
int a = 0;
String test_string = "";
void loop() {
  test_string = "testing";

  SD_write(test_string, filename);
  SD_write(String(a),filename);
  a+= 1;


  
//  digitalWrite(8, HIGH);
//  logfile.print("A0 = "); logfile.println(analogRead(0));
//  //logfile.flush(); will draw three times as much power if added well need to cheak our budget
//  Serial.print("A0 = "); Serial.println(analogRead(0));
//  digitalWrite(8, LOW);
  
  delay(100);
}
