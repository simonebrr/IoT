#ifndef BLINK_TASK_H
#define BLINK_TASK_H

#include "Actuators/Led.h"
#include "Task.h"

class BlinkTask : public Task {
  Led* led;
  bool blinking;

 public:
  BlinkTask(Led* led);
  void setBlinking(bool blinking);
  void tick() override;
};

#endif
