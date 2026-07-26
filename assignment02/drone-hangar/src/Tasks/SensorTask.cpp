#include "Tasks/SensorTask.h"

SensorTask::SensorTask(Sonar* sonar, Pir* pir, TempSensor* tempSensor) {
  this->sonar = sonar;
  this->pir = pir;
  this->tempSensor = tempSensor;
  distance = 0.0f;
  dronePresent = false;
  temperature = 20.0f;
}

void SensorTask::tick() {
  distance = sonar->getDistance();
  dronePresent = pir->isDetected();
  temperature = tempSensor->getTemperature();
}
