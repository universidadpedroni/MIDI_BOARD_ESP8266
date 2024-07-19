#include "switchesFunc.h"

void mySwitch::init(int id, int midiChannel, int CC_or_PC, int param, int value, bool toggleValue, int PC_min, int PC_max, bool sendMidiNow) {
    this->id = id;
    this->midiChannel = midiChannel;
    this->CC_or_PC = CC_or_PC;
    this->param = param;
    this->value = value;
    this->toggle = toggleValue;
    this->PC_min = PC_min;
    this->PC_max = PC_max;
    this->sendMidiNow = sendMidiNow;
}

void mySwitch::loadDefaults() {
    switch (this->id) {
    case 0:
        // RC5 Play/Stop
        this->init(this->id, MIDI_CHANNEL_1, MIDI_CH_CTRL_CHANGE, CC_RHYTHM_P_S, 127, true);
        break;
    case 1:
        // RC5 Loop Down
        this->init(this->id, MIDI_CHANNEL_1, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, 0, false, 0, 99);
        break;
    case 2:
        // RC5 Loop Up
        this->init(this->id, MIDI_CHANNEL_1, MIDI_CH_PRGM_CHANGE, MIDI_CH_PRGM_CHANGE, 0, false, 0, 99);
        break;
    case 3:
        // Nemesis Prog Down
        this->init(this->id, MIDI_CHANNEL_2, MIDI_CH_CTRL_CHANGE, CC_PRESET_DOWN, 127, false, 0, 99);
        break;
    case 4:
        // Nemesis Prog Up
        this->init(this->id, MIDI_CHANNEL_2, MIDI_CH_CTRL_CHANGE, CC_PRESET_UP, 127, false, 0, 99);
        break;
    default:
        break;
    }
}

void mySwitch::update() {
    // Aquí puedes agregar la lógica de actualización según tus necesidades.
}

void mySwitch::save() {
    // Calcula la dirección de inicio para este switch
    int address = this->id * sizeof(mySwitch);

    // Guarda los valores del switch en la EEPROM
    EEPROM.put(address, *this);

    // Asegura que los datos se escriban en la EEPROM inmediatamente
    EEPROM.commit();
}

void mySwitch::load() {
    // Calcula la dirección de inicio para este switch
    int address = this->id * sizeof(mySwitch);

    // Lee los valores almacenados en la EEPROM para este switch
    EEPROM.get(address, *this);
}

void mySwitch::showConfig() {
    Serial.printf("Switch %d Config: Channel=", this->id);
    Serial.print(this->midiChannel + 1);
    Serial.print(", CC_or_PC=");
    Serial.print(this->CC_or_PC);
    Serial.print(", Param=");
    Serial.print(this->param);
    Serial.print(", Value=");
    Serial.print(this->value);
    Serial.print(", PC_min=");
    Serial.print(this->PC_min);
    Serial.print(", PC_max=");
    Serial.print(this->PC_max);
    Serial.print(", Toggle=");
    Serial.print(this->toggle);
    Serial.print(", SendMidiNow=");
    Serial.println(this->sendMidiNow);
}
