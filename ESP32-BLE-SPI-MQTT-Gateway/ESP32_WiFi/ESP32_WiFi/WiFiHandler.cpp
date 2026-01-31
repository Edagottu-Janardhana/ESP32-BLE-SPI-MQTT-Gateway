/**************************************************************************************
 *  File: WiFiHandler.cpp
 *  Description:
 *  -----------------
 *  Handles Wi-Fi and MQTT setup, reconnection, and data publishing.
 **************************************************************************************/
/*
#include "WiFiHandler.h"

// ====== Wi-Fi and MQTT Configuration ======
const char* ssid = "realme 7";
const char* password = "123456789";

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);

// ====== Setup Wi-Fi ======
void setupWiFi() {
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWi-Fi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWi-Fi connection failed!");
  }

  client.setServer(mqtt_server, mqtt_port);
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
    Serial.print("MQTT Published -> Topic: ");
    Serial.print(topic);
    Serial.print(" | Message: ");
    Serial.println(message);
  } else {
    Serial.println("MQTT Publish failed!");
  }
}
*/
/**************************************************************************************
 * File: WiFiHandler.cpp
 * Description:
 * -----------------
 * Implements Wi-Fi connection setup and reconnection logic.
 **************************************************************************************/

#include "WiFiHandler.h"
#include <ETH.h>


//const char* ssid = "Honey";
//const char* password = "Vishnu@8500";

const char* ssid = "realme 7";
const char* password = "123456789";

// ====== Setup Wi-Fi ======
bool isWiFiConnected() {
  return (WiFi.status() == WL_CONNECTED);
}


void setupWiFi() {
  Serial.print("Connecting to Wi-Fi: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  int retries = 0;
  while (WiFi.status() != WL_CONNECTED && retries < 30) {
    delay(500);
    Serial.print(".");
    retries++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\n✅ Wi-Fi connected!");
    Serial.print("IP Address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\n❌ Wi-Fi connection failed!");
  }
}

// ====== Reconnect Wi-Fi if lost ======
void reconnectWiFi() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("Reconnecting Wi-Fi...");
    WiFi.disconnect();
    WiFi.reconnect();
  }
}

