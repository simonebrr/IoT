#include <Arduino.h>

#include "../config.h"
#include "Protocols/MqttClient.h"
#include "Sensors/Sonar.h"
#include "Tasks/MonitorTask.h"
#include "Tasks/TaskScheduler.h"

TaskScheduler scheduler;
Sonar sonar(SONAR_TRIG, SONAR_ECHO);
MqttClient mqtt;
MonitorTask* monitorTask;

void setup() {
  Serial.begin(9600);
  delay(1000);

  sonar.init();
  mqtt.init();

  monitorTask = new MonitorTask(SAMPLE_INTERVAL, &sonar, &mqtt);
  scheduler.addTask(monitorTask);
  scheduler.initAll();
}

void loop() {
  mqtt.loop();
  scheduler.runAll();
  delay(10);
}