#ifndef TASK_H
#define TASK_H

#include <Arduino.h>

class Task {
 protected:
  unsigned long lastExecution;
  unsigned long interval;
  bool enabled;

 public:
  Task(unsigned long interval = 1000);
  virtual ~Task();

  virtual void init() = 0;
  virtual void execute() = 0;

  void run();
  void setEnable(bool en);
  bool isEnabled() { return this->enabled; }
  void setInteraval(unsigned long ms);
  unsigned long getInterval() { return this->interval; }
};

#endif