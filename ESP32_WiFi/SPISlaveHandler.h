/************************************************************
 * File: SPISlaveHandler.h
 * Description:
 *  - Header for managing SPI slave communication
 ************************************************************/

#ifndef SPI_SLAVE_HANDLER_H
#define SPI_SLAVE_HANDLER_H

#include <Arduino.h>
#include <ESP32SPISlave.h>

class SPISlaveHandler {
public:
  void begin();
  void handleTransaction();
 


private:
  static constexpr uint32_t BUFFER_SIZE = 64;
  ESP32SPISlave slave;
  uint8_t txBuf[BUFFER_SIZE];
  uint8_t rxBuf[BUFFER_SIZE];
};

#endif
