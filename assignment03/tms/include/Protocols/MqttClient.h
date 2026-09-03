#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "../../config.h"

class MqttClient {
  WiFiClient wifiClient;
  PubSubClient client;
  bool connected;
  unsigned long lastReconnectAttempt;

 public:
  MqttClient();

  void init();
  void loop();
  bool isConnected();
  void publish(const char* topic, const char* payload);

 private:
  void setupWiFi();
  bool connect();
  void reconnect();
};

#endif