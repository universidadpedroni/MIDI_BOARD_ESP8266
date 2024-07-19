#ifndef SWITCHESFUNC_H
#define SWITCHESFUNC_H

#include <Arduino.h>
#include "midiConstants.h"
#include <EEPROM.h>

class mySwitch {
public:
    int id;
    int midiChannel;
    int CC_or_PC;
    int param;
    int value;
    int PC_min;
    int PC_max;
    bool toggle;
    bool sendMidiNow;

    void init(int id, int midiChannel, int CC_or_PC, int param, int value, bool toggleValue = false, int PC_min = 0, int PC_max = 100, bool sendMidiNow = false);
    void update();
    void loadDefaults();
    void save();
    void load();
    void showConfig();
};

extern mySwitch misSwitch[]; // Declarar externamente
extern const int NUM_SWITCHES; // Declarar externamente

#endif // SWITCHESFUNC_H
