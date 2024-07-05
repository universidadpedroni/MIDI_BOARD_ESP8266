#include "wiFiFunctions.h"

wifiFunct::wifiFunct() : server(80) {}

void wifiFunct::init() {
    // Configure fixed IP address for the access point
    if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
        Serial.println("Failed to configure IP.");
    }

    // Start the access point
    if (!WiFi.softAP(ssid, password)) {
        Serial.println("Failed to start AP.");
    } else {
        Serial.println("Access point started.");
        Serial.print("IP Address: ");
        Serial.println(WiFi.softAPIP());
    }

    // Initialize SPIFFS
    if (!SPIFFS.begin()) {
        Serial.println("Failed to mount file system");
        return;
    }

    // Handle root URL request with embedded HTML content
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/index.html", "text/html");
    });

    // Serve static files from SPIFFS (e.g., CSS, JavaScript)
    server.on("/styles.css", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send(SPIFFS, "/styles.css", "text/css");
    });

    // Start the server
    server.begin();
}

