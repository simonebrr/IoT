#include "Actuators/LcdDisplay.h"

LcdDisplay::LcdDisplay(uint8_t address) : lcd(address, 16, 2) {}

void LcdDisplay::init() {
  lcd.init();
  lcd.backlight();
}

void LcdDisplay::showMessage(const String& msg) {
  if (msg == currentMsg) {
    return;  // evita clear/print continui
  }
  currentMsg = msg;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print(msg);
}
