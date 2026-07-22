#include <Arduino.h>

#include "../include/Actuators/LcdDisplay.h"
#include "../include/Actuators/ServoMotor.h"
#include "../include/Protocols/SerialProtocol.h"
#include "../include/Sensors/Button.h"
#include "../include/Sensors/Potentiometer.h"
#include "../include/Tasks/ControlTask.h"
#include "../include/Tasks/TaskScheduler.h"
#include "config.h"

TaskScheduler scheduler;
ServoMotor servo(SERVO_PIN);
Potentiometer potentiometer(POTENTIOMETER_PIN);
Button button(BUTTON_PIN);
SerialProtocol serialProtocol;
ControlTask* controlTask;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  servo.init();
  potentiometer.init();
  button.init();
  serialProtocol.init();
  controlTask = new ControlTask(CONTROL_INTERVAL, &servo, &potentiometer,
                                &button, &serialProtocol);
  scheduler.addTask(controlTask);

  scheduler.initAll();
}

void loop() {
  scheduler.runAll();
  delay(10);
}