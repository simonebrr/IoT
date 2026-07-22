#ifndef SERVO_MOTOR_H
#define SERVO_MOTOR_H

#include <Arduino.h>
#include <Servo.h>

#include "../config.h"

class ServoMotor {
 private:
  Servo servo;
  int currentAngle;
  int pin;

 public:
  ServoMotor(int pin = SERVO_PIN);

  void init();
  void setAngle(int angle);
  int getAngle() { return this->currentAngle; }

  void open() { setAngle(SERVO_OPEN); }
  void close() { setAngle(SERVO_CLOSED); }

 private:
  int limit(int angle);
};

#endif