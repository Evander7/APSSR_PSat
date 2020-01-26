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
#define BARO_ON
//#define IMU_ON //todo: gotta calibrate this shite lol
//#define GPS_ON // DEMON CODE NEVER RUN THIS
//#define WiFi_ON
//#define CAM_ON
#define SD_ON
//#define RTC_ON

// Sets up the output filename to save data to. the '00' will be changed each time to be sequential.
String output_filename = "APSSR00.csv";


struct datapoint {
  String time_point;
  float alt;
  float temp;
  float pressure;
  int accel_x;
  int accel_y;
  int accel_z;
  int mag_x;
  int mag_y;
  int mag_z;
  int gyro_x;
  int gyro_y;
  int gyro_z;
  int GPS;
  int WiFi_status;
  int camera_status;
};
char filename[10];
//typedef struct datapoint Datapoint;

void setup() {
  // put your setup code here, to run once:

  //Starts serial communication
  Serial.begin(9600);
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

// GPS IS DEMON CODE DO NOT RUN
//   #ifdef GPS_ON
//  // GPS
//  GPS_setup();
//  #endif
  
  #ifdef WiFi_ON
  // WiFi
  #endif

  #ifdef CAM_ON
  // Camera
  camera_setup();
  #endif

  #ifdef SD_ON
  //SD Card
  SD_setup(&output_filename);
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
  // Creates #fresh datapoint object, so we can log stuff to it
  datapoint dp = {"placeholder"};

//  Log telemetry
//  baro_read()
//  IMU_read()
//  GPS_read() [+ status?]
//  WiFi status read [?]
//  RTC_read()

  #ifdef BARO_ON
  // Temp/Pressure/Alt
  baro_read(&dp);
//  Serial.println(dp.temp);
//  Serial.println(dp.pressure);
//  Serial.println(dp.alt);
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
  // Turns the datapoint struct into a csv string
  String data_string;
  data_string = dp.time_point + "," + String(dp.alt) + "," + String(dp.temp) + "," + String(dp.pressure) + "," 
  + String(dp.accel_x) + "," + String(dp.accel_y) + "," + String(dp.accel_z) + "," 
  + String(dp.mag_x) + "," + String(dp.mag_y) + "," + String(dp.mag_z) + "," 
  + String(dp.gyro_x) + "," + String(dp.gyro_y) + "," + String(dp.gyro_z) + "," 
  + String(dp.GPS) + "," + String(dp.WiFi_status) + "," + String(dp.camera_status);
  Serial.println(data_string);
  SD_write(data_string, output_filename);
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















  
