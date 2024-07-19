#ifndef MIDICONSTANTS_H
#define MIDICONSTANTS_H

/* CONSTANTES DEL RC5*/
//https://www.kraftmusic.com/media/ownersmanual/Boss_RC-5_Reference_Manual.pdf

const int CC_TAP_TEMPO = 80;
const int CC_TRK_PLY_STP = 81;
const int CC_RHYTHM_P_S = 82;
const int CC_VARIATION = 83;
const int CC_RHY_PART_1 = 84;
const int CC_RHY_PART_2 = 85;
const int CC_RHY_PART_3 = 86;
const int CC_RHY_PART_4 = 87;

/* CONSTANTES DEL NEMESIS*/
const int CC_PRESET_UP = 80;
const int CC_PRESET_DOWN = 82;



/* Channel messages.
   4 most significant bytes is the type, 4 least significant is the channel.
   Example: 0x83 is note off channel 4*/
#define MIDI_CH_NOTE_OFF                  0x80
#define MIDI_CH_NOTE_ON                   0x90
#define MIDI_CH_POLY_AFTER_TOUCH          0xA0
#define MIDI_CH_CTRL_CHANGE               0xB0
#define MIDI_CH_PRGM_CHANGE               0xC0
#define MIDI_CH_CHANNEL_AFTER_TOUCH       0xD0
#define MIDI_CH_PITCH_WHEEL               0xE0

   /* Midi channels
	  4 most significant bytes is the type, 4 least significant is the channel.
	  Example: 0x83 is note off channel 4 */

#define MIDI_CHANNEL_1  0x00
#define MIDI_CHANNEL_2  0x01
#define MIDI_CHANNEL_3  0x02
#define MIDI_CHANNEL_4  0x03
#define MIDI_CHANNEL_5  0x04
#define MIDI_CHANNEL_6  0x05
#define MIDI_CHANNEL_7  0x06
#define MIDI_CHANNEL_8  0x07
#define MIDI_CHANNEL_9  0x08
#define MIDI_CHANNEL_10 0x09
#define MIDI_CHANNEL_11 0x0A
#define MIDI_CHANNEL_12 0x0B
#define MIDI_CHANNEL_13 0x0C
#define MIDI_CHANNEL_14 0x0D
#define MIDI_CHANNEL_15 0x0E
#define MIDI_CHANNEL_16 0x0F

#endif