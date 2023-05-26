#ifndef SMART_WINDOW_H
#define SMART_WINDOW_H

#include <Arduino.h>
#include <Servo.h>
#include <WiFi101.h>
#include<DFRobot_RGBLCD1602.h>

//creation de notre objet

class SmartWindow {
private:
  Servo myServo;
  int pinT; // broche TMP36
  int pinP; // broche capteur pluie
  int pinS; //broche servomoteur
  int pinM; // broche capteur de magnetisme
  float Temp; // variable temperature
  int angle; // variable iclinaison du servomoteur
  int niveau2; //variable mapping
  int sensorValeurPluie; //  pourcentage pluviometrie
  int readingPluie; // lecture broche capteur pluie
  int sensorValue; // lecture broche capteur temperature
  int etatMagnetisme; //lecture broche capteur magnetique
  String statutWindow;
  const char* ssid;
  const char* password;
  const char* serverIP;
  int serverPort;

public:
  SmartWindow(int tPin, int pPin, int sPin, int mPin, const char* wifiSsid, const char* wifiPassword, const char* ip, int port);
  void setup();
  void loop();
};

#endif  // SMART_WINDOW_H
