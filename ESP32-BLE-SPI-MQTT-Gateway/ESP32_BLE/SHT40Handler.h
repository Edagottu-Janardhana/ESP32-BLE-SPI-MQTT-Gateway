/************************************************************
 * File: SHT40Handler.h
 * Description: Header file for SHT40 sensor interface using I2C.
 *              Provides functions to initialize and read temperature
 *              and humidity data, returning formatted strings for SPI transmission.
 ************************************************************/

#ifndef SHT40_HANDLER_H
#define SHT40_HANDLER_H

#include <Arduino.h>
#include <Adafruit_SHT4x.h>

void SHT40_Init();
String getSHT40Data();

#endif
