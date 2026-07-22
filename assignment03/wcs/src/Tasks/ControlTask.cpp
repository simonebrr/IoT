#include "../../include/Tasks/ControlTask.h"

ControlTask::ControlTask(unsigned long interval, ServoMotor* servoMotor,
                         Potentiometer* pot, Button* btn,
                         SerialProtocol* serial)
    : Task(interval) {
  this->servo = servoMotor;
  this->potentiometer = pot;
  this->button = btn;
  this->serialProtocol = serial;
  this->currentMode = MODE_MANUAL;
  this->targetAngle = SERVO_CLOSED;
}

void ControlTask::init() {}

void ControlTask::execute() {
  serialProtocol->update();
  if (serialProtocol->isMessageReady()) {
    char* cmd = serialProtocol->getCommand();
    if (strcmp(cmd, "AUTOMATIC") == 0) {
      currentMode = MODE_AUTOMATIC;
    } else if (strcmp(cmd, "MANUAL") == 0) {
      currentMode = MODE_MANUAL;
    } else if (strncmp(cmd, "ANGLE:", 6) == 0) {
      targetAngle = atoi(cmd + 6);
    }
  }
  if (currentMode == MODE_MANUAL) {
    handleManualMode();
  } else if (currentMode == MODE_AUTOMATIC) {
    handleAutomaticMode();
  }

  sendStatusUpdate();
}

void ControlTask::handleManualMode() {
  targetAngle = potentiometer->mapToServoAngle();
  updateServo();
}

void ControlTask::handleAutomaticMode() { updateServo(); }

void ControlTask::updateServo() { servo->setAngle(targetAngle); }

void ControlTask::sendStatusUpdate() {
  serialProtocol->sendStatus(currentMode, servo->getAngle());
}