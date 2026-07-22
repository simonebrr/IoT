#ifndef TMS_CONFIG_H
#define TMS_CONFIG_H

#define WIFI_SSID "YOUR_SSID"
#define WIFI_PASS "YOUR_PASSWORD"

#define MQTT_SERVER "192.168.1.100"
#define MQTT_PORT 1883
#define MQTT_USER "user"
#define MQTT_PASS "pass"
#define MQTT_CLIENT_ID "ESP32-TMS"
#define MQTT_TOPIC_WATER_LEVEL "tms/water_level"

#define SONAR_TRIG 5
#define SONAR_ECHO 18
#define LED_GREEN 2
#define LED_RED 4

#define PUBLISH_INTERVAL 5000  // ms
#define WIFI_TIMEOUT 20000     // ms

#define MQTT_CONNECTED 1
#define MQTT_DISCONNECTED 0

#endif