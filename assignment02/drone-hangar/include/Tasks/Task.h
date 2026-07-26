#ifndef TASK_H
#define TASK_H

#include <Arduino.h>

class Task {
  int period;
  int timeElapsed;
  bool active;

  bool counting;
  unsigned long condStart;

 public:
  virtual ~Task() {}

  void init(int period) {
    this->period = period;
    this->timeElapsed = 0;
    this->active = true;
    this->counting = false;
  }

  bool updateAndCheckTime(int basePeriod) {
    timeElapsed += basePeriod;
    if (timeElapsed >= period) {
      timeElapsed = 0;
      return true;
    }
    return false;
  }

  bool isActive() { return active; }

  void setActive(bool a) {
    active = a;
    timeElapsed = 0;
  }

  virtual void tick() = 0;

 protected:
  /*
   * true se la condizione resta vera ininterrottamente per duration ms.
   */
  bool heldFor(bool condition, unsigned long duration) {
    if (!condition) {
      counting = false;
      return false;
    }
    if (!counting) {
      counting = true;
      condStart = millis();
    }
    return millis() - condStart >= duration;
  }

  /* da chiamare quando la FSM cambia stato */
  void resetTimer() { counting = false; }
};

#endif
