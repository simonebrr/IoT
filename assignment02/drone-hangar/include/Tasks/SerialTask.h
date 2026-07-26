#ifndef SERIAL_TASK_H
#define SERIAL_TASK_H

#include "ControlTask.h"
#include "SensorTask.h"
#include "Task.h"
#include "TemperatureTask.h"

class SerialTask : public Task {
  ControlTask* control;
  SensorTask* sensors;
  TemperatureTask* tempMonitor;

  char buffer[32];
  unsigned int bufLen;
  unsigned long lastTelemetry;

  void processLine(const char* line);

 public:
  SerialTask(ControlTask* control, SensorTask* sensors,
             TemperatureTask* tempMonitor);
  void tick() override;
};

#endif
