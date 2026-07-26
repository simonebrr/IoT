#include "Sensors/Potentiometer.h"

Potentiometer::Potentiometer(int pin) {
  this->pin = pin;
  this->lastValue = 0;
}

void Potentiometer::init() { pinMode(pin, INPUT); }

int Potentiometer::readValue() {
  this->lastValue = analogRead(pin);  // 0-1023
  return lastValue;
}

int Potentiometer::mapToServoAngle() {
  return map(readValue(), 0, 1023, 0, 90);
}