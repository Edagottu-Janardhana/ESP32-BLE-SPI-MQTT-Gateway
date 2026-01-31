#include "BLECentralHandler.h"
#include "SHT40Handler.h"
#include "SPIMasterHandler.h"

void setup() {
  Serial.begin(115200);
  Serial.println("ESP32 Gateway Started");

  BLE_init();     // Initialize BLE Central
  SPI_init();     // Initialize HSPI Master
  SHT40_Init();
}

void loop() {
  String bleData = BLE_update();   // Check BLE notifications
  String shtData = getSHT40Data();  // e.g., "|##|TEMP:25.6|HUM:55.3|**|"


  //if (bleData.length() > 0) {
    Serial.println("Forwarding BLE data to SPI Slave...");
    SPI_send(bleData.c_str());     // Send BLE data to SPI Slave
  //}
  
  delay(1000);

  sendSPIMessage(shtData);
  delay(2000);

}
