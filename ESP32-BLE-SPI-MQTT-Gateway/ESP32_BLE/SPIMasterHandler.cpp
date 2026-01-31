
// ################################################################SPI WITHOUT INCLUDING SHT40
#include "SPIMasterHandler.h"
#include <SPI.h>

#define HSPI_MISO   12
#define HSPI_MOSI   13
#define HSPI_SCLK   14
#define HSPI_SS     15

static const int spiClk = 500000; // 500 kHz
SPIClass *hspi = nullptr;

void SPI_init() {
  Serial.println("=== HSPI Master Init ===");

  pinMode(HSPI_SS, OUTPUT);
  digitalWrite(HSPI_SS, HIGH);

  hspi = new SPIClass(HSPI);
  hspi->begin(HSPI_SCLK, HSPI_MISO, HSPI_MOSI, HSPI_SS);
}

void SPI_send(const char *msg) {
  size_t len = strlen(msg);
  char rxBuffer[64] = {0};

  Serial.print("Sending via SPI: ");
  Serial.println(msg);

  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(HSPI_SS, LOW);

  for (size_t i = 0; i < len; i++) {
    rxBuffer[i] = hspi->transfer(msg[i]);
    delayMicroseconds(10);
  }

  digitalWrite(HSPI_SS, HIGH);
  hspi->endTransaction();

  Serial.print("Received from Slave: ");
  Serial.println(rxBuffer);
  Serial.println("---------------------------");
}
/************************************************************
 * Function: sendSPIMessage
 * Description: Sends a formatted string message over SPI to slave
 *              and prints the received response.
 ************************************************************/
void sendSPIMessage(const String &msg) {
  size_t len = msg.length();
  char rxBuffer[64] = {0};

  hspi->beginTransaction(SPISettings(spiClk, MSBFIRST, SPI_MODE0));
  digitalWrite(HSPI_SS, LOW);

  for (size_t i = 0; i < len; i++) {
    rxBuffer[i] = hspi->transfer(msg[i]);
    delayMicroseconds(10);
  }

  digitalWrite(HSPI_SS, HIGH);
  hspi->endTransaction();

  Serial.print("Sent to Slave: ");
  Serial.println(msg);
  Serial.print("Received: ");
  Serial.println(rxBuffer);
  Serial.println("-----------------------");
}

//###############################################################end*/


