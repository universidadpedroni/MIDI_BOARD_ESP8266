#include "wifiFunctions.h"

// Constructor para inicializar el servidor en el puerto 80
wifiFunctions::wifiFunctions() : server(80) {}

void wifiFunctions::init() {
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

    // Iniciar el servidor
    server.begin();
}

void wifiFunctions::handleClient() {
    WiFiClient client = server.accept();
    if (client) {
        Serial.println("Cliente conectado");
        String currentLine = "";
        while (client.connected()) {
            if (client.available()) {
                char c = client.read();
                Serial.write(c);
                if (c == '\n') {
                    if (currentLine.length() == 0) {
                        client.println("HTTP/1.1 200 OK");
                        client.println("Content-type:text/html");
                        client.println();

                        // Enviar la página HTML
                        String htmlContent = String(htmlPage);
                        htmlContent.replace("%SETTINGS_SECTIONS%", settingsSections);
                        client.println(htmlContent);

                        client.println();
                        break;
                    } else {
                        currentLine = "";
                    }
                } else if (c != '\r') {
                    currentLine += c;
                }
            }
        }
        client.stop();
        Serial.println("Cliente desconectado");
    }
}
