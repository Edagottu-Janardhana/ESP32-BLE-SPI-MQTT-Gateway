/************************************************************
 * File: SPIMasterHandler.h
 * Description:
 *  - Provides APIs to initialize and communicate with SPI Slave.
 *  - Used by main.ino or other modules (e.g., BLEHandler, SHT40Handler)
 *    to send data frames to the SPI slave device.
 *  - Compatible with ESP32 SPI Master mode.
 ************************************************************/

#ifndef SPI_MASTER_HANDLER_H
#define SPI_MASTER_HANDLER_H

#include <Arduino.h>

// Function prototypes
void SPI_init();
void SPI_send(const char *msg);
void sendSPIMessage(const String &msg);
#endif
