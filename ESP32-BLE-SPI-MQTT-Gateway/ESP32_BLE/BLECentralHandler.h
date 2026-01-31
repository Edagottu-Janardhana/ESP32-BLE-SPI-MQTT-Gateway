#ifndef BLE_CENTRAL_HANDLER_H
#define BLE_CENTRAL_HANDLER_H

#include <Arduino.h>

void BLE_init();    // Called once in setup()
String BLE_update();  // returns received data if any

#endif
