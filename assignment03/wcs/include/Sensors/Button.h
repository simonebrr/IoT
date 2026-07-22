#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

#include "../config.h"

class Button {
 private:
  int pin;
  bool lastState;
  unsigned long lastDebounceTime;

 public:
  Button(int pin = BUTTON_PIN);

  void init();
  bool isPressed();
  bool wasPressed();

 private:
  bool readRaw();
};
#endif