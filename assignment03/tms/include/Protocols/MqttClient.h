#ifndef MQTT_CLIENT_H
#define MQTT_CLIENT_H

#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFi.h>

#include "../config.h"

class MqttClient {
 private:
  WiFiClient wifiClient;
  PubSubClient client;
  bool connected;
  unsigned long lastReconnectAttempt;

 public:
  MqttClient();

  void init();
  bool connect();
  bool isConnected();
  void reconnect();
  void publish(const char* topic, const char* payload);
  void subscribe(const char* topic);
  void loop();

 private:
  void setupWifi();
  void onMessageReceived(char* topic, byte* payload, unsigned long lenght);
};

#endif