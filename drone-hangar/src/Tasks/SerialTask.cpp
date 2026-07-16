#include "../../include/Tasks/SerialTask.h"

#include <Arduino.h>

#include "../../include/FSM/DroneState.h"
#include "../../include/FSM/StateMachine.h"
#include "../../include/Tasks/SensorTask.h"
#include "../../include/config.h"

extern SensorTask sensorTask;
extern StateMachine fsm;

void SerialTask::init() {}

void SerialTask::execute() {
  float temp = sensorTask.getTemperature();
  float humidity = sensorTask.getHumidity();
  int battery = 85;

  DroneStateType state = fsm.getCurrentStateType();

  String stateStr = "IDLE";
  if (state == STATE_ARMED)
    stateStr = "ARMED";
  else if (state == STATE_TAKEOFF)
    stateStr = "TAKEOFF";
  else if (state == STATE_LANDING)
    stateStr = "LANDING";
  else if (state == STATE_EMERGENCY)
    stateStr = "EMERGENCY";

  Serial.print("TEMP:");
  Serial.print(temp);
  Serial.print(",HUMIDITY:");
  Serial.print(humidity);
  Serial.print(",STATE:");
  Serial.print(stateStr);
  Serial.print(",BATTERY:");
  Serial.println(battery);
}

unsigned long SerialTask::getInterval() { return SERIAL_TASK_INTERVAL; }