#ifndef CONTROL_TASK_H
#define CONTROL_TASK_H

#include <Arduino.h>

#include "../Actuators/LcdDisplay.h"
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
  LcdDisplay* lcd;

  int currentMode;
  int targetAngle;
  int valvePercent;      // apertura logica corrente (0-100), sorgente di verita'
  int lastPotRaw;
  bool lastPressed;
  int cusValvePercent;   // ultima apertura comandata dal CUS (0-100)
  bool cusValveChanged;  // il CUS ha appena inviato un nuovo VALVE

 public:
  ControlTask(unsigned long interval, ServoMotor* servoMotor,
              Potentiometer* pot, Button* btn, SerialProtocol* serial,
              LcdDisplay* display);

  void init() override;
  void execute() override;

  void setMode(int mode) { this->currentMode = mode; }
  int getMode() { return this->currentMode; }
  int getTargetAngle() { return this->targetAngle; }

 private:
  void processCommand(char* cmd);
  void handleManualMode();
  void handleAutomaticMode();
  void updateServo();
  void sendStatusUpdate();
};

#endif