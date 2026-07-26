#include <Arduino.h>

#include "Actuators/LcdDisplay.h"
#include "Actuators/ServoMotor.h"
#include "Protocols/SerialProtocol.h"
#include "Sensors/Button.h"
#include "Sensors/Potentiometer.h"
#include "Tasks/ControlTask.h"
#include "Tasks/TaskScheduler.h"
#include "config.h"

TaskScheduler scheduler;
Potentiometer potentiometer(POTENTIOMETER_PIN);
ServoMotor servo(SERVO_PIN);
Button button(BUTTON_PIN);
LcdDisplay lcd;
SerialProtocol serialProtocol;
ControlTask* controlTask;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  servo.init();
  potentiometer.init();
  button.init();
  lcd.init();
  serialProtocol.init();

  controlTask = new ControlTask(CONTROL_INTERVAL, &servo, &potentiometer,
                                &button, &serialProtocol, &lcd);
  scheduler.addTask(controlTask);
  scheduler.initAll();
}

void loop() {
  scheduler.runAll();
  delay(10);
}