#ifndef LCD_DISPLAY_H
#define LCD_DISPLAY_H

#include <LiquidCrystal_I2C.h>

class LcdDisplay {
  LiquidCrystal_I2C lcd;
  String currentMsg;

 public:
  LcdDisplay(uint8_t address);
  void init();
  void showMessage(const String& msg);
};

#endif
