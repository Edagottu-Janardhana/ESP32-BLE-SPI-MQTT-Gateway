
# ESP32 BLE – SPI – Wi‑Fi / Ethernet MQTT Gateway

## Project Overview
This project demonstrates a **two‑node ESP32 IoT gateway architecture** designed for reliable sensor data acquisition and cloud communication.

The system separates **sensor acquisition and BLE communication** from **network connectivity**, creating a modular architecture where one ESP32 focuses on sensing and local communication while another handles networking and cloud integration.

This design improves:
- Modularity
- System reliability
- Maintainability
- Scalability for larger IoT deployments

---

## System Architecture

Sensor Node                        Gateway Node                      
┌─────────────────────┐            ┌────────────────────────┐
│     ESP32_BLE       │            │     ESP32_Gateway      │
│  (Client + Master)  │            │   (Slave + Publisher)  │      MQTT
│                     │   SPI      │                        │------------->Cloud 
│ • BLE Central       │ <--------> │ • SPI Slave            │
│ • SHT40 Sensor      │            │ • WiFi / Ethernet      │
│ • SPI Master        │            │ • MQTT Client          │
└─────────────────────┘            └────────────────────────┘

---

## Data Flow

1. The **SHT40 sensor** measures temperature and humidity.
2. The **ESP32_BLE node** reads the sensor data via I2C.
3. Sensor values are formatted into a data frame:

   |##|T:25.6|H:55.3|**|

4. The formatted frame is transmitted via **SPI Master → SPI Slave**.
5. The **ESP32_Gateway node** receives the SPI data.
6. The gateway publishes the data to an **MQTT broker** via Wi‑Fi or Ethernet.
7. Cloud dashboards or IoT platforms subscribe to the MQTT topics and visualize the data.

---

## Repository Structure

ESP32-BLE-SPI-MQTT-Gateway/
│
├── ESP32_BLE_Node/                
│   ├── ESP32_BLE.ino
│   ├── BLECentralHandler.cpp
│   ├── BLECentralHandler.h
│   ├── SHT40Handler.cpp
│   ├── SHT40Handler.h
│   ├── SPIMasterHandler.cpp
│   └── SPIMasterHandler.h
│
├── ESP32_Gateway_Node/            
│   ├── ESP32_WiFi.ino
│   ├── SPISlaveHandler.cpp
│   ├── SPISlaveHandler.h
│   ├── WiFiHandler.cpp
│   ├── WiFiHandler.h
│   ├── EthernetHandler.cpp
│   ├── EthernetHandler.h
│   ├── MQTTHandler.cpp
│   └── MQTTHandler.h
│
└── README.md

---

## File‑by‑File Description

### ESP32_BLE_Node (Sensor Node)

| File | Description |
|-----|-------------|
| ESP32_BLE.ino | Main firmware entry point for the BLE node |
| BLECentralHandler.* | Handles BLE central communication |
| SHT40Handler.* | Driver for reading temperature and humidity from the SHT40 sensor |
| SPIMasterHandler.* | Implements SPI Master communication to send sensor data |

This node is responsible for:
- Reading sensor data
- Managing BLE connections
- Sending formatted data to the gateway via SPI

---

### ESP32_Gateway_Node (Gateway Node)

| File | Description |
|-----|-------------|
| ESP32_WiFi.ino | Main gateway firmware |
| SPISlaveHandler.* | Handles SPI slave communication and receives data from sensor node |
| WiFiHandler.* | Manages Wi‑Fi connection |
| EthernetHandler.* | Handles Ethernet connectivity |
| MQTTHandler.* | Publishes sensor data to MQTT broker |

This node acts as the **IoT gateway**, responsible for:
- Receiving SPI data
- Managing network connectivity
- Publishing sensor data to MQTT cloud

---

## Key Features

• Modular firmware architecture using handler‑based design  
• BLE central communication using NimBLE  
• High‑precision SHT40 temperature and humidity sensing  
• Reliable SPI Master‑Slave communication between ESP32 nodes  
• MQTT cloud publishing for IoT integration  
• Support for both Wi‑Fi and Ethernet connectivity  
• Scalable architecture suitable for multi‑sensor deployments  

---

## Technologies Used

- ESP32
- Embedded C / C++
- BLE (NimBLE stack)
- SPI communication
- I2C communication
- Wi‑Fi networking
- Ethernet (W5500)
- MQTT (PubSubClient library)
- SHT40 Temperature & Humidity Sensor

---

## Potential Applications

- Industrial IoT sensor gateways
- Smart agriculture monitoring systems
- Environmental monitoring networks
- Edge‑to‑cloud data pipelines
- Embedded systems architecture demonstrations

---

## Author

Edagottu Janardhana  
Firmware / Embedded Systems Engineer

---
