#include "Sensors/Button.h"

#include <Arduino.h>

Button::Button(int pin) {
  this->pin = pin;
  pinMode(pin, INPUT_PULLUP);
  lastRaw = false;
  debounced = false;
  lastChangeTime = 0;
}

bool Button::isPressed() {
  bool raw = (digitalRead(pin) == LOW);
  unsigned long now = millis();
  if (raw != lastRaw) {
    lastRaw = raw;
    lastChangeTime = now;
  }
  if (now - lastChangeTime >= DEBOUNCE_MS) {
    debounced = raw;
  }
  return debounced;
}
