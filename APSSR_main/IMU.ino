// APSSR PSat code 2020
// Header file for the IMU sensor

//Includes
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_LSM303_U.h>
#include <Adafruit_L3GD20_U.h>
#include <Adafruit_9DOF.h>

// todo: return quaternions?! 
//imu::Quaternion quat = bno.getQuat();

/* Assign a unique ID to the sensors */
Adafruit_LSM303_Accel_Unified accel = Adafruit_LSM303_Accel_Unified(30301);
Adafruit_LSM303_Mag_Unified   mag   = Adafruit_LSM303_Mag_Unified(30302);
Adafruit_L3GD20_Unified       gyro  = Adafruit_L3GD20_Unified(20);

void IMU_setup(){
    Serial.println(F("IMU starting up\n")); 

    /* Initialise the sensors */
  if(!accel.begin())
  {
    /* There was a problem detecting the ADXL345 ... check your connections */
    Serial.println(F("Ooops, no LSM303 detected ... Check your wiring!"));
    while(1);
  }
  if(!mag.begin())
  {
    /* There was a problem detecting the LSM303 ... check your connections */
    Serial.println("Ooops, no LSM303 detected ... Check your wiring!");
    while(1);
  }
  if(!gyro.begin())
  {
    /* There was a problem detecting the L3GD20 ... check your connections */
    Serial.print("Ooops, no L3GD20 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
}

void IMU_read(datapoint * dp){
// Reads from the IMU
// Saves it to the datapoint object
// Serial.println("Imu ing");
  /* Get a new sensor event */
  sensors_event_t event;

//  Gets acceleration (measured in m/s^2)
  accel.getEvent(&event);

  //Reads, saves data
  //Accelerometer
  dp->accel_x = event.acceleration.x;
  dp->accel_y = event.acceleration.y;
  dp->accel_z = event.acceleration.z;

  //Magnetometer
  dp->mag_x = event.magnetic.x;
  dp->mag_y = event.magnetic.y;
  dp->mag_z = event.magnetic.z;

  // Gyroscope
  dp->gyro_x = event.gyro.x;
  dp->gyro_y = event.gyro.y;
  dp->gyro_z = event.gyro.z; 
//  Serial.println(event.acceleration.x);
}
