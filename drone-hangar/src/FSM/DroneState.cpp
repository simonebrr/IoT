#include "../../include/FSM/DroneState.h"

#include <Arduino.h>

#include "../../include/config.h"

void IdleState::enter() {
  Serial.println("STATE: IDLE");
  digitalWrite(LED_ARM_PIN, LOW);
}

void IdleState::execute() {}

void IdleState::exit() { Serial.println("Leaving IDLE"); }

void ArmedState::enter() {
  Serial.println("STATE: ARMED");
  digitalWrite(LED_ARM_PIN, HIGH);
}

void ArmedState::execute() {}

void ArmedState::exit() { Serial.println("Leaving ARMED"); }

void TakeoffState::enter() {
  Serial.println("STATE: TAKEOFF");
  digitalWrite(LED_TAKEOFF_PIN, HIGH);
}

void TakeoffState::execute() {}

void TakeoffState::exit() { digitalWrite(LED_TAKEOFF_PIN, LOW); }

void LandingState::enter() { Serial.println("STATE: LANDING"); }

void LandingState::execute() {}

void LandingState::exit() { Serial.println("Landed"); }

void EmergencyState::enter() {
  Serial.println("STATE: EMERGENCY");
  digitalWrite(BUZZER_PIN, HIGH);
  digitalWrite(LED_ARM_PIN, HIGH);
  digitalWrite(LED_TAKEOFF_PIN, HIGH);
}

void EmergencyState::execute() {}

void EmergencyState::exit() {
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(LED_ARM_PIN, LOW);
  digitalWrite(LED_TAKEOFF_PIN, LOW);
}