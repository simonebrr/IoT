#ifndef CONFIG_H
#define CONFIG_H

// Pin configurazioni
#define DHT_PIN 2
#define LED_ARM_PIN 3
#define LED_TAKEOFF_PIN 4
#define BUZZER_PIN 5
#define BUTTON_ARM_PIN 6
#define BUTTON_EMERGENCY_PIN 7

// Serial configurazione
#define BAUD_RATE 9600

// Task timing (millisecondi)
#define SENSOR_TASK_INTERVAL 2000  // Leggi sensori
#define SERIAL_TASK_INTERVAL 3000  // Comunica ogni 0.5s
#define CONTROL_TASK_INTERVAL 200  // Controlla attuatori ogni 0.2s

// FSM timing
#define FSM_UPDATE_INTERVAL 100  // Aggiorna FSM

#endif