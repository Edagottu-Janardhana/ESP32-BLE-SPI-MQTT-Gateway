/************************************************************
 * File: SPISlaveHandler.cpp
 * Description:
 *  - Implements SPI slave communication logic
 ************************************************************/
/*
#include "SPISlaveHandler.h"

void SPISlaveHandler::begin() 
{
  slave.setDataMode(SPI_MODE0);
  slave.begin(); // Use HSPI default pins

  memset(txBuf, 0, BUFFER_SIZE);
  memset(rxBuf, 0, BUFFER_SIZE);
  Serial.println("SPI Slave initialized successfully");
}

void SPISlaveHandler::handleTransaction() {
  const char *response = "ACK_FROM_SLAVE";
  memset(txBuf, 0, BUFFER_SIZE);
  memcpy(txBuf, response, strlen(response));

  Serial.println("Waiting for master...");
  slave.wait(rxBuf, txBuf, BUFFER_SIZE);
  Serial.println("Transaction completed!");

  // Copy received data into provided buffer
  size_t copyLen = min(length - 1, (size_t)BUFFER_SIZE);
  memcpy(outBuffer, rxBuf, copyLen);
  outBuffer[copyLen] = '\0'; // Null-terminate

  Serial.print("Received from Master: ");
  Serial.println(outBuffer);

  Serial.print("Sent back to Master: ");
  Serial.println(response);
  Serial.println("---------------------------");

  return true;  // indicate a transaction happened
}
*/

/************************************************************
 * File: SPISlaveHandler.cpp
 * Description:
 *  - Handles SPI slave transactions using ESP32SPISlave library
 *  - Waits for master data and publishes received data via MQTT
 ************************************************************/

#include "SPISlaveHandler.h"
#include "WiFiHandler.h"   // for publishToMQTT()
#include "EthernetHandler.h"
#include "MQTTHandler.h"

void SPISlaveHandler::begin() {
  slave.setDataMode(SPI_MODE0);
  slave.begin();  // Uses default HSPI pins (GPIO14, 12, 13, 15)

  memset(txBuf, 0, BUFFER_SIZE);
  memset(rxBuf, 0, BUFFER_SIZE);

  Serial.println("SPI Slave Initialized");
}

void SPISlaveHandler::handleTransaction() {
  // Prepare ACK message for master before transaction
  const char *ackMsg; // = "ACK_FROM_SLAVE";

    if (isEthernetConnected()) 
    {
        ackMsg = "ACK_ETH_OK";
    } 
    else if (isWiFiConnected())
    {
        ackMsg = "ACK_WIFI_OK";
    } 
    else 
    {
        ackMsg = "ACK_NET_FAIL";
    }
  memset(txBuf, 0, BUFFER_SIZE);
  memcpy(txBuf, ackMsg, strlen(ackMsg));

  Serial.println("Waiting for SPI master...");

  // Blocking wait until transaction completes 
  slave.wait(rxBuf, txBuf, BUFFER_SIZE);

  Serial.println("Transaction completed!");

  // Print received data
  Serial.print("SPI Received: ");
  for (int i = 0; i < BUFFER_SIZE; i++) {
    if (rxBuf[i] == 0) break;
    Serial.write(rxBuf[i]);
  }
  Serial.println();

  // Publish received data to MQTT broker
  publishToMQTT("gateway/data", (char*)rxBuf);

  Serial.println("---------------------------");
}

