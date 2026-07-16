#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include "Task.h"

class TaskScheduler {
 private:
  static const int MAX_TASKS = 5;
  Task* tasks[MAX_TASKS];
  unsigned long lastExecution[MAX_TASKS];
  int taskCount;

 public:
  TaskScheduler();
  void addTask(Task* task);
  void executeTasks();
};

#endif