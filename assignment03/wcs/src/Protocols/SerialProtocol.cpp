#include "../../include/Protocols/SerialProtocol.h"

SerialProtocol::SerialProtocol() {
  this->bufferIndex = 0;
  this->messageReady = false;
  clearBuffer();
}

void SerialProtocol::init() { Serial.begin(SERIAL_BAUD); }

void SerialProtocol::update() {
  while (Serial.available() > 0) {
    char c = Serial.read();

    if (c == '\n') {
      buffer[bufferIndex] = '\0';
      bufferIndex = 0;
      messageReady = true;
    } else if (bufferIndex < BUFFER_SIZE - 1) {
      buffer[bufferIndex] = c;
      bufferIndex++;
    }
  }
}

bool SerialProtocol::isMessageReady() { return this->messageReady; }

char* SerialProtocol::getCommand() {
  this->messageReady = false;
  return this->buffer;
}

void SerialProtocol::sendResponse(const char* response) {
  Serial.println(response);
}

void SerialProtocol::sendSensorData(float pot, bool button) {
  char payload[64];
  snprintf(payload, sizeof(payload), "SENSOR:%.2f:%d", pot, button ? 1 : 0);
  Serial.println(payload);
}

void SerialProtocol::sendStatus(int mode, int servoAngle) {
  char payload[64];
  snprintf(payload, sizeof(payload), "STATUS:%d:%d", mode, servoAngle);
  Serial.println(payload);
}

void SerialProtocol::clearBuffer() {
  memset(buffer, 0, BUFFER_SIZE);
  bufferIndex = 0;
}