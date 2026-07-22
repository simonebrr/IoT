#include "../../include/Tasks/Task.h"

Task::Task(unsigned long interval) {
  this->interval = interval;
  this->lastExecution = 0;
  this->enabled = true;
}

Task::~Task() {}

void Task::run() {
  if (!enabled) return;

  unsigned long now = millis();
  if (now - lastExecution >= interval) {
    execute();
    lastExecution = now;
  }
}

void Task::setEnable(bool en) { this->enabled = en; }

void Task::setInteraval(unsigned long ms) { this->interval = ms; }