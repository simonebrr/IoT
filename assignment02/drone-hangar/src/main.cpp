#include <Arduino.h>

#include "Actuators/Door.h"
#include "Actuators/LcdDisplay.h"
#include "Actuators/Led.h"
#include "Sensors/Button.h"
#include "Sensors/Pir.h"
#include "Sensors/Sonar.h"
#include "Sensors/TempSensor.h"
#include "Tasks/BlinkTask.h"
#include "Tasks/ControlTask.h"
#include "Tasks/SensorTask.h"
#include "Tasks/SerialTask.h"
#include "Tasks/TaskScheduler.h"
#include "Tasks/TemperatureTask.h"
#include "config.h"

Led l1(L1_PIN);
Led l2(L2_PIN);
Led l3(L3_PIN);
Button resetButton(RESET_PIN);
Pir pir(PIR_PIN);
Sonar sonar(SONAR_TRIG_PIN, SONAR_ECHO_PIN);
TempSensor tempSensor(TEMP_PIN);
Door door(SERVO_PIN);
LcdDisplay lcd(LCD_ADDR);

SensorTask sensorTask(&sonar, &pir, &tempSensor);
TemperatureTask temperatureTask(&sensorTask);
BlinkTask blinkTask(&l2);
ControlTask controlTask(&sensorTask, &temperatureTask, &door, &l1, &l3,
                        &blinkTask, &lcd, &resetButton);
SerialTask serialTask(&controlTask, &sensorTask, &temperatureTask);
TaskScheduler scheduler;

void setup() {
  Serial.begin(SERIAL_BAUD);
  door.init();
  lcd.init();

  scheduler.init(10);

  sensorTask.init(SENSOR_TASK_INTERVAL);
  temperatureTask.init(SENSOR_TASK_INTERVAL);
  controlTask.init(CONTROL_TASK_INTERVAL);
  blinkTask.init(BLINK_PERIOD_MS);
  serialTask.init(TELEMETRY_PERIOD_MS);

  scheduler.addTask(&sensorTask);
  scheduler.addTask(&temperatureTask);
  scheduler.addTask(&controlTask);
  scheduler.addTask(&blinkTask);
  scheduler.addTask(&serialTask);

  controlTask.start();
}

void loop() { scheduler.schedule(); }