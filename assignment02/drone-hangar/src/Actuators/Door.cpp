#include "Actuators/Door.h"

#include <Arduino.h>

#include "config.h"

Door::Door(int pin) {
  this->pin = pin;
  this->opened = false;
}

void Door::init() {
  servo.attach(pin);
  servo.write(DOOR_CLOSED_ANGLE);
}

void Door::open() {
  servo.write(DOOR_OPEN_ANGLE);
  this->opened= true;
}

void Door::close() {
  servo.write(DOOR_CLOSED_ANGLE);
  this->opened = false;
}

bool Door::isOpen() { return this->opened; }
