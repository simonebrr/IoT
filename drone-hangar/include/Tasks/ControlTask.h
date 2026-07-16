#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H

#include "Task.h"

class ControlTask : public Task {
 public:
  void init() override;
  void execute() override;
  unsigned long getInterval() override;
};

#endif