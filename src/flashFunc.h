#ifndef FLASHFUNC_H
#define FLASHFUNC_H
#include <Arduino.h>

/* Función para determinar el tamaño y forma de funcionamiento de la memoria de la ESP8266.
Tomado del ejemplo checkMemorySize de Arduino IDE*/

class flashFunctions{
    public:
        void checkFlash();
};


#endif