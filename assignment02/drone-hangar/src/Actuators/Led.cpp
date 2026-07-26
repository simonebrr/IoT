#include "Actuators/Led.h"

#include <Arduino.h>

Led::Led(int pin) {
  this->pin = pin;
  this->on = false;
  pinMode(pin, OUTPUT);
  digitalWrite(pin, LOW);
}

void Led::switchOn() {
  on = true;
  digitalWrite(pin, HIGH);
}

void Led::switchOff() {
  on = false;
  digitalWrite(pin, LOW);
}

void Led::toggle() {
  if (on) {
    switchOff();
  } else {
    switchOn();
  }
}
