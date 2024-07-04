#include <Arduino.h>
#include "blink.h"
#include "wiFiFunctions.h"

// https://www.instructables.com/ESP-12F-ESP8266-Module-Minimal-Breadboard-for-Flas/
// https://randomnerdtutorials.com/esp8266-nodemcu-client-server-wi-fi/


/* PARA PROGRAMAR: 
1. GPIO0 a GND
2. Dar un toque a GND al RESET. La esp entra en modo FLASH
3. Cargar el software
4. Levantar el GPIO0
5. Dar un toque a GND al reset.
*/

blink ledBlink(LED_BUILTIN);


wifiFunct wifiF;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println();
  Serial.printf("Fecha y Hora: %s, %s\n", __DATE__, __TIME__);
  ledBlink.init();
  wifiF.init();
}

void loop() {
  ledBlink.update(500);
}

