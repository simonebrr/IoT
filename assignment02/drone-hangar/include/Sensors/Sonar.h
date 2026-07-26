#ifndef SONAR_H
#define SONAR_H

class Sonar {
  static const unsigned long TIMEOUT_US = 30000;  // ~5m andata+ritorno
  int trigPin;
  int echoPin;

 public:
  static constexpr float MAX_DISTANCE = 999.0f;

  Sonar(int trigPin, int echoPin);
  float getDistance();  // cm
};

#endif
