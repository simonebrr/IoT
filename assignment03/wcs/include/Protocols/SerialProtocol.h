#ifndef SERIAL_PROTOCOL_H
#define SERIAL_PROTOCOL_H

#include <Arduino.h>

#include "../config.h"

#define BUFFER_SIZE 64

class SerialProtocol {
 private:
  char buffer[BUFFER_SIZE];
  int bufferIndex;
  bool msgReady;

 public:
  SerialProtocol();

  void init();
  void update();
  bool isMsgReady();
  char* getCmd();

  void sendResponse(const char* response);
  void sendSensorData(int pot, bool button);
  void sendStatus(int mode, int servoAngle);

 private:
  void parseMessage();
  void clsBuffer();
};

#endif