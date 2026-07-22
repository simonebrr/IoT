#ifndef TASK_H
#define TASK_h

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
  bool isEnable();
  void setInterval(unsigned long ms);
  unsigned long getInterval();
};

#endif