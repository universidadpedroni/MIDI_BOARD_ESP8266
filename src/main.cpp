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
#include "pushButtonFunctions.h"
#include "EEPROM.h"


AsyncWebServer server(80);
pushButton myPB[NUM_PUSH_BUTTON];
HardwareSerial SerialMidi = Serial1;
bool dataChanged = false;

void sendMIDI(int id){
    SerialMidi.write(myPB[id].CC_or_PC | myPB[id].midiChannel);
	SerialMidi.write(myPB[id].param);
    if(myPB[id].CC_or_PC == MIDI_CH_CTRL_CHANGE) SerialMidi.write(myPB[id].value);
    
    // manejo de los casos especiales
    // toggle
    if(myPB[id].toggle) myPB[id].value == myPB[id].value_max? myPB[id].value = myPB[id].value_min : myPB[id].value = myPB[id].value_max;
    // incremento del valor de PC
    if(myPB[id].CC_or_PC == MIDI_CH_PRGM_CHANGE){
        myPB[id].param++;
        if(myPB[id].param > myPB[id].value_max)  myPB[id].param = myPB[id].value_min;
        myPB[id].save(id);
    }

}

void testMidiComm(){
    for(int i = 0; i < NUM_PUSH_BUTTON; i++){
        Serial.print("Enviando datos MIDI: ");
        myPB[i].showConfig(i);
        sendMIDI(i);
        delay(100);
    }
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

void pushButtonInit(){
    for(int i = 0; i < NUM_PUSH_BUTTON; i++){
        myPB[i].load(i);
        //myPB[i].loadDefaults(i);
        //myPB[i].begin(MIDI_CHANNEL_1 + i, MIDI_CH_CTRL_CHANGE, 12, i * 10, false);    
        //myPB[i].save(i);
    }
}

void pushButtonShowConfig(){
    for (int i = 0; i < NUM_PUSH_BUTTON; i++){
            myPB[i].showConfig(i);
        }
}

void serverInit() {
    Serial.println("Inicializando Servidor Web");

    // Página inicial
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
        String index = String(index_html);
        index.replace("%style", styles_css);
        index.replace("%__TIME__", __TIME__);
        index.replace("%__DATE__", __DATE__);
        request->send_P(200, "text/html", index.c_str());
    });

    // Página de cada push button
    for (int i = 0; i < NUM_PUSH_BUTTON; i++) {
        // Send web page with input fields to client
        server.on(String("/switch" + String(i)).c_str(), HTTP_GET, [i](AsyncWebServerRequest *request) {
            // Agrega el estilo al formulario html
            String page = String(switch_html);
            page.replace("%style", styles_css);
            page.replace("%idSwitch", String(i + 1));
            // Reemplazar los valores de %SW_0_MIDI_CH_X% basados en CanalMidi
            for (int j = 1; j <= 16; ++j) {
                String placeholder = "%PB_MIDI_CH_" + String(j) + "%";
                if (j == myPB[i].midiChannel + 1) {
                    page.replace(placeholder, "selected");
                } else {
                    page.replace(placeholder, "");
                }
            }
            // Reemplaza los valores de CC o PC
            if (myPB[i].CC_or_PC == MIDI_CH_CTRL_CHANGE) {
                page.replace("%PB_CC%", "selected");
                page.replace("%PB_PC%", "");
            } else {
                page.replace("%PB_CC%", "");
                page.replace("%PB_PC%", "selected");
            }
            // Reemplaza value
            page.replace("%pushButton0Value%", String(myPB[i].value));
        
            // Reemplaza el valor de toggle
            if (myPB[i].toggle) {
                page.replace("%PB_Yes%", "selected");
                page.replace("%PB_No%", "");
            } else {
                page.replace("%PB_Yes%", "");
                page.replace("%PB_No%", "selected");
            }

            request->send_P(200, "text/html", page.c_str());
        });
    }

    // Ruta para el botón Update (OTA)
    server.on("/update", HTTP_GET, [](AsyncWebServerRequest *request) {
        // Redirigir a OTA
        //request->redirect("/update");
        request->send(200, "text/plain", "OTA Update Page - Under Construccion");
        
        
    });

    

    // ruta para recibir los datos enviados desde los formularios
    server.on("/get", HTTP_GET, [](AsyncWebServerRequest *request){
        String inputMessage;
        String inputParam;
        if(request->hasParam("buttonIndex")){
            int pushButtonIndex = request->getParam("buttonIndex")->value().toInt() - 1;
            //Serial.printf("Index: %d\n", pushButtonIndex);
            if (pushButtonIndex < 0 || pushButtonIndex >= NUM_PUSH_BUTTON) {
                request->send(400, "text/plain", "Invalid button index");
                return;
            }
            // Cambio en Canal Midi
            if(request->hasParam(PB_MIDI_CH_NAME)){
                inputMessage = request->getParam(PB_MIDI_CH_NAME)->value();
                myPB[pushButtonIndex].midiChannel = inputMessage.toInt() - 1;
                myPB[pushButtonIndex].save(pushButtonIndex);
                dataChanged = true;
            } else if (request->hasParam(PB_CC_PC_NAME)){
                inputMessage = request->getParam(PB_CC_PC_NAME)->value();
                inputMessage == "PC" ? myPB[pushButtonIndex].CC_or_PC = MIDI_CH_PRGM_CHANGE : myPB[pushButtonIndex].CC_or_PC = MIDI_CH_CTRL_CHANGE;
                myPB[pushButtonIndex].save(pushButtonIndex);
                dataChanged = true;
            } else if (request->hasParam(PB_VALUE_NAME)) {
                inputMessage = request->getParam(PB_VALUE_NAME)->value();
                myPB[pushButtonIndex].value = inputMessage.toInt();
                myPB[pushButtonIndex].save(pushButtonIndex);
                dataChanged = true;
            } else if (request->hasParam(PB_TOGGLE_NAME)) {
                inputMessage = request->getParam(PB_TOGGLE_NAME)->value();
                myPB[pushButtonIndex].toggle = inputMessage.equals("Yes");
                myPB[pushButtonIndex].save(pushButtonIndex);
                dataChanged = true;
            } else {
                inputMessage = "No message sent";
                inputParam = "none";
            }
            Serial.printf("[%lu] Param: %s, Message: %s\n",millis(), inputParam.c_str(), inputMessage.c_str());
            
        }
        
    });

    



    server.onNotFound(notFound);
    server.begin();
}

void setup(){
    Serial.begin(BAUDRATE);
    Serial.printf("Fecha y Hora: %s, %s\n", __DATE__, __TIME__);
    SerialMidi.begin(MIDI_BAUDRATE);
    //flashF.checkFlash();
    EEPROM.begin(EEPROM_SIZE);
    pushButtonInit();
    Serial.println("Configuracion de switches");
    pushButtonShowConfig();
    Serial.print("Conectando a WiFi");
    if(wifiInit(WiFi_NODE)) serverInit();
    while(1){testMidiComm();}
    
    Serial.println("Setup terminado");
    
}

void loop(){
    if(dataChanged){
        pushButtonShowConfig();
        dataChanged = false;
    }
    
}

