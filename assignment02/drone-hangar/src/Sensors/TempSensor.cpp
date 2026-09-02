#include "Sensors/TempSensor.h"

#include <Arduino.h>

TempSensor::TempSensor(int pin) : dht(pin, DHT22) {
  this->pin = pin;
  lastTemp = 20.0f;
}

void TempSensor::init() { dht.begin(); }

float TempSensor::getTemperature() {
  float t = dht.readTemperature();
  if (!isnan(t)) {
    lastTemp = t;
  }
  return lastTemp;
}