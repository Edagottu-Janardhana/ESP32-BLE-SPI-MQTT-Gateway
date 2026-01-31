# ESP32 BLE – SPI – Wi‑Fi MQTT Gateway

## 📌 Project Overview
This project implements a **two‑node ESP32 IoT gateway architecture** designed for reliable sensor data collection and cloud publishing.

The system separates **sensor acquisition & BLE communication** from **network connectivity**, improving modularity, scalability, and reliability.

---

## 🧩 System Architecture

```
+-----------------------+        SPI        +------------------------+        MQTT
|  ESP32_BLE Node       |  <------------>  |  ESP32_WiFi Gateway    |  ----------->  Cloud
|  (Client + Master)    |                  |  (Slave + Publisher)   |
|                       |                  |                        |
| • BLE Central (NimBLE)|                  | • SPI Slave            |
| • SHT40 Sensor (I2C)  |                  | • Wi‑Fi STA            |
| • SPI Master          |                  | • MQTT Client          |
+-----------------------+                  +------------------------+
```

---

## 🔁 Data Flow

1. **SHT40 sensor** measures temperature and humidity.
2. ESP32_BLE formats data into a frame:
   ```
   |##|T:25.6|H:55.3|**|
   ```
3. Frame is sent via **SPI Master → SPI Slave**.
4. ESP32_WiFi receives SPI data.
5. Data is published to an **MQTT broker** over Wi‑Fi.
6. Cloud dashboards or subscribers consume the data.

---

## 📂 Repository Structure

```
ESP32-BLE-SPI-MQTT-Gateway/
│
├── ESP32_BLE/                # Sensor & BLE node (SPI Master)
│   ├── ESP32_BLE.ino         # Main application
│   ├── BLECentralHandler.*   # BLE Central (NimBLE) logic
│   ├── SHT40Handler.*        # SHT40 sensor driver (I2C)
│   ├── SPIMasterHandler.*    # SPI Master implementation
│
├── ESP32_WiFi/               # Gateway node (SPI Slave)
│   ├── ESP32_WiFi.ino        # Main gateway firmware
│   ├── SPISlaveHandler.*     # SPI Slave handling
│   ├── WiFiHandler.*         # Wi‑Fi + MQTT management
│
└── README.md
```

---

## 🧠 File‑by‑File Explanation

### ESP32_BLE (Client + SPI Master)

| File | Purpose |
|----|----|
| `ESP32_BLE.ino` | Initializes BLE, SHT40, and SPI Master |
| `BLECentralHandler.*` | Connects to BLE peripherals and receives notifications |
| `SHT40Handler.*` | Reads temperature & humidity from SHT40 sensor |
| `SPIMasterHandler.*` | Sends formatted data to SPI Slave |

---

### ESP32_WiFi (Gateway + SPI Slave)

| File | Purpose |
|----|----|
| `ESP32_WiFi.ino` | Initializes Wi‑Fi, MQTT, and SPI Slave |
| `SPISlaveHandler.*` | Receives data from SPI Master |
| `WiFiHandler.*` | Handles Wi‑Fi connection and MQTT publishing |

---

## ✨ Key Features

- Modular firmware design (BLE / SPI / Wi‑Fi isolated)
- Reliable SPI Master–Slave communication
- BLE Central using **NimBLE** (low memory footprint)
- SHT40 high‑precision temperature & humidity sensor
- MQTT cloud publishing
- Scalable for multiple BLE nodes
- Interview‑ready, production‑style structure

---

## 🛠 Technologies Used

- **ESP32**
- **Embedded C / C++**
- **BLE (NimBLE)**
- **SPI (Master–Slave)**
- **I2C**
- **Wi‑Fi (STA mode)**
- **MQTT (PubSubClient)**
- **SHT40 Sensor**

---

## 🚀 Use Cases

- Industrial sensor gateways
- Smart agriculture monitoring
- IoT edge‑to‑cloud bridges
- Distributed sensor networks
- Embedded firmware architecture demos

---

## 👤 Author

**Edagottu Janardhana**  
Firmware / Embedded Systems Engineer  

---

## 📄 License
This project is provided for educational and development purposes.
