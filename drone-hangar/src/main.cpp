#include <Arduino.h>

#include "FSM/StateMachine.h"
#include "Tasks/ControlTask.h"
#include "Tasks/SensorTask.h"
#include "Tasks/SerialTask.h"
#include "Tasks/TaskScheduler.h"
#include "config.h"

StateMachine fsm;
SensorTask sensorTask;
SerialTask serialTask;
ControlTask controlTask;
TaskScheduler scheduler;

void setup() {
  Serial.begin(BAUD_RATE);
  pinMode(LED_ARM_PIN, OUTPUT);
  pinMode(LED_TAKEOFF_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  scheduler.addTask(&sensorTask);
  scheduler.addTask(&serialTask);
  scheduler.addTask(&controlTask);
  fsm.init();
  Serial.println("Hangar pronto");
}

void loop() {
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();

    Serial.print("DEBUG: Comando ricevuto = '");
    Serial.print(cmd);
    Serial.println("'");

    if (cmd == "CMD:ARM") {
      Serial.println(">> ARM eseguito");
      fsm.handleEvent(1);
    } else if (cmd == "CMD:TAKEOFF") {
      Serial.println(">> TAKEOFF eseguito");
      fsm.handleEvent(2);
    } else if (cmd == "CMD:LAND") {
      Serial.println(">> LAND eseguito");
      fsm.handleEvent(3);
    } else if (cmd == "CMD:EMERGENCY") {
      Serial.println(">> EMERGENCY eseguito");
      fsm.handleEvent(4);
    } else if (cmd == "CMD:DISARM") {
      Serial.println(">> DISARM eseguito");
      fsm.handleEvent(0);
    }
  }

  scheduler.executeTasks();
  fsm.update();
  delay(100);
}