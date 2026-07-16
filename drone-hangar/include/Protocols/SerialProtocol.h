#ifndef SERIAL_PROTOCOL_H
#define SERIAL_PROTOCOL_H

#include <Arduino.h>
#include <string.h>

class SerialProtocol {
 public:
  static const char* CMD_ARM;
  static const char* CMD_TAKEOFF;
  static const char* CMD_LAND;
  static const char* CMD_EMERGENCY;
  static const char* CMD_DISARM;

  static void sendTelemtry(float temp, float humidity, const char* state,
                           int battery) {
    Serial.print("TEMP:");
    Serial.print(temp);
    Serial.print(",HUMIDITY:");
    Serial.print(humidity);
    Serial.print(",STATE:");
    Serial.print(state);
    Serial.print(",BATTERY:");
    Serial.println(battery);
  }

  static bool isCommand(const char* cmd, const char* expected) {
    return strcmp(cmd, expected) == 0;
  }
};

const char* SerialProtocol::CMD_ARM = "CMD:ARM";
const char* SerialProtocol::CMD_TAKEOFF = "CMD:TAKEOFF";
const char* SerialProtocol::CMD_LAND = "CMD:LAND";
const char* SerialProtocol::CMD_EMERGENCY = "CMD:EMERGENCY";
const char* SerialProtocol::CMD_DISARM = "CMD:DISARM";

#endif