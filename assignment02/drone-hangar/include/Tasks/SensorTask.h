#ifndef SENSOR_TASK_H
#define SENSOR_TASK_H

#include "Sensors/Pir.h"
#include "Sensors/Sonar.h"
#include "Sensors/TempSensor.h"
#include "Task.h"

class SensorTask : public Task {
  Sonar* sonar;
  Pir* pir;
  TempSensor* tempSensor;

  float distance;
  bool dronePresent;
  float temperature;

 public:
  SensorTask(Sonar* sonar, Pir* pir, TempSensor* tempSensor);
  void tick() override;

  float getDistance() { return distance; }
  bool isDronePresent() { return dronePresent; }
  float getTemperature() { return temperature; }
};

#endif
