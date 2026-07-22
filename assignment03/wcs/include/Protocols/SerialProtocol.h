#ifndef SERIAL_PROTOCOL_H
#define SERIAL_PROTOCOL_H

#include <Arduino.h>

#include "../config.h"

#define BUFFER_SIZE 64

class SerialProtocol {
 private:
  char buffer[BUFFER_SIZE];
  int bufferIndex;
  bool messageReady;

 public:
  SerialProtocol();

  void init();
  void update();
  bool isMessageReady();
  char* getCommand();

  void sendResponse(const char* response);
  void sendSensorData(float pot, bool button);
  void sendStatus(int mode, int servoAngle);

 private:
  void parseMessage();
  void clearBuffer();
};

#endif