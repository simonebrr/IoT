#include "Tasks/TaskScheduler.h"

#include <Arduino.h>

void TaskScheduler::init(int basePeriod) {
  this->basePeriod = basePeriod;
  nTasks = 0;
  lastTickTime = millis();
}

void TaskScheduler::addTask(Task* task) {
  if (nTasks >= MAX_TASKS) {
    return ;
  }
  tasks[nTasks++] = task;
}

void TaskScheduler::schedule() {
  unsigned long now = millis();
  if (now - lastTickTime < (unsigned long)basePeriod) {
    return;
  }
  lastTickTime = now;
  for (int i = 0; i < nTasks; i++) {
    if (tasks[i]->isActive() && tasks[i]->updateAndCheckTime(basePeriod)) {
      tasks[i]->tick();
    }
  }
}
