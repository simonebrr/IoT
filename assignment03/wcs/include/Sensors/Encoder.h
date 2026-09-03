#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

#include "../config.h"

class Encoder {
 public:
  Encoder();
  void init();
  void poll();
  int consumeDelta();

 private:
  int lastClk;
  volatile int delta;
};

#endif