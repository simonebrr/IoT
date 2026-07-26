#ifndef MONITOR_TASK_H
#define MONITOR_TASK_H

#include <Arduino.h>

#include "../Protocols/MqttClient.h"
#include "../Sensors/Sonar.h"
#include "../../config.h"
#include "Task.h"

class MonitorTask : public Task {
  Sonar* sonar;
  MqttClient* mqtt;
  float lastLevel;

 public:
  MonitorTask(unsigned long interval, Sonar* sonar, MqttClient* mqtt);

  void init() override;
  void execute() override;

  float getLastLevel() { return this->lastLevel; }

 private:
  void publishLevel();
  void updateLeds(bool ok);
};

#endif