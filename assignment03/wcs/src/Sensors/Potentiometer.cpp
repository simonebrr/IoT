#include "../../include/Sensors/Potentiometer.h"

Potentiometer::Potentiometer(int pin) {
  this->pin = pin;
  this->lastValue = 0;
}

void Potentiometer::init() { pinMode(this->pin, INPUT); }

int Potentiometer::readValue() {
  this->lastValue = analogRead(pin);
  return lastValue;
}

int Potentiometer::mapToServoAngle() {
  int rawValue = readValue();
  return map(rawValue, 0, 1023, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
}

int Potentiometer::limit(int val) { return constrain(val, 0, 1023); }