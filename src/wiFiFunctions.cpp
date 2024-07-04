#include <Arduino.h>
#include "wiFiFunctions.h"
//#include <ESP8266WiFi.h>
//#include <ESPAsyncWebServer.h>



// Constructor para inicializar el servidor en el puerto 80
wifiFunct::wifiFunct() : server(80) {}

void wifiFunct::init() {
    // Inicializar LittleFS
    if (!LittleFS.begin()) {
        Serial.println("Error al montar LittleFS");
        return;
    }

    // Configurar la IP fija
    if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
        Serial.println("Fallo al configurar la IP.");
    }

    // Iniciar el punto de acceso
    if (!WiFi.softAP(ssid, password)) {
        Serial.println("Fallo al iniciar el AP.");
    } else {
        Serial.println("Punto de acceso iniciado.");
        Serial.print("IP Address: ");
        Serial.println(WiFi.softAPIP());
    }

    // Configurar las rutas del servidor
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(LittleFS, "/index.html", "text/html");
    });

    // Iniciar el servidor
    server.begin();
}
