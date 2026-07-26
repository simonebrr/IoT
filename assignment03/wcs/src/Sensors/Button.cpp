#include "Sensors/Button.h"

#include <Arduino.h>

Button::Button(int pin) {
  this->pin = pin;
  this->lastRaw = HIGH;
  this->debounced = HIGH;
  this->lastChangeTime = 0;
}

void Button::init() { pinMode(pin, INPUT_PULLUP); }

bool Button::isPressed() {
  bool raw = digitalRead(pin);

  if (raw != lastRaw) {
    lastChangeTime = millis();
    lastRaw = raw;
  }

  if ((millis() - lastChangeTime) > DEBOUNCE_MS) {
    debounced = lastRaw;
  }

  return (debounced == LOW);  // LOW = premuto (pullup)
}