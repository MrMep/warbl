/*
*   Type defines
*
*/
#ifndef TYPES_H
#define TYPES_H


//Runtime types

//20231005 GLB New custom fingering
/*
    midi_note: the associated midi note
    fingeringSelector: the associated fingerPattern ID
    hole covered:   
        first 8 bits: holes from 0 = R4 to 8 = thumb
        last 8 bits: half holes: 0 = thumb, 1 = R4, 2 = R3 for now
*/
struct custom_fingering_t {
    uint8_t midi_note;
    uint8_t fingeringSelector;
    uint16_t holeCovered; //bit mast of holes and half hole
};

//HALF HOLE DETECTION
struct rt_half_hole_detection_t {

    byte buffer;
    byte samples = 0;
    
    uint16_t prevSampleValue = 0;

    int sampleDirection = 0;
    byte currentHoleSettings = -1;

    float correction = 0;
    bool enabled[TONEHOLE_SENSOR_NUMBER];
};

struct rt_fingering_t {
    //To hold in sram the current table
    custom_fingering_t custom_fingering[CUSTOM_FINGERING_MAX];

    //Temp fingering entry for receiving from Config tool
    custom_fingering_t temp_custom_fingering;

    //Total number of custom fingerings memorized
    uint8_t customFingeringTotalNumber = 0;

    //Number of custom fingerings applied to current fingeringSelector
    uint8_t customFingeringCurrentNumber = 0;

    //Are we receiving a custom fingerin pattern?
    bool customFingeringReceivingStatus = false;

    rt_half_hole_detection_t halfHole;      //Half-Hole Detecion

};

//Harmonizer 

//GLB Harmonizer base type (for each of the three harmonizers)
struct harmonizer_t {
    int8_t interval;      //interval of harmonizer
    int8_t baseNote;    //current base note
    int8_t currentNote; //Current played note
    int8_t tonic;
    uint16_t scale;
    uint8_t scaleIndex;
    uint8_t  scaleSteps;
};


struct rt_harmonizer_t {
    int8_t transposeShift = 0; //note transposition, for transposer function
    int8_t prevTransposeShift = 0; //note transposition, for momentary action
    int8_t fixedNote = -1; //Note to be played along current note.
    bool fixedNoteON = false;
    harmonizer_t harmonizers[HARMONIZER_VOICES];
};


rt_fingering_t fingering; // Fingering Parameters
rt_harmonizer_t harmonizer; //Harmonizer Parameters

#endif //TYPES_H