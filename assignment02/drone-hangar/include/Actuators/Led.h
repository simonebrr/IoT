#ifndef LED_H
#define LED_H

class Led {
  int pin;
  bool on;

 public:
  Led(int pin);
  void switchOn();
  void switchOff();
  void toggle();
};

#endif
