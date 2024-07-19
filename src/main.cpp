#include <Arduino.h>
#include "config.h"
#include "midiConstants.h"
#ifdef ESP32
    #include <WiFi.h>
    #include <AsyncTCP.h>
#else
    #include "flashFunc.h"
    #include <ESP8266WiFi.h>
    #include <ESPAsyncTCP.h>
#endif
#include <ESPAsyncWebServer.h>
//https://randomnerdtutorials.com/esp32-esp8266-input-data-html-form/
#include "webpage.h"
#include "styles_css.h"
//#include "switchesFunc.h"

//flashFunctions flashF;



AsyncWebServer server(80);
pushButton myPB;
bool dataChanged = false;
// Replaces placeholder with stored values

String procesamientoSwitch0(const String& var){
    Serial.print("Procesamiento Switch 0: var = ");
    Serial.println(var);
    if (var == "pushButton0Value"){
        return String(myPB.value);
    }
    
    Serial.println("No entró a ningun if");
    return String();
}

void notFound(AsyncWebServerRequest *request){
    request->send(404, "text/plain", "Not found");
}

bool wifiInit(bool AP){
    bool wifiConnected;
    if (AP) {
        WiFi.mode(WIFI_AP);
        if (!WiFi.softAPConfig(local_IP, gateway, subnet)) {
            Serial.println("Fallo al configurar la IP.");
        }
        if (!WiFi.softAP(ssid_AP, password_AP)) {
            Serial.println("Fallo al iniciar el AP.");
            wifiConnected = false;
        } else {
            WiFi.hostname(hostName);
            Serial.println("Punto de acceso iniciado.");
            Serial.print("IP Address: ");
            Serial.println(WiFi.softAPIP());
            wifiConnected = true;
        }
        
    } 
    else {
        WiFi.mode(WIFI_STA);
        WiFi.begin(ssid_NODE, password_NODE);
        int contador = 0;
        while (WiFi.status() != WL_CONNECTED && contador < 200) {
            delay(250);
            Serial.print('.');
            contador++;
        }
        if (WiFi.status() == WL_CONNECTED) {
            WiFi.hostname(hostName);
            Serial.println("Connection established");
            Serial.print("IP address:\t");
            Serial.println(WiFi.localIP());
            wifiConnected = true;
        } else {
            Serial.println("Failed to connect to the network.");
            wifiConnected = false;
        }
    }
    return wifiConnected;
}

void serverInit(){
    Serial.println("Inicializando Servidor Web");
    // Send web page with input fields to client
    server.on("/switch0", HTTP_GET, [](AsyncWebServerRequest *request){
        // Agrega el estilo al formulario html
        String page = String(switch_html);
        page.replace("%style", styles_css);
        page.replace("%idSwitch", String(4));
        // Reemplazar los valores de %SW_0_MIDI_CH_X% basados en CanalMidi
        for (int i = 1; i <= 16; ++i) {
            String placeholder = "%PB_MIDI_CH_" + String(i) + "%";
            if (i == myPB.midiChannel +1) {
                page.replace(placeholder, "selected");
            } else {
                page.replace(placeholder, "");
            }
        }
        // Reemplaza los valores de CC o PC
        if (myPB.CC_or_PC == MIDI_CH_CTRL_CHANGE) {
            page.replace("%PB_CC%", "selected");
            page.replace("%PB_PC%", "");
        } else {
            page.replace("%PB_CC%", "");
            page.replace("%PB_PC%", "selected");
        }
        // Reemplaza value
        page.replace("%pushButton0Value%", String(myPB.value));
        
        // Reemplaza el valor de toggle
        if (myPB.toggle) {
            page.replace("%PB_Yes%", "selected");
            page.replace("%PB_No%", "");
        } else {
            page.replace("%PB_Yes%", "");
            page.replace("%PB_No%", "selected");
        }

        request->send_P(200, "text/html", page.c_str(), procesamientoSwitch0);
        
        
    });
    // Send a GET request to <ESP_IP>/get?SW_0_VALUE=<inputMessage>
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
        String inputMessage;
        String inputParam;
        
        if(request->hasParam(PB_MIDI_CH_NAME)){
            inputMessage = request->getParam(PB_MIDI_CH_NAME)->value();
            inputParam = PB_MIDI_CH_NAME;
            myPB.midiChannel = inputMessage.toInt() - 1;
            dataChanged = true;
        }
        else if(request->hasParam(PB_CC_PC_NAME)){
            inputMessage = request->getParam(PB_CC_PC_NAME)->value();
            inputParam = PB_CC_PC_NAME;
            inputMessage == "PC" ? myPB.CC_or_PC = MIDI_CH_PRGM_CHANGE : myPB.CC_or_PC = MIDI_CH_CTRL_CHANGE;
            dataChanged = true;
        }
        else if (request->hasParam(PB_VALUE_NAME)) {
            inputMessage = request->getParam(PB_VALUE_NAME)->value();
            inputParam = PB_VALUE_NAME;
            myPB.value = inputMessage.toInt();
            dataChanged = true;
        } 
        else if (request->hasParam(PB_TOGGLE_NAME)) {
            inputMessage = request->getParam(PB_TOGGLE_NAME)->value();
            inputParam = PB_TOGGLE_NAME;
            myPB.toggle = inputMessage.equals("Yes");
            dataChanged = true;
        }
        else {
            inputMessage = "No message sent";
            inputParam = "none";
        }
        Serial.printf("[%d] Param: %s, Message: %s\n",millis(), inputParam.c_str(), inputMessage.c_str());
        request->send(200, "text/plain", inputMessage);
    });
    server.onNotFound(notFound);
    server.begin();
     

}

void setup(){
    Serial.begin(BAUDRATE);
    Serial.printf("Fecha y Hora: %s, %s\n", __DATE__, __TIME__);
    //flashF.checkFlash();
    if(wifiInit(WiFi_NODE)) serverInit();
    Serial.println("Setup terminado");
    myPB.midiChannel = MIDI_CHANNEL_10;
    myPB.CC_or_PC = MIDI_CH_PRGM_CHANGE;
    myPB.value = 12;
    myPB.toggle = true;
}

void loop(){
    if(dataChanged){
        Serial.printf("[%d], MidiChannel: %d, CC o PC: %s, value: %d, toggle: %s\n",
        millis(),
        myPB.midiChannel + 1 , myPB.CC_or_PC == MIDI_CH_CTRL_CHANGE? "CC":"PC", myPB.value,
        myPB.toggle? "Yes" : "No");
        dataChanged = false;
    }
    

}

