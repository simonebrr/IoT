#include <Arduino.h>

#include "../config.h"
#include "Actuators/LcdDisplay.h"
#include "Actuators/ServoMotor.h"
#include "Protocols/SerialProtocol.h"
#include "Sensors/Button.h"
#include "Sensors/Encoder.h"
#include "Tasks/ControlTask.h"
#include "Tasks/TaskScheduler.h"

TaskScheduler scheduler;
Encoder enc;
ServoMotor servo(SERVO_PIN);
Button button(BUTTON_PIN);
LcdDisplay lcd;
SerialProtocol serialProtocol;
ControlTask* controlTask;

void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(1000);

  servo.init();
  enc.init();
  button.init();
  lcd.init();
  serialProtocol.init();

  controlTask = new ControlTask(CONTROL_INTERVAL, &servo, &enc, &button,
                                &serialProtocol, &lcd);
  scheduler.addTask(controlTask);
  scheduler.initAll();
}

void loop() {
  enc.poll();
  scheduler.runAll();
  delay(10);
}