#include "../../include/FSM/StateMachine.h"

#include <Arduino.h>

#include "../../include/FSM/DroneState.h"

StateMachine::StateMachine() {
  currentState = nullptr;
  idleState = nullptr;
  armedState = nullptr;
  takeoffState = nullptr;
  landingState = nullptr;
  emergencyState = nullptr;
}

StateMachine::~StateMachine() {
  delete idleState;
  delete armedState;
  delete takeoffState;
  delete landingState;
  delete emergencyState;
}

void StateMachine::init() {
  idleState = new IdleState();
  armedState = new ArmedState();
  takeoffState = new TakeoffState();
  landingState = new LandingState();
  emergencyState = new EmergencyState();

  currentState = idleState;
  currentState->enter();
}

void StateMachine::update() {
  if (currentState != nullptr) {
    currentState->execute();
  }
}

void StateMachine::changeState(State* newState) {
  if (currentState != nullptr) {
    currentState->exit();
  }
  currentState = newState;
  if (currentState != nullptr) {
    currentState->enter();
  }
}

void StateMachine::handleEvent(int event) {
  if (event == 4) {
    changeState(emergencyState);
    return;
  }

  if (currentState == idleState && event == 1) {
    changeState(armedState);
  } else if (currentState == armedState && event == 2) {
    changeState(takeoffState);
  } else if (currentState == armedState && event == 0) {
    changeState(idleState);
  } else if (currentState == takeoffState && event == 3) {
    changeState(landingState);
  } else if (currentState == landingState) {
    changeState(idleState);
  }
}

State* StateMachine::getCurrentState() { return currentState; }

DroneStateType StateMachine::getCurrentStateType() {
  if (currentState == idleState) return STATE_IDLE;
  if (currentState == armedState) return STATE_ARMED;
  if (currentState == takeoffState) return STATE_TAKEOFF;
  if (currentState == landingState) return STATE_LANDING;
  if (currentState == emergencyState) return STATE_EMERGENCY;
  return STATE_IDLE;
}