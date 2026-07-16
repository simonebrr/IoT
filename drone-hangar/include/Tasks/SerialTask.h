#ifndef SERIAL_TASK_H
#define SERIAL_TASK_H

#include "Task.h"

class SerialTask : public Task {
 public:
  void init() override;
  void execute() override;
  unsigned long getInterval() override;
};

#endif