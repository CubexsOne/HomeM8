#include <Arduino.h>
#include "MqttClient.h"

#ifndef ScannerH
#define ScannerH

class Scanner {
public:
  Scanner();
  void begin(DisplayManager, MqttClient);
  void loop();
};

#endif