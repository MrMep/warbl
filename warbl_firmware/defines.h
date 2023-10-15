/*
*   Defines and management of MIDI and EEPROM for saved preferences and other parameters
*
*/
#ifndef DEFINES_H
#define DEFINES_H

#define VERSION 23  //software version number (without decimal point)
#define hardwareRevision 31  //hardware revision number (without decimal point)
#define BUILD_VERSION 1 //GLB Build, 0 = factory

//GLB Specific
//Half Thumb hole detection
#define DEBUG_HALF_HOLE           0
#define HALF_HOLE_BUFFER_SIZE    30
#define THUMB_HOLE                8
#define R4_HOLE                   1
#define R3_HOLE                   2

#define HALF_HOLE_DIRECTION_LIMIT    HALF_HOLE_BUFFER_SIZE/2

//Harmonizer
#define DEBUG_HARMONIZER    0
#define HARMONIZER_VOICES   3
#define HARMONIZER_VOICE_1    0
#define HARMONIZER_VOICE_2    1
#define HARMONIZER_VOICE_3    2
#define HARMONIZER_VELOCITY    0.5

//Harmonizer Scales Types
#define S_MAJOR                 0
#define S_MELODIC_MINOR         1
#define S_HARMONIC_MINOR        2
#define S_DIMINISHED_1_SCALE    3
#define S_DIMINISHED_2_SCALE    4
#define S_AUGMENTED_1_SCALE     5
#define S_AUGMENTED_2_SCALE     6
#define S_WHOLETONE_SCALE       7
#define S_BEBOP_MAJOR_SCALE     8
#define S_BEBOP_DOMINANT_SCALE  9
#define S_PENTA_MAJOR_SCALE     10
#define S_PENTA_MINOR_SCALE     11
#define S_BLUES_SCALE           12
#define S_SCALE_NUMBER          13

//Scale definition for diatonic harmonization
#define MAJOR_SCALE             0b101011010101
#define MELODIC_MINOR_SCALE     0b101101010101
#define HARMONIC_MINOR_SCALE    0b101101011001
#define DIMINISHED_1_SCALE      0b110110110110
#define DIMINISHED_2_SCALE      0b101101101101
#define AUGMENTED_1_SCALE       0b100110011001
#define AUGMENTED_2_SCALE       0b110011001100
#define WHOLETONE_SCALE         0b101010101010
#define BEBOP_MAJOR_SCALE       0b101011011101
#define BEBOP_DOMINANT_SCALE    0b101011010111
#define PENTA_MAJOR_SCALE       0b101010010100
#define PENTA_MINOR_SCALE       0b100101010010
#define BLUES_SCALE             0b101101110010

//General Paramenters
#define GPIO2_PREFER_SPEED 1  //digitalread speed, see: https://github.com/Locoduino/DIO2/blob/master/examples/standard_outputs/standard_outputs.ino

#define DEBOUNCE_TIME 0.02    //button debounce time, in seconds---Integrating debouncing algorithm is taken from debounce.c, written by Kenneth A. Kuhn:http://www.kennethkuhn.com/electronics/debounce.c
#define SAMPLE_FREQUENCY 200  //button sample frequency, in Hz

#define MAXIMUM (DEBOUNCE_TIME * SAMPLE_FREQUENCY)  //the integrator value required to register a button press

#define PRESET_NUMBER                             3 //Number of instruments
#define SENSOR_NUMBER                            10 //Number of thone hole sensors + bell
#define TONEHOLE_SENSOR_NUMBER                    9 //Number of thone hole sensors + bell
#define BUTTONS_MAX_ACTIONS                      18 //Number of maximum actions associated to buttons
#define CUSTOM_FINGERING_MAX                     30 //Max number of custom fingering

//Button Actions
#define ACTION_NONE                 0
#define ACTION_MIDI                 1
#define ACTION_VIBRATO_MODE         2
#define ACTION_CHANGE_INSTRUMENT    3
#define ACTION_PLAY_STOP            4
#define ACTION_TRANSPOSE            5
#define ACTION_FIXED_NOTE           6
#define ACTION_MIDI_PANIC           7
#define ACTION_REGISTER_MODE        8
#define ACTION_TOGGLE_DRONE         9
#define ACTION_HARMONIZER_1         10
#define ACTION_HARMONIZER_2         11
#define ACTION_HARMONIZER_3         12
#define ACTION_CALIBRATE            13


// Fingering Patterns
#define kModeWhistle 0
#define kModeUilleann 1
#define kModeGHB 2
#define kModeNorthumbrian 3
#define kModeChromatic 4
#define kModeGaita 5
#define kModeNAF 6
#define kModeKaval 7
#define kModeRecorder 8
#define kModeBansuriWARBL 9       //only used for a custom regulators implementation, not the "official" software, or BansuriWARBL
#define kModeUilleannStandard 10  //contains no accidentals
#define kModeXiao 11
#define kModeSax 12
#define kModeGaitaExtended 13
#define kModeSaxBasic 14
#define kModeEVI 15
#define kModeShakuhachi 16
#define kModeSackpipaMajor 17
#define kModeSackpipaMinor 18
#define kModeCustom 19
#define kModeBombarde 20
#define kModeBaroqueFlute 21
#define kModeMedievalPipes 22
#define kModeBarbaro 23
#define kModeNModes 24

// Pitch bend modes
#define kPitchBendSlideVibrato 0
#define kPitchBendVibrato 1
#define kPitchBendNone 2
#define kPitchBendLegatoSlideVibrato 3
#define kPitchBendNModes 4

// Register control modes
#define kPressureSingle 0
#define kPressureBreath 1
#define kPressureThumb 2
#define kPressureBell 3
#define kPressureNModes 4

// Drones control mode
#define kNoDroneControl 0
#define kSecretDroneControl 1
#define kBaglessDroneControl 2
#define kPressureDroneControl 3
#define kDroneNModes 4

//used in register state machine
#define SILENCE 1
#define BOTTOM_REGISTER 2
#define TOP_REGISTER 3
#define SILENCE_HYSTERESIS 1
#define JUMP 0
#define DROP 1

//Variables in the switches array (settings for the swiches in the slide/vibrato and register control panels)
#define VENTED 0
#define BAGLESS 1
#define SECRET 2
#define INVERT 3
#define CUSTOM 4
#define SEND_VELOCITY 5
#define SEND_AFTERTOUCH 6  //second bit of this one is used for poly
#define FORCE_MAX_VELOCITY 7
#define IMMEDIATE_PB 8
#define LEGATO 9
#define OVERRIDE 10
#define THUMB_AND_OVERBLOW 11
#define R4_FLATTEN 12
#define kSWITCHESnVariables 13

//Variables in the ED array (all the settings for the Expression and Drones panels)
#define EXPRESSION_ON 0
#define EXPRESSION_DEPTH 1
#define SEND_PRESSURE 2
#define CURVE 3  // (0 is linear, 1 and 2 are power curves)
#define PRESSURE_CHANNEL 4
#define PRESSURE_CC 5
#define INPUT_PRESSURE_MIN 6
#define INPUT_PRESSURE_MAX 7
#define OUTPUT_PRESSURE_MIN 8
#define OUTPUT_PRESSURE_MAX 9
#define DRONES_ON_COMMAND 10
#define DRONES_ON_CHANNEL 11
#define DRONES_ON_BYTE2 12
#define DRONES_ON_BYTE3 13
#define DRONES_OFF_COMMAND 14
#define DRONES_OFF_CHANNEL 15
#define DRONES_OFF_BYTE2 16
#define DRONES_OFF_BYTE3 17
#define DRONES_CONTROL_MODE 18
#define DRONES_PRESSURE_LOW_BYTE 19
#define DRONES_PRESSURE_HIGH_BYTE 20
#define VELOCITY_INPUT_PRESSURE_MIN 21
#define VELOCITY_INPUT_PRESSURE_MAX 22
#define VELOCITY_OUTPUT_PRESSURE_MIN 23
#define VELOCITY_OUTPUT_PRESSURE_MAX 24
#define AFTERTOUCH_INPUT_PRESSURE_MIN 25
#define AFTERTOUCH_INPUT_PRESSURE_MAX 26
#define AFTERTOUCH_OUTPUT_PRESSURE_MIN 27
#define AFTERTOUCH_OUTPUT_PRESSURE_MAX 28
#define POLY_INPUT_PRESSURE_MIN 29
#define POLY_INPUT_PRESSURE_MAX 30
#define POLY_OUTPUT_PRESSURE_MIN 31
#define POLY_OUTPUT_PRESSURE_MAX 32
#define VELOCITY_CURVE 33
#define AFTERTOUCH_CURVE 34
#define POLY_CURVE 35
#define EXPRESSION_MIN 36
#define EXPRESSION_MAX 37
// #define CUSTOM_FINGERING_1 38
// #define CUSTOM_FINGERING_2 39
// #define CUSTOM_FINGERING_3 40
// #define CUSTOM_FINGERING_4 41
// #define CUSTOM_FINGERING_5 42
// #define CUSTOM_FINGERING_6 43
// #define CUSTOM_FINGERING_7 44
// #define CUSTOM_FINGERING_8 45
// #define CUSTOM_FINGERING_9 46
// #define CUSTOM_FINGERING_10 47
// #define CUSTOM_FINGERING_11 48
#define kEXPRESSIONnVariables 38


//MIDI Defs
//Midi configuration
#define MIDI_CONF_CHANNEL                     7 //Midi channel

// MIDI CCs 102 -119 are "undefined" in standard MIDI 

#define MIDI_SLOT_02                     102 //base CC
    #define MIDI_SAVE_CALIB                   19 //Data
    #define MIDI_CALIB_SLOW_OS                20 //Data
    // #define MIDI_SEND_FINGER_PATTERN_OS       30 //Offset
    // #define MIDI_SEND_MODE_SELECTOR_OS        33 //Offset
    #define MIDI_CURRENT_INSTR_OS             60 //Offset
    #define MIDI_PB_MODE_OS                   63 //Offset Was 70
    #define MIDI_BREATH_MODE_OS               68 //Offset Was 80
    #define MIDI_DEFAULT_INSTR_OS             73 //Offset Was 85
    #define MIDI_SEND_BUTTON_PREF_OS          76 //Offset Was 90
    #define MIDI_SEND_MOMENTARY_OS            76 //Offset Was 90

    #define MIDI_SEND_CUSTOM_FINGERING	         84 //Activates the trasmission of a custom fingering scheme
    #define MIDI_SEND_CUSTOM_FINGERING_NOTE	     85 //	Note corresponding to current fingerPAttern
    #define MIDI_SEND_CUSTOM_FINGERING_CURRENT   86 //	Number of custom fignering for current schema
    #define MIDI_SEND_CUSTOM_FINGERING_TOTAL     87 //	Total number of custom fingerings
    #define MIDI_DELETE_CUSTOM_FINGERING_CURRENT 88 //Delete all custom fignerings for current selector
    #define MIDI_DELETE_CUSTOM_FINGERING         89 //Delete all custom fingerings

    #define MIDI_TURN_OFF_COMM                90 //Offset Was 99
    #define MIDI_BUTTON_PREF_ACTION_OS        91 //Offset Was 100 *** MAX 18 *** ->109

    #define MIDI_BUTTON_PREF_MIDI_CMD_OS     110 //Offset Was 112
    #define MIDI_MOMENTARY_OFF_OS            115 //Offset Was 117
    #define MIDI_MOMENTARY_ON_OS             116 //Offset Was 118
    #define MIDI_BUTTON_AUTO_CALIB_OS        117 //Offset Was 119
    #define MIDI_BELL_SENSOR_OS              118 //Offset Was 120

    #define MIDI_DUMP_SETTINGS_CURRENT       121 //Offset

    #define MIDI_DUMP_EEPROM                 122 //Offset
    #define MIDI_SAVE_SETTING_CURRENT        123 //Offset
    #define MIDI_SAVE_SETTING_ALL            124 //Offset
    #define MIDI_RESTORE_FACTORY_SETTING     125 //Offset
    #define MIDI_SEND_SETTINGS               126 //Offset
    #define MIDI_AUTO_CALIB                  127 //Offset


#define MIDI_SLOT_03                     103 //base CC senseDistanceSelector

#define MIDI_SLOT_04                     104 //base CC 
    #define MIDI_SEND_PRESSURE_VARS_OS         0 //Offset - PRessure VARS 0-12

    #define MIDI_SEND_EXPRESSION_VARS_1_OS     13 //Offset - Espression VARS 13 + (0/20) ->  33
    #define MIDI_SEND_EXPRESSION_DEPTH         14 
    #define MIDI_SEND_LSB_LEARN_DRONE_PRESS_OS 32 //Offset
    #define MIDI_SEND_MSB_LEARN_DRONE_PRESS_OS 33 //Offset
    #define MIDI_SEND_LSB_LEARN_PRESS_OS       34 //Offset
    #define MIDI_SEND_MSB_LEARN_PRESS_OS       35 //Offset

    #define MIDI_SEND_SWITCH_VARS_OS           40 //Offset -  kSWITCHESnVariables == 13 -> 52

    #define MIDI_SEND_EXPRESSION_VARS_2_OS     49 //Offset - +21/48 (kEXPRESSIONnVariables) == 70/87
    #define MIDI_SEND_BEND_RANGE_OS            61 //Offset
    #define MIDI_SEND_MIDI_CHAN_OS             62 //Offset

    #define MIDI_SEND_TRANSPOSE_SHIFT                    100 //Offset 0=-12 ... 24=+12
    #define MIDI_SEND_HARMONIZER_FIXED_NOTE              101 //Offset 
    #define MIDI_SEND_HARMONIZER_INTERVAL                102 //Offset +2  0=-12 ... 24=+12
    #define MIDI_SEND_HARMONIZER_TONIC                   105 //Offset +2 0=C ... 11=B
    #define MIDI_SEND_HARMONIZER_SCALE                   108 //Offset +2 
    #define MIDI_SEND_HARMONIZER_BASE_NOTE               111 //Offset +2  0=C ... 11=B
    #define MIDI_SEND_HARMONIZER_BASE_NOTE_DIATONIC      114 //Offset +2 0/1
    #define MIDI_SEND_HARMONIZER_CURRENT_NOTE            117 //Offset +2  0=C ... 11=B
    #define MIDI_SEND_HARMONIZER_CURRENT_NOTE_DIATONIC   120 //Offset +2 0/1

    #define MIDI_SEND_HALFHOLE_BUFFER                    123
    #define MIDI_SEND_HALFHOLE_CURRENT                   124 //current hole
    #define MIDI_SEND_HALFHOLE_SAVE_CURRENT              125 //SAves calibration and transient
    // #define MIDI_SEND_HALFHOLE_CURRENT_READ              125 //toneholeCovered[hole]
    // #define MIDI_SEND_HALFHOLE_MIN                       126 //lowerLimit
    // #define MIDI_SEND_HALFHOLE_MAX                       127 //upperLimit

#define MIDI_SLOT_05                     105 //base CC - switches values

#define MIDI_SLOT_06                     106 //base CC
/*
From 0 to 15 button actions MIDI Channel
*/
    #define MIDI_EN_VIBRATO_HOLES_OS          20 //Offset
    #define MIDI_CALIB_OPTION_OS              39 //Offset
    #define MIDI_USE_LEARN_PRESS_OFF          39 //Offset
    #define MIDI_USE_LEARN_PRESS_ON           40 //Offset
    #define MIDI_SEND_LEARN_PRESS             41 //Offset
    #define MIDI_AUTO_CALIB_BELL              42 //Offset
    #define MIDI_SEND_LEARN_PRESS_DRONE       43 //Offset
    #define MIDI_SAVE_CALIB_AS_FACTORY        45 //Offset

    // #define MIDI_SEND_DEBUG_LSB_OS            48 //Offset
    // #define MIDI_SEND_DEBUG_MSB_OS            49 //Offset
    // #define MIDI_DEBUG_2BYTE_MSG_OS           51 //Offset

#define MIDI_SLOT_07                     107 //base CC buttons actions byte2
#define MIDI_SLOT_08                     108 //base CC buttons actions byte3

#define MIDI_SLOT_09                     109 //CC Custom Fingering msgs

#define MIDI_SW_VERSION                  110 //CC
#define MIDI_SW_BUILD_VERSION            111 //CC


#define MIDI_SLOT_12                     112 //base CC WAS 11 OFFSET +2 - noteShiftSelector //Not used anymore

#define MIDI_SLOT_13                     113 //base To send int values

    #define MIDI_SEND_HOLE_COVERED            10 // Current holeCovered Value
    #define MIDI_SEND_KEY_SELECT              12 //noteshiftSelector
    #define MIDI_SEND_MODE_SELECTOR           30 // Sends fingering scheme index for preset  Value + 0/2 -> 32

    #define MIDI_SEND_HALFHOLE_CALIBRATION    90 //lowerLimit
    #define MIDI_SEND_HALFHOLE_MIN            91 //lowerLimit
    #define MIDI_SEND_HALFHOLE_MAX            92 //upperLimit

    #define MIDI_SEND_TONE_COVERED_0         100 // Calibration for hole 0
    #define MIDI_SEND_TONE_COVERED_1         101 // Calibration for hole 1
    #define MIDI_SEND_TONE_COVERED_2         102 // Calibration for hole 2
    #define MIDI_SEND_TONE_COVERED_3         103 // Calibration for hole 3
    #define MIDI_SEND_TONE_COVERED_4         104 // Calibration for hole 4
    #define MIDI_SEND_TONE_COVERED_5         105 // Calibration for hole 5
    #define MIDI_SEND_TONE_COVERED_6         106 // Calibration for hole 6
    #define MIDI_SEND_TONE_COVERED_7         107 // Calibration for hole 7
    #define MIDI_SEND_TONE_COVERED_8         108 // Calibration for hole 8

    #define MIDI_SEND_TONE_READ_0            110 // Sensor read value for hole 0
    #define MIDI_SEND_TONE_READ_1            111 // Sensor read value for hole 1
    #define MIDI_SEND_TONE_READ_2            112 // Sensor read value for hole 2
    #define MIDI_SEND_TONE_READ_3            113 // Sensor read value for hole 3
    #define MIDI_SEND_TONE_READ_4            114 // Sensor read value for hole 4
    #define MIDI_SEND_TONE_READ_5            115 // Sensor read value for hole 5
    #define MIDI_SEND_TONE_READ_6            116 // Sensor read value for hole 6
    #define MIDI_SEND_TONE_READ_7            117 // Sensor read value for hole 7
    #define MIDI_SEND_TONE_READ_8            118 // Sensor read value for hole 8

    #define MIDI_SEND_DEBUG                  127 //Sends debug info


#define MIDI_SLOT_14                     114 //base CC High Byte
#define MIDI_SLOT_15                     115 //base CC Low Byte


#define MIDI_SLOT_16                     116 //base CC - FREE
#define MIDI_SLOT_17                     117 //base CC - vibrato depth 
#define MIDI_SLOT_18                     118 //base CC FREE
#define MIDI_SLOT_19                     119 //base CC FREE


//MIDI commands
#define NOTE_OFF                0x80  //127
#define NOTE_ON                 0x90  // 144
#define KEY_PRESSURE            0xA0  // 160
#define CC                      0xB0  // 176
#define PROGRAM_CHANGE          0xC0  // 192
#define CHANNEL_PRESSURE        0xD0  // 208
#define PITCH_BEND              0xE0  // 224


//EEPROM Addresses & Parameters
#define EEPROM_SENSOR_CALIB_FACTORY               0 //Base Address
#define EEPROM_SENSOR_CALIB_CURRENT              SENSOR_NUMBER*2 //Base Address

#define EEPROM_CALIBRATION_SAVED                 37 //Base Address

#define EEPROM_FINGERING_SELECTOR                     40 //Base Address

#define EEPROM_SETTINGS_SAVED                    44 //Base Address

#define EEPROM_DEFAULT_PRESET                      48 //Base Address

#define EEPROM_SENSEDISTANCE_SELECTOR            50 //Base Address
#define EEPROM_NOTESHIFT_SELECTOR                53 //Base Address
#define EEPROM_SWITCHES                          56 //Base Address

#define EEPROM_BUTTON_PREFS                     100 //Base Address
#define EEPROM_BUTTON_PREFS_SLOT                 50 //Distancing between instruments
#define EEPROM_BUTTON_PREFS_NUMBER               10 //Number of actions

#define EEPROM_MOMENTARY_ACTIONS                250 //Base Address

#define EEPROM_PRESSURE_SELECTOR                260 //Base Address
#define EEPROM_PRESSURE_SELECTOR_SLOT            20 //Distancing between instruments

#define EEPROM_LEARNPRESS_SELECTOR              273 //Base Address
#define EEPROM_PB_MODE_SELECTOR                 313 //Base Address
#define EEPROM_BREATH_MODE_SELECTOR             316 //Base Address
#define EEPROM_BEND_RANGE_SELECTOR              319 //Base Address
#define EEPROM_MIDI_CHANNEL_SELECTOR            322 //Base Address


#define EEPROM_VIBRATOHOLE_SELECTOR             333 //Base Address
#define EEPROM_VIBRATODEPTH_SELECTOR            339 //Base Address
#define EEPROM_USE_LEARNPRESS_SELECTOR          345 //Base Address

#define EEPROM_EXPRESSION_VARS                  351 //Base Address up to 497


#define EEPROM_SENSOR_CALIB_BASELINE_FACTORY    731 //Base Address up 70 739
#define EEPROM_SENSOR_CALIB_BASELINE_CURRENT    EEPROM_SENSOR_CALIB_BASELINE_FACTORY-SENSOR_NUMBER  //Base Address 721

#define EEPROM_HALF_HOLE_BUFFER_SIZE            799 //Current transient max value

#define EEPROM_CUSTOM_FINGERING_START           800  //Base address for new custom fingering. 
                                                     // Each custom fingering takes 4 byte: Midi note, fingeringSelectr and fingering mask (16bit)
                                                     // Ends at 919

#define EEPROM_HALF_HOLE_CALIBRATION            960  //Base address for half hole calibration for 8 holes * 4 bytes (lower/upper)

#define EEPROM_SW_VERSION                      1011 //Base Address
#define EEPROM_HW_VERSION                      1012 //Base Address
#define EEPROM_SW_CUSTOM_BUILD                 1013 //Base Address


#endif //#define DEFINES_H