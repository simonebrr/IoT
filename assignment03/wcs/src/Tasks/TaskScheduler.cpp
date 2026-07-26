#include "Tasks/TaskScheduler.h"

TaskScheduler::TaskScheduler() {
  this->taskCount = 0;
  for (int i = 0; i < MAX_TASKS; i++) {
    tasks[i] = nullptr;
  }
}

void TaskScheduler::addTask(Task* task) {
  if (taskCount >= MAX_TASKS) return;
  tasks[taskCount] = task;
  taskCount++;
}

void TaskScheduler::removeTask(Task* task) {
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i] == task) {
      tasks[i] = tasks[taskCount - 1];
      tasks[taskCount - 1] = nullptr;
      taskCount--;
      return;
    }
  }
}

void TaskScheduler::initAll() {
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i]) tasks[i]->init();
  }
}

void TaskScheduler::runAll() {
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i]) tasks[i]->run();
  }
}

void TaskScheduler::stopAll() {
  for (int i = 0; i < taskCount; i++) {
    if (tasks[i]) tasks[i]->setEn(false);
  }
}