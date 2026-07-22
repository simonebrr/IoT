#include <Arduino.h>

#include "../include/Protocols/MqttClient.h"
#include "../include/Sensors/Sonar.h"
#include "../include/Tasks/MqttPublishTask.h"
#include "../include/Tasks/TaskScheduler.h"
#include "config.h"

TaskScheduler scheduler;
Sonar sonar(SONAR_TRIG, SONAR_ECHO);
MqttClient mqttClient;
MqttPublishTask* publishTask;

void setup() {
  Serial.begin(9600);
  delay(1000);

  Serial.println("TMS - Tank Monitoring System");

  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_RED, OUTPUT);
  digitalWrite(LED_GREEN, LOW);
  digitalWrite(LED_RED, HIGH);

  sonar.init();
  mqttClient.init();

  publishTask = new MqttPublishTask(PUBLISH_INTERVAL, &mqttClient, &sonar);
  scheduler.addTask(publishTask);
}

void loop() {
  mqttClient.loop();
  if (mqttClient.isConnected()) {
    digitalWrite(LED_GREEN, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    digitalWrite(LED_GREEN, LOW);
    digitalWrite(LED_RED, HIGH);
  }

  scheduler.runAll();

  delay(10);
}