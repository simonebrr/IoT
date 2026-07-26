#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>

#include "../../config.h"

class Sonar {
  int trigPin;
  int echoPin;
  float lastDistance;

 public:
  Sonar(int trig = SONAR_TRIG, int echo = SONAR_ECHO);

  void init();
  float readDistance();
  float getLastDistance() { return this->lastDistance; }

 private:
  float calculateDistance(long duration);
};

#endif