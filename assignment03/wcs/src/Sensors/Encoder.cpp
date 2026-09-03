#include "Sensors/Encoder.h"

Encoder::Encoder() : lastClk(HIGH), delta(0) {}

void Encoder::init() {
  pinMode(ENCODER_CLK, INPUT_PULLUP);
  pinMode(ENCODER_DT, INPUT_PULLUP);
  lastClk = digitalRead(ENCODER_CLK);
}

void Encoder::poll() {
  int clk = digitalRead(ENCODER_CLK);
  if (lastClk == HIGH && clk == LOW) {
    delta += (digitalRead(ENCODER_DT) == LOW) ? 1 : -1;
  }
  lastClk = clk;
}

int Encoder::consumeDelta() {
  int d = delta;
  delta = 0;
  return d;
}