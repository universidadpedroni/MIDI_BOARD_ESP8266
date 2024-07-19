#ifndef CONFIG_H
#define CONFIG_H

#include <Arduino.h>
#ifdef ESP32
    #include <WiFi.h>
    const unsigned long BAUDRATE = 115200;
#else
    #include <ESP8266WiFi.h>
    const unsigned long BAUDRATE = 74880;
#endif

const char* PB_MIDI_CH_NAME = "PB_MIDI_CH";
const char* PB_CC_PC_NAME = "PB_CC_PC";
const char* PB_VALUE_NAME = "PB_VALUE";
const char* PB_TOGGLE_NAME = "PB_TOGGLE";


#define WiFi_AP true
#define WiFi_NODE false
IPAddress local_IP = IPAddress(192, 168, 10, 1);
IPAddress gateway = IPAddress(192, 168, 10, 1);
IPAddress subnet = IPAddress(255, 255, 255, 0);
const char* ssid_AP = "MIDI_ESP_AP";
const char* password_AP = "";
const char* ssid_NODE = "TheShield";
const char* password_NODE = "JamesBond007";

//const char* ssid_NODE = "iPhone de Juan";
//const char* password_NODE = "HelpUsObiJuan";
const char* hostName = "ESP8266 Midi Board";

class pushButton{
    public:
        int midiChannel;
        int CC_or_PC;
        int param;
        int value;
        bool toggle;
};

const int NUM_PUSH_BUTTON = 7;

#endif