#include "Actuators/LcdDisplay.h"

LcdDisplay::LcdDisplay() : lcd(0x27, 16, 2) {
  this->lastMode = -1;
  this->lastPercent = -1;
}

void LcdDisplay::init() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("WCS Starting...");
}

void LcdDisplay::update(int mode, int valPercent) {
  if (mode == lastMode && valPercent == lastPercent) return;

  lastMode = mode;
  lastPercent = valPercent;

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Mode: ");
  lcd.print(modeName(mode));

  lcd.setCursor(0, 1);
  lcd.print("Valve: ");
  lcd.print(valPercent);
  lcd.print("%");
}

const char* LcdDisplay::modeName(int mode) {
  switch (mode) {
    case MODE_AUTOMATIC:
      return "AUTO";
    case MODE_MANUAL:
      return "MANUAL";
    case MODE_UNCONNECTED:
      return "UNCONN";
    default:
      return "UNKNOWN";
  }
}