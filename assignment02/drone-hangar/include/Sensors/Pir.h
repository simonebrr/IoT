#ifndef PIR_H
#define PIR_H

class Pir {
  int pin;

 public:
  Pir(int pin);
  bool isDetected();
};

#endif
