/**************************************************************************************
 * File: MQTTHandler.h
 * Description:
 * -----------------
 * Provides MQTT client setup and message publishing.
 * - Connects to the MQTT broker.
 * - Handles reconnection.
 * - Publishes messages to given topics.
 **************************************************************************************/
/*
#ifndef MQTT_HANDLER_H
#define MQTT_HANDLER_H

#include <WiFi.h>
#include <PubSubClient.h>

// ====== MQTT Configuration ======
extern const char* mqtt_server;
extern const int mqtt_port;
extern WiFiClient espClient;
extern PubSubClient client;

// ====== Function Declarations ======
void setupMQTT();                                    // Initialize MQTT
void reconnectMQTT();                                // Reconnect if disconnected
void publishToMQTT(const char* topic, const char* message);  // Publish message

#endif  // MQTT_HANDLER_H
*/

#include <PubSubClient.h>
#include <Ethernet.h>
#include <WiFi.h>

// Declare separate clients
extern WiFiClient wifiNetClient;
extern EthernetClient ethNetClient;
extern PubSubClient mqttClient;

// Functions
void setupMQTT(bool useEthernet);
void reconnectMQTT();
void publishToMQTT(const char* topic, const char* payload);
