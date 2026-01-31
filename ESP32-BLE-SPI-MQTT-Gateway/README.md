# ESP32 BLE Sensor Gateway using SPI and MQTT

## Overview
This project implements a distributed IoT gateway using two ESP32 devices.

- ESP32 (BLE Client + SPI Master) collects temperature and humidity data from an SHT40 sensor.
- Data is transmitted via SPI to a second ESP32 acting as a Wi-Fi gateway.
- The gateway publishes data to an MQTT broker for cloud monitoring.

## Architecture
ESP32 (BLE + SHT40) → SPI → ESP32 (Wi-Fi + MQTT) → Cloud

## Features
- BLE Central using NimBLE
- SHT40 Temperature & Humidity Sensor
- SPI Master–Slave Communication
- Wi-Fi MQTT Publishing
- Modular firmware architecture

## Technologies Used
- ESP32
- Embedded C/C++
- BLE (NimBLE)
- SPI, I2C
- Wi-Fi
- MQTT
- SHT40 Sensor

## Author
Edagottu Janardhana
