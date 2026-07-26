#include "Protocols/SerialProtocol.h"

SerialProtocol::SerialProtocol() {
  this->bufferIndex = 0;
  this->msgReady = false;
  memset(buffer, 0, BUFFER_SIZE);
}

void SerialProtocol::init() { Serial.begin(SERIAL_BAUD); }

void SerialProtocol::update() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    if (c == '\n') {
      buffer[bufferIndex] = '\0';
      msgReady = true;
      bufferIndex = 0;
    } else if (bufferIndex < BUFFER_SIZE - 1) {
      buffer[bufferIndex++] = c;
    }
  }
}

bool SerialProtocol::isMsgReady() { return this->msgReady; }

char* SerialProtocol::getCmd() {
  this->msgReady = false;
  return this->buffer;
}

void SerialProtocol::sendStatus(int mode, int valvePercent) {
  char payload[64];
  snprintf(payload, sizeof(payload), "STATUS:%d:%d\n", mode, valvePercent);
  Serial.print(payload);
}

void SerialProtocol::sendSensorData(int potValue, bool btnPressed) {
  char payload[64];
  snprintf(payload, sizeof(payload), "SENSOR:%d:%d\n", potValue,
           btnPressed ? 1 : 0);
  Serial.print(payload);
}