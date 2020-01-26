// APSSR PSat code 2020
// Header file for the barometer/temp/altitude sensor

// Includes
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_BMP280.h>

// SPI Constants
//#define BMP_SCK  (13)
//#define BMP_MISO (12)
//#define BMP_MOSI (11)
//#define BMP_CS   (10)

Adafruit_BMP280 bmp; // I2C -> pins SCL, SDA
//Adafruit_BMP280 bmp(BMP_CS); // hardware SPI
//Adafruit_BMP280 bmp(BMP_CS, BMP_MOSI, BMP_MISO,  BMP_SCK);

void baro_setup() {
  // put your setup code here, to run once:
    Serial.println(F("BMP280 loaded\n"));

  if (!bmp.begin()) {
    Serial.println(F("Could not find a valid BMP280 sensor, check wiring!"));
//    while (1);
  }

    /* Default settings from datasheet. */
  bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,     /* Operating Mode. */
                  Adafruit_BMP280::SAMPLING_X2,     /* Temp. oversampling */
                  Adafruit_BMP280::SAMPLING_X16,    /* Pressure oversampling */
                  Adafruit_BMP280::FILTER_X16,      /* Filtering. */
                  Adafruit_BMP280::STANDBY_MS_500); /* Standby time. */

}

float baro_read(datapoint * dp) {
  float temp;
  float pressure;
  float altitude;
//    Serial.print(F("Temperature = "));
    temp = bmp.readTemperature();
//    Serial.print(temp);
//    Serial.println(" *C");

//    Serial.print(F("Pressure = "));
    pressure = bmp.readPressure();
//    Serial.print(pressure);
//    Serial.println(" Pa");

//    Serial.print(F("Approx altitude = "));
    altitude = bmp.readAltitude(1013.25);
//    Serial.print(altitude); /* Adjusted to local forecast! */
//    Serial.println(" m");

// Saves data to dp structure
    dp->temp = temp;
    dp->pressure = pressure;
    dp->alt = altitude;
}
