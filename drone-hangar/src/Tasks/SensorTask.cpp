#include "../../include/Tasks/SensorTask.h"

#include <Arduino.h>

#include "../../include/config.h"

void SensorTask::init() {
  temperature = 0.0;
  humidity = 0.0;
  Serial.println("sensor init");
}

void SensorTask::execute() {
  temperature = 25.5;
  humidity = 60.2;
}

unsigned long SensorTask::getInterval() { return SENSOR_TASK_INTERVAL; }

float SensorTask::getTemperature() { return temperature; }

float SensorTask::getHumidity() { return humidity; }