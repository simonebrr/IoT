#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASS "YOUR_PASSWORD"

#define MQTT_SERVER "192.168.1.100"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "ESP32-TMS"
#define MQTT_TOPIC_LEVEL "tms/water_level"
#define MQTT_TOPIC_STATUS "tms/status"

#define SONAR_TRIG D6
#define SONAR_ECHO D7
#define LED_GREEN D1
#define LED_RED D2

#define SAMPLE_INTERVAL 1000  // ms
#define WIFI_TIMEOUT 20000    // ms

#define TANK_MAX_CM 30.0f
#define L1 0.50f  // 50%
#define L2 0.75f  // 75%

#endif