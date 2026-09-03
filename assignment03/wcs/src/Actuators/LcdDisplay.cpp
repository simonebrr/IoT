#include "Actuators/LcdDisplay.h"

LcdDisplay::LcdDisplay()
    : lcd(LCD_ADDR, LCD_COLS, LCD_ROWS), lastMode(-1), lastPercent(-1) {
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

  char line[17];
  snprintf(line, sizeof(line), "Mode: %-10s", modeName(mode));
  lcd.setCursor(0, 0);
  lcd.print(line);

  snprintf(line, sizeof(line), "Valve: %3d%%    ", valPercent);
  lcd.setCursor(0, 1);
  lcd.print(line);
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