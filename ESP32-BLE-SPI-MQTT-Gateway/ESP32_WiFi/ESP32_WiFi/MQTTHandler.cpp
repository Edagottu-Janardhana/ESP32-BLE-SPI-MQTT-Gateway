/**************************************************************************************
 * File: MQTTHandler.cpp
 * Description:
 * -----------------
 * Implements MQTT broker connection and data publishing.
 **************************************************************************************/
/*
#include "MQTTHandler.h"

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// ====== MQTT Setup ======
void setupMQTT() {
  client.setServer(mqtt_server, mqtt_port);
  Serial.println("MQTT client configured.");
}

// ====== Reconnect MQTT if needed ======
void reconnectMQTT() {
  while (!client.connected()) {
    Serial.print("Connecting to MQTT...");
    if (client.connect("ESP32Client_WiFi")) {
      Serial.println("Connected!");
    } else {
      Serial.print("Failed, rc=");
      Serial.println(client.state());
      delay(2000);
    }
  }
}

// ====== Publish Data ======
void publishToMQTT(const char* topic, const char* message) {
  if (!client.connected()) reconnectMQTT();
  client.loop();

  if (client.publish(topic, message)) {
    Serial.print("MQTT Published → ");
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(message);
  } else {
    Serial.println("MQTT publish failed!");
  }
}
*/

/************************************************************
 * File: MQTTHandler.cpp
 * Description:
 *  - Handles MQTT setup, reconnection, and publishing
 *  - Automatically uses Ethernet or Wi-Fi client
 ************************************************************/

#include "MQTTHandler.h"
#include "EthernetHandler.h"
#include "WiFiHandler.h"

#define MQTT_SERVER "test.mosquitto.org"
#define MQTT_PORT   1883

WiFiClient wifiNetClient;
EthernetClient ethNetClient;
PubSubClient mqttClient;

bool usingEthernetMQTT = false;

void setupMQTT(bool useEthernet) {
  usingEthernetMQTT = useEthernet;

  if (useEthernet) {
    mqttClient.setClient(ethNetClient);
    Serial.println("🌐 MQTT using EthernetClient");
  } else {
    mqttClient.setClient(wifiNetClient);
    Serial.println("📶 MQTT using WiFiClient");
  }

  mqttClient.setServer(MQTT_SERVER, MQTT_PORT);
  Serial.println("MQTT client configured.");
}

void reconnectMQTT() {
  if (!mqttClient.connected()) {
    Serial.println("Connecting to MQTT...");
    if (mqttClient.connect("ESP32_Gateway")) {
      Serial.println("✅ MQTT Connected!");
    } else {
      Serial.print("❌ MQTT connect failed, state=");
      Serial.println(mqttClient.state());
    }
  }
}

void publishToMQTT(const char* topic, const char* payload) {
  if (mqttClient.connected()) {
    mqttClient.publish(topic, payload);
    Serial.print("📤 Published to ");
    Serial.print(topic);
    Serial.print(": ");
    Serial.println(payload);
  }
}

