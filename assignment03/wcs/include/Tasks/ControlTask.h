#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H

#include <Arduino.h>

#include "../Actuators/ServoMotor.h"
#include "../Protocols/SerialProtocol.h"
#include "../Sensors/Button.h"
#include "../Sensors/Potentiometer.h"
#include "../config.h"
#include "Task.h"

class ControlTask : public Task {
 private:
  ServoMotor* servo;
  Potentiometer* potentiometer;
  Button* button;
  SerialProtocol* serialProtocol;

  int currentMode;
  int targetAngle;

 public:
  ControlTask(unsigned long interval, ServoMotor* servoMotor,
              Potentiometer* pot, Button* btn, SerialProtocol* serial);

  void init() override;
  void execute() override;

  void setMode(int mode) { this->currentMode = mode; }
  int getMode() { return this->currentMode; }
  int getTargetAngle() { return this->targetAngle; }

 private:
  void handleManualMode();
  void handleAutomaticMode();
  void updateServo();
  void sendStatusUpdate();
};

#endif