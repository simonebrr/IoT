
#ifndef CONFIG_H
#define CONFIG_H

#define PIR_PIN 2
#define SONAR_TRIG_PIN 3
#define SONAR_ECHO_PIN 4
#define L1_PIN 5
#define L2_PIN 6
#define L3_PIN 7
#define RESET_PIN 8
#define SERVO_PIN 9
#define TEMP_PIN A0

#define LCD_ADDR 0x27
#define LCD_COLS 16
#define LCD_ROWS 2

#define SERIAL_BAUD 9600

#define DOOR_CLOSED_ANGLE 0
#define DOOR_OPEN_ANGLE 90

#define SENSOR_TASK_INTERVAL 100
#define CONTROL_TASK_INTERVAL 50
#define COMM_TASK_INTERVAL 100
#define BLINK_PERIOD_MS 250

#define D1 50.0     // Drone considered outside
#define T1 3000
#define D2 10.0     // Drone considered landed
#define T2 3000
#define TEMP1 30.0  // Pre-alarm threshold
#define T3 3000
#define TEMP2 40.0  // Alarm threshold
#define T4 2000


#define DEBOUNCE_MS 50
#define TELEMETRY_PERIOD_MS 500

#endif
