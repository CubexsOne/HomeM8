#include "WifiManager.h"
#include <WiFi.h>
#include "secrets.h"

// Variables
const char* ssid = WIFI_SSID;
const char* password = WIFI_PASSWORD;
bool isConnected = false;
DisplayManager wifiDM;

// Definitions
void printConnecting();
void printConnected();

WifiManager::WifiManager() {}

void WifiManager::begin(DisplayManager displayManager) {
  wifiDM = displayManager;
}

void WifiManager::loop() {
  if (WiFi.status() != WL_CONNECTED) {
    isConnected = false;
    WiFi.begin(ssid, password);
    printConnecting();
  }

  while(WiFi.status() != WL_CONNECTED);

  if (WiFi.status() == WL_CONNECTED && !isConnected) {
    isConnected = true;
    printConnected();
  }
}

void WifiManager::printConnecting() {
  wifiDM.printText(24, 0, 3, "Wifi:", true);
  wifiDM.printText(8, 32, 2, "Connecting");
  Serial.println("Connecting to Wifi...");
}

void WifiManager::printConnected() {
  wifiDM.printText(24, 0, 3, "Wifi:", true);
  wifiDM.printText(8, 32, 2, "Connected!");
  Serial.println("Wifi connected!");
}