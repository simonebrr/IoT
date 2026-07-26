#ifndef TEMP_SENSOR_H
#define TEMP_SENSOR_H

class TempSensor {
  int pin;

 public:
  TempSensor(int pin);
  float getTemperature();
};

#endif
