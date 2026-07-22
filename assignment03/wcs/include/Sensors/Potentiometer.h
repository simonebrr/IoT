#ifndef POTENTIOMETER_H
#define POTENTIOMETER_H

#include <Arduino.h>

#include "../config.h"

class Potentiometer {
 private:
  int pin;
  int lastValue;

 public:
  Potentiometer(int potPin = POTENTIOMETER_PIN);

  void init();
  int readValue();
  int getLastValue() { return this->lastValue; }

  int mapToServoAngle();

 private:
  int limit(int val);
};

#endif