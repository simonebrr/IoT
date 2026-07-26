#include "Sensors/Sonar.h"

#include <Arduino.h>

Sonar::Sonar(int trigPin, int echoPin) {
  this->trigPin = trigPin;
  this->echoPin = echoPin;
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  digitalWrite(trigPin, LOW);
}

float Sonar::getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(3);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  unsigned long duration = pulseIn(echoPin, HIGH, TIMEOUT_US);
  if (duration == 0) {
    return MAX_DISTANCE;
  }

  return duration * 0.0343f / 2.0f;
}
