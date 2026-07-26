#include "Actuators/ServoMotor.h"

ServoMotor::ServoMotor(int pin) {
  this->pin = pin;
  this->currentAngle = 0;
}

void ServoMotor::init() {
  servo.attach(pin);
  servo.write(0);
}

void ServoMotor::setAngle(int angle) {
  this->currentAngle = constrain(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
  servo.write(this->currentAngle);
}