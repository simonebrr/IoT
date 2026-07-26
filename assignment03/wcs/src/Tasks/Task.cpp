#include "../include/Tasks/Task.h"

Task::Task(unsigned long interval) {
  this->interval = interval;
  this->lastExecute = 0;
  this->en = true;
}

Task::~Task() {}

void Task::run() {
  if (!this->en) return;

  unsigned long now = millis();
  if (now - lastExecute >= interval) {
    execute();
    lastExecute = now;
  }
}

void Task::setEn(bool en) { this->en = en; }

void Task::setInterval(unsigned long ms) { this->interval = ms; }