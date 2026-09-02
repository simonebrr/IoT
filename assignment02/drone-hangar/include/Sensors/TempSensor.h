#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

#include <DHT.h>

class TempSensor {
  int pin;
  DHT dht;
  float lastTemp;

 public:
  TempSensor(int pin);
  void init();
  float getTemperature();
};

#endif