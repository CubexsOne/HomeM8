#include "Scanner.h"

#include <SoftwareSerial.h>
#include <Wire.h> 
#include "MqttClient.h"

// Variables
String barcode = "";
SoftwareSerial barcodeScanner(16, 17);
MqttClient scannerMqtt;
DisplayManager scannerDM;

Scanner::Scanner() {}

void Scanner::begin(DisplayManager displayManager, MqttClient mqttClient) {
  scannerDM = displayManager;
  scannerMqtt = mqttClient;
  barcodeScanner.begin(9600);
}

void Scanner::loop() {
  if (barcodeScanner.available()) {
    while (barcodeScanner.available()) {
      char input = barcodeScanner.read();
      if (input == '\n') {
        scannerMqtt.sendMQTTMessage(barcode);
        barcode = "";
        return;
      }
      if (input != '\r') {
        barcode += input;
      }
    }
  }
}