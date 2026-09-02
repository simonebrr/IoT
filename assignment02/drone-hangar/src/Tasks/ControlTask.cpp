#include "Tasks/ControlTask.h"

#include "config.h"

ControlTask::ControlTask(SensorTask* sensors, TemperatureTask* tempMonitor,
                         Door* door, Led* l1, Led* l3, BlinkTask* blink,
                         LcdDisplay* lcd, Button* resetButton) {
  this->sensors = sensors;
  this->tempMonitor = tempMonitor;
  this->door = door;
  this->l1 = l1;
  this->l3 = l3;
  this->blink = blink;
  this->lcd = lcd;
  this->resetButton = resetButton;
  state = DRONE_INSIDE;
  droneInside = true;
  takeoffRequested = false;
  landRequested = false;
}

void ControlTask::start() { changeState(DRONE_INSIDE); }

bool ControlTask::operationsAllowed() {
  return !tempMonitor->isPreAlarm() && !tempMonitor->isAlarm();
}

void ControlTask::changeState(HangarState newState) {
  state = newState;
  resetTimer();

  switch (newState) {
    case DRONE_INSIDE:
      droneInside = true;
      door->close();
      l1->switchOn();
      blink->setBlinking(false);
      lcd->showMessage("DRONE INSIDE");
      break;

    case TAKING_OFF:
      door->open();
      l1->switchOff();
      blink->setBlinking(true);
      lcd->showMessage("TAKE OFF");
      break;

    case DRONE_OUTSIDE:
      droneInside = false;
      door->close();
      l1->switchOff();
      blink->setBlinking(false);
      lcd->showMessage("DRONE OUT");
      break;

    case LANDING:
      door->open();
      blink->setBlinking(true);
      lcd->showMessage("LANDING");
      break;

    case HANGAR_ALARM:
      door->close();
      l1->switchOff();
      blink->setBlinking(false);
      l3->switchOn();
      lcd->showMessage("ALARM");
      break;
  }
}

void ControlTask::tick() {
  if (tempMonitor->isAlarm() && state != HANGAR_ALARM) {
    changeState(HANGAR_ALARM);
  }

  switch (state) {
    case DRONE_INSIDE:
      if (takeoffRequested && operationsAllowed()) {
        changeState(TAKING_OFF);
      }
      break;

    case TAKING_OFF:
      if (heldFor(sensors->getDistance() > D1, T1)) {
        changeState(DRONE_OUTSIDE);
      }
      break;

    case DRONE_OUTSIDE:
      if (landRequested && sensors->isDronePresent() && operationsAllowed()) {
        changeState(LANDING);
      }
      break;

    case LANDING:
      if (heldFor(sensors->getDistance() < D2, T2)) {
        changeState(DRONE_INSIDE);
      }
      break;

    case HANGAR_ALARM:
      if (resetButton->isPressed() || resetRequested) {
        tempMonitor->reset();
        l3->switchOff();
        changeState(droneInside ? DRONE_INSIDE : DRONE_OUTSIDE);
      }
      break;
  }

  takeoffRequested = false;
  landRequested = false;
  resetRequested = false;
}

const char* ControlTask::getStateName() {
  switch (state) {
    case DRONE_INSIDE:
      return "DRONE_INSIDE";
    case TAKING_OFF:
      return "TAKE_OFF";
    case DRONE_OUTSIDE:
      return "DRONE_OUTSIDE";
    case LANDING:
      return "LANDING";
    case HANGAR_ALARM:
      return "ALARM";
  }
  return "?";
}
