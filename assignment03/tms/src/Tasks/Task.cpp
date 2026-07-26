#include "Tasks/Task.h"

#include <Arduino.h>

Task::Task(unsigned long interval) {
  this->interval = interval;
  this->lastExec = 0;
  this->en = true;
}

void Task::run() {
  if (!en) return;

  unsigned long now = millis();

  if (now - lastExec >= interval) {
    execute();
    lastExec = now;
  }
}