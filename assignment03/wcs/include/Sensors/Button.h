#ifndef BUTTON_H
#define BUTTON_H

class Button {
  static const unsigned long DEBOUNCE_MS = 50;
  int pin;
  bool lastRaw;
  bool debounced;
  unsigned long lastChangeTime;

 public:
  Button(int pin);
  void init();
  bool isPressed();
};

#endif
