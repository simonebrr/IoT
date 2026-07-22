#ifndef SONAR_H
#define SONAR_H

#include <Arduino.h>

#include "../config.h"

class Sonar {
 private:
  int trigPin;
  int echoPin;
  float lastDistance;

 public:
  Sonar(int trigPin = SONAR_TRIG, int echoPin = SONAR_ECHO);

  void init();
  float readDistance();
  float getLastDistance();

 private:
  float calculateDistance(long duration);
};

#endif
