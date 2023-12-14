#include <Arduino.h>
#include "DisplayManager.h"

#ifndef MqttClientH
#define MqttClientH

class MqttClient {
public:
  MqttClient();
  void begin(DisplayManager);
  void loop();
  void sendMQTTMessage(String);
private:
  void reconnect();
  void printConnecting();
  void printConnected();
  void printScannedBarcode(String);
};

#endif