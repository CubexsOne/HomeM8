#include "MqttClient.h"
#include <PubSubClient.h>
#include <WiFi.h>
#include "secrets.h"

WiFiClient wifiClient;
PubSubClient pubSubClient(wifiClient);

// Variables
const char* mqtt_server = MQTT_HOST;
const int mqtt_port = 1884;
const char* mqtt_user = MQTT_USER;
const char* mqtt_password = MQTT_PASSWORD;
const char* mqtt_read_topic = MQTT_READ_TOPIC;
const char* mqtt_write_topic = MQTT_WRITE_TOPIC;
DisplayManager mqttDM;

// Definitions
void callback(char*, byte*, unsigned int);

MqttClient::MqttClient() {}

void MqttClient::begin(DisplayManager displayManager) {
  mqttDM = displayManager;

  pubSubClient.setServer(mqtt_server, mqtt_port);
  pubSubClient.setCallback(callback);
  pubSubClient.setKeepAlive(60);
}

void MqttClient::loop() {
  if (!pubSubClient.connected()) {
    reconnect();
  }
  pubSubClient.loop();
}

void callback(char* topic, byte* payload, unsigned int length) {
  String product = "";
  for (int i = 0; i < length; i++) {
    product += (char)payload[i];
  }

  int16_t margin = 21 - product.length();
  if (margin < 0) margin = 0;
  mqttDM.printText(32, 0, 2, "Item:", true);
  mqttDM.printText(margin * 3, 24, 1, product);
}

void MqttClient::reconnect() {
  printConnecting();
  while (!pubSubClient.connected()) {
    if (pubSubClient.connect("Scanner_001_ClientID", mqtt_user, mqtt_password)) {
      printConnected();
      pubSubClient.subscribe(mqtt_read_topic);
    } else {
      Serial.println("Retrying in 5 seconds... rc: " + pubSubClient.state());
      delay(5000);
    }
  }
}

void MqttClient::sendMQTTMessage(String message) {
  if (!pubSubClient.connected()) {
    reconnect();
  }
  printScannedBarcode(message);
  pubSubClient.publish(mqtt_write_topic, message.c_str());
}

void MqttClient::printConnecting() {
  mqttDM.printText(24, 0, 3, "MQTT:", true);
  mqttDM.printText(8, 32, 2, "Connecting");
  Serial.println("Connecting to MQTT-Broker...");
}

void MqttClient::printConnected() {
  mqttDM.printText(24, 0, 3, "MQTT:", true);
  mqttDM.printText(8, 32, 2, "Connected!");
  Serial.println("MQTT-Broker connected!");
}

void MqttClient::printScannedBarcode(String barcode) {
  mqttDM.printText(16, 0, 2, "Barcode:", true);
  int16_t margin = 21 - barcode.length();
  if (margin < 0) margin = 0;
  mqttDM.printText(margin * 3, 24, 1, barcode);
}