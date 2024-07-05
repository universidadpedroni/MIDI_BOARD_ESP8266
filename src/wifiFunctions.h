#ifndef WIFIFUNCTIONS_H
#define WIFIFUNCTIONS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "htmlContent.h"

class wifiFunctions {
public:
    wifiFunctions(); // Declarar el constructor
    void init();
    void handleClient();

private:
    WiFiServer server;
    IPAddress local_IP = IPAddress(192, 168, 10, 1);
    IPAddress gateway = IPAddress(192, 168, 10, 1);
    IPAddress subnet = IPAddress(255, 255, 255, 0);
    const char* ssid = "MIDI_ESP_AP"; // Definimos la SSDI de nuestro servidor WiFi -nombre de red-
    const char* password = "";
};

#endif // WIFIFUNCTIONS_H
