#include "SmartWindow.h"

SmartWindow::SmartWindow(int tPin, int pPin, int sPin, int mPin, const char* wifiSsid, const char* wifiPassword, const char* ip, int port)
  : pinT(tPin), pinP(pPin), pinS(sPin), pinM(mPin), ssid(wifiSsid), password(wifiPassword), serverIP(ip), serverPort(port) {}

void SmartWindow::setup() {

    // initialisation des instruments

  Serial.begin(9600);
  myServo.attach(pinS);
  pinMode(pinM, INPUT);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connexion WiFi en cours...");
  }
  Serial.println("Connecté au réseau WiFi !");
}

void SmartWindow::loop() {

    // traitement des donnees

  sensorValue = analogRead(pinT);
  etatMagnetisme = digitalRead(pinM);
  readingPluie = analogRead(pinP);

  float voltage = (sensorValue * 3.3) / 1023;
  Temp = ((voltage * 1000) - 500) / 10;

  niveau2 = map(readingPluie, 1023, 0, 0, 100);
  sensorValeurPluie = niveau2;

  if (Temp < 20 || sensorValeurPluie > 45) {
    angle = 0;
  }
  else {
    angle = 75;
  }

  myServo.write(angle);

  if (etatMagnetisme == HIGH) {
    statutWindow = "FERME";
  }
  else {
    statutWindow = "OUVERT";
  }
// envoi des donnees au server

  String url = "/api/data?temperature=" + String(Temp) + "&intensite_pluie=" + String(sensorValeurPluie) + "&etat_fenetre=" + statutWindow;

  WiFiClient client;
  if (client.connect(serverIP, serverPort)) {
    Serial.println("Connecté au serveur intermédiaire !");

    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + serverIP + "\r\n" +
                 "Connection: close\r\n\r\n");

    while (client.connected()) {
      if (client.available()) {
        String line = client.readStringUntil('\n');
      }
    }
    client.stop();
  }
  else {
    Serial.println("Impossible de se connecter au serveur");
    }
}