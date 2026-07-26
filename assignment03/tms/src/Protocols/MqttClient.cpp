#include "Protocols/MqttClient.h"

MqttClient::MqttClient() : client(wifiClient) {
  this->connected = false;
  this->lastReconnectAttempt = 0;
}

void MqttClient::init() {
  setupWiFi();
  client.setServer(MQTT_SERVER, MQTT_PORT);
}

void MqttClient::setupWiFi() {
  WiFi.begin(WIFI_SSID, WIFI_PASS);

  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 20000) {
    delay(500);
  }

  connect();
}

bool MqttClient::connect() {
  if (client.connect(MQTT_CLIENT_ID)) {
    this->connected = true;
    return true;
  }
  this->connected = false;
  return false;
}

void MqttClient::reconnect() {
  unsigned long now = millis();
  if (now - lastReconnectAttempt > 5000) {
    lastReconnectAttempt = now;
    if (WiFi.status() != WL_CONNECTED)
      setupWiFi();
    else
      connect();
  }
}

bool MqttClient::isConnected() { return client.connected(); }

void MqttClient::publish(const char* topic, const char* payload) {
  if (client.connected()) {
    client.publish(topic, payload);
  }
}

void MqttClient::loop() {
  if (!client.connected()) reconnect();
  client.loop();
}