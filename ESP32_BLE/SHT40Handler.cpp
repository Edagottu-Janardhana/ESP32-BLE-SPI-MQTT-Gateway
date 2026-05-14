/************************************************************
 * File: SHT40Handler.cpp
 * Description: Handles initialization and data acquisition from
 *              the SHT40 sensor via I2C. Returns formatted data
 *              strings to be sent over SPI to the slave.
 ************************************************************/

#include "SHT40Handler.h"
#include <Wire.h>

#define SDA_PIN 21
#define SCL_PIN 22

Adafruit_SHT4x sht4 = Adafruit_SHT4x();

void SHT40_Init(){
  Wire.begin(SDA_PIN, SCL_PIN);
  if (!sht4.begin()) {
    Serial.println("Couldn't find SHT4x sensor!");
    while (1) delay(1);
  }
  sht4.setPrecision(SHT4X_HIGH_PRECISION);
  sht4.setHeater(SHT4X_NO_HEATER);

  Serial.println("SHT40 initialized successfully!");
}

String getSHT40Data() {
  sensors_event_t humidity, temp;
  sht4.getEvent(&humidity, &temp);

  // Example format: |##|TEMP:25.6|HUM:55.3|**|
  String data = "|##|SHT40|" + String(temp.temperature, 1) +
                "|" + String(humidity.relative_humidity, 1) + "|**|";
  return data;
}
