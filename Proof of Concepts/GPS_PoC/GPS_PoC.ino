// Proof of Concept
// Arduino feather GPS code
// For PSat 2020

// Test code for Ultimate GPS Using Hardware Serial
// (e.g. GPS for Leonardo, Flora or FeatherWing)
//
// This code shows how to test a passthru between USB and hardware serial
//
// Tested and works great with the Adafruit GPS FeatherWing
// ------> https://www.adafruit.com/products/3133
// or Flora GPS
// ------> https://www.adafruit.com/products/1059
// but also works with the shield, breakout
// ------> https://www.adafruit.com/products/1272
// ------> https://www.adafruit.com/products/746
//
// Pick one up today at the Adafruit electronics shop
// and help support open source hardware & software! -ada


// what's the name of the hardware serial port?
#define GPSSerial Serial1


void setup() {
  // wait for hardware serial to appear
  while (!Serial);

  // make this baud rate fast enough to we aren't waiting on it
  Serial.begin(115200);

  // 9600 baud is the default rate for the Ultimate GPS
  GPSSerial.begin(9600);
}


void loop() {
  String gps_string = "";
       // Get char
     // if (char == '$') then start reading 
    // read char again, store to string
    // (if char == '\n') then set string to "", return string
    // else not nl -> keep reading

    if (GPSSerial.available()) {
      char c = GPSSerial.read();
      Serial.println(c);
      if (strcmp(c,"$")==0){
        gps_string += c;
        c = GPSSerial.read();
        Serial.println(c);        
      }


      
//      Serial.write(c);
    }





  
//  Serial.println("testing");

//for (int i=0; i<15; i++){
//  gps_string+= i;
//  Serial.println(gps_string);
//  
//}


//    if (GPSSerial.available()) {
//      char c = GPSSerial.read();
//      Serial.write(c);
//    }


  
//  if (Serial.available()) {
//    char c = Serial.read();
//    GPSSerial.write(c);
//  }
//  if (GPSSerial.available()) {
//    char c = GPSSerial.read();
//    Serial.write(c);
//  }
}
