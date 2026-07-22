#include "../../include/Sensors/Button.h"

Button::Button(int buttonPin) {
  this->pin = buttonPin;
  this->lastState = LOW;
  this->lastDebounceTime = 0;
}

void Button::init() { pinMode(pin, INPUT_PULLUP); }

bool Button::isPressed() {
  bool currentState = readRaw();

  if (currentState != lastState) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > BUTTON_DEBOUNCE) {
    lastState = currentState;
  }
  return (lastState == LOW);
}

bool Button::wasPressed() {
  bool pressed = isPressed();
  if (pressed) {
    delay(50);
    return !isPressed();
  }
  return false;
}

bool Button::readRaw() { return digitalRead(pin); }