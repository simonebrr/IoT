#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include "DroneState.h"
#include "State.h"

class StateMachine {
 private:
  State* currentState;
  State* idleState;
  State* armedState;
  State* takeoffState;
  State* landingState;
  State* emergencyState;

 public:
  StateMachine();
  ~StateMachine();

  void init();
  void update();
  void changeState(State* newState);
  void handleEvent(int event);
  State* getCurrentState();
  DroneStateType getCurrentStateType();
};

#endif