#include "Tasks/ControlTask.h"

ControlTask::ControlTask(unsigned long interval, ServoMotor* servoMotor,
                         Encoder* enc, Button* btn, SerialProtocol* serial,
                         LcdDisplay* display)
    : Task(interval),
      servo(servoMotor),
      encoder(enc),
      button(btn),
      serialProtocol(serial),
      lcd(display),
      currentMode(MODE_AUTOMATIC),
      valvePercent(0),
      lastPressed(false) {}

void ControlTask::init() {}

void ControlTask::execute() {
  serialProtocol->update();
  if (serialProtocol->isMsgReady()) {
    char* cmd = serialProtocol->getCmd();
    char* colon = strchr(cmd, ':');
    if (colon != nullptr) {
      *colon = '\0';
      int remotePercent = atoi(colon + 1);
      if (strcmp(cmd, "AUTOMATIC") == 0) {
        currentMode = MODE_AUTOMATIC;
        valvePercent = remotePercent;
      } else if (strcmp(cmd, "MANUAL") == 0) {
        currentMode = MODE_MANUAL;
        valvePercent = remotePercent;
      } else if (strcmp(cmd, "UNCONNECTED") == 0) {
        currentMode = MODE_UNCONNECTED;
      }
    }
  }

  bool pressed = button->isPressed();
  if (pressed && !lastPressed) {
    currentMode = (currentMode == MODE_MANUAL) ? MODE_AUTOMATIC : MODE_MANUAL;
  }
  lastPressed = pressed;

  // annche in auto altrimenti quando va in manual li fa tutti insieme
  int delta = encoder->consumeDelta();

  if (currentMode == MODE_MANUAL && delta != 0) {
    valvePercent = constrain(valvePercent + delta * ENCODER_STEP, 0, 100);
  }

  servo->setAngle(map(valvePercent, 0, 100, SERVO_MIN_ANGLE, SERVO_MAX_ANGLE));
  lcd->update(currentMode, valvePercent);
  serialProtocol->sendStatus(currentMode, valvePercent);
}