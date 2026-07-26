#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

#include "../config.h"

class LcdDisplay {
 private:
  LiquidCrystal_I2C lcd;
  int lastMode;
  int lastPercent;

 public:
  LcdDisplay();
  void init();
  void update(int mode, int valPercent);

 private:
  const char* modeName(int mode);
};

#endif