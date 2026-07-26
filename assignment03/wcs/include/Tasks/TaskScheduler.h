#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <Arduino.h>

#include "Task.h"

#define MAX_TASKS 3

class TaskScheduler {
 private:
  Task* tasks[MAX_TASKS];
  int taskCount;

 public:
  TaskScheduler();

  void addTask(Task* task);
  void removeTask(Task* task);
  void initAll();
  void runAll();
  void stopAll();

  int getTaskCount() { return this->taskCount; }
  Task* getTask(int index) {
    return (index < taskCount) ? tasks[index] : nullptr;
  }
};

#endif
