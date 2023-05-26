#include <Arduino.h>
#include <SPI.h>
#include "SmartWindow.h"

DFRobot_RGBLCD1602 lcd(16, 2);
SmartWindow smartWindow(A1, A2, 3, 1, "UNIFI_IDO1", "42Bidules!", "192.168.1.155", 8080);


void setup() {
  lcd.init();
  smartWindow.setup();
}

void loop() {
  smartWindow.loop();
}
