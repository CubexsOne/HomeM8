#include "DisplayManager.h"
#include <Adafruit_SSD1306.h>
#include <Wire.h>

// Variables
#define SCREEN_ADDRESS 0x3C
Adafruit_SSD1306 oled(128, 64, &Wire, -1);
// auto-disable
bool isEnabled = true;
long timeOnEnable = 0;
int timeToDim = 3000;

// Definitions
void initialize();
void disableDisplay();

DisplayManager::DisplayManager() {}

void DisplayManager::begin() {
  oled.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS);
  oled.setTextWrap(true);
  initialize();
}

void DisplayManager::loop() {
  if (isEnabled && (timeOnEnable + timeToDim < millis())) {
    disableDisplay();
  }
}

void initialize() {
  oled.clearDisplay();
  oled.display();
}

void disableDisplay() {
  isEnabled = false;
  oled.clearDisplay();
  oled.display();
}

void DisplayManager::printText(int16_t x, int16_t y, uint8_t textSize, String text, boolean shouldClear) {
  isEnabled = true;
  timeOnEnable = millis();

  if (shouldClear) {
    oled.clearDisplay();
  }
  oled.setCursor(x, y);
  oled.setTextSize(textSize);
  oled.setTextColor(WHITE);
  oled.print(text);
  oled.display();
}