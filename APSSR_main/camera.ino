// APSSR PSat code 2020
// Header file for the camera


#ifndef CAMDEF
#define CAMDEF
int CAM_trig = 11;
int led = 13;
bool photo = false; // False for video
int video_length = 3; // Video length in seconds
#endif
 
void camera_setup() {                
  // initialize the digital pins as output.
  pinMode(led, OUTPUT);
  pinMode(CAM_trig, OUTPUT);         
 
  digitalWrite(led, HIGH);  
  digitalWrite(CAM_trig, HIGH); 
  while(!Serial)
  Serial.begin(9600);
}
 
// Hold HIGH and trigger quick (<250ms) LOW to take a photo. Holding LOW and trigger HIGH starts/stops video recording
void start_video(){
  // Hold low
    Serial.print("Start recording\n");
    digitalWrite(CAM_trig, LOW);
    delay(1500);
    digitalWrite(CAM_trig, HIGH);
  
}

void stop_video(){
  // Stops recording
    Serial.println("Stops recording");
    digitalWrite(CAM_trig, LOW);
    delay(1500);
    digitalWrite(CAM_trig, HIGH);
}

void take_photo(){
    digitalWrite(CAM_trig, LOW);   
    digitalWrite(led, LOW);
    
    delay(50);               
    
    digitalWrite(CAM_trig, HIGH);    
    digitalWrite(led, HIGH);  
}