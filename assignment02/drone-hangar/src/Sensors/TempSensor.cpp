#include "Sensors/TempSensor.h"

#include <Arduino.h>

TempSensor::TempSensor(int pin) { this->pin = pin; }

float TempSensor::getTemperature() {
  int raw = analogRead(pin);
  float volts = raw * (5.0f / 1023.0f);
  return volts * 100.0f;
}
