#ifndef WCS_CONFIG_H
#define WCS_CONFIG_H

#define SERIAL_BAUD 9600
#define SERIAL_TIMEOUT 1000  // ms

#define SERVO_PIN 9
#define POTENTIOMETER_PIN A0
#define BUTTON_PIN 2
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 10
#define LCD_D5 8
#define LCD_D6 7
#define LCD_D7 6

#define CONTROL_INTERVAL 500  // ms
#define BUTTON_DEBOUNCE 50    // ms

#define SERVO_MIN_ANGLE 0
#define SERVO_MAX_ANGLE 90
#define SERVO_CLOSED 0
#define SERVO_OPEN 90

#define MODE_AUTOMATIC 1
#define MODE_MANUAL 0
#define MODE_UNCONNECTED 2

#endif