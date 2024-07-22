#ifndef PUSHBUTTONFUNCTIONS_H
#define PUSHBUTTONFUNCTIONS_H

#include <Arduino.h>
#include "midiConstants.h"
#include "EEPROM.h"

class pushButton{
    public:
        int midiChannel;
        int CC_or_PC;
        int param;
        int value;
        bool toggle;
        int value_min;
        int value_max;
        void begin(int midiChannel, int CC_or_PC, int param, int value, bool toggle, int value_min = 0, int value_max = 100);
        void showConfig(int id = 1);
        void loadDefaults(int id);
        void save(int id);
        void load(int id);
};

#endif
