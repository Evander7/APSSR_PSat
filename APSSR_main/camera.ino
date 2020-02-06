// APSSR PSat code 2020
// Header file for the camera

int CAM_trig = 11;
int led = 13;
 
void camera_setup() {                
  // initialize the digital pins as output.
  pinMode(led, OUTPUT);
  pinMode(CAM_trig, OUTPUT);         
  digitalWrite(led, HIGH);  
  digitalWrite(CAM_trig, HIGH); 
  time_since_last_photo = millis();
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
    photos_taken += 1;
}
