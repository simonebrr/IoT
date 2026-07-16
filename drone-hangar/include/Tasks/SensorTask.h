#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "Task.h"

class SensorTask : public Task {
 private:
  float temperature;
  float humidity;

 public:
  void init() override;
  void execute() override;
  unsigned long getInterval() override;
  float getTemperature();
  float getHumidity();
};
#endif