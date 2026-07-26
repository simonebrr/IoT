#include "Tasks/TemperatureTask.h"

#include "config.h"

TemperatureTask::TemperatureTask(SensorTask* sensors) {
  this->sensors = sensors;
  state = TEMP_NORMAL;
}

void TemperatureTask::tick() {
  float t = sensors->getTemperature();

  switch (state) {
    case TEMP_NORMAL:
      if (heldFor(t >= TEMP1, T3)) {
        state = TEMP_PREALARM;
        resetTimer();
      }
      break;

    case TEMP_PREALARM:
      if (t < TEMP1) {
        state = TEMP_NORMAL;
        resetTimer();
      } else if (heldFor(t >= TEMP2, T4)) {
        state = TEMP_ALARM;
        resetTimer();
      }
      break;

    case TEMP_ALARM:
      // asptto il reset
      break;
  }
}

void TemperatureTask::reset() {
  state = TEMP_NORMAL;
  resetTimer();
}
