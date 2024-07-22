#include "pushButtonFunctions.h"


void pushButton::begin(int midiChannel, int CC_or_PC, int param, int value, bool toggle, int value_min, int value_max){
    this->midiChannel = midiChannel;
    this->CC_or_PC = CC_or_PC;
    this->param = param;
    this->value = value;
    this->toggle = toggle;
    this->value_min = value_min;
    this->value_max = value_max;
}

void pushButton::showConfig(int id){
    Serial.printf("[%lu], PushButton: %d: MidiChannel: %d, CC o PC: %s, param: %d, value: %d(%d - %d), toggle: %s\n",
            millis(), 
            id + 1,
            this->midiChannel + 1,
            this->CC_or_PC == MIDI_CH_CTRL_CHANGE? "CC":"PC",
            this->param,
            this->value,
            this->value_min,
            this->value_max,
            this->toggle? "Yes" : "No");
            
}

void pushButton::loadDefaults(int id){
    switch (id)
    {
    case 0:
        // RC5 Play/Stop
        this->begin(MIDI_CHANNEL_1, MIDI_CH_CTRL_CHANGE, CC_RHYTHM_P_S, 127, true);
        break;
    case 1:
        // RC5 Loop Down
        this->begin(MIDI_CHANNEL_1, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, 0, false);
        break;
    case 2:
        // RC5 Loop Up
        this->begin(MIDI_CHANNEL_1, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, 0, false);
        break;
    case 3:
        // Nemesis Prog Down
        this->begin(MIDI_CHANNEL_2, MIDI_CH_CTRL_CHANGE, CC_PRESET_DOWN, 127, false);
        break;
    case 4:
        // Nemesis Prog Up
        this->begin(MIDI_CHANNEL_2, MIDI_CH_CTRL_CHANGE, CC_PRESET_UP, 127, false);
        break;
    default:
        this->begin(MIDI_CHANNEL_16, MIDI_CH_CTRL_CHANGE, 127, 127, false);
        break;
        
    }
}

void pushButton::save(int id){
    // Calcula la dirección de inicio para este switch
    int address = id * sizeof(pushButton);    
    // Guarda los valores del switch en la EEPROM
    EEPROM.put(address, *this);

    // Asegura que los datos se escriban en la EEPROM inmediatamente
    EEPROM.commit();
}

void pushButton::load(int id) {
    // Calcula la dirección de inicio para este switch
    int address = id * sizeof(pushButton);

    // Lee los valores almacenados en la EEPROM para este switch
    EEPROM.get(address, *this);
}