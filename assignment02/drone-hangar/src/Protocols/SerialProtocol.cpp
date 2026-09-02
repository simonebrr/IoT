#include "Protocols/SerialProtocol.h"

#include <Arduino.h>
#include <string.h>

const char* SerialProtocol::CMD_TAKEOFF = "CMD:TAKEOFF";
const char* SerialProtocol::CMD_LAND = "CMD:LAND";
const char* SerialProtocol::CMD_RESET = "CMD:RESET";

bool SerialProtocol::isCommand(const char* line, const char* cmd) {
  return strcmp(line, cmd) == 0;
}

void SerialProtocol::sendTelemetry(const char* state, float temperature,
                                   float distance, bool preAlarm, bool alarm,
                                   bool pir) {
  Serial.print(F(",STATE:"));
  Serial.print(state);
  Serial.print(F(",TEMP:"));
  Serial.print(temperature, 1);
  Serial.print(F(",DIST:"));
  Serial.print(distance, 1);
  Serial.print(F(",PREALARM:"));
  Serial.print(preAlarm ? 1 : 0);
  Serial.print(F(",ALARM:"));
  Serial.print(alarm ? 1 : 0);
  Serial.print(F(",PIR:"));
  Serial.println(pir ? 1 : 0);
}
