#ifndef CONFIG_H
#define CONFIG_H

#define WIFI_SSID "sssss"
#define WIFI_PASS "xxxx"

#define MQTT_SERVER "192.168.178.29"
#define MQTT_PORT 1883
#define MQTT_CLIENT_ID "ESP32-TMS"
#define MQTT_TOPIC_LEVEL "tms/water_level"
#define MQTT_TOPIC_STATUS "tms/status"

#define SONAR_TRIG 5
#define SONAR_ECHO 18
#define LED_GREEN 27
#define LED_RED 26

#define SAMPLE_INTERVAL 1000
#define WIFI_TIMEOUT 20000

#define ECHO_TIMEOUT_US 25000UL
#define SOUND_SPEED_CM_US 0.0343f

#define TANK_MAX_CM 30.0f
#define L1 0.50f  // 50%
#define L2 0.75f  // 75%

#endif