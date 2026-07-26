#include "Tasks/BlinkTask.h"

BlinkTask::BlinkTask(Led* led) {
  this->led = led;
  blinking = false;
}

void BlinkTask::setBlinking(bool blinking) {
  if (this->blinking && !blinking) {
    led->switchOff();
  }
  this->blinking = blinking;
}

void BlinkTask::tick() {
  if (blinking) {
    led->toggle();
  }
}
