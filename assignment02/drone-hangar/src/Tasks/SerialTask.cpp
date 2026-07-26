#include "Tasks/SerialTask.h"

#include <Arduino.h>

#include "Protocols/SerialProtocol.h"
#include "config.h"

SerialTask::SerialTask(ControlTask* control, SensorTask* sensors,
                       TemperatureTask* tempMonitor) {
  this->control = control;
  this->sensors = sensors;
  this->tempMonitor = tempMonitor;
  bufLen = 0;
  lastTelemetry = 0;
}

void SerialTask::tick() {

  while (Serial.available() > 0) {
    char c = (char)Serial.read();
    if (c == '\n') {
      buffer[bufLen] = '\0';
      processLine(buffer);
      bufLen = 0;
    } else if (c != '\r' && bufLen < sizeof(buffer) - 1) {
      buffer[bufLen++] = c;
    }
  }

  unsigned long now = millis();
  if (now - lastTelemetry >= TELEMETRY_PERIOD_MS) {
    lastTelemetry = now;
    SerialProtocol::sendTelemetry(
        control->getStateName(), sensors->getTemperature(),
        sensors->getDistance(), tempMonitor->isPreAlarm(),
        tempMonitor->isAlarm());
  }
}

void SerialTask::processLine(const char* line) {
  if (SerialProtocol::isCommand(line, SerialProtocol::CMD_TAKEOFF)) {
    control->requestTakeoff();
  } else if (SerialProtocol::isCommand(line, SerialProtocol::CMD_LAND)) {
    control->requestLand();
  }
}
