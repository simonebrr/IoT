#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include "Task.h"

class TaskScheduler {
  static const int MAX_TASKS = 10;
  Task* tasks[MAX_TASKS];
  int nTasks;
  int basePeriod;
  unsigned long lastTickTime;

 public:
  void init(int basePeriod);
  void addTask(Task* task);
  void schedule();
};

#endif
