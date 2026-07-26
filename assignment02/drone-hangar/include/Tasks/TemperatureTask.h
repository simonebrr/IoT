#ifndef TEMPERATURE_TASK_H
#define TEMPERATURE_TASK_H

#include "SensorTask.h"
#include "Task.h"

enum TempState { TEMP_NORMAL, TEMP_PREALARM, TEMP_ALARM };

class TemperatureTask : public Task {
  SensorTask* sensors;
  TempState state;

 public:
  TemperatureTask(SensorTask* sensors);
  void tick() override;

  bool isPreAlarm() { return state == TEMP_PREALARM; }
  bool isAlarm() { return state == TEMP_ALARM; }
  void reset();
};

#endif
