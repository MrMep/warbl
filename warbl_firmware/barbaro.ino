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

    - Added Half hole management for left thumb and R3-R4, with configuration in the config tool.
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

*/
#include "defines.h"
#include "types.h"

//Globals
bool toneholeHalfCovered[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0 };         //storage for half-covered tonehole


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


//Initializes runtime parameters
void rt_init() {
    //General
    // bytes[RT_BYTE_BLINK_NUMBER] = 1;
    fingering.halfHole.currentHoleSettings = 99; //disabled

    resetHalfHoleConfig();

    //Harmonizer
    for (byte i = 0; i <HARMONIZER_VOICES; i++) {
        harmonizer.harmonizers[i] = {0,-1,-1,-1, harmonizer_scales[S_MAJOR],0,7 };
    }

}

//EEPROM Utils for ints
int readIntFromEEPROM(uint16_t address) {
    return word(EEPROM.read(address), EEPROM.read(address+1));
}
void writeIntToEEPROM(uint16_t address, int value) {
    EEPROM.update(address, highByte(value));
    EEPROM.update(address + 1, lowByte(value));
} 

//Util to send int values to the config tool between -8192 and + 8192
void sendIntValue(byte valueIndex, int value) {
    if (communicationMode) {
        value += 8192;
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_13, valueIndex);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_14, (value >> 7) &0x7F);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_15, lowByte(value) & 0x7F);
    }
}

//Resets saved Half Hole Calibration values
void resetHalfHoleConfig() {
    fingering.halfHole.buffer = HALF_HOLE_BUFFER_SIZE;
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        fingering.halfHole.enabled[i] = false;
    }
    fingering.halfHole.enabled[THUMB_HOLE] = true;
    fingering.halfHole.enabled[R3_HOLE] = true;
    fingering.halfHole.enabled[R4_HOLE] = true;
    
}

//Loads Half Hole Detection parameters
void  loadHalfHoleConfig() {
    fingering.halfHole.buffer = EEPROM.read(EEPROM_HALF_HOLE_BUFFER_SIZE);
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        fingering.halfHole.enabled[i] = EEPROM.read(EEPROM_HALF_HOLE_ENABLED + i);
    }
}
//Saves Half Hole Detection parameters
void  saveHalfHoleConfig() {
    EEPROM.update(EEPROM_HALF_HOLE_BUFFER_SIZE, fingering.halfHole.buffer);
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        EEPROM.update(EEPROM_HALF_HOLE_ENABLED + i, fingering.halfHole.enabled[i]);
    }
}

//Always call UpperBound first, to calculate correction
uint16_t getHalfHoleLowerBound(byte hole) {
    return getHalfHoleUpperBound(hole) + HALF_HOLE_LOWER_OFFSET;
}

uint16_t getHalfHoleUpperBound(byte hole) {
    if (!fingering.halfHole.enabled[hole]) {
        return 1024;
    }
    return toneholeCovered[hole] - HOLE_OPEN_OFFSET + HALF_HOLE_UPPER_OFFSET + fingering.halfHole.correction*5.0;
}

//Calculates the baseline moving average for readings in the current time window and applies an eventual correction factor to half hole detection
void baselineUpdate() {
    byte counter = 0;
    baselineCurrentAverage = 0;
    for (byte i = 0; i<TONEHOLE_SENSOR_NUMBER; i++) {

        if (toneholeBaselineCurrent[i] >= 0 && toneholeBaselineCurrent[i] <= maxBaseline)  { //LPF
            baselineCurrentAverage += toneholeBaselineCurrent[i];
            counter++;
        }
        toneholeBaselineCurrent[i] = 1024; //Resets for next run

        //Updates baseline too with previous average - Useful for PB
        toneholeBaseline[i] = ((float) toneholeBaseline[i] * baselinePreviousAverage/baselineAverage);
    }
    if (counter > 0 ) { //Found usable values
        baselineCurrentAverage = BASELINE_AVRG_SPEED*((baselineCurrentAverage / (float) counter)*BASELINE_MACRO_FACTOR) + (1.0-BASELINE_AVRG_SPEED)*baselinePreviousAverage;
        if (baselinePreviousAverage != baselineCurrentAverage) {
            fingering.halfHole.correction = (baselineCurrentAverage - baselineAverage)/BASELINE_MACRO_FACTOR;
            baselinePreviousAverage = baselineCurrentAverage;
            if (communicationMode) {
                sendIntValue(MIDI_SEND_BASELINE_CURRENT_AVERAGE, baselineCurrentAverage - baselineAverage);
            }
        }
    }
}

//Sends the calculated limit and other paramenters for Half hole detection
void sendHalfHoleParams( int hole) {

    if (communicationMode && hole < TONEHOLE_SENSOR_NUMBER ) { //we send debug info to the config tool

        //Sends current Hole
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HALFHOLE_CURRENT);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, fingering.halfHole.currentHoleSettings);

        //Sends current Hole upperLimit
        sendIntValue(MIDI_SEND_HALFHOLE_MAX, getHalfHoleUpperBound(hole) );

        //Sends current Hole lowerLimit
        sendIntValue(MIDI_SEND_HALFHOLE_MIN, getHalfHoleLowerBound(hole) );

        //Sends current Hole Read 
        sendIntValue(MIDI_SEND_TONE_READ_0 + hole, toneholeLastRead[hole]);

        //Sends current hole Calibration baseline
        sendIntValue(MIDI_SEND_TONE_BASELINE_0 + hole, toneholeBaseline[hole]);

        //Sends current hole Calibration
        sendIntValue(MIDI_SEND_TONE_COVERED_0 + hole, toneholeCovered[hole]);

    }
}

//returns if the selected hole is half covered
bool isHalfHole(int hole) {
    if (!fingering.halfHole.enabled[hole]) return false; //disabled
    return toneholeRead[hole] <  getHalfHoleUpperBound(hole) && toneholeRead[hole] > getHalfHoleLowerBound(hole);
}




//Harmonizer / Tranpose / Fixed note generic functions

//Sends the whole current configuration
void sendHarmonizerConfiguration() {

    if (communicationMode) {
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
    sendHarmonizerConfiguration();
}

//Wrapper to set the base harmonizer diatonic scale
void setHarmonizerScale(byte voice, int8_t value) {
    harmonizer.harmonizers[voice].scaleIndex = value;
    harmonizer.harmonizers[voice].scale = harmonizer_scales[value];
    harmonizer.harmonizers[voice].scaleSteps = __builtin_popcount(harmonizer.harmonizers[voice].scale); //countSteps(harmonizer.harmonizers[voice].scale);

    sendHarmonizerConfiguration();
}

//Wrapper to set the fixed Note
void setHarmonizerFixedNote(int8_t value) {
    if (value < 0) { //turning off
        sendUSBMIDI(NOTE_OFF, mainMidiChannel, harmonizer.fixedNote, 64);
        harmonizer.fixedNoteON = false;
    }
    harmonizer.fixedNote = value;

    sendHarmonizerConfiguration();
}

//Wrapper to set the harmonizer tonic note
void setHarmonizerTonic(byte voice, byte value) {
    harmonizer.harmonizers[voice].tonic = value;
    sendHarmonizerConfiguration();
}

//20231021
//is note currently used by the harmonizer? If not, closes it
bool noteOFFIfOK(byte note) {
    if (harmonizer.fixedNote == note) {
        return false;
    }
    for (byte i = 0; i < HARMONIZER_VOICES; i++) {
        if (harmonizer.harmonizers[i].currentNote == note) {
            return false;
        }
    }

    sendUSBMIDI(NOTE_OFF, mainMidiChannel, note, 64);
    return true;
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
    
    sendHarmonizerConfiguration();
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

        sendHarmonizerConfiguration();
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

//Genral manager for custom finger operations
bool manageCustomFingerings(byte operation, byte midiNote, uint16_t fingerPattern) {

    bool result = false;
    for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
        if (EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4) < 0xFF) { //otherwise it's disabled/inactive
            if (operation == ResetAll) { 
                EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, 0xFF);
            } else if (EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4 + 1) == fingeringSelector) { //It applies to current fingering schema
                if (operation == ResetForCurrent) {
                    EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, 0xFF);
                } else if (readIntFromEEPROM(EEPROM_CUSTOM_FINGERING_START + i*4 + 2) == fingerPattern) {
                    if (operation == Delete) {
                        EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, 0xFF);
                        result =  true;
                    } else if (operation == Update) {
                        EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, midiNote);
                        result = true;
                    }
                }
            }
        }
    }
    if (operation == ResetAll) {
        fingering.customFingeringTotalNumber = 0;
        fingering.customFingeringCurrentNumber = 0;
        result =  true;
    }
    if (operation == ResetForCurrent) {
        result = true;
    }
    if (result) {
        loadCustomFingering();
    }

    return result;
}

int8_t getCustomFingeringNote(uint16_t fingerPattern) {
    for (byte i = 0; i < fingering.customFingeringCurrentNumber; i++) {
        if (fingering.custom_fingering[i].holeCovered == fingerPattern) {
            return fingering.custom_fingering[i].midi_note;
        }
    }
    return 0x7f;
}

//Save custom Fingerings
bool saveCustomFingering(byte midiNote, uint16_t fingerPattern) {

    if (fingering.customFingeringTotalNumber >= CUSTOM_FINGERING_MAX ) {  //It shouldn't happen, but still we check...
        return false;
    }

    if (midiNote == get_note(fingerPattern, false)) { // it's not different from default We delete it
        return manageCustomFingerings(customFingeringOperations::Delete, 0, fingerPattern);

        return false;
    }

    if (getCustomFingeringNote(fingerPattern) == 0x7f) { //it doesn't already exists 
        for (byte i = 0; i < CUSTOM_FINGERING_MAX; i++) {
            if (EEPROM.read(EEPROM_CUSTOM_FINGERING_START + i*4) == 0xFF) { //finds the first free spot
                EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4, midiNote);
                EEPROM.update(EEPROM_CUSTOM_FINGERING_START + i*4 + 1, fingeringSelector);
                writeIntToEEPROM(EEPROM_CUSTOM_FINGERING_START + i*4 + 2, fingerPattern);
                loadCustomFingering();
                return true;
            }
        }
    } else { //it already exists, updates it
        return manageCustomFingerings(customFingeringOperations::Update, midiNote, fingerPattern);
    }
    return false;
}

//Sends all custom fingerings
void sendCustomFingering() {
    if (communicationMode) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING); //Entering custom fingering trasmission mode
        
        for (byte i = 0; i < fingering.customFingeringCurrentNumber; i++) {
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.custom_fingering[i].midi_note);
            sendIntValue(MIDI_SEND_HOLE_COVERED, fingering.custom_fingering[i].holeCovered);
        }
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING); //Exiting custom fingering trasmission mode

        //Sends the number for current scheme
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING_CURRENT);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.customFingeringCurrentNumber);

        //Sends the total number of custom fingerings
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING_TOTAL);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.customFingeringTotalNumber);
    }
}

