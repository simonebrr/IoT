#ifndef SERIAL_PROTOCOL_H
#define SERIAL_PROTOCOL_H

class SerialProtocol {
 public:
  static const char* CMD_TAKEOFF;
  static const char* CMD_LAND;
  static const char* CMD_RESET;

  static bool isCommand(const char* line, const char* cmd);
  static void sendTelemetry(const char* state, float temperature,
                            float distance, bool preAlarm, bool alarm,
                            bool pir);
};

#endif
