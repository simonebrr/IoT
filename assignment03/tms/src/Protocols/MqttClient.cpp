#include "../../include/Protocols/MqttClient.h"

MqttClient::MqttClient() : client(wifiClient) {
  this->connected = false;
  this->lastReconnectAttempt = 0;
}

void MqttClient::init() {
  setupWifi();

  client.setServer(MQTT_SERVER, MQTT_PORT);
  connect();
}

void MqttClient::setupWifi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(WIFI_SSID, WIFI_PASS);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("Connection failed");
  }
}

bool MqttClient::connect() {
  if (client.connect(MQTT_CLIENT_ID, MQTT_USER, MQTT_PASS)) {
    this->connected = true;
    subscribe("tms/control");
    return true;
  } else {
    Serial.println(client.state());
    this->connected = false;
    return false;
  }
}

bool MqttClient::isConnected() { return this->connected; }

void MqttClient::reconnect() {
  unsigned long now = millis();
  if (now - lastReconnectAttempt > 5000) {
    lastReconnectAttempt = now;

    if (WiFi.status() != WL_CONNECTED) {
      setupWifi();
    }

    if (WiFi.status() == WL_CONNECTED && !client.connected()) {
      connect();
    }
  }
}

void MqttClient::subscribe(const char* topic) {
  if (client.connected()) {
    client.subscribe(topic);
    Serial.println(topic);
  }
}

void MqttClient::loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}