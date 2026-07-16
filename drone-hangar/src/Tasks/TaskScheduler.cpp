#include "../../include/Tasks/TaskScheduler.h"

#include <Arduino.h>

TaskScheduler ::TaskScheduler() {
  taskCount = 0;
  for (int i = 0; i < MAX_TASKS; i++) {
    tasks[i] = nullptr;
    lastExecution[i] = 0;
  }
}

void TaskScheduler::addTask(Task* task) {
  if (taskCount < MAX_TASKS) {
    tasks[taskCount] = task;
    task->init();
    taskCount++;
  }
}

void TaskScheduler::executeTasks() {
  unsigned long int currentTime = millis();
  for (int i = 0; i < MAX_TASKS; i++) {
    if (tasks[i] != nullptr) {
      unsigned long interval = tasks[i]->getInterval();
      if (currentTime - lastExecution[i] >= interval) {
        tasks[i]->execute();
        lastExecution[i] = currentTime;
      }
    }
  }
}