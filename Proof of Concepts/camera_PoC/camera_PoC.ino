// Proof of Concept
// Arduino feather timelapse camera code
// For PSat 2020

#ifndef camera_defs
#define camera_defs
int CAM_trig = 11;
int led = 13;
bool photo = false; // False for video
int video_length = 3; // Video length in seconds
#endif
 
void setup() {                
  // initialize the digital pins as output.
  pinMode(led, OUTPUT);
  pinMode(CAM_trig, OUTPUT);         
 
  digitalWrite(led, HIGH);  
  digitalWrite(CAM_trig, HIGH); 
  while(!Serial)
  Serial.begin(9600);
}
 
// Hold HIGH and trigger quick (<250ms) LOW to take a photo. Holding LOW and trigger HIGH starts/stops video recording
 
void loop() {
//  todo: incorporate clock?
  if (photo){
      digitalWrite(CAM_trig, LOW);   
      digitalWrite(led, LOW);
      
      delay(50);               
     
      digitalWrite(CAM_trig, HIGH);    
      digitalWrite(led, HIGH);   
     
      //Delay between pictures
      delay(1000);               
  } else {
    // take video!
    // Hold low
    Serial.print("Start recording\n");
    digitalWrite(CAM_trig, LOW);
    delay(1500);
    digitalWrite(CAM_trig, HIGH);

    delay(7000);

    // Stops recording
    Serial.println("Stops recording");
    digitalWrite(CAM_trig, LOW);
    delay(1500);
    digitalWrite(CAM_trig, HIGH);

    delay(10*10000);

    // need to: write separate functions for starting and stopping. 
    // also not sure if it stops recording if you just turn it off.
    
  }

  
}
