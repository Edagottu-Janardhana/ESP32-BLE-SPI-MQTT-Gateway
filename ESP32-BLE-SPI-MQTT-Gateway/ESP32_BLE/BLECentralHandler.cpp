/*

//################################################################################
//ble pheripheral and central without spi communication and others

#include "BLECentralHandler.h"
#include <NimBLEDevice.h>

#define MAX_NODES 6
#define SCAN_TIME 5

static NimBLEUUID serviceUUID("abcd1234-1234-1234-1234-123456789abc");
static NimBLEUUID charUUID("12345678-1234-1234-1234-123456789abc");

struct NodeInfo {
  NimBLEAdvertisedDevice* device;
  NimBLEClient* client;
  NimBLERemoteCharacteristic* characteristic;
  bool connected;
};

static NodeInfo nodes[MAX_NODES];
static int nodeCount = 0;

//********************** CALLBACK: Notifications **********************
void notifyCallback(NimBLERemoteCharacteristic* pCharacteristic,
                    uint8_t* pData, size_t length, bool isNotify) {
  NimBLEClient* client = pCharacteristic->getRemoteService()->getClient();
  String addr = client->getPeerAddress().toString().c_str();

  Serial.print("[" + addr + "] => ");
  for (size_t i = 0; i < length; i++) {
    Serial.print((char)pData[i]);
  }
  Serial.println();
}

//********************** CALLBACK: Advertised Devices **********************
class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
    if (advertisedDevice->haveName() &&
        advertisedDevice->getName().find("ESP32_Node_") != std::string::npos) {
      if (nodeCount < MAX_NODES) {
        Serial.print("Found node: ");
        Serial.println(advertisedDevice->toString().c_str());
        nodes[nodeCount++].device = advertisedDevice;
      }
    }
  }
};

//********************** Function: Connect to Node **********************
void connectToNode(NodeInfo& node) {
  node.client = NimBLEDevice::createClient();

  Serial.print("Connecting to ");
  Serial.println(node.device->getAddress().toString().c_str());

  if (!node.client->connect(node.device)) {
    Serial.println("❌ Connection failed!");
    NimBLEDevice::deleteClient(node.client);
    return;
  }

  NimBLERemoteService* remoteService = node.client->getService(serviceUUID);
  if (remoteService == nullptr) {
    Serial.println("❌ Service not found!");
    node.client->disconnect();
    NimBLEDevice::deleteClient(node.client);
    return;
  }

  node.characteristic = remoteService->getCharacteristic(charUUID);
  if (node.characteristic == nullptr) {
    Serial.println("❌ Characteristic not found!");
    node.client->disconnect();
    NimBLEDevice::deleteClient(node.client);
    return;
  }

  // Subscribe for notifications
  if (node.characteristic->canNotify()) {
    node.characteristic->subscribe(true, notifyCallback);
  }

  node.connected = true;
  Serial.print("✅ Connected and subscribed to ");
  Serial.println(node.device->getAddress().toString().c_str());
}

//********************** Function: BLE_init() **********************
void BLE_init() {
  Serial.println("🔹 ESP32 NimBLE Central: Multi-Node Collector");

  NimBLEDevice::init("ESP32_Central_Multi");
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  NimBLEScan* pScan = NimBLEDevice::getScan();

  pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pScan->setActiveScan(true);
  pScan->setInterval(45);
  pScan->setWindow(15);

  Serial.println("🔍 Scanning for BLE nodes...");
  pScan->start(SCAN_TIME, false);

  if (nodeCount == 0) {
    Serial.println("⚠️ No nodes found!");
    return;
  }

  // Connect to all found nodes
  for (int i = 0; i < nodeCount; i++) {
    connectToNode(nodes[i]);
    delay(500);
  }
}

//********************** Function: BLE_update() **********************
void BLE_update() {
  for (int i = 0; i < nodeCount; i++) {
    if (nodes[i].connected && !nodes[i].client->isConnected()) {
      Serial.print("❌ Node disconnected: ");
      Serial.println(nodes[i].device->getAddress().toString().c_str());
      nodes[i].connected = false;
    }
  }
}

//END 
//#####################################################################################################*/

#include "BLECentralHandler.h"
#include <NimBLEDevice.h>

#define MAX_NODES 6
#define SCAN_TIME 5

static NimBLEUUID serviceUUID("abcd1234-1234-1234-1234-123456789abc");
static NimBLEUUID charUUID("12345678-1234-1234-1234-123456789abc");

struct NodeInfo {
  NimBLEAdvertisedDevice* device;
  NimBLEClient* client;
  NimBLERemoteCharacteristic* characteristic;
  bool connected;
};

static NodeInfo nodes[MAX_NODES];
static int nodeCount = 0;
static String latestData = "";

/********************** CALLBACK: Notifications **********************/
void notifyCallback(NimBLERemoteCharacteristic* pCharacteristic,
                    uint8_t* pData, size_t length, bool isNotify) {
  NimBLEClient* client = pCharacteristic->getRemoteService()->getClient();
  String addr = client->getPeerAddress().toString().c_str();

  latestData = "";
  for (size_t i = 0; i < length; i++) latestData += (char)pData[i];

  Serial.print("📡 [");
  Serial.print(addr);
  Serial.print("] => ");
  Serial.println(latestData);
}

/********************** CALLBACK: Advertised Devices **********************/
class MyAdvertisedDeviceCallbacks : public NimBLEAdvertisedDeviceCallbacks {
  void onResult(NimBLEAdvertisedDevice* advertisedDevice) {
    if (advertisedDevice->haveName() &&
        advertisedDevice->getName().find("ESP32_Node_") != std::string::npos) {
      if (nodeCount < MAX_NODES) {
        Serial.print("Found node: ");
        Serial.println(advertisedDevice->toString().c_str());
        nodes[nodeCount++].device = advertisedDevice;
      }
    }
  }
};

/********************** Function: Connect to Node **********************/
void connectToNode(NodeInfo& node) {
  node.client = NimBLEDevice::createClient();

  Serial.print("Connecting to ");
  Serial.println(node.device->getAddress().toString().c_str());

  if (!node.client->connect(node.device)) {
    Serial.println("❌ Connection failed!");
    NimBLEDevice::deleteClient(node.client);
    return;
  }

  NimBLERemoteService* remoteService = node.client->getService(serviceUUID);
  if (remoteService == nullptr) {
    Serial.println("❌ Service not found!");
    node.client->disconnect();
    NimBLEDevice::deleteClient(node.client);
    return;
  }

  node.characteristic = remoteService->getCharacteristic(charUUID);
  if (node.characteristic == nullptr) {
    Serial.println("❌ Characteristic not found!");
    node.client->disconnect();
    NimBLEDevice::deleteClient(node.client);
    return;
  }

  if (node.characteristic->canNotify()) {
    node.characteristic->subscribe(true, notifyCallback);
  }

  node.connected = true;
  Serial.print("Connected to ");
  Serial.println(node.device->getAddress().toString().c_str());
}

/********************** Function: BLE_init() **********************/
void BLE_init() {
  Serial.println("🔹 Initializing NimBLE Central...");

  NimBLEDevice::init("ESP32_Central_Multi");
  NimBLEDevice::setPower(ESP_PWR_LVL_P9);
  NimBLEScan* pScan = NimBLEDevice::getScan();

  pScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pScan->setActiveScan(true);
  pScan->setInterval(45);
  pScan->setWindow(15);

  Serial.println("Scanning for BLE nodes...");
  pScan->start(SCAN_TIME, false);

  if (nodeCount == 0) {
    Serial.println("⚠️ No nodes found!");
    return;
  }

  for (int i = 0; i < nodeCount; i++) {
    connectToNode(nodes[i]);
    delay(500);
  }
}

/********************** Function: BLE_update() **********************/
String BLE_update() {
  for (int i = 0; i < nodeCount; i++) {
    if (nodes[i].connected && !nodes[i].client->isConnected()) {
      Serial.print("❌ Node disconnected: ");
      Serial.println(nodes[i].device->getAddress().toString().c_str());
      nodes[i].connected = false;
    }
  }

  String temp = latestData;
  latestData = "";  // clear after reading
  return temp;
}


