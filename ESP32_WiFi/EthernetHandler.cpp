/************************************************************
 * File: EthernetHandler.cpp
 * Description:
 *  - Initializes W5500 Ethernet module via SPI
 *  - Handles DHCP connection and IP assignment
 *  - Continuously monitors Ethernet link
 *  - Automatically reconnects if link drops
 ************************************************************/

#include "EthernetHandler.h"

byte ethMac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
EthernetClient ethClient;

// Track connection state
bool ethernetConnected = false;

void setupEthernet() {
  Serial.println("\n=== Initializing W5500 Ethernet (DHCP) ===");

  // Initialize SPI with custom pins
  SPI.begin(ETH_SCK, ETH_MISO, ETH_MOSI, ETH_CS);
  Ethernet.init(ETH_CS);

  // Hardware reset
  pinMode(ETH_RST, OUTPUT);
  digitalWrite(ETH_RST, LOW);
  delay(50);
  digitalWrite(ETH_RST, HIGH);
  delay(100);

  // Start DHCP
  Serial.println("Obtaining IP address via DHCP...");
  if (Ethernet.begin(ethMac) == 0) {
    Serial.println("DHCP failed! Check cable or router.");
    ethernetConnected = false;
    return;
  }

  delay(1000);
  Serial.print("Ethernet Connected! IP: ");
  Serial.println(Ethernet.localIP());
  ethernetConnected = true;
}

bool isEthernetConnected() {
  // Ethernet.linkStatus() returns LinkON or LinkOFF
  return (Ethernet.linkStatus() == LinkON);
}

void reconnectEthernet() {
  if (!isEthernetConnected()) {
    if (ethernetConnected) {
      Serial.println("⚠️ Ethernet link lost!");
      ethernetConnected = false;
    }

    // Retry DHCP if link comes back
    if (Ethernet.linkStatus() == LinkON) {
      Serial.println("Ethernet link detected, reconnecting...");
      if (Ethernet.begin(ethMac) != 0) {
        Serial.print("Reconnected! IP: ");
        Serial.println(Ethernet.localIP());
        ethernetConnected = true;
      } else {
        Serial.println("Reconnection failed!");
      }
    }
  }
}

void resetEthernetChip() {
  digitalWrite(ETH_RST, LOW);
  delay(50);
  digitalWrite(ETH_RST, HIGH);
  delay(100);
}
