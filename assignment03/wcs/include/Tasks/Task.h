#ifndef TASK_H
#define TASK_H

#include <Arduino.h>

class Task {
 protected:
  unsigned long lastExecute;
  unsigned long interval;
  bool en;

 public:
  Task(unsigned long inteval = 1000);
  virtual ~Task();

  virtual void init() = 0;
  virtual void execute() = 0;

  void run();
  void setEn(bool en);
  bool isEn() { return this->en; }
  void setInterval(unsigned long ms);
  unsigned long getInterval() { return this->interval; }
};

#endif