
#include "../../include/Actuators/ServoMotor.h"

ServoMotor::ServoMotor(int pin) {
  this->pin = pin;
  this->currentAngle = SERVO_CLOSED;
}

void ServoMotor::init() {
  servo.attach(pin);
  servo.write(currentAngle);
}

void ServoMotor::setAngle(int angle) {
  this->currentAngle = limit(angle);
  servo.write(this->currentAngle);
  Serial.println(this->currentAngle);
}

int ServoMotor::limit(int angle) {
  return constrain(angle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE);
}