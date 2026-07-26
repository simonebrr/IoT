#include "Tasks/MonitorTask.h"

MonitorTask::MonitorTask(unsigned long interval, Sonar* sonar, MqttClient* mqtt)
    : Task(interval) {
  this->sonar = sonar;
  this->mqtt = mqtt;
  this->lastLevel = 0.0f;
}

void MonitorTask::init() {
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);
}

void MonitorTask::execute() {
  lastLevel = sonar->readDistance();
  publishLevel();
  updateLeds(mqtt->isConnected());
}

void MonitorTask::publishLevel() {
  if (!mqtt->isConnected()) return;

  char payload[32];
  snprintf(payload, sizeof(payload), "%.2f", lastLevel);
  mqtt->publish(MQTT_TOPIC_LEVEL, payload);
}

void MonitorTask::updateLeds(bool ok) {
  digitalWrite(LED_GREEN, ok ? HIGH : LOW);
  digitalWrite(LED_RED, ok ? LOW : HIGH);
}