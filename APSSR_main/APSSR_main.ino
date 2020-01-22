// APSSR PSat code 2020
// Ver 0.1
// Amelia Cordwell, Ana Kiddle, Darya Krylova, James Brown, Jonathan Mace, Keshav Krishna,


// List of modules:
// - Temp/Pressure/Alt
// - IMU
// - GPS
// - WiFi
// - Camera
// - RTC/SD Card
// - A U D I O

//#define CAMDEF

/*Comment/Uncomment to turn modules on/off*/
//#define BARO_ON
//#define IMU_ON
//#define GPS_ON
//#define WiFi_ON
//#define CAM_ON
//#define SD_ON
//#define RTC_ON



void setup() {
  // put your setup code here, to run once:

  //Starts serial communication
  Serial.begin(115200);
  Serial.println("PSat starting up");

  // Setup of individual modules
  #ifdef BARO_ON
  // Temp/Pressure/Alt
  baro_setup();
  #endif

  #ifdef IMU_ON
  // IMU
   IMU_setup();
   #endif

   #ifdef GPS_ON
  // GPS
  GPS_setup();
  #endif
  
  #ifdef WiFi_ON
  // WiFi
  #endif

  #ifdef CAM_ON
  // Camera
  camera_setup();
  #endif

  #ifdef SD_ON
  //SD Card
  SD_setup();
  #endif

  #ifdef RTC_ON
  //RTC
  #endif

  

  
// PLAY AUDIO

}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println("PSat loopin'");
  delay(1000);

//  Log telemetry
//  baro_read()
//  IMU_read()
//  GPS_read() [+ status?]
//  WiFi status read [?}
//  RTC_read()

  #ifdef BARO_ON
  // Temp/Pressure/Alt
  baro_read();
  #endif

  #ifdef IMU_ON
  // IMU
   IMU_read();
   #endif

   #ifdef GPS_ON
  // GPS
  Serial.println(GPS_read()); //[+ status?]
  #endif
  
  #ifdef WiFi_ON
  // WiFi
//   WiFi status read [?}
  #endif

  #ifdef CAM_ON
  // Camera
  camera_setup();
  #endif

  #ifdef RTC_ON
  //RTC
//  RTC_read();
  #endif


//*****Other stuff*****\\
//Camera:
//  have_we_deployed?()
//  if (deployed) & (!camera_on){turn_video_on} else {nada}
// [can we video and photo at the same time?
// turn camera off?
// AUDIO: do we need to turn it on? off?

//Save telemetry to SD card
//SD_write(data_string)
  #ifdef SD_ON
  //SD Card
  SD_write("Test data");
  #endif

//Send telemetry via wifi
// ??
}


/* 
 *  What do we want the telemetry report to look like?
 *  -----------
 *  Alt: 12m
 *  Temperature: 20 deg
 *  
 *  Acceleration vector: 
 *  
 *  GPS status:
 *  
 *  WiFi status:
 *  
 *  Camera status: 
 *  
 */


 /*Data for logging to SD card:
  * |Time[since turned on?]|Alt|Temp|Press|Accel_x|Accel_y|Accel_z|Mag_x|Mag_y|Mag_z|Gyro_x|Gyro_y|Gyro_z|GPS|WiFi_status|camera_status|
  * 
  * Do we want more GPS data/refined GPS data?
  * 
  */













  
