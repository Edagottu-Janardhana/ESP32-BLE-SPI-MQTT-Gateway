/**************************************************************************************
 *  File: WiFiHandler.h
 *  Description:
 *  -----------------
 *  Provides Wi-Fi and MQTT connection management for the ESP32.
 *  - Connects to a Wi-Fi network.
 *  - Connects to MQTT broker (e.g., test.mosquitto.org).
 *  - Publishes messages to given MQTT topics.
 *  - Automatically reconnects if Wi-Fi or MQTT disconnects.
 **************************************************************************************/
/*
#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>
#include <PubSubClient.h>

// ====== Wi-Fi and MQTT Configuration ======
extern const char* ssid;
extern const char* password;

extern const char* mqtt_server;
extern const int mqtt_port;

extern WiFiClient espClient;
extern PubSubClient client;

// ====== Function Declarations ======
void setupWiFi();                            // Connects to Wi-Fi
void reconnectMQTT();                        // Ensures MQTT connection
void publishToMQTT(const char* topic, const char* message);  // Publish data

#endif  // WIFI_HANDLER_H
*/
/**************************************************************************************
 * File: WiFiHandler.h
 * Description:
 * -----------------
 * Provides Wi-Fi connection management for the ESP32.
 * - Connects to a Wi-Fi network.
 * - Handles automatic reconnection.
 **************************************************************************************/

#ifndef WIFI_HANDLER_H
#define WIFI_HANDLER_H

#include <WiFi.h>

// ====== Wi-Fi Configuration ======
extern const char* ssid;
extern const char* password;

// ====== Function Declarations ======
void setupWiFi();        // Connects to Wi-Fi network
void reconnectWiFi();    // Ensures Wi-Fi stays connected
bool isWiFiConnected();
#endif  // WIFI_HANDLER_H
