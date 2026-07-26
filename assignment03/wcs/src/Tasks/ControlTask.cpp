#include "Tasks/ControlTask.h"

ControlTask::ControlTask(unsigned long interval, ServoMotor* servoMotor,
                         Potentiometer* pot, Button* btn,
                         SerialProtocol* serial, LcdDisplay* display)
    : Task(interval) {
  this->servo = servoMotor;
  this->potentiometer = pot;
  this->button = btn;
  this->serialProtocol = serial;
  this->lcd = display;
  this->currentMode = MODE_AUTOMATIC;
  this->targetAngle = SERVO_CLOSED;
  this->lastPotRaw = 0;
  this->lastPressed = false;
}

void ControlTask::init() {}

void ControlTask::execute() {
  // Controlla bottone - toggle modalità
  bool pressed = button->isPressed();
  if (pressed && !lastPressed) {
    currentMode = (currentMode == MODE_MANUAL) ? MODE_AUTOMATIC : MODE_MANUAL;
  }
  lastPressed = pressed;

  // Leggi comandi dal CUS
  serialProtocol->update();
  if (serialProtocol->isMsgReady()) {
    char* cmd = serialProtocol->getCmd();
    if (strcmp(cmd, "AUTOMATIC") == 0) {
      currentMode = MODE_AUTOMATIC;
    } else if (strcmp(cmd, "UNCONNECTED") == 0) {
      currentMode = MODE_UNCONNECTED;
    } else if (strncmp(cmd, "ANGLE:", 6) == 0) {
      targetAngle = atoi(cmd + 6);
    }
  }
  if (currentMode == MODE_MANUAL) {
    handleManualMode();
  } else {
    handleAutomaticMode();
  }

  updateServo();
  sendStatusUpdate();
}

void ControlTask::handleManualMode() {
  targetAngle = potentiometer->mapToServoAngle();
}

void ControlTask::handleAutomaticMode() {}

void ControlTask::updateServo() { servo->setAngle(targetAngle); }

void ControlTask::sendStatusUpdate() {
  int percent = map(targetAngle, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE, 0, 100);
  lcd->update(currentMode, percent);
  serialProtocol->sendStatus(currentMode, percent);
}