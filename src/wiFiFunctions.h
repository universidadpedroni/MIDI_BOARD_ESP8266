#ifndef WIFIFUNCTIONS_H
#define WIFIFUNCTIONS_H

#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "ESPAsyncWebServer.h"
#include "LittleFS.h"



class wifiFunct {
    public:
        wifiFunct();
        void init();
    private:
        const char* ssid = "MIDI BOARD AP";
        const char* password = "";
        
        IPAddress local_IP = IPAddress(192, 168, 10, 1);
        IPAddress gateway = IPAddress(192, 168, 10, 1);
        IPAddress subnet = IPAddress(255, 255, 255, 0);
        AsyncWebServer server;
};


#endif