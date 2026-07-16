#ifndef DRONE_STATE_H
#define DRONE_STATE_H

#include "State.h"

enum DroneStateType {
  STATE_IDLE,
  STATE_ARMED,
  STATE_TAKEOFF,
  STATE_LANDING,
  STATE_EMERGENCY
};

class IdleState : public State {
 public:
  void enter() override;
  void exit() override;
  void execute() override;
};

class ArmedState : public State {
 public:
  void enter() override;
  void exit() override;
  void execute() override;
};

class TakeoffState : public State {
 public:
  void enter() override;
  void exit() override;
  void execute() override;
};

class LandingState : public State {
 public:
  void enter() override;
  void exit() override;
  void execute() override;
};

class EmergencyState : public State {
 public:
  void enter() override;
  void execute() override;
  void exit() override;
};

#endif