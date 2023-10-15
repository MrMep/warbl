/*
    Creates default configuration for all three instruments
*/


void setDefaultConfiguration(byte preset) {
    if (preset >= 0 || preset < PRESET_NUMBER ) {
        //Same defaults for all
        senseDistanceSelector = 10;
        vibratoHolesSelector = 0b011111111; 
        vibratoDepthSelector = 1024;

        for (byte j = 0; j < 5; j++) {  
            for (byte k = 0; k < 8; k++) {
                buttonPrefs[k][j] = 0;
            }
        }

        for (byte h = 0; h < 3; h++) {
            momentary[h] = 0;
        }

    byte tmp_pressureSelector[] = { 50, 20, 20, 15, 50, 75,
                            3, 7, 20, 0, 12, 50 }; 
        for (byte q = 0; q < 12; q++) {
            pressureSelector[q] = tmp_pressureSelector[q];
        }

        pitchBendModeSelector = 1;
        midiBendRangeSelector = 2;
        midiChannelSelector = 1;

        switch (preset) {
            default:
            case 0:
            {
                fingeringSelector = kModeWhistle;
                noteShiftSelector = 0;

                byte tmp_switches[] = { 1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
                for (byte n = 0; n < kSWITCHESnVariables; n++) {
                    switches[n] = tmp_switches[n];
                }
                
                useLearnedPressureSelector = 0;
                learnedPressureSelector = 0;
                breathModeSelector = 1;

                byte tmp_ED[] = { 0, 3, 0, 0, 1, 7, 0, 100, 0, 127, 0, 1, 51, 36, 0, 1, 51, 36, 0, 0, 0, 0, 100, 0, 127, 0, 100, 0, 127, 0, 100, 0, 127, 0, 0, 0, 0, 100 };
                for (byte n = 0; n < kEXPRESSIONnVariables; n++) {
                    ED[n] = tmp_ED[n];
                }
            }
            break;

            case 1:
            {
                fingeringSelector = kModeUilleann;
                noteShiftSelector = 0;
                byte tmp_switches[] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
                for (byte n = 0; n < kSWITCHESnVariables; n++) {
                    switches[n] = tmp_switches[n];
                }
                useLearnedPressureSelector = 1;
                learnedPressureSelector = 280;
                breathModeSelector = 1;
                byte tmp_ED[] = { 0, 3, 0, 0, 1, 7, 0, 100, 0, 127, 0, 1, 51, 36, 0, 1, 51, 36, 0, 0, 0, 0, 127, 0, 127, 0, 127, 0, 127, 0, 127, 0, 127, 0, 0, 0, 0, 100 };
                for (byte n = 0; n < kEXPRESSIONnVariables; n++) {
                    ED[n] = tmp_ED[n];
                }
            }
            break;

            case 2:
            {
                fingeringSelector = kModeGHB;
                noteShiftSelector = 8;
                byte tmp_switches[] = { 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
                for (byte n = 0; n < kSWITCHESnVariables; n++) {
                    switches[n] = tmp_switches[n];
                }
                useLearnedPressureSelector = 1;
                learnedPressureSelector = 475 ;
                breathModeSelector = 0;
                byte tmp_ED[] = { 0, 3, 0, 0, 1, 7, 0, 100, 0, 127, 0, 1, 51, 36, 0, 1, 51, 36, 0, 0, 0, 0, 127, 0, 127, 0, 127, 0, 127, 0, 127, 0, 127, 0, 0, 0, 0, 100 };            
                for (byte n = 0; n < kEXPRESSIONnVariables; n++) {
                    ED[n] = tmp_ED[n];
                }
            }
            break;
        }
    }
}


//This is used the first time the software is run, to copy all the default settings to EEPROM, and is also used to restore factory settings.
void saveFactorySettings() {


    for (byte i = 0; i < 3; i++) {  //save all the current settings for all three instruments.
        setDefaultConfiguration(i);
        currentPreset = i;
        saveSettings(i);
    }

    for (byte i = EEPROM_SENSOR_CALIB_FACTORY; i < EEPROM_SENSOR_CALIB_CURRENT; i++) {  //copy sensor calibration from factory settings location (copy 0-17 to 18-35).
        EEPROM.update((i + EEPROM_SENSOR_CALIB_CURRENT), EEPROM.read(i));
    }

    for (int i = EEPROM_SENSOR_CALIB_BASELINE_CURRENT; i < EEPROM_SENSOR_CALIB_BASELINE_FACTORY; i++) {  //copy sensor baseline calibration from factory settings location.
        EEPROM.update((i), EEPROM.read(i + 10));
    }

    //New custom fingering
    resetAllCustomFingering();

    EEPROM.update(EEPROM_DEFAULT_PRESET, defaultPreset);  //save default currentPreset

    EEPROM.update(EEPROM_SETTINGS_SAVED, 3);  //indicates settings have been saved



    blinkNumber = 3;
}