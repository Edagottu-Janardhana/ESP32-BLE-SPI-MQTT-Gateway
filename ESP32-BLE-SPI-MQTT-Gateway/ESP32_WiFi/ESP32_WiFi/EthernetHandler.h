/************************************************************
 * File: EthernetHandler.h
 * Description:
 *  - Handles Ethernet (W5500) initialization and status checking
 *  - Gives priority to Ethernet over Wi-Fi
 *  - Provides helper functions for link monitoring and switching
 ************************************************************/

#ifndef ETHERNET_HANDLER_H
#define ETHERNET_HANDLER_H

#include <SPI.h>
#include <Ethernet.h>

// --- W5500 Ethernet module pin connections ---
#define ETH_CS   5
#define ETH_RST  21
#define ETH_MOSI 23
#define ETH_MISO 19
#define ETH_SCK  18

// --- MAC address (must be unique per device) ---
extern byte ethMac[];

// --- Global Ethernet client object ---
extern EthernetClient ethClient;

// --- Function declarations ---
void setupEthernet();
bool isEthernetConnected();
void reconnectEthernet();
void resetEthernetChip();

#endif
