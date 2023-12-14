#include <Arduino.h>

#ifndef DisplayManagerH
#define DisplayManagerH

class DisplayManager {
public:
  DisplayManager();
  void begin();
  void loop();
  void printText(int16_t, int16_t, uint8_t, String, boolean = false);
};

#endif