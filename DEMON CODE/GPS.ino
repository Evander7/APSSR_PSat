// APSSR PSat code 2020
// Header file for the GPS sensor

// what's the name of the hardware serial port?
#define GPSSerial Serial1

void GPS_setup() {
  //Connect to GPS module
  // 9600 baud is the default rate for the Ultimate GPS
  GPSSerial.begin(9600);
}

// Reads from the GPS module, returns string containing GPS coords and other yummies
// Maybe it's worth parsing the data and extracting useful info in here?
// YO maybe this just reads character by characters... Might have to read a certain amount of characters into a string then return that
// I wonder 
//void GPS_read(){}
String GPS_read(){
  char c;
  String GPS_string = "";
  bool sentence_end = false;
  for (int i=0; i<15; i++){
    // Start reading
    if (GPSSerial.available()) {
      char c = GPSSerial.read();     
      if (String(c) == "$"){
        //If you read the start of the GPS string ("$"), start reading
        Serial.println("dollas");
        while(!sentence_end){
          // Define the sentence end by another "$"
          if (GPSSerial.available()){
            // Read nonstop until encounter a "$"
            char c = GPSSerial.read();
            if (String(c) =="$"){
              // if the GPS string ends
              sentence_end = true;
            }
            GPS_string += String(c);
            Serial.print(c);
          }
        }
        }
      Serial.print(c);
    }
  }
}
