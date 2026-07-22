#include "../../include/Tasks/MqttPublishTask.h"

MqttPublishTask::MqttPublishTask(unsigned long interval, MqttClient* mqtt,
                                 Sonar* sonarSensor)
    : Task(interval) {
  this->mqttClient = mqttClient;
  this->sonar = sonar;
  this->waterLevel = 0.0;
}

void MqttPublishTask::init() {}

void MqttPublishTask::execute() {
  waterLevel = sonar->readDistance();
  publishWaterLevel();
}

void MqttPublishTask::publishWaterLevel() {
  if (!mqttClient->isConnected()) {
    return;
  }
  char paload[50];
  Serial.print(paload);
}