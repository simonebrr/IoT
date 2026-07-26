#ifndef DOOR_H
#define DOOR_H

#include <Servo.h>

class Door {
 private:
  Servo servo;
  int pin;
  bool opened;

 public:
  Door(int pin);
  void init();
  void open();
  void close();
  bool isOpen();
};

#endif
