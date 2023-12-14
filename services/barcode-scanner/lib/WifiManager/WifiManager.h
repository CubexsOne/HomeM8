#ifndef WifiManagerH
#define WifiManagerH
#include "DisplayManager.h"

class WifiManager {
public:
  WifiManager();
  void begin(DisplayManager);
  void loop();
private:
  void printConnecting();
  void printConnected();
};

#endif