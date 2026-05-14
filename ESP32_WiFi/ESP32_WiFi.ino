/************************************************************
 * File: main.ino
 * Project: ESP32 SPI Slave Communication
 * Description:
 *  - Initializes SPI slave module
 *  - Receives and responds to SPI transactions
 *  - Future expansion: add Ethernet/Wi-Fi MQTT modules
 ************************************************************/
/*
#include <Arduino.h>
#include "SPISlaveHandler.h"

SPISlaveHandler spiSlave;  // Create SPI slave handler object

void setup()
{
  Serial.begin(115200);
  delay(1000);
  Serial.println("=== ESP32 SPI Slave System Start ===");

  spiSlave.begin();  // Initialize SPI slave
}

void loop() 
{
  spiSlave.handleTransaction();  // Wait for SPI communication
  delay(1000);
}
*/
/************************************************************
 * Project: ESP32 SPI Slave with Wi-Fi + MQTT Integration
 * ---------------------------------------------------------
 * - Acts as SPI Slave for receiving data from SPI Master
 * - Connects to Wi-Fi network
 * - Publishes received SPI data to MQTT broker
 *
 * Date: October 2025
 ************************************************************/
/************************************************************
 * File: GatewayMain.ino
 * Description:
 *  - ESP32 Gateway with Ethernet (W5500) + Wi-Fi + MQTT + SPI Slave
 *  - Ethernet has first priority for network connection
 *  - Automatically switches between Ethernet and Wi-Fi
 *  - Publishes SPI-received data via MQTT
 ************************************************************/

#include "WiFiHandler.h"
#include "EthernetHandler.h"
#include "MQTTHandler.h"
#include "SPISlaveHandler.h"

SPISlaveHandler spiHandler;

// Track active interface
bool usingEthernet = false;

void setup() {
  Serial.begin(115200);
  Serial.println("\n=== ESP32 Gateway: Ethernet + WiFi + MQTT ===");

  /******************** Initialize Ethernet ********************/
  setupEthernet();
  bool ethernetOnline = isEthernetConnected();

  if (ethernetOnline) {
    usingEthernet = true;
    Serial.println("🌐 Using Ethernet for Internet");
  } else {
    /******************** Fallback to Wi-Fi ********************/
    setupWiFi();
    usingEthernet = false;
    Serial.println("📶 Using Wi-Fi for Internet");
  }

  /******************** Initialize MQTT ********************/
  setupMQTT(usingEthernet);

  /******************** Initialize SPI Slave ********************/
  spiHandler.begin();

  Serial.println("✅ Gateway Initialization Complete");
}

void loop() {
  /******************** MQTT Keepalive ********************/
  reconnectMQTT();
  mqttClient.loop();

  /******************** Handle SPI Data ********************/
  spiHandler.handleTransaction();

  /******************** Network Management ********************/
  // Ethernet takes priority
  if (isEthernetConnected()) {
    // If Ethernet link detected but currently using Wi-Fi, switch
    if (!usingEthernet) {
      Serial.println("🔁 Ethernet link detected, switching from Wi-Fi → Ethernet");
      WiFi.disconnect(true);
      usingEthernet = true;
      setupMQTT(true);  // Reconfigure MQTT to use Ethernet
    }
  } else {
    // Ethernet is down
    if (usingEthernet) {
      Serial.println("⚠️ Ethernet link lost, switching to Wi-Fi");
      setupWiFi();
      usingEthernet = false;
      setupMQTT(false); // Reconfigure MQTT to use Wi-Fi
    } else {
      reconnectWiFi();  // Keep Wi-Fi alive
    }
  }

  delay(1000);
}
