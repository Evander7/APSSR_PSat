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
int photo_gap = 500; // gap between subsequenct photos, in millisceconds
int photos_taken = 0;

/*Comment/Uncomment to turn modules on/off*/
#define BARO_ON
#define IMU_ON
//#define GPS_ON // DEMON CODE NEVER RUN THIS
//#define WiFi_ON
#define CAM_ON
#define SD_ON
#define RTC_ON
#define ALLSTAR
#define RGB_LED

// Sets out a "datapoint" structure
// Every loop, each sensor will read its specific values, and put them into a loop-specific dp object
// This then gets concatenated together and saved as a .csv file!
// If changing the datapoint struct, you need to change the way it's concatenated down below, and change the csv headers.


// Sets up the output filename to save data to. the '00' will be changed each time to be sequential.
String output_filename;
unsigned long time_since_last_photo;

struct datapoint {
  uint32_t time_point;
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

//char filename[10];
//typedef struct datapoint Datapoint;

void baro_setup();
String SD_setup();
void SD_write(String to_write, String filename);
int r = 255;
int g = 0;
int b = 0;
int t; //temp led value


void setup() {
  //Starts serial communication
  Serial.begin(9600);
  Serial.println("APSSR PSat starting up");

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
  output_filename = SD_setup();
  // Writes initial .csv headers
  SD_write("Time stamp,Altitude [m],Temperature [*C],Pressure [pa],Acceleration_x [m/s^2],Acceleration_y [m/s^2 ],Acceleration_z [m/s^2],Magnetometer_x [uT],Magnetometer_y [uT],Magnetometer_z [uT],Gyroscope_x [rad/s],Gyroscope_y [rad/s],Gyroscope_z [rad/s],GPS,WiFi Status,Photos Taken",output_filename);
  #endif

  #ifdef RTC_ON
  //RTC
  RTC_setup();
  #endif

  #ifdef ALLSTAR
// PLAY AUDIO
  allstar_setup();
  #endif

  #ifdef RGB_LED
  // Starts up the RGB LED
  RGB_setup();
  #endif

}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println("PSat loopin'");
  
//  delay(1000);

  #ifdef RGB_LED
  // Flashes the RGB LED
  RGB_on(r,g,b);
  t = r;
  r = g;
  g = b;
  b = t;
  #endif
  
  // Creates #fresh datapoint object, so we can log stuff to it
  datapoint dp = {0};

/* ---------- Logs telemetry ---------- */
// Barometer
  #ifdef BARO_ON
  // Temp/Pressure/Alt
  baro_read(&dp);
  #endif

// IMU
  #ifdef IMU_ON
  // Accel/Mag/Gyro
   IMU_read(&dp);
   #endif

// GPS
   #ifdef GPS_ON
//  Serial.println(GPS_read()); //[+ status?]
  #endif

// WiFi
  #ifdef WiFi_ON
//   WiFi status read [?}
  #endif

// RTC
  #ifdef RTC_ON
  // Adds unix timestamp to our datapoint struct
  get_unix(&dp);
  #endif

/* ---------- Other stuff ---------- */

  #ifdef CAM_ON
//Camera logic:
//  have_we_deployed?()
//  if (deployed) & (!camera_on){turn_video_on} else {nada}
// [can we video and photo at the same time?
// turn camera off?

// Take photo every x seconds 
if ((time_since_last_photo - millis()) > photo_gap){
  take_photo();
  time_since_last_photo = millis();
}

// todo: if below certain altitude, start taking video?
  #endif

// Save telemetry to SD card
  #ifdef SD_ON
  // SD Card
  // Turns the datapoint struct into a csv string
  // I'm sure there's a better way to do this, I'm sorry
  // Where's Python's ",".join(list) when ya need it eh
  String data_string;
  data_string = String(dp.time_point) + "," + String(dp.alt) + "," + String(dp.temp) + "," + String(dp.pressure) + "," 
  + String(dp.accel_x) + "," + String(dp.accel_y) + "," + String(dp.accel_z) + "," 
  + String(dp.mag_x) + "," + String(dp.mag_y) + "," + String(dp.mag_z) + "," 
  + String(dp.gyro_x) + "," + String(dp.gyro_y) + "," + String(dp.gyro_z) + "," 
  + String(dp.GPS) + "," + String(dp.WiFi_status) + "," + String(photos_taken);
//  Serial.println(data_string);
  SD_write(data_string, output_filename);
  #endif

//Send telemetry via wifi
// ??

// Play buzzer @ end of loop
  #ifdef ALLSTAR
// PLAY AUDIO
//  start_buzzer();
  buzzer_loop();
  #endif

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
