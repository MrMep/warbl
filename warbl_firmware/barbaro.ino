/*
    Copyright (C) 2023 Gianluca Barbaro barbaro.it

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see http://www.gnu.org/licenses/
*/

/*
    Mods by Gianluca Barbaro - 2023

    - Added Half hole management for left thumb and R3-R4, with calibration in the config tool.
    - Added General Tranposer (substitutes previous semitone and octave actions)
    - Added a Fixed note action (to keep the current note always on - not a drone, it switches off with the main note)
    - Added a 3-voice harmonizer where you can select the interval and a reference scale. If you activate the harmonizer while playing a note,
        it will adjast the interval to keep it "diatonic" to the selected scale.
    - Added a Perfomance Monitor section in the Config tool, with a piano keyboard and current state of the fingering, the hamonizer, the transpose, etc.
    - Added a new custom fingering management. There are up to 30 custom fingering slot.
    - Having a single "mode" or instrument and load the corresponding prefs runtime, when the instrument is changed - to release memory and flash footprint
    - 
    Code moddings:
    - Added defines.h for (almost) all constants used in the sketch
    - Added type.h for (almost) all type defs used in the sketch
    - Modified the Settings CC message mapping to allocate for more button actions (now up to 20 different actions)
    - Moved some Midi CC messages to make room for new ones.

    TODOs:
    - Add "ignore hole" to custom fingering management.

    - DONE Create a default configuration for all three presets.
    - DONE - Make half hole detection more robust.
    - NOT A GOOD IDEA - Make one big struct to contain all the parameters settings, with a single mechanism to communicate with the config tool
    - NOT A GOOD IDEA - Make one big struct containing all run-time parameters.

*/
#include "defines.h"
#include "types.h"

//Globals
bool toneholeHalfCovered[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };         //storage for half-covered tonehole
int toneholeLastRead[TONEHOLE_SENSOR_NUMBER] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 }; //Last read before modification from half hole detection, for the config Tool


const uint16_t harmonizer_scales [S_SCALE_NUMBER] = {
    MAJOR_SCALE,
    MELODIC_MINOR_SCALE,
    HARMONIC_MINOR_SCALE,
    DIMINISHED_1_SCALE,
    DIMINISHED_2_SCALE,
    AUGMENTED_1_SCALE,
    AUGMENTED_2_SCALE,
    WHOLETONE_SCALE,
    BEBOP_MAJOR_SCALE,
    BEBOP_DOMINANT_SCALE,
    PENTA_MAJOR_SCALE,
    PENTA_MINOR_SCALE,
    BLUES_SCALE
};


//Initializes settings parameters
// void settings_init(byte preset) {

//     // settings.bytes[SET_BYTE_PB_MODE] = kPitchBendSlideVibrato;  
//     // senseDistance = 10;  
//     // settings.bytes[SET_BYTE_VIBRATO_DEPTH] = 1024;  

// } 
//Initializes runtime parameters
void rt_init() {
    //General
    // bytes[RT_BYTE_BLINK_NUMBER] = 1;
    fingering.halfHole.currentHoleSettings = 99; //disabled

    fingering.halfHole.halfHoleBuffer = HALF_HOLE_BUFFER_SIZE;

    //Harmonizer
    for (byte i = 0; i <HARMONIZER_VOICES; i++) {
        harmonizer.harmonizers[i] = {0,-1,-1,-1, harmonizer_scales[S_MAJOR],0,7 };
    }

}

void sendAsPitchBend(int value) {
    value += 8192;
    sendUSBMIDI(PITCH_BEND, mainMidiChannel,  lowByte(value << 1) >> 1, highByte(value << 1)) ;
}

//EEPROM Utils for ints
int readIntFromEEPROM(uint16_t address) {
    return word(EEPROM.read(address), EEPROM.read(address+1));
}
void writeIntToEEPROM(uint16_t address, int value) {
    EEPROM.update(address, highByte(value));
    EEPROM.update(address + 1, lowByte(value));
}

void sendIntValue(byte valueIndex, int value) {
    if (communicationMode) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_13, valueIndex);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_14, value >> 7);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_15, lowByte(value));
    }
}

//Resets saved Half Hole Calibration values
void resetHalfHoleCalibration() {
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        for (byte j = 0; j<4; j++) {
            EEPROM.update(EEPROM_HALF_HOLE_CALIBRATION + i*4 + j, 0xFF);
        }
    }
}


//Save all Half Hole Calibration values
void saveHalfHoleCalibration() {
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        saveHalfHoleLowerLimit(i);
        saveHalfHoleUpperLimit(i);
    }
}
//Loads from EEPROM
void loadHalfHoleCalibration() {

    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        //Read upper limit
        // byte high = EEPROM.read(EEPROM_HALF_HOLE_CALIBRATION + i*4);
        // byte low = EEPROM.read(EEPROM_HALF_HOLE_CALIBRATION + i*4 + 1);
        // fingering.halfHole.lower_limit[i] = word(high, low);

        fingering.halfHole.lower_limit[i] = readIntFromEEPROM(EEPROM_HALF_HOLE_CALIBRATION + i*4);
        if (fingering.halfHole.lower_limit[i] == 0xFFFF) { //null calibration
            fingering.halfHole.lower_limit[i] =  senseDistance/2; //Default value
        }

        // high = EEPROM.read(EEPROM_HALF_HOLE_CALIBRATION + i*4 +2);
        // low = EEPROM.read(EEPROM_HALF_HOLE_CALIBRATION + i*4 + 3);
        // fingering.halfHole.upper_limit[i] = word(high, low);

        fingering.halfHole.upper_limit[i] = readIntFromEEPROM(EEPROM_HALF_HOLE_CALIBRATION + i*4 +2);
        if (fingering.halfHole.upper_limit[i] == 0xFFFF) { //null calibration
            fingering.halfHole.upper_limit[i] = toneholeCovered[i] - senseDistance/2; //Default value
        }
    }
}

void saveHalfHoleLowerLimit(byte hole) {
    if (hole < TONEHOLE_SENSOR_NUMBER) {
        // EEPROM.update(EEPROM_HALF_HOLE_CALIBRATION + hole*4 , highByte(fingering.halfHole.lower_limit[hole]));
        // EEPROM.update(EEPROM_HALF_HOLE_CALIBRATION + hole*4 + 1, lowByte(fingering.halfHole.lower_limit[hole]));
        writeIntToEEPROM(EEPROM_HALF_HOLE_CALIBRATION + hole*4, fingering.halfHole.lower_limit[hole]);

    }
}

void saveHalfHoleUpperLimit(byte hole) {
    if (hole < TONEHOLE_SENSOR_NUMBER) {
        // EEPROM.update(EEPROM_HALF_HOLE_CALIBRATION + hole*4 +2, highByte(fingering.halfHole.upper_limit[hole]));
        // EEPROM.update(EEPROM_HALF_HOLE_CALIBRATION + hole*4 +3, lowByte(fingering.halfHole.upper_limit[hole]));
        writeIntToEEPROM(EEPROM_HALF_HOLE_CALIBRATION + hole*4 + 2, fingering.halfHole.upper_limit[hole]);

    }
}

void sendHoleCovered(uint16_t holes) {
    sendIntValue(MIDI_SEND_HOLE_COVERED, holes);
}

//Sends the calculated limit and other paramenters for Half hole detection
void sendHalfHoleParams( int hole) {

    if (communicationMode && hole < TONEHOLE_SENSOR_NUMBER ) { //we send debug info to the config tool

        //Sends current senseDistance
        // sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_03, senseDistance);  //send sense distance

        //Sends current Hole
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HALFHOLE_CURRENT);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, fingering.halfHole.currentHoleSettings);


        //Sends current Hole lowerLimit
        sendIntValue(MIDI_SEND_HALFHOLE_MIN, fingering.halfHole.lower_limit[hole] );

        //Sends current Hole upperLimit
        sendIntValue(MIDI_SEND_HALFHOLE_MAX, fingering.halfHole.upper_limit[hole] );

        //Sends current Hole calibration 
        // sendIntValue(MIDI_SEND_TONE_COVERED_0 + hole, toneholeCovered[hole]);

        //Sends current Hole Read 
        sendIntValue(MIDI_SEND_TONE_READ_0 + hole, toneholeLastRead[hole]);
    }
}

// //Returns the calculated lower limit for select hole
// int getHalfHoleLowerLimit(int hole) {
//      int result = 0;

//     if (hole > TONEHOLE_SENSOR_NUMBER) {
//         return result;
//     }

//     switch (hole) {
//             case R3_HOLE:
//             case R4_HOLE:
//                 result = senseDistance/2;
//                 break;
//             case THUMB_HOLE:
//                 result = senseDistance*2 ;
//                 break;

//             default:
//                 break;
//         }
//     return result;
// }

// //Return the calculated upper limit for select hole
// int getHalfHoleUpperLimit(int hole) {
//      int result = 0;
//     if (hole > TONEHOLE_SENSOR_NUMBER) {
//         return result;
//     }

//     switch (hole) {
//             case R3_HOLE:
//             case R4_HOLE:
//                 // result = senseDistance*2;
//                 result = toneholeCovered[hole] - senseDistance/2;
//                 break;
//             case THUMB_HOLE:
//                 result = toneholeCovered[hole] - senseDistance/2 +20;
//                 break;

//             default:
//                 break;
//         }
//     return result;
// }
//returns if the selected hole is half covered
bool isHalfHole(int hole) {

    // if (hole > TONEHOLE_SENSOR_NUMBER) {
    //     return false;
    // }

    return toneholeRead[hole] > fingering.halfHole.lower_limit[hole] && toneholeRead[hole] <  fingering.halfHole.upper_limit[hole];
}
//Returns true if the status of the thumb hole is clear, otherwise false
bool debounceHalfHole(int hole) {

    bool halfHoleNow =   isHalfHole(hole);

    if (halfHoleNow != toneholeHalfCovered[hole] || fingering.halfHole.halfHoleSamples != 0) { //A change is detected or we are in detection

        if (fingering.halfHole.halfHoleSamples == 0) { //Entering Half hole detection
            fingering.halfHole.prevSampleValue = toneholeRead[hole];
            fingering.halfHole.sampleDirection = 0;

#if DEBUG_HALF_HOLE
            sendUSBMIDI(CC, mainMidiChannel,  12, halfHoleNow);
            sendAsPitchBend(toneholeRead[hole]);
            if (!fingering.halfHole.debugSent) {
                fingering.halfHole.debugSent = true;
                sendAsPitchBend((senseDistance*2));
                sendAsPitchBend(toneholeCovered[hole] -senseDistance/2 +20);
            }
#endif
            ++fingering.halfHole.halfHoleSamples; //Entering detection mode
            return false; //half hole still to be determined
        } else { //Detection Phase

            //Gesture Detection
            if (toneholeRead[hole] == fingering.halfHole.prevSampleValue && fingering.halfHole.halfHoleSamples < fingering.halfHole.halfHoleBuffer ) { //no change, we skip detection
                return false;
            }

            fingering.halfHole.sampleDirection += toneholeRead[hole] - fingering.halfHole.prevSampleValue;
            fingering.halfHole.prevSampleValue = toneholeRead[hole];

#if DEBUG_HALF_HOLE_DISAB
                    sendUSBMIDI(CC, mainMidiChannel,  14, halfHoleNow) ;
                    sendAsPitchBend(fingering.halfHole.halfHoleSamples);
                    sendAsPitchBend(fingering.halfHole.sampleDirection);
#endif

            if (toneholeHalfCovered[hole]) { //Previously Half-Covered
                //The value is increasing - going to covered - we can exit detection
                //value is decreasing - going to open - we can exit detection
                if (fingering.halfHole.sampleDirection > HALF_HOLE_DIRECTION_LIMIT || fingering.halfHole.sampleDirection < -HALF_HOLE_DIRECTION_LIMIT) { 
#if DEBUG_HALF_HOLE
                    sendUSBMIDI(CC, mainMidiChannel,  15, halfHoleNow) ;
                    sendAsPitchBend(fingering.halfHole.halfHoleSamples);
                    sendAsPitchBend(fingering.halfHole.sampleDirection);
                    sendAsPitchBend(toneholeRead[hole]);

#endif
                    fingering.halfHole.halfHoleSamples = 0; //Exit half hole detection
                    toneholeHalfCovered[hole] = false;
                    goto end;
                } //else we go on with detection
            } else if (bitRead(holeCovered, hole)) { //Previously Covered
                if (fingering.halfHole.sampleDirection > HALF_HOLE_DIRECTION_LIMIT) { //The value is increasing - still covered - we can exit detection
#if DEBUG_HALF_HOLE
                    sendUSBMIDI(CC, mainMidiChannel,  16, halfHoleNow) ;
                    sendAsPitchBend(fingering.halfHole.halfHoleSamples);
                    sendAsPitchBend(fingering.halfHole.sampleDirection);
                    sendAsPitchBend(toneholeRead[hole]);

#endif
                    fingering.halfHole.halfHoleSamples = 0; //Exit half hole detection
                    toneholeHalfCovered[hole] = false;
                    goto end;
                } //if value is decreasing, no way to know if it's going to half or open yet
                  // we go on with detection
            } else { //Previously Open
                    //if value is increasing, no way to know if it's going to half or covered yet
                if (fingering.halfHole.sampleDirection < -HALF_HOLE_DIRECTION_LIMIT) { //value is decreasing - still opened - we can exit detection
#if DEBUG_HALF_HOLE
                    sendUSBMIDI(CC, mainMidiChannel,  17, halfHoleNow) ;
                    sendAsPitchBend(fingering.halfHole.halfHoleSamples);
                    sendAsPitchBend(fingering.halfHole.sampleDirection);
                    sendAsPitchBend(toneholeRead[hole]);
#endif
                    fingering.halfHole.halfHoleSamples = 0; //Exit half hole detection
                    toneholeHalfCovered[hole] = false;
                    goto end;
                }  //else we go on with detection
            }

            if (++fingering.halfHole.halfHoleSamples > fingering.halfHole.halfHoleBuffer) { //Exiting detection mode
#if DEBUG_HALF_HOLE
                sendUSBMIDI(CC, mainMidiChannel,  18, halfHoleNow) ;
                sendAsPitchBend(fingering.halfHole.halfHoleSamples);
                sendAsPitchBend(toneholeRead[hole]);
#endif
                fingering.halfHole.halfHoleSamples = 0; //Exit half hole detection
                toneholeHalfCovered[hole] = halfHoleNow;

            } else {
                return false; //half thumb still to be determined
            } 
        }
    } else {
        fingering.halfHole.halfHoleSamples = 0; //Exit half hole detection
    }

    end:
    toneholeLastRead[hole] = toneholeRead[hole];
    if (toneholeHalfCovered[hole]) { 
        bitWrite(holeCovered, hole, 1); //To determine the base note to be altered in fingerings
        toneholeRead[hole] = toneholeCovered[hole]; //Force read as covered
    }
    bitWrite(holeCovered, 9, toneholeHalfCovered[hole] ? 1 : 0); //To trigger fingering change

    return true; //Debounced

}

//Generic tools
//20230927 GLB
void sendMIDIPanic() {
    for (byte i = 1; i < 17; i++) {  //send MIDI panic
        sendUSBMIDI(CC, i, 123, 0);
        dronesOn = 0;  //remember that drones are off, because MIDI panic will have most likely turned them off in all apps.
        HarmonizerReset(); //remember that harmonizer is off, because MIDI panic will have most likely turned them off in all apps.
    }
}

//END GLB

//Harmonizer / Tranpose / Fixed note generic functions
//Utils function to count the number of steps in a scale
// uint8_t countSteps(uint16_t scale)
// {
//     return __builtin_popcount(scale);
//     uint8_t count = 0;
//     while (scale) {
//         count += scale & 1;
//         scale >>= 1;
//     }
//     return count;
// }

//Sends the whole current configuration
void sendHarmonizerConfiguration() {

    //Tranpose shift
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_TRANSPOSE_SHIFT);
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.transposeShift +12);
    //Fixed note 1
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_FIXED_NOTE);
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.fixedNote);

    for (uint8_t i = 0; i<HARMONIZER_VOICES; i++) {


        //Harmonizer intervals
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_INTERVAL +i);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[i].interval +12);

        //Harmonizer tonic
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_TONIC +i);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[i].tonic);

        //Harmonizer scales
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_SCALE +i);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[i].scaleIndex);
    }
}

//
//Diatonic Harmonizer Functions

//Returns the scale step the note is at in the current scale
uint8_t getStep(byte voice, byte note)
{
    //Transpose the note in the tonic octave
    while (note < harmonizer.harmonizers[voice].tonic) {
        note += 12;
    }

    return __builtin_popcount(harmonizer.harmonizers[voice].scale >> (11 - (note - harmonizer.harmonizers[voice].tonic) % 12));

    //Calculates the chromatic interval from the tonic
    // uint8_t interval = (note - harmonizer.harmonizers[voice].tonic) % 12;

    // uint8_t step = 0;

    // for(uint8_t i=11; i>=0; i--) {
    //     if (bitRead(harmonizer.harmonizers[voice].scale, i)) {
    //         step++;
    //     }
    //     if (11-i == interval) {
    //         break;
    //     }
    // }
    // return step;
}

//Returns the number of semitones from the tonic for the step
uint8_t getChromaticInterval(byte voice, uint8_t step) {
    uint8_t step_count = 0;

    for(uint8_t i=11; i>=0; i--) {
        if (bitRead(harmonizer.harmonizers[voice].scale, i)) {
            step_count++;
        }
        if (step_count == step) {
            return 11-i;
        }
    }
    return -1;
}
//Determines if a note is diatonic to current scale of harmonizer
bool isNoteDiatonic(byte voice, byte note) {
    if (harmonizer.harmonizers[voice].tonic < 0) { //no tonic set
        return true;
    }

    while (note < harmonizer.harmonizers[voice].tonic) {
        note += 12;
    }
    byte interval = abs(note-harmonizer.harmonizers[voice].tonic) % 12;
    return bitRead(harmonizer.harmonizers[voice].scale, 11-interval);
}

//Wrapper to set the base harmonizer shift interval
void setHarmonizerInterval(byte voice, int8_t value) {
    harmonizer.harmonizers[voice].interval = value;
    if (communicationMode) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_INTERVAL + voice);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[voice].interval +12);
    }
}

//Wrapper to set the base harmonizer diatonic scale
void setHarmonizerScale(byte voice, int8_t value) {
    harmonizer.harmonizers[voice].scaleIndex = value;
    harmonizer.harmonizers[voice].scale = harmonizer_scales[value];
    harmonizer.harmonizers[voice].scaleSteps = __builtin_popcount(harmonizer.harmonizers[voice].scale); //countSteps(harmonizer.harmonizers[voice].scale);

    if (communicationMode) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_SCALE + voice);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[voice].scaleIndex);
    }
}

//Wrapper to set the fixed Note
void setHarmonizerFixedNote(int8_t value) {
    if (value < 0) { //turning off
        sendUSBMIDI(NOTE_OFF, mainMidiChannel, harmonizer.fixedNote, 64);
        harmonizer.fixedNoteON = false;
    }
    harmonizer.fixedNote = value;

    if (communicationMode) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_FIXED_NOTE);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.fixedNote);
    }
}

//Wrapper to set the harmonizer tonic note
void setHarmonizerTonic(byte voice, byte value) {
    harmonizer.harmonizers[voice].tonic = value;
    if (communicationMode) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_TONIC + voice);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[voice].tonic);
    }
}

//Checks is note is the current fixed note
bool isFixedNote(byte note) {
    return harmonizer.fixedNote == note;
}

//Checks is note is one of the current voices
bool isHarmonizerCurrentNote(byte note) {
    for (byte i = 0; i < HARMONIZER_VOICES; i++) {
        if (harmonizer.harmonizers[i].currentNote == note) {
            return true;
        }
    }
    return false;
}

//Checks is note is one the current of other voices
bool isHarmonizerOtherCurrentNote(byte voice, byte note) {
    for (byte i = 0; i < HARMONIZER_VOICES; i++) {
        if (harmonizer.harmonizers[i].currentNote == note && i != voice) {
            return true;
        }
    }
    return false;
}

//Harmonizer specific voice note on method
void HarmonizerReset() {
    for (byte i = 0; i< HARMONIZER_VOICES;i++) {
        harmonizer.harmonizers[i] = {0,-1,-1,-1, harmonizer_scales[S_MAJOR],0,7};
    }
    harmonizer.fixedNote = -1;
    harmonizer.fixedNoteON = false;
    if (communicationMode) {
        sendHarmonizerConfiguration();
    }
}

void harmonizerNoteON (byte voice, byte baseNote, byte velocity) {
    if (harmonizer.harmonizers[voice].interval != 0) {
        if (harmonizer.harmonizers[voice].currentNote >= 0 
            && harmonizer.harmonizers[voice].currentNote != notePlaying
            && !isHarmonizerOtherCurrentNote(voice, harmonizer.harmonizers[voice].currentNote)) {
            harmonizerNoteOFF (voice);
        }
        harmonizer.harmonizers[voice].baseNote = baseNote;
        harmonizer.harmonizers[voice].currentNote = baseNote + harmonizer.harmonizers[voice].interval;

        bool baseNoteDiatonic = isNoteDiatonic(voice, baseNote);


        #if DEBUG_HARMONIZER
            sendUSBMIDI(CC, mainMidiChannel,  12, harmonizer.harmonizers[voice].tonic);
            sendUSBMIDI(CC, mainMidiChannel,  13, harmonizer.harmonizers[voice].scaleSteps);
            sendAsPitchBend(harmonizer.harmonizers[voice].interval);
            sendUSBMIDI(CC, mainMidiChannel,  14, baseNote);
            sendUSBMIDI(CC, mainMidiChannel,  15, harmonizer.harmonizers[voice].currentNote);
            sendUSBMIDI(CC, mainMidiChannel,  16, baseNoteDiatonic);
            sendUSBMIDI(CC, mainMidiChannel,  17, harmonizer.harmonizers[voice].tonic + harmonizer.harmonizers[voice].interval);

        #endif


        //If baseNote or interval are not diatonic, no need to adjust the harmonizer (it goes chromatic)
        //Otherwise calculates the shifted note.
        if (
            harmonizer.harmonizers[voice].tonic > 0 //tonic set
            // !isNoteDiatonic(voice, harmonizer.harmonizers[voice].currentNote) && //This doesn't work with scales containing interval > 2, we must always calculate the interval based on the step of the scale
            &&  baseNoteDiatonic
            && isNoteDiatonic(voice, harmonizer.harmonizers[voice].tonic + harmonizer.harmonizers[voice].interval) //is selected interval diatonic to the scale?
            ) {

#if DEBUG_HARMONIZER //Verbose version
            //The step of the scale corresponding to the selected interval
            uint8_t base_interval_step = getStep(voice, harmonizer.harmonizers[voice].tonic + harmonizer.harmonizers[voice].interval);

            //The step of the currently played note
            uint8_t current_note_step = getStep(voice, baseNote);

            //The musical sum of the two previous steps
            uint8_t step_from_tonic = (base_interval_step + current_note_step -1) % harmonizer.harmonizers[voice].scaleSteps;
#else
            //The musical sum of the two previous steps
            uint8_t step_from_tonic = (
                                        ( //base_interval_step
                                            getStep(voice, harmonizer.harmonizers[voice].tonic + harmonizer.harmonizers[voice].interval)
                                        )
                                        + 
                                        ( //current_note_step
                                            getStep(voice, baseNote)
                                        )
                                        -1
                                      ) % harmonizer.harmonizers[voice].scaleSteps;

#endif
            
            //Adjust last step
            if (step_from_tonic == 0) step_from_tonic = harmonizer.harmonizers[voice].scaleSteps;

#if DEBUG_HARMONIZER //Verbose version
            //the semitone distance from tonic of the harmonizer interval
            uint8_t chromatic_interval_from_tonic = getChromaticInterval(voice, step_from_tonic);

            //semitones distance from tonic of the current note
            int8_t chromatic_interval_tonic_current = (baseNote - harmonizer.harmonizers[voice].tonic) % 12;

            //semitone distance of harmonized note from current note
            int8_t chromatic_interval_landing_current = (chromatic_interval_from_tonic -  chromatic_interval_tonic_current) % 12;

            uint8_t new_note = baseNote + chromatic_interval_landing_current;
#else
            uint8_t new_note = baseNote + 
                                ( //chromatic_interval_landing_current
                                    ( //chromatic_interval_from_tonic
                                        getChromaticInterval(voice, step_from_tonic)
                                    ) -
                                    ( //chromatic_interval_tonic_current
                                        (baseNote - harmonizer.harmonizers[voice].tonic) % 12
                                    )
                                ) % 12;

#endif
            //Adjust the octave, if necessary
            if (harmonizer.harmonizers[voice].interval > 0 
                && new_note <= baseNote 
                ) {
                    new_note += 12;
            } else if (harmonizer.harmonizers[voice].interval < 0 
                       && new_note >= baseNote
                       ) {
                    new_note -= 12;
            }

            #if DEBUG_HARMONIZER
                sendUSBMIDI(CC, mainMidiChannel,  12, harmonizer.harmonizers[voice].tonic);
                sendUSBMIDI(CC, mainMidiChannel,  13, harmonizer.harmonizers[voice].scaleSteps);
                sendAsPitchBend(harmonizer.harmonizers[voice].interval);
                sendUSBMIDI(CC, mainMidiChannel,  14, base_interval_step);
                sendUSBMIDI(CC, mainMidiChannel,  15, baseNote);
                sendUSBMIDI(CC, mainMidiChannel,  16, current_note_step);
                sendUSBMIDI(CC, mainMidiChannel,  17, step_from_tonic);
                sendUSBMIDI(CC, mainMidiChannel,  18, chromatic_interval_from_tonic);
                sendAsPitchBend(chromatic_interval_tonic_current);
                sendUSBMIDI(CC, mainMidiChannel,  19, chromatic_interval_landing_current);
                sendUSBMIDI(CC, mainMidiChannel,  20, new_note);
            #endif

            harmonizer.harmonizers[voice].currentNote = new_note;
        }
        sendUSBMIDI(NOTE_ON, mainMidiChannel, harmonizer.harmonizers[voice].currentNote, (uint8_t)((float)velocity*HARMONIZER_VELOCITY));

        if (communicationMode) {
            //Harmonizer baseNote
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_BASE_NOTE + voice);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[voice].baseNote);

            //Harmonizer baseNote diatonic?
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_BASE_NOTE_DIATONIC + voice);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, baseNoteDiatonic ? 1 : 0);

            //Harmonizer currentNote
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_CURRENT_NOTE + voice);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.harmonizers[voice].currentNote);

            //Harmonizer currentNote diatonic?
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_CURRENT_NOTE_DIATONIC + voice);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, isNoteDiatonic(voice, harmonizer.harmonizers[voice].currentNote) ? 1 : 0);


        }
    }
    if (harmonizer.fixedNote >= 0 && !harmonizer.fixedNoteON) { //Send the fixed note too
        sendUSBMIDI(NOTE_ON, mainMidiChannel, harmonizer.fixedNote, (uint8_t)((float)velocity*HARMONIZER_VELOCITY));
        harmonizer.fixedNoteON = true;
        if (communicationMode) {
            //Harmonizer harmonizer.fixedNote
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_FIXED_NOTE);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.fixedNote);
        }
    }
}

//Harmonizer all voices note on method

void harmonizerNoteON (byte baseNote, byte velocity) {
    for (byte i = 0; i < HARMONIZER_VOICES; i++) {
        harmonizerNoteON (i, baseNote, velocity);
    }
}

//Harmonizer specific voice note off method
void harmonizerNoteOFF (byte voice) {
    if (harmonizer.harmonizers[voice].currentNote >= 0) {
        sendUSBMIDI(NOTE_OFF, mainMidiChannel, harmonizer.harmonizers[voice].currentNote, 64);
        harmonizer.harmonizers[voice].baseNote = -1;
        harmonizer.harmonizers[voice].currentNote = -1;
    }
    if (harmonizer.fixedNote >= 0) { //Send the fixed note too
        sendUSBMIDI(NOTE_OFF, mainMidiChannel, harmonizer.fixedNote, 64); 
        harmonizer.fixedNoteON = false;
    }
}

//Harmonizer all voices note off method
void harmonizerNoteOFF () {
    for (byte i = 0; i < HARMONIZER_VOICES; i++) {
        harmonizerNoteOFF (i);
    }
}


//20231005 New custom fingering management

//Loads from EEPROM
void loadCustomFingering() {
    byte totalCounter = 0;
    byte currentCounter = 0;

    for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
        byte midi_note = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4);
        if (midi_note < 0xFF ) { //otherwise it's disabled/inactive
            byte tmp_fingeringSelector = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 1);
            if (tmp_fingeringSelector == fingeringSelector) { //It applies to current fingering schema
                fingering.custom_fingering[currentCounter].midi_note = midi_note;
                fingering.custom_fingering[currentCounter].fingeringSelector = tmp_fingeringSelector;
                // byte high = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 2);
                // byte low = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 3);
                // fingering.custom_fingering[currentCounter].holeCovered =  word(high, low);
                fingering.custom_fingering[currentCounter].holeCovered = readIntFromEEPROM(EEPROM_CUSTOM_FINGERING_START + i*4 + 2);
                currentCounter++;
            }
            totalCounter ++;
        }
    }
    fingering.customFingeringCurrentNumber = currentCounter;
    fingering.customFingeringTotalNumber = totalCounter;

    sendCustomFingering();
}

//Erases all custom Fingerings
void resetAllCustomFingering() {

    for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
        if (EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4) < 0xFF) { //otherwise it's already disabled/inactive
            EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, 0xFF);
        }
    }
    fingering.customFingeringTotalNumber = 0;
    fingering.customFingeringCurrentNumber = 0;

    loadCustomFingering();

}

//Erases all custom Fingerings for current fingeringSelector
void resetCustomFingeringForCurrent() {

    for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
        if (EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4) < 0xFF) { //otherwise it's already disabled/inactive
            if (EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 1) == fingeringSelector) { //It applies to current fingering schema
                EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, 0xFF);
            }
        }
    }
    loadCustomFingering();
}

int8_t getCustomFingeringNote(uint16_t fingerPattern) {
    for (byte i = 0; i < fingering.customFingeringCurrentNumber; i++) {
        if (fingering.custom_fingering[i].holeCovered == fingerPattern) {
            return fingering.custom_fingering[i].midi_note;
        }
    }
    return 0x7f;
}

bool deleteCustomFingeringNote(uint16_t fingerPattern) {
    for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
        byte midi_note = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4);
        if (midi_note < 0xFF) { //otherwise it's disabled/inactive
            byte tmp_fingeringSelector = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 1);
            if (tmp_fingeringSelector == fingeringSelector) { //It applies to current fingering schema
                // byte high = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 2);
                // byte low = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 3);
                // uint16_t tmp_holeCovered =  word(high, low);
                uint16_t tmp_holeCovered = readIntFromEEPROM(EEPROM_CUSTOM_FINGERING_START + i*4 + 2);
                if (tmp_holeCovered == fingerPattern) {
                    EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, 0xFF);
                    return true;
                }
            }
        }
    }
    return false;
}

bool updateCustomFingeringNote(byte midiNote, uint16_t fingerPattern) {
    for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
        byte midi_note = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4);
        if (midi_note < 0xFF) { //otherwise it's disabled/inactive or different
            byte tmp_fingeringSelector = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 1);
            if (tmp_fingeringSelector == fingeringSelector) { //It applies to current fingering schema
                // byte high = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 2);
                // byte low = EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 3);
                // uint16_t tmp_holeCovered =  word(high, low);
                uint16_t tmp_holeCovered = readIntFromEEPROM(EEPROM_CUSTOM_FINGERING_START + i*4 + 2);
                if (tmp_holeCovered == fingerPattern) {
                    EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, midiNote);
                    return true;
                }
            }
        }
    }
    return false;
}
//Save custom Fingerings
bool saveCustomFingering(byte midiNote, uint16_t fingerPattern) {

    if (fingering.customFingeringTotalNumber >= CUSTOM_FINGERING_MAX ) {  //It shouldn't happen, but still we check...
        return false;
    }

    if (midiNote == get_note(fingerPattern)) { // it's not different from default We delete it
        if (deleteCustomFingeringNote(fingerPattern)) {
            loadCustomFingering();
            return true;

        }
        return false;
    }

    if (getCustomFingeringNote(fingerPattern) == 0x7f) { //it doesn't already exists 
        for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
            if (EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4) == 0xFF) { //finds the first free spot
                EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, midiNote);
                EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4 + 1, fingeringSelector);
                
                // EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4 + 2, highByte(fingerPattern));
                // EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4 + 3, lowByte(fingerPattern));
                writeIntToEEPROM(EEPROM_CUSTOM_FINGERING_START + i*4 + 2, fingerPattern);
                loadCustomFingering();
                return true;
            }
        }
    } else { //it already exists, updates it
        if (updateCustomFingeringNote(midiNote, fingerPattern)) {
            loadCustomFingering();
            return true;
        }
    }
    return false;
}

//Sends all custom fignerings
void sendCustomFingering() {
        if (communicationMode) {
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING); //Entering custom fingering trasmission mode
            for (byte i = 0; i < fingering.customFingeringCurrentNumber; i++) {
                sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.custom_fingering[i].midi_note);
                sendHoleCovered(fingering.custom_fingering[i].holeCovered);
            }
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING); //Exiting custom fingering trasmission mode

            //Sends the number for current scheme
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING_CURRENT);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.customFingeringCurrentNumber);

            //Sends the total number of custom fingerings
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING_TOTAL); //Exiting custom fingering trasmission mode
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.customFingeringTotalNumber);
        }
}