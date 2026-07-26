#include "Sensors/Sonar.h"

Sonar::Sonar(int trig, int echo) {
  this->trigPin = trig;
  this->echoPin = echo;
  this->lastDistance = 0.0f;
}

void Sonar::init() {
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

float Sonar::readDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH, 30000);
  if (duration == 0) return lastDistance;

  lastDistance = calculateDistance(duration);
  return lastDistance;
}

float Sonar::calculateDistance(long duration) {
  return duration * 0.0343f / 2.0f;
}