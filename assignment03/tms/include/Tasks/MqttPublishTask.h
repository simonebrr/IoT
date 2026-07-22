#ifndef MQTT_PUBLISH_TASK_H
#define MQTT_PUBLISH_TASK_H

#include <Arduino.h>

#include "../Protocols/MqttClient.h"
#include "../Sensors/Sonar.h"
#include "Task.h"

class MqttPublishTask : public Task {
 private:
  MqttClient* mqttClient;
  Sonar* sonar;
  float waterLevel;

 public:
  MqttPublishTask(unsigned long interval, MqttClient* mqtt, Sonar* sonarSensor);

  void init() override;
  void execute() override;

  float getWaterLevel() { return this->waterLevel; }

 private:
  void publishWaterLevel();
};

#endif