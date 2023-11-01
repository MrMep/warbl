#include "defines.h"
#include "types.h"


//Monitor the status of the 3 buttons. The integrating debouncing algorithm is taken from debounce.c, written by Kenneth A. Kuhn:http://www.kennethkuhn.com/electronics/debounce.c
void checkButtons() {
    for (byte j = 0; j < 3; j++) {

        if (digitalRead2f(buttons[j]) == 0) {    //if the button reads low, reduce the integrator by 1
            if (integrator[j] > 0) {
                integrator[j]--;
            }
        } else if (integrator[j] < MAXIMUM) {    //if the button reads high, increase the integrator by 1
            integrator[j]++;
        }


        if (integrator[j] == 0) {    //the button is pressed.
            pressed[j] = 1;                    //we make the output the inverse of the input so that a pressed button reads as a "1".
            buttonUsed = 1;                    //flag that there's been button activity, so we know to handle it.

            if (prevOutput[j] == 0 && !longPressUsed[j]) {
                justPressed[j] = 1;    //the button has just been pressed
            }

            else {
                justPressed[j] = 0;
            }

            if (prevOutput[j] == 1) {    //increase a counter so we know when a button has been held for a long press
                longPressCounter[j]++;
            }
        } else if (integrator[j] >= MAXIMUM) {    //the button is not pressed
            pressed[j] = 0;
            integrator[j] = MAXIMUM;    // defensive code if integrator got corrupted

            if (prevOutput[j] == 1 && !longPressUsed[j]) {
                released[j] = 1;    //the button has just been released
                buttonUsed = 1;
            }

            longPress[j] = 0;
            longPressUsed[j] = 0;    //if a button is not pressed, reset the flag that tells us it's been used for a long press.
            longPressCounter[j] = 0;
        }

        if (longPressCounter[j] > 300 && !longPressUsed[j]) {    //if the counter gets to a certain level, it's a long press
            longPress[j] = 1;
        }

        prevOutput[j] = pressed[j];    //keep track of state for next time around.
    }
}

//Key delay feature for delaying response to tone holes and filtering out transient notes, by Louis Barman
bool debounceFingerHoles() {

    if (holeCovered == lastHoleCovered) {    //After a twitch returns to last recognized fingering, does nothing //If note is not on, we don't care //tempNewNote could be silent
        return false;
    }

    if (prevHoleCovered != holeCovered) {
        prevHoleCovered = holeCovered;
        int tempNewNote = get_note(holeCovered, false);

        if (tempNewNote >= 0 && noteon //Valid note and currently playin
                && (
                        abs(tempNewNote - notePlaying) > 11 //the interval for the current fingered note is an octave or more
                        || abs(__builtin_popcount(lastHoleCovered) - __builtin_popcount(holeCovered)) >= 4 //the number of changed finger is > 5,
                        || abs(toneholeLastRead[THUMB_HOLE] - toneholeRead[THUMB_HOLE]) > HOLE_COVERED_OFFSET/2 //Thumb hole is changing
                        )
                ) {
            transientFilter =    ((pressureSelector[9] + fingering.halfHole.buffer) / 1.25); //it adds up to the transient Filter
        } else {
                transientFilter = ((pressureSelector[9] + 1) / 1.25);
        }
        holeDebounceCounter = transientFilter + 1;
    }

    if (toneholesReady) {                         //use this as a timer (~1.25 mS)
        if (holeDebounceCounter > 0) {    //slight changes by AM to prevent a 1 mS delay with a setting of 0.
            holeDebounceCounter--;
            if (holeDebounceCounter == 0) {
                return true;
            }
        }
    }

    return false;
}



void ADC_init(void) {

    ADCSRA &= ~(bit(ADPS0) | bit(ADPS1) | bit(ADPS2));    // clear ADC prescaler bits
    if (EEPROM.read(EEPROM_HW_VERSION) == 31) {
        ADCSRA = (1 << ADEN) | ((1 << ADPS2) | (1 << ADPS0));    //32 (60 uS) some versions of the tone hole sensors have a longer rise time
                                                                                                                     //ADCSRA |= bit(ADPS1) | bit(ADPS2);    //    64 (110 uS)
    } else {
        ADCSRA = (1 << ADEN) | ((1 << ADPS2));    // enable ADC Division Factor 16 (36 uS)
    }
    ADMUX = (1 << REFS0);    //Voltage reference from Avcc (3.3v)
    ADC_read(1);                     //start an initial conversion (pressure sensor), which will also enable the ADC complete interrupt and trigger subsequent conversions.
}


        

//start an ADC conversion.
void ADC_read(byte pin) {

    if (pin >= 18) pin -= 18;    // allow for channel or pin numbers
    pin = analogPinToChannel(pin);

    ADCSRB = (ADCSRB & ~(1 << MUX5)) | (((pin >> 3) & 0x01) << MUX5);
    ADMUX = (1 << REFS0) | (pin & 0x07);

    ADCSRA |= bit(ADSC) | bit(ADIE);    //start a conversion and enable the ADC complete interrupt
}

// ADC complete ISR for reading sensors. We read the sensors asynchronously by starting a conversion and then coming back by interrupt when it is complete.
ISR(ADC_vect) {

    byte prev = 8;
    if (lastRead != 0) {
        prev = lastRead - 1;
    }

    byte next = lastRead + 1;
    if (lastRead == 8) {
        next = 0;
    }

    if (lastRead == 9) {    //this time is different because we're about to take a short break and read the pressure sensor.

        digitalWrite2f(pins[8], LOW);                                            //turn off the previous LED
        tempToneholeRead[8] = (ADC)-tempToneholeReadA[8];    //get the previous illuminated reading and subtract the ambient light reading
        toneholesReadyInterupt = true;
        Timer1.resume();    //start the timer to take a short break, conserving some power.
        return;
    }

    if (firstTime) {
        if (lastRead == 0) {
            tempSensorValue = (ADC);    //we've just returned from starting the pressure sensor reading, so get the conversion and flag that it is ready.
            sensorDataReady = 1;
        } else {
            digitalWrite2f(pins[prev], LOW);                                                 //turn off the previous LED
            tempToneholeRead[prev] = (ADC)-tempToneholeReadA[prev];    //get the previous illuminated reading and subtract the ambient light reading
        }
        ADC_read(holeTrans[next]);    // start ambient reading for next sensor
        firstTime = 0;
        if (lastRead != 0) {
            digitalWrite2f(pins[lastRead], HIGH);    //turn on the current LED
        }
        return;
    }

    //if !firstTime (implied, because we wouldn't have gotten this far otherwise)
    tempToneholeReadA[next] = (ADC);    //get the ambient reading for the next sensor
    ADC_read(holeTrans[lastRead]);        //start illuminated reading for current sensor
    firstTime = 1;
    lastRead++;
}



//Timer ISR for adding a small delay after reading new sensors, to conserve a bit of power and give the processor time to catch up if necesary.
void timerDelay(void) {

    timerCycle++;

    if (timerCycle == 2) {
        digitalWrite2f(pins[0], HIGH);    //turn on the LED for the bell sensor (this won't use any power if the sensor isn't plugged in). It will be on for ~170 uS, which is necesary because it's a slower sensor than the others.
        return;
    }

    if (timerCycle == 3) {
        Timer1.stop();    //stop the timer after running twice to add a delay.
        ADC_read(4);        //start reading the pressure sensor (pinA4).
        firstTime = 1;
        lastRead = 0;
        timerCycle = 0;
    }
    //if timerCycle is 1 we just return and wait until next time.
}


//Determine which holes are covered
void get_fingers() {

    byte bitSet = 0;

    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {

        if (fingering.halfHole.enabled[i]) {
            bool halfHoleNow = isHalfHole(i);
            int thRead = toneholeRead[i];

            byte bitOffset = 9;    //For forcing a change in holeCovered
            if ((i == R4_HOLE || i == R3_HOLE)) {
                bitOffset += i;
            }

            if (halfHoleNow) {
                bitWrite(holeCovered, bitOffset, 1);     //To trigger fingering change
                toneholeHalfCovered[i] = true;                 //for get_note
                thRead = toneholeCovered[i];    //Force read as covered
            } else {
                bitWrite(holeCovered, bitOffset, 0);    //To trigger fingering change
                toneholeHalfCovered[i] = false;             //for get_note
            } 

            if (thRead > getHalfHoleUpperBound(i)) {
                bitSet = 1;
            } else if (thRead < getHalfHoleLowerBound(i)) {
                bitSet = 0;
            }

        } else {
            if ((toneholeRead[i]) > (toneholeCovered[i] - HOLE_COVERED_OFFSET)) {
                bitSet = 1;
            } else if ((toneholeRead[i]) <= (toneholeCovered[i] - HOLE_OPEN_OFFSET)) {
                bitSet = 0;
            }
        }

        bitWrite(holeCovered, i, bitSet);    //use the tonehole readings to decide which holes are covered
    }
}





//Send the pattern of covered holes to the Configuration Tool
void send_fingers(uint8_t defaultNote, uint8_t customNote) {

    if (communicationMode) {    //send information about which holes are covered to the Configuration Tool if we're connected. Because it's MIDI we have to send it in two 7-bit chunks.
        // sendHoleCovered(holeCovered);
        sendIntValue(MIDI_SEND_HOLE_COVERED, holeCovered);
        //20231005 GLB - New custom fingering
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING_NOTE);
        if (customNote >= 0 && customNote < 127) {
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, customNote);
        } else {
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, 0x7F);
        }

        if (defaultNote <= 127) {
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, defaultNote < 0 ? 0 : defaultNote);
        }

        //Sends Half hole sensor info
        sendHalfHoleParams(fingering.halfHole.currentHoleSettings);
        //END GLB
    }
}











//Add up any transposition based on key and register.
void get_shift() {

    //20230927 GLB
    // shift = ((octaveShift * 12) + noteShift);    //adjust for key and octave shift.
    shift = (noteShift + harmonizer.transposeShift);    //adjust for key and octave shift.

    //END GLB

    //if (newState == 3 && !(fingeringSelector == kModeEVI || (fingeringSelector == kModeSax && newNote < 62) || (fingeringSelector == kModeSaxBasic && newNote < 74) || (fingeringSelector == kModeRecorder && newNote < 76)) && !(newNote == 62 && (fingeringSelector == kModeUilleann || fingeringSelector == kModeUilleannStandard))) {    //if overblowing (except EVI, sax in the lower register, and low D with uilleann fingering, which can't overblow)
    if (newState == 3 && !(fingeringSelector == kModeEVI || (fingeringSelector == kModeSax && newNote < 62) || (fingeringSelector == kModeSaxBasic && newNote < 74)) && !(newNote == 62 && (fingeringSelector == kModeUilleann || fingeringSelector == kModeUilleannStandard))) {    //if overblowing (except EVI, sax in the lower register, and low D with uilleann fingering, which can't overblow)
        shift = shift + 12;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    //add a register jump to the transposition if overblowing.
        if (fingeringSelector == kModeKaval) {                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             //Kaval only plays a fifth higher in the second register.
            shift = shift - 5;
        }
    }

    if (breathMode == kPressureBell && fingeringSelector != kModeUilleann && fingeringSelector != kModeUilleannStandard) {    //if we're using the bell sensor to control register
        if (bitRead(holeCovered, 0) == switches[INVERT]) {
            shift = shift + 12;    //add a register jump to the transposition if necessary.
            if (fingeringSelector == kModeKaval) {
                shift = shift - 5;
            }
        }
    }

    // else if ((breathMode == kPressureThumb && (fingeringSelector == kModeWhistle || fingeringSelector == kModeChromatic || fingeringSelector == kModeNAF || fingeringSelector == kModeBansuriWARBL || fingeringSelector == kModeCustom)) || (breathMode == kPressureBreath && fingeringSelector == kModeCustom && switches[THUMB_AND_OVERBLOW])) {    //if we're using the left thumb to control the regiser with a fingering patern that doesn't normally use the thumb
    else if ((breathMode == kPressureThumb && (fingeringSelector == kModeWhistle || fingeringSelector == kModeChromatic || fingeringSelector == kModeNAF || fingeringSelector == kModeBansuriWARBL ))) {    //if we're using the left thumb to control the regiser with a fingering patern that doesn't normally use the thumb

        if (bitRead(holeCovered, 8) == switches[INVERT]) {
            shift = shift + 12;    //add an octave jump to the transposition if necessary.
        }
    }

    //Some charts require another transposition to bring them to the correct key
    if (fingeringSelector == kModeGaita || fingeringSelector == kModeGaitaExtended) {
        shift = shift - 1;
    }

    if (fingeringSelector == kModeSax || fingeringSelector == kModeBarbaroEWI || fingeringSelector == kModeBarbaroRecorder) {
        shift = shift + 2;
    }

    if (fingeringSelector == kModeBansuriWARBL) {
        shift = shift - 5;
    }
}





//State machine that models the way that a tinwhistle etc. begins sounding and jumps octaves in response to breath pressure.
//The jump/drop behavior is from Louis Barman
void get_state() {

    noInterrupts();
    sensorValue2 = tempSensorValue;    //transfer last reading to a non-volatile variable
    interrupts();


    byte scalePosition = newNote;

    // if (fingeringSelector == kModeCustom) {
    //     scalePosition = 110 - customScalePosition;    //scalePosition is used to tell where we are on the scale, because higher notes are more difficult to overblow.
    // } else {
    //     scalePosition = newNote;
    // }

    if (ED[DRONES_CONTROL_MODE] == 3) {    //use pressure to control drones if that option has been selected. There's a small amount of hysteresis added.

        if (!dronesOn && sensorValue2 > 5 + (ED[DRONES_PRESSURE_HIGH_BYTE] << 7 | ED[DRONES_PRESSURE_LOW_BYTE])) {
            startDrones();
        }

        else if (dronesOn && sensorValue2 < (ED[DRONES_PRESSURE_HIGH_BYTE] << 7 | ED[DRONES_PRESSURE_LOW_BYTE])) {
            stopDrones();
        }
    }

    upperBound = (sensorThreshold[1] + ((scalePosition - 60) * multiplier));    //calculate the threshold between state 2 (bottom register) and state 3 (top register). This will also be used to calculate expression.


    newState = currentState;

    if (sensorValue2 <= sensorThreshold[0]) {
        newState = SILENCE;
        holdoffActive = false;    //no need to wait for jump/drop if we've already crossed the threshold for silence
    } else if (sensorValue2 > sensorThreshold[0] + SILENCE_HYSTERESIS) {
        if (currentState == SILENCE) {
            newState = BOTTOM_REGISTER;
        }

        // if (breathMode == kPressureBreath || (breathMode == kPressureThumb && fingeringSelector == kModeCustom && switches[THUMB_AND_OVERBLOW])) {    //if overblowing is enabled
        if (breathMode == kPressureBreath) {    //if overblowing is enabled
            upperBoundHigh = calcHysteresis(upperBound, true);
            upperBoundLow = calcHysteresis(upperBound, false);
            if (sensorValue2 > upperBoundHigh) {
                newState = TOP_REGISTER;
                holdoffActive = false;
            } else if (sensorValue2 <= upperBoundLow) {
                newState = BOTTOM_REGISTER;
            }

            //wait to decide about jump or drop if necessary
            if (currentState == SILENCE && newState == BOTTOM_REGISTER) {
                newState = delayStateChange(JUMP, sensorValue2, upperBoundHigh);
            } else if (currentState == TOP_REGISTER && newState == BOTTOM_REGISTER && (millis() - fingeringChangeTimer) > 20) {    //only delay for drop if the note has been playing for a bit. This fixes erroneous high-register notes
                newState = delayStateChange(DROP, sensorValue2, upperBoundLow);
            }
        }
    }

    currentState = newState;
    sensorValue = sensorValue2;    //we'll use the current reading as the baseline next time around, so we can monitor the rate of change.
    sensorDataReady = 0;                 //we've used the sensor reading, so don't use it again
}






//Delay the overblow state until either it has timed out or the pressure has leveled off.
byte delayStateChange(byte jumpDrop, int pressure, int upper) {


    if (!holdoffActive) {    //start our timer if we haven't already
        holdoffActive = true;
        if (jumpDrop == JUMP) {
            holdoffCounter = jumpTime + 1;    //AM add 1 to make sure jumpTime and dropTime are never set to 0, as this function won't work.
        } else {
            holdoffCounter = dropTime + 1;
        }
        rateChangeIdx = 0;
        previousPressure = 0;
        previousAverage1 = 0;
        previousAverage2 = 0;
    }

    if (holdoffCounter > 0) {
        holdoffCounter--;

        bool exitEarly = false;

        //if we've paused long enough or the pressure has stabilized, go to the bottom register
        int rateChange = pressureRateChange(pressure);
        if (rateChange != 2000) {    //make sure it's valid
            if (jumpDrop == JUMP && rateChange <= 0) {
                exitEarly = true;
            } else if (jumpDrop == DROP && rateChange >= 0) {
                exitEarly = true;
            }
        }


        if (holdoffCounter == 0 || exitEarly) {
            holdoffActive = false;
            return BOTTOM_REGISTER;
        }
    }

    return currentState;    //stay in the current state if we haven't waited the total time and the pressure hasn't yet leveled off.
}







//Calculates how fast (the rate) pressures is changing, from Louis Barman
int pressureRateChange(int pressure) {

    int rateChange = 2000;    //if not valid
    if (rateChangeIdx == 0) {
        rateChangeIdx = 1;
        previousPressure = pressure;
    } else {
        rateChangeIdx = 0;
        // no need to divide the average by the number of entries so we don't loose resolution
        int average = pressure + previousPressure;

        // check we have enough readings to be valid
        if (previousAverage2 > 0) {
            rateChange = average - previousAverage2;
        }

        // this works as a very fast FIFO (first in first out) with a length 3
        previousAverage2 = previousAverage1;
        previousAverage1 = average;
    }
    return rateChange;
}









//calculate the upper boundary for the register when hysteresis is applied, from Louis Barman
int calcHysteresis(int currentUpperBound, bool high) {
    if (hysteresis == 0) {
        return currentUpperBound;
    }
    int range = currentUpperBound - sensorThreshold[0];
    int newUpperBound;
    if (high) {
        newUpperBound = currentUpperBound + (range * hysteresis) / 400;
    } else {
        newUpperBound = currentUpperBound - (range * hysteresis * 3) / 400;
    }

    return newUpperBound;
}








//calculate pitchbend expression based on pressure
void getExpression() {

    //calculate the center pressure value for the current note, regardless of register, unless "override" is turned on and we're not in overblow mode. In that case, use the override bounds instead


    int lowerBound;
    int useUpperBound;

    if (switches[OVERRIDE] && (breathMode != kPressureBreath)) {
        lowerBound = (ED[EXPRESSION_MIN] * 9) + 100;
        useUpperBound = (ED[EXPRESSION_MAX] * 9) + 100;
    } else {
        lowerBound = sensorThreshold[0];
        if (newState == 3) {
            useUpperBound = upperBoundLow;    //get the register boundary taking hysteresis into consideration
        } else {
            useUpperBound = upperBoundHigh;
        }
    }

    unsigned int halfway = ((useUpperBound - lowerBound) >> 1) + lowerBound;    //calculate the midpoint of the curent register, where the note should play in tune.

    if (newState == 3) {
        halfway = useUpperBound + halfway;
        lowerBound = useUpperBound;
    }

    if (sensorValue < halfway) {
        byte scale = (((halfway - sensorValue) * ED[EXPRESSION_DEPTH] * 20) / (halfway - lowerBound));    //should maybe figure out how to do this without dividing.
        expression = -((scale * scale) >> 3);
    } else {
        expression = (sensorValue - halfway) * ED[EXPRESSION_DEPTH];
    }


    if (expression > ED[EXPRESSION_DEPTH] * 200) {
        expression = ED[EXPRESSION_DEPTH] * 200;    //put a cap on it, because in the upper register or in single-register mode, there's no upper limit
    }


    if (pitchBendMode == kPitchBendNone) {    //if we're not using vibrato, send the pitchbend now instead of adding it in later.
        pitchBend = 0;
        sendPitchbend();
    }
}






//find how many steps down to the next lower note on the scale.
void findStepsDown() {

    slideHole = findleftmostunsetbit(holeCovered);    //determine the highest uncovered hole, to use for sliding
    if (slideHole == 127) {                                                 //this means no holes are covered.
        // this could mean the highest hole is starting to be uncovered, so use that as the slideHole
        slideHole = 7;
        //return;
    }
    unsigned int closedSlideholePattern = holeCovered;
    bitSet(closedSlideholePattern, slideHole);                                                                        //figure out what the fingering pattern would be if we closed the slide hole
    stepsDown = constrain(tempNewNote - get_note(closedSlideholePattern, false), 0, 2);    //and then figure out how many steps down it would be if a new note were triggered with that pattern.
}








//Custom pitchbend algorithms, tin whistle and uilleann by Michael Eskin
void handleCustomPitchBend() {

    iPitchBend[2] = 0;    //reset pitchbend for the holes that are being used
    iPitchBend[3] = 0;

    if (pitchBendMode == kPitchBendSlideVibrato || pitchBendMode == kPitchBendLegatoSlideVibrato) {    //calculate slide if necessary.
        getSlide();
    }


    if (fingeringSelector != kModeGHB && fingeringSelector != kModeNorthumbrian) {    //only used for whistle and uilleann
        if (vibratoEnable == 1) {                                                                                                         //if it's a vibrato fingering pattern
            if (slideHole != 2) {
                iPitchBend[2] = adjvibdepth;    //just assign max vibrato depth to a hole that isn't being used for sliding (it doesn't matter which hole, it's just so it will be added in later).
                iPitchBend[3] = 0;
            } else {
                iPitchBend[3] = adjvibdepth;
                iPitchBend[2] = 0;
            }
        }




        if (vibratoEnable == 0b000010) {    //used for whistle and uilleann, indicates that it's a pattern where lowering finger 2 or 3 partway would trigger progressive vibrato.

            if (fingeringSelector == kModeWhistle || fingeringSelector == kModeChromatic) {
                for (byte i = 2; i < 4; i++) {
                    if ((toneholeReadForPB[i] > senseDistance) && (bitRead(holeCovered, i) != 1 && (i != slideHole))) {    //if the hole is contributing, bend down
                        iPitchBend[i] = ((toneholeReadForPB[i] - senseDistance) * vibratoScale[i]) >> 3;
                    } else if (i != slideHole) {
                        iPitchBend[i] = 0;
                    }
                }
                if (iPitchBend[2] + iPitchBend[3] > adjvibdepth) {
                    iPitchBend[2] = adjvibdepth;    //cap at max vibrato depth if they combine to add up to more than that (just set one to max and the other to zero)
                    iPitchBend[3] = 0;
                }
            }


            else if (fingeringSelector == kModeUilleann || fingeringSelector == kModeUilleannStandard) {

                // If the back-D is open, and the vibrato hole completely open, max the pitch bend
                if ((holeCovered & 0b100000000) == 0) {
                    if (bitRead(holeCovered, 3) == 1) {
                        iPitchBend[3] = 0;
                    } else {
                        // Otherwise, bend down proportional to distance
                        if (toneholeReadForPB[3] > senseDistance) {
                            iPitchBend[3] = adjvibdepth - (((toneholeReadForPB[3] - senseDistance) * vibratoScale[3]) >> 3);
                        } else {
                            iPitchBend[3] = adjvibdepth;
                        }
                    }
                } else {

                    if ((toneholeReadForPB[3] > senseDistance) && (bitRead(holeCovered, 3) != 1) && 3 != slideHole) {
                        iPitchBend[3] = ((toneholeReadForPB[3] - senseDistance) * vibratoScale[3]) >> 3;
                    }

                    else if ((toneholeReadForPB[3] < senseDistance) || (bitRead(holeCovered, 3) == 1)) {
                        iPitchBend[3] = 0;    // If the finger is removed or the hole is fully covered, there's no pitchbend contributed by that hole.
                    }
                }
            }
        }

    }


    else if (fingeringSelector == kModeGHB || fingeringSelector == kModeNorthumbrian) {    //this one is designed for closed fingering patterns, so raising a finger sharpens the note.
        for (byte i = 2; i < 4; i++) {                                                                                                         //use holes 2 and 3 for vibrato
            if (i != slideHole || (holeCovered & 0b100000000) == 0) {
                static unsigned int testNote;                                         // the hypothetical note that would be played if a finger were lowered all the way
                if (bitRead(holeCovered, i) != 1) {                             //if the hole is not fully covered
                    if (fingersChanged) {                                                     //if the fingering pattern has changed
                        testNote = get_note(bitSet(holeCovered, i), false);    //check to see what the new note would be
                        fingersChanged = 0;
                    }
                    if (testNote == newNote) {    //if the hole is uncovered and covering the hole wouldn't change the current note (or the left thumb hole is uncovered, because that case isn't included in the fingering chart)
                        if (toneholeReadForPB[i] > senseDistance) {
                            iPitchBend[i] = 0 - (((toneholeCovered[i] - 50 - toneholeReadForPB[i]) * vibratoScale[i]) >> 3);    //bend up, yielding a negative pitchbend value
                        } else {
                            iPitchBend[i] = 0 - adjvibdepth;    //if the hole is totally uncovered, max the pitchbend
                        }
                    }
                } else {                            //if the hole is covered
                    iPitchBend[i] = 0;    //reset the pitchbend to 0
                }
            }
        }
        if ((((iPitchBend[2] + iPitchBend[3]) * -1) > adjvibdepth) && ((slideHole != 2 && slideHole != 3) || (holeCovered & 0b100000000) == 0)) {    //cap at vibrato depth if more than one hole is contributing and they add to up to more than the vibrato depth.
            iPitchBend[2] = 0 - adjvibdepth;                                                                                                                                                                                                                 //assign max vibrato depth to a hole that isn't being used for sliding
            iPitchBend[3] = 0;
        }
    }
    sendPitchbend();
}






//Andrew's version of vibrato
void handlePitchBend() {

    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {    //reset
        iPitchBend[i] = 0;
    }


    if (pitchBendMode == kPitchBendSlideVibrato || pitchBendMode == kPitchBendLegatoSlideVibrato) {    //calculate slide if necessary.
        getSlide();
    }


    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {

        if (bitRead(holeLatched, i) == 1 && toneholeReadForPB[i] < senseDistance) {
            (bitWrite(holeLatched, i, 0));    //we "unlatch" (enable for vibrato) a hole if it was covered when the note was triggered but now the finger has been completely removed.
        }

        if (bitRead(vibratoHoles, i) == 1 && bitRead(holeLatched, i) == 0 && (pitchBendMode == kPitchBendVibrato || i != slideHole)) {    //if this is a vibrato hole and we're in a mode that uses vibrato, and the hole is unlatched
            if (toneholeReadForPB[i] > senseDistance) {
                if (bitRead(holeCovered, i) != 1) {
                    iPitchBend[i] = (((toneholeReadForPB[i] - senseDistance) * vibratoScale[i]) >> 3);    //bend downward
                    pitchBendOn[i] = 1;
                }
            } else {
                pitchBendOn[i] = 0;
                if (bitRead(holeCovered, i) == 1) {
                    iPitchBend[i] = 0;
                }
            }

            if (pitchBendOn[i] == 1 && (bitRead(holeCovered, i) == 1)) {
                iPitchBend[i] = adjvibdepth;    //set vibrato to max downward bend if a hole was being used to bend down and now is covered
            }
        }
    }

    sendPitchbend();
}






//calculate slide pitchBend, to be added with vibrato.
void getSlide() {
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        if (toneholeReadForPB[i] > senseDistance && i == slideHole && stepsDown > 0) {
            if (bitRead(holeCovered, i) != 1) {
                iPitchBend[i] = ((toneholeReadForPB[i] - senseDistance) * toneholeScale[i]) >> (4 - stepsDown);    //bend down toward the next lowest note in the scale, the amount of bend depending on the number of steps down.
            }
        } else {
            iPitchBend[i] = 0;
        }
    }
}







void sendPitchbend() {


    pitchBend = 0;    //reset the overall pitchbend in preparation for adding up the contributions from all the toneholes.
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        pitchBend = pitchBend + iPitchBend[i];
    }

    int noteshift = 0;
    if (noteon && pitchBendModeSelector == kPitchBendLegatoSlideVibrato) {
        noteshift = (notePlaying - shift) - newNote;
        pitchBend += noteshift * pitchBendPerSemi;
    }

    pitchBend = 8192 - pitchBend + expression;
    if (pitchBend < 0) {
        pitchBend = 0;
    } else if (pitchBend > 16383) {
        pitchBend = 16383;
    }

    if (prevPitchBend != pitchBend) {

        if (noteon) {

            sendUSBMIDI(PITCH_BEND, mainMidiChannel, pitchBend & 0x7F, pitchBend >> 7);
            prevPitchBend = pitchBend;
        }
    }
}


void calculateAndSendPitchbend() {
    if (ED[EXPRESSION_ON] && !switches[BAGLESS]) {
        getExpression();    //calculate pitchbend based on pressure reading
    }

    if (!customEnabled && pitchBendMode != kPitchBendNone) {
        handlePitchBend();
    } else if (customEnabled) {
        handleCustomPitchBend();
    }
}




//send MIDI NoteOn/NoteOff events when necessary
void sendNote() {
    const int velDelayMs = switches[SEND_AFTERTOUCH] != 0 ? 3 : 16;    // keep this minimal to avoid latency if also sending aftertouch, but enough to get a good reading, otherwise use longer

    if (    //several conditions to tell if we need to turn on a new note.
        (!noteon
         || (pitchBendModeSelector != kPitchBendLegatoSlideVibrato && newNote != (notePlaying - shift))
         || (pitchBendModeSelector == kPitchBendLegatoSlideVibrato && abs(newNote - (notePlaying - shift)) > midiBendRange - 1))
        &&                                                                                                                                                                                    //if there wasn't any note playing or the current note is different than the previous one
        ((newState > 1 && !switches[BAGLESS]) || (switches[BAGLESS] && play)) &&                                        //and the state machine has determined that a note should be playing, or we're in bagless mode and the sound is turned on
        !(prevNote == 62 && (newNote + shift) == 86 && !sensorDataReady) &&                                                 // and if we're currently on a middle D in state 3 (all finger holes covered), we wait until we get a new state reading before switching notes. This it to prevent erroneous octave jumps to a high D.
        !(switches[SEND_VELOCITY] && !noteon && ((millis() - velocityDelayTimer) < velDelayMs)) &&    // and not waiting for the pressure to rise to calculate note on velocity if we're transitioning from not having any note playing.
        !(fingeringSelector == kModeNorthumbrian && newNote == 60) &&                                                             //and if we're in Northumbrian mode don't play a note if all holes are covered. That simulates the closed pipe.
        !(breathMode != kPressureBell && bellSensor && holeCovered == 0b111111111)) {                             // don't play a note if the bell sensor and all other holes are covered, and we're not in "bell register" mode. Again, simulating a closed pipe.

        int notewason = noteon;
        int notewasplaying = notePlaying;


        // if this is a fresh/tongued note calculate pressure now to get the freshest initial velocity/pressure
        if (!notewason) {
            if (ED[SEND_PRESSURE]) {
                calculatePressure(0);
            }
            if (switches[SEND_VELOCITY]) {
                calculatePressure(1);
            }
            if (switches[SEND_AFTERTOUCH] & 1) {
                calculatePressure(2);
            }
            if (switches[SEND_AFTERTOUCH] & 2) {
                calculatePressure(3);
            }
        }

        if (notewason && !switches[LEGATO]) {
            // send prior noteoff now if legato is selected.
            //20231001 GLB
            noteOFFIfOK(notePlaying);
            // if (isNoteOkToClose(notePlaying)) {
            //         sendUSBMIDI(NOTE_OFF, mainMidiChannel, notePlaying, 64);
            //         // if (communicationMode) {
            //         //         sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_BASE_NOTE);
            //         //         sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, 0);
            //         // }
            // }
            notewason = 0;
        }

        // need to send pressure prior to note, in case we are using it for velocity
        if (ED[SEND_PRESSURE] == 1 || switches[SEND_AFTERTOUCH] != 0 || switches[SEND_VELOCITY] == 1) {
            sendPressure(true);
        }

        // set it now so that send pitchbend will operate correctly
        noteon = 1;    //keep track of the fact that there's a note turned on
        notePlaying = newNote + shift;

        // send pitch bend immediately prior to note if necessary
        if (switches[IMMEDIATE_PB]) {
            calculateAndSendPitchbend();
        }


        sendUSBMIDI(NOTE_ON, mainMidiChannel, notePlaying, velocity);    //send the new note

        // if (communicationMode) {
        //         sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HARMONIZER_BASE_NOTE);
        //         sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, notePlaying);
        // }

        //20230927 GLB
        harmonizerNoteON(notePlaying, velocity);

        if (notewason) {
            // turn off the previous note after turning on the new one (if it wasn't already done above)
            // We do it after to signal to synths that the notes are legato (not all synths will respond to this).
            //20230927 GLB
            noteOFFIfOK(notewasplaying);

            // if (isNoteOkToClose(notewasplaying)) {
            //         sendUSBMIDI(NOTE_OFF, mainMidiChannel, notewasplaying, 64);
            // }
        }

        //END GLB

        pitchBendTimer = millis();    //for some reason it sounds best if we don't send pitchbend right away after starting a new note.
        noteOnTimestamp = pitchBendTimer;

        prevNote = newNote;

        if (ED[DRONES_CONTROL_MODE] == 2 && !dronesOn) {    //start drones if drones are being controlled with chanter on/off
            startDrones();
        }
    }


    if (noteon) {    //several conditions to turn a note off
        if (
            ((newState == 1 && !switches[BAGLESS]) || (switches[BAGLESS] && !play)) ||        //if the state drops to 1 (off) or we're in bagless mode and the sound has been turned off
            (fingeringSelector == kModeNorthumbrian && newNote == 60) ||                                    //or closed Northumbrian pipe
            (breathMode != kPressureBell && bellSensor && holeCovered == 0b111111111)) {    //or completely closed pipe

            if (noteOFFIfOK(notePlaying)) {
                //sendUSBMIDI(NOTE_OFF, mainMidiChannel, notePlaying, 64);                                                            //turn the note off if the breath pressure drops or if we're in uilleann mode, the bell sensor is covered, and all the finger holes are covered.
                //20230927 GLB
                harmonizerNoteOFF();    //Send the harmonizer note too
                //END GLB
            }


            noteon = 0;    //keep track

            sendPressure(true);

            if (ED[DRONES_CONTROL_MODE] == 2 && dronesOn) {    //stop drones if drones are being controlled with chanter on/off
                stopDrones();
            }
        }
    }
}




//Calibrate the sensors and store them in EEPROM
//mode 1 calibrates all sensors, mode 2 calibrates bell sensor only.
void calibrate() {

    if (!LEDon) {
        digitalWrite2(ledPin, HIGH);
        LEDon = 1;
        calibrationTimer = millis();

        if (calibration == 1) {    //calibrate all sensors if we're in calibration "mode" 1
            for (byte i = 1; i < TONEHOLE_SENSOR_NUMBER; i++) {
                toneholeCovered[i] = 0;    //first set the calibration to 0 for all of the sensors so it can only be increassed by calibrating

                //20231022 . GLB . Actually, this should be put to the sensor max malue, which should be 1024
                //toneholeBaseline[i] = 255;    //and set baseline high so it can only be reduced
                toneholeBaseline[i] = 1024;    //and set baseline high so it can only be reduced
            }
        }
        if (bellSensor) {
            toneholeCovered[0] = 0;    //also zero the bell sensor if it's plugged in (doesn't matter which calibration mode for this one).
            toneholeBaseline[0] = 1024;
        }
        return;    //we return once to make sure we've gotten some new sensor readings.
    }

    bool calibrationOn = ((calibration == 1 && ((millis() - calibrationTimer) <= 10000)) || (calibration == 2 && ((millis() - calibrationTimer) <= 5000)));
    //if ((calibration == 1 && ((millis() - calibrationTimer) <= 10000)) || (calibration == 2 && ((millis() - calibrationTimer) <= 5000))) {    //then set the calibration to the highest reading during the next ten seconds(or five seconds if we're only calibrating the bell sensor).
    if (calibrationOn) {
        if (calibration == 1) {
            for (byte i = 1; i < TONEHOLE_SENSOR_NUMBER; i++) {
                if (toneholeCovered[i] < toneholeRead[i]) {    //covered calibration
                    toneholeCovered[i] = toneholeRead[i];
                }

                if (toneholeBaseline[i] > toneholeRead[i]) {    //baseline calibration
                    toneholeBaseline[i] = toneholeRead[i];
                }
            }
        }

        if (bellSensor && toneholeCovered[0] < toneholeRead[0]) {
            toneholeCovered[0] = toneholeRead[0];    //calibrate the bell sensor too if it's plugged in.
        }
        if (bellSensor && toneholeBaseline[0] > toneholeRead[0]) {
            toneholeBaseline[0] = toneholeRead[0];    //calibrate the bell sensor too if it's plugged in.
        }
    } else {

        // if ((calibration == 1 && ((millis() - calibrationTimer) > 10000)) || (calibration == 2 && ((millis() - calibrationTimer) > 5000))) {
        saveCalibration();
        loadPrefs();    //do this so pitchbend scaling will be recalculated.
    }
}



//save sensor calibration (EEPROM bytes up to 35 are used (plus byte 37 to indicate a saved calibration)
void saveCalibration() {

    for (byte i = EEPROM_SENSOR_CALIB_FACTORY; i < TONEHOLE_SENSOR_NUMBER; i++) {
        writeIntToEEPROM((i + TONEHOLE_SENSOR_NUMBER) * 2, toneholeCovered[i]);

        EEPROM.update((EEPROM_SENSOR_CALIB_BASELINE_CURRENT + i), lowByte(toneholeBaseline[i]));    //the baseline readings can be stored in a single byte because they should be close to zero.
    }
    calibration = 0;
    EEPROM.update(EEPROM_CALIBRATION_SAVED, 3);    //we write a 3 to address 37 to indicate that we have stored a set of calibrations.
    digitalWrite2(ledPin, LOW);
    LEDon = 0;
}





//Load the stored sensor calibrations from EEPROM
void loadCalibration() {
    for (byte i = EEPROM_SENSOR_CALIB_FACTORY; i < TONEHOLE_SENSOR_NUMBER; i++) {
        toneholeCovered[i] = readIntFromEEPROM((i + TONEHOLE_SENSOR_NUMBER) * 2);
        toneholeBaseline[i] = EEPROM.read(EEPROM_SENSOR_CALIB_BASELINE_CURRENT + i);
    }
}





//send MIDI messages
void sendUSBMIDI(uint8_t m, uint8_t c, uint8_t d1, uint8_t d2)    // send a 3-byte MIDI event over USB
{
    c--;    // Channels are zero-based
    m &= 0xF0;
    c &= 0xF;
    d1 &= 0x7F;
    d2 &= 0x7F;
    midiEventPacket_t msg = { m >> 4, m | c, d1, d2 };
    noInterrupts();
    MidiUSB.sendMIDI(msg);
    MidiUSB.flush();
    interrupts();
}






void sendUSBMIDI(uint8_t m, uint8_t c, uint8_t d)    // send a 2-byte MIDI event over USB
{
    c--;    // Channels are zero-based
    m &= 0xF0;
    c &= 0xF;
    d &= 0x7F;
    midiEventPacket_t msg = { m >> 4, m | c, d, 0 };
    noInterrupts();
    MidiUSB.sendMIDI(msg);
    MidiUSB.flush();
    interrupts();
}






//check for and handle incoming MIDI messages from the WARBL Configuration Tool.
void receiveMIDI() {

    midiEventPacket_t rx;
    do {
        noInterrupts();
        rx = MidiUSB.read();    //check for MIDI input
        interrupts();
        if (rx.header != 0) {

            //Serial.println(rx.byte2);
            //Serial.println(rx.byte3);
            //Serial.println("");

            if ((rx.byte1 & 0x0f) == MIDI_CONF_CHANNEL - 1) {    //if we're on channel 7, we may be receiving messages from the configuration tool.
                blinkNumber = 1;                                                                 //blink once, indicating a received message. Some commands below will change this to three (or zero) blinks.

                switch (rx.byte1 & 0xf0) {
                    // case PITCH_BEND:
                    // {
                    //         if (fingering.customFingeringReceivingStatus) {
                    //                 fingering.temp_custom_fingering.holeCovered = ( rx.byte3 << 7) | (rx.byte2 & 0x7F);
                    //                 if (saveCustomFingering(fingering.temp_custom_fingering.midi_note, fingering.temp_custom_fingering.holeCovered) ) {
                    //                         //Debug
                    //                         // sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.temp_custom_fingering.midi_note);
                    //                         // sendHoleCovered(fingering.temp_custom_fingering.holeCovered);
                    //                 }
                    //         }
                    // }
                    //         break;
                    case CC:
                        {
                            if (rx.byte2 < MIDI_SLOT_19) {    //Chrome sends CC 121 and 123 on all channels when it connects, so ignore these.

                                if (rx.byte2 == MIDI_SLOT_02) {                    //many settings are controlled by a value in CC 102 (always channel 7).
                                    if (rx.byte3 > 0 && rx.byte3 <= 18) {    //handle sensor calibration commands from the configuration tool.
                                        if ((rx.byte3 & 1) == 0) {
                                            toneholeCovered[(rx.byte3 >> 1) - 1] -= 5;
                                            if ((toneholeCovered[(rx.byte3 >> 1) - 1] - 54) < 5) {    //if the tonehole calibration gets set too low so that it would never register as being uncovered, send a message to the configuration tool.
                                                sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, (MIDI_CALIB_SLOW_OS + ((rx.byte3 >> 1) - 1)));
                                            }
                                        } else {
                                            toneholeCovered[((rx.byte3 + 1) >> 1) - 1] += 5;
                                        }
                                    }

                                    if (rx.byte3 == MIDI_SAVE_CALIB) {    //save calibration if directed.
                                        saveCalibration();
                                        blinkNumber = 3;
                                    }

                                    //20231006 GLB - New Custom Fingering
                                    else if (rx.byte3 == MIDI_SEND_CUSTOM_FINGERING) {    //toggles custon fingering learning mode
                                        fingering.customFingeringReceivingStatus = !fingering.customFingeringReceivingStatus;
                                    }

                                    else if (rx.byte3 == MIDI_DELETE_CUSTOM_FINGERING_CURRENT) {    //deletes all custom fingering for current selector
                                        manageCustomFingerings(customFingeringOperations::ResetForCurrent, 0, 0);
                                    }

                                    else if (rx.byte3 == MIDI_DELETE_CUSTOM_FINGERING) {    //deletes all custom fingering
                                        manageCustomFingerings(customFingeringOperations::ResetAll, 0, 0);
                                    }
                                    //END GLB
                                    else if (rx.byte3 == MIDI_AUTO_CALIB) {    //begin auto-calibration if directed.
                                        blinkNumber = 0;
                                        calibration = 1;
                                    }

                                    else if (rx.byte3 == MIDI_SEND_SETTINGS) {    //when communication is established, send all current settings to tool.
                                        communicationMode = 1;
                                        sendSettings(false);
                                    }

                                    //20231014 GLB
                                    else if (rx.byte3 == MIDI_DUMP_SETTINGS_CURRENT) {    //For Exporting Settings
                                        sendSettings(true);
                                    }

                                    else if (rx.byte3 == MIDI_TURN_OFF_COMM) {    //turn off communication mode
                                        communicationMode = 0;
                                    }



                                    // else if (rx.byte3 == MIDI_DUMP_EEPROM) {    // dump EEPROM
                                    //         for (int i = 0; i < EEPROM.length(); i++) {
                                    //                 debug_log(EEPROM.read(i));
                                    //                 delay(3);
                                    //                 blinkNumber = 3;
                                    //         }
                                    // }


                                    // for (byte i = 0; i < 3; i++) {    // update the three selected fingering patterns if prompted by the tool.
                                    //         if (rx.byte3 == MIDI_SEND_FINGER_PATTERN_OS + i) {
                                    //                 fingeringReceiveMode = i;
                                    //         }
                                    // }
                                    // if (rx.byte3 == MIDI_SEND_FINGER_PATTERN_OS) {
                                    //                 fingeringReceiveMode = 0;
                                    //         }

                                    // if (rx.byte3 >= MIDI_SEND_MODE_SELECTOR_OS && rx.byte3 < MIDI_CURRENT_INSTR_OS) {
                                    //         fingeringSelector = rx.byte3 - MIDI_SEND_MODE_SELECTOR_OS;
                                    //         loadPrefs();
                                    // }


                                    for (byte i = 0; i < 3; i++) {    //update current mode (instrument) if directed.
                                        if (rx.byte3 == MIDI_CURRENT_INSTR_OS + i) {
                                            currentPreset = i;
                                            play = 0;
                                            loadFingering();            //Loads fingering for current preset
                                            loadSettings();             //Loads the current preset
                                            loadPrefs();                    //load the correct user settings based on current instrument.
                                            sendSettings(false);    //send settings for new mode to tool.
                                            blinkNumber = abs(currentPreset) + 1;
                                        }
                                    }

                                    for (byte i = 0; i < 4; i++) {    //update current pitchbend mode if directed.
                                        if (rx.byte3 == MIDI_PB_MODE_OS + i) {
                                            pitchBendModeSelector = i;
                                            loadPrefs();
                                            blinkNumber = abs(pitchBendMode) + 1;
                                        }
                                    }

                                    for (byte i = 0; i < 5; i++) {    //update current breath mode if directed.
                                        if (rx.byte3 == MIDI_BREATH_MODE_OS + i) {
                                            breathModeSelector = i;
                                            loadPrefs();    //load the correct user settings based on current instrument.
                                            blinkNumber = abs(breathMode) + 1;
                                        }
                                    }

                                    for (byte i = 0; i < 8; i++) {    //update button receive mode (this indicates the row in the button settings for which the next received byte will be).
                                        if (rx.byte3 == MIDI_SEND_BUTTON_PREF_OS + i) {
                                            buttonReceiveMode = i;
                                        }
                                    }

                                    for (byte i = 0; i < 8; i++) {    //update button configuration
                                        if (buttonReceiveMode == i) {
                                            // if (rx.byte3 == 100 + ACTION_CALIBRATE) {    //this is a special value for autocalibration because I ran out of values in teh range 0-12 below.
                                            //         buttonPrefs[i][0] = ACTION_CALIBRATE;
                                            //         blinkNumber = 0;
                                            // }

                                            for (byte j = 0; j <= BUTTONS_MAX_ACTIONS; j++) {    //update column 0 (action).
                                                if (rx.byte3 == MIDI_BUTTON_PREF_ACTION_OS + j) {
                                                    buttonPrefs[i][0] = j;
                                                    //blinkNumber = 0;
                                                }
                                            }
                                            for (byte k = 0; k < 5; k++) {    //update column 1 (MIDI action).
                                                if (rx.byte3 == MIDI_BUTTON_PREF_MIDI_CMD_OS + k) {
                                                    buttonPrefs[i][1] = k;
                                                }
                                            }
                                        }
                                    }

                                    for (byte i = 0; i < 3; i++) {    //update momentary
                                        if (buttonReceiveMode == i) {
                                            if (rx.byte3 == MIDI_MOMENTARY_OFF_OS) {
                                                momentary[i] = 0;
                                                noteOnOffToggle[i] = 0;
                                            } else if (rx.byte3 == MIDI_MOMENTARY_ON_OS) {
                                                momentary[i] = 1;
                                                noteOnOffToggle[i] = 0;
                                            }
                                        }
                                    }

                                    if (rx.byte3 == MIDI_DEFAULT_INSTR_OS) {    //set current Instrument as default and save default to settings.
                                        defaultPreset = currentPreset;
                                        EEPROM.update(EEPROM_DEFAULT_PRESET, defaultPreset);
                                    }


                                    if (rx.byte3 == MIDI_SAVE_SETTING_CURRENT) {    //save settings as the defaults for the current instrument
                                        saveSettings(currentPreset);
                                        blinkNumber = 3;
                                    }


                                    else if (rx.byte3 == MIDI_SAVE_SETTING_ALL) {    //Save settings as the defaults for all instruments
                                        for (byte k = 0; k < 3; k++) {
                                            saveSettings(k);
                                        }
                                        sendSettings(false);    //send settings to tool.
                                        // loadFingering();
                                        // loadSettings();
                                        // loadPrefs();
                                        blinkNumber = 3;

                                    }

                                    else if (rx.byte3 == MIDI_RESTORE_FACTORY_SETTING) {    //restore all factory settings
                                        EEPROM.update(EEPROM_SETTINGS_SAVED, 255);                    //indicates that settings should be resaved at next startup
                                        wdt_enable(WDTO_30MS);                                                            //restart the device in order to trigger resaving default settings
                                        while (true) {}
                                    }
                                }


                                else if (rx.byte2 == MIDI_SLOT_03) {
                                    senseDistanceSelector = rx.byte3;
                                    loadPrefs();
                                    sendHalfHoleParams(fingering.halfHole.currentHoleSettings);

                                }

                                //20231005 GLB - New custom fingering, receiving messages
                                else if (rx.byte2 == MIDI_SLOT_09) {    //midi_note
                                    if (fingering.customFingeringReceivingStatus) {
                                        fingering.temp_custom_fingering.midi_note = rx.byte3;
                                        fingering.temp_custom_fingering.fingeringSelector = fingeringSelector;
                                    }
                                }

                                else if (rx.byte2 == MIDI_SLOT_17) {
                                    unsigned long v = rx.byte3 * 8191UL / 100;
                                    vibratoDepthSelector = v;    //scale vibrato depth in cents up to pitchbend range of 0-8191
                                    loadPrefs();
                                }

                                //Int value from config tool
                                else if (rx.byte2 == MIDI_SLOT_13) {    //update receive mode for int values
                                    intReceiveIndex = rx.byte3;
                                }
                                //Int value - high byte from config tool
                                else if (rx.byte2 == MIDI_SLOT_14) {
                                    intReceivedH = rx.byte3;
                                }

                                //Int transmission from config tool terminated - manages the value received
                                else if (rx.byte2 == MIDI_SLOT_15) {
                                    int value = ((intReceivedH << 7) | rx.byte3) - 8192;

                                    switch (intReceiveIndex) {
                                        // case MIDI_SEND_HALFHOLE_CALIBRATION:
                                        //         if (fingering.halfHole.currentHoleSettings < TONEHOLE_SENSOR_NUMBER) {
                                        //                 toneholeCovered[fingering.halfHole.currentHoleSettings] = value;
                                        //                 sendHalfHoleParams(fingering.halfHole.currentHoleSettings);
                                        //         }

                                        // break;

                                        // case MIDI_SEND_HALFHOLE_MIN:
                                        //         fingering.halfHole.lower_limit[fingering.halfHole.currentHoleSettings] = value;
                                        //         break;
                                        case MIDI_SEND_HALFHOLE_MAX:
                                            fingering.halfHole.enabled[fingering.halfHole.currentHoleSettings] = value < 1024;
                                            break;

                                        case MIDI_SEND_HOLE_COVERED:
                                            if (fingering.customFingeringReceivingStatus) {
                                                fingering.temp_custom_fingering.holeCovered = value;
                                                if (saveCustomFingering(fingering.temp_custom_fingering.midi_note, fingering.temp_custom_fingering.holeCovered)) {
                                                    //         //Debug
                                                    //         // sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_09, fingering.temp_custom_fingering.midi_note);
                                                    //         // sendHoleCovered(fingering.temp_custom_fingering.holeCovered);
                                                }
                                            }
                                            break;

                                        case MIDI_SEND_KEY_SELECT:
                                            if (value < 50) {
                                                noteShiftSelector = value;
                                            } else {
                                                noteShiftSelector = -127 + value;
                                            }
                                            loadPrefs();
                                            break;

                                        case MIDI_SEND_MODE_SELECTOR:
                                        case MIDI_SEND_MODE_SELECTOR + 1:
                                        case MIDI_SEND_MODE_SELECTOR + 2:
                                            fingeringSelector = value;
                                            loadPrefs();
                                            break;

                                        default:
                                            break;
                                    }
                                }


                                if (rx.byte2 == MIDI_SLOT_04) {    //update receive mode, used for advanced pressure range sliders, switches, and expression and drones panel settings (this indicates the variable for which the next received byte on CC 105 will be).
                                    pressureReceiveMode = rx.byte3 - 1;
                                }

                                else if (rx.byte2 == MIDI_SLOT_05) {
                                    if (pressureReceiveMode < 12) {
                                        pressureSelector[pressureReceiveMode] = rx.byte3;    //advanced pressure values
                                        loadPrefs();
                                    }

                                    else if (pressureReceiveMode < 33) {
                                        ED[pressureReceiveMode - 12] = rx.byte3;    //expression and drones settings
                                        loadPrefs();
                                    }

                                    else if (pressureReceiveMode == 33) {
                                        LSBlearnedPressure = rx.byte3;

                                    }

                                    else if (pressureReceiveMode == 34) {
                                        learnedPressureSelector = (rx.byte3 << 7) | LSBlearnedPressure;
                                        loadPrefs();
                                    }


                                    else if (pressureReceiveMode < 53) {
                                        switches[pressureReceiveMode - 39] = rx.byte3;    //switches in the slide/vibrato and register control panels
                                        loadPrefs();
                                    }

                                    else if (pressureReceiveMode == 60) {
                                        midiBendRangeSelector = rx.byte3;
                                        loadPrefs();
                                    }

                                    else if (pressureReceiveMode == 61) {
                                        midiChannelSelector = rx.byte3;
                                        loadPrefs();
                                    }

                                    else if (pressureReceiveMode < 98) {
                                        ED[pressureReceiveMode - 48] = rx.byte3;    //more expression and drones settings
                                        loadPrefs();
                                    }

                                    //Half Hole detection Settings - needs to be re-organized
                                    else if (pressureReceiveMode + 1 == MIDI_SEND_HALFHOLE_CURRENT) {
                                        fingering.halfHole.currentHoleSettings = rx.byte3;
                                        sendHalfHoleParams(fingering.halfHole.currentHoleSettings);
                                    }

                                    else if (pressureReceiveMode + 1 == MIDI_SEND_HALFHOLE_BUFFER) {
                                        fingering.halfHole.buffer = rx.byte3;
                                        sendHalfHoleParams(fingering.halfHole.currentHoleSettings);
                                    }

                                    // else if (pressureReceiveMode + 1 == MIDI_SEND_HALFHOLE_SAVE) {
                                    //         saveHalfHoleCalibration();
                                    //         EEPROM.update(EEPROM_HALF_HOLE_BUFFER_SIZE, fingering.halfHole.halfHoleBuffer);
                                    // }
                                }




                                if (rx.byte2 == MIDI_SLOT_06 && rx.byte3 > 15) {


                                    if (rx.byte3 >= MIDI_EN_VIBRATO_HOLES_OS && rx.byte3 < 29) {    //update enabled vibrato holes for "universal" vibrato
                                        bitSet(vibratoHolesSelector, rx.byte3 - 20);
                                        loadPrefs();
                                    }

                                    else if (rx.byte3 > 29 && rx.byte3 < MIDI_CALIB_OPTION_OS) {
                                        bitClear(vibratoHolesSelector, rx.byte3 - 30);
                                        loadPrefs();
                                    }

                                    else if (rx.byte3 == MIDI_USE_LEARN_PRESS_OFF) {
                                        useLearnedPressureSelector = 0;
                                        loadPrefs();
                                    }

                                    else if (rx.byte3 == MIDI_USE_LEARN_PRESS_ON) {
                                        useLearnedPressureSelector = 1;
                                        loadPrefs();
                                    }

                                    else if (rx.byte3 == MIDI_SEND_LEARN_PRESS) {
                                        learnedPressureSelector = sensorValue;
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_LSB_LEARN_PRESS_OS);        //indicate that LSB of learned pressure is about to be sent
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, learnedPressureSelector & 0x7F);    //send LSB of learned pressure
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_MSB_LEARN_PRESS_OS);        //indicate that MSB of learned pressure is about to be sent
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, learnedPressureSelector >> 7);        //send MSB of learned pressure
                                        loadPrefs();
                                    }

                                    else if (rx.byte3 == MIDI_AUTO_CALIB_BELL) {    //autocalibrate bell sensor only
                                        calibration = 2;
                                        blinkNumber = 0;
                                    }


                                    else if (rx.byte3 == MIDI_SEND_LEARN_PRESS_DRONE) {
                                        int tempPressure = sensorValue;
                                        ED[DRONES_PRESSURE_LOW_BYTE] = tempPressure & 0x7F;
                                        ED[DRONES_PRESSURE_HIGH_BYTE] = tempPressure >> 7;
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_LSB_LEARN_DRONE_PRESS_OS);    //indicate that LSB of learned drones pressure is about to be sent
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, ED[DRONES_PRESSURE_LOW_BYTE]);                //send LSB of learned drones pressure
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_MSB_LEARN_DRONE_PRESS_OS);    //indicate that MSB of learned drones pressure is about to be sent
                                        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, ED[DRONES_PRESSURE_HIGH_BYTE]);             //send MSB of learned drones pressure
                                    }


                                    // else if (rx.byte3 == MIDI_SAVE_CALIB_AS_FACTORY) {    //save current sensor calibration as factory calibration
                                    //         for (byte i = EEPROM_SENSOR_CALIB_FACTORY; i < EEPROM_SENSOR_CALIB_CURRENT; i++) {
                                    //                 EEPROM.update(i, EEPROM.read(i + EEPROM_SENSOR_CALIB_CURRENT));
                                    //         }
                                    //         for (int i = EEPROM_SENSOR_CALIB_BASELINE_FACTORY; i < EEPROM_SENSOR_CALIB_BASELINE_FACTORY + TONEHOLE_SENSOR_NUMBER; i++) {    //save baseline calibration as factory baseline
                                    //                 EEPROM.update(i, EEPROM.read(i - TONEHOLE_SENSOR_NUMBER));
                                    //         }
                                    // }
                                }



                                for (byte i = 0; i < 8; i++) {    //update channel, byte 2, byte 3 for MIDI message for button MIDI command for row i
                                    if (buttonReceiveMode == i) {
                                        if (rx.byte2 == MIDI_SLOT_06 && rx.byte3 < 16) {
                                            buttonPrefs[i][2] = rx.byte3;
                                        } else if (rx.byte2 == MIDI_SLOT_07) {
                                            buttonPrefs[i][3] = rx.byte3;
                                            //20231001 GLB
                                            //Live update for Transposer and harmonizer
                                            if (buttonPrefs[i][0] == ACTION_TRANSPOSE && harmonizer.transposeShift != 0) {    //Action Tranposer
                                                harmonizer.transposeShift = buttonPrefs[i][3] - 12;
                                                // if (communicationMode) {
                                                //         sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_TRANSPOSE_SHIFT);
                                                //         sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.transposeShift +12);
                                                // }
                                            } else if (buttonPrefs[i][0] >= ACTION_HARMONIZER_1 && buttonPrefs[i][0] <= ACTION_HARMONIZER_3) {    //Action Harmonize voice 1
                                                byte voice = buttonPrefs[i][0] - ACTION_HARMONIZER_1;
                                                if (harmonizer.harmonizers[voice].interval != 0) {
                                                    setHarmonizerInterval(voice, buttonPrefs[i][3] - 12);
                                                }
                                                if (harmonizer.harmonizers[voice].currentNote >= 0) {
                                                    harmonizerNoteOFF(voice);
                                                    harmonizerNoteON(voice, notePlaying, velocity);
                                                }
                                            }
                                        } else if (rx.byte2 == MIDI_SLOT_08) {
                                            buttonPrefs[i][4] = rx.byte3;
                                            if (buttonPrefs[i][0] >= ACTION_HARMONIZER_1 && buttonPrefs[i][0] <= ACTION_HARMONIZER_3) {    //Action Harmonize voice 1
                                                byte voice = buttonPrefs[i][0] - ACTION_HARMONIZER_1;
                                                setHarmonizerScale(voice, buttonPrefs[i][4]);
                                                if (harmonizer.harmonizers[voice].currentNote >= 0) {
                                                    harmonizerNoteOFF(voice);
                                                    harmonizerNoteON(voice, notePlaying, velocity);
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }    //end of ignore CCs 121, 123
                        break;
                }
            }
        }

    } while (rx.header != 0);
}



//save settings for current instrument as defaults for given instrument (i)
void saveSettings(byte i) {

    EEPROM.update(EEPROM_FINGERING_SELECTOR + i, fingeringSelector);
    EEPROM.update(EEPROM_NOTESHIFT_SELECTOR + i, noteShiftSelector);
    EEPROM.update(EEPROM_SENSEDISTANCE_SELECTOR + i, senseDistanceSelector);

    for (byte n = 0; n < kSWITCHESnVariables; n++) {
        EEPROM.update((EEPROM_SWITCHES + n + (i * kSWITCHESnVariables)), switches[n]);
    }

    //20231013 Bytes swapped
    writeIntToEEPROM(EEPROM_VIBRATOHOLE_SELECTOR + (i * 2), vibratoHolesSelector);

    writeIntToEEPROM(EEPROM_VIBRATODEPTH_SELECTOR + (i * 2), vibratoDepthSelector);

    EEPROM.update(EEPROM_USE_LEARNPRESS_SELECTOR + i, useLearnedPressureSelector);

    for (byte j = 0; j < 5; j++) {    //save button configuration for current currentPreset
        for (byte k = 0; k < 8; k++) {
            EEPROM.update(EEPROM_BUTTON_PREFS + (i * EEPROM_BUTTON_PREFS_SLOT) + (j * EEPROM_BUTTON_PREFS_NUMBER) + k, buttonPrefs[k][j]);
        }
    }

    for (byte h = 0; h < 3; h++) {
        EEPROM.update(EEPROM_MOMENTARY_ACTIONS + (i * 3) + h, momentary[h]);
    }

    for (byte q = 0; q < 12; q++) {
        EEPROM.update((EEPROM_PRESSURE_SELECTOR + q + (i * EEPROM_PRESSURE_SELECTOR_SLOT)), pressureSelector[q]);
    }

    //20231013 Swapped Bytes
    writeIntToEEPROM(EEPROM_LEARNPRESS_SELECTOR + (i * 2), learnedPressureSelector);

    EEPROM.update(EEPROM_PB_MODE_SELECTOR + i, pitchBendModeSelector);
    EEPROM.update(EEPROM_BREATH_MODE_SELECTOR + i, breathModeSelector);
    EEPROM.update(EEPROM_BEND_RANGE_SELECTOR + i, midiBendRangeSelector);
    EEPROM.update(EEPROM_MIDI_CHANNEL_SELECTOR + i, midiChannelSelector);

    for (byte n = 0; n < kEXPRESSIONnVariables; n++) {
        EEPROM.update((EEPROM_EXPRESSION_VARS + n + (i * kEXPRESSIONnVariables)), ED[n]);
    }

    //GLB Half Hole Detection Calibration
    saveHalfHoleConfig();
}




//load saved fingering patterns
void loadFingering() {

    fingeringSelector = EEPROM.read(EEPROM_FINGERING_SELECTOR + currentPreset);
    noteShiftSelector = (int8_t)EEPROM.read(EEPROM_NOTESHIFT_SELECTOR + currentPreset);

    loadCustomFingering();
}


//load settings for all three instruments from EEPROM
void loadSettings() {

    defaultPreset = EEPROM.read(EEPROM_DEFAULT_PRESET);    //load default currentPreset

    senseDistanceSelector = EEPROM.read(EEPROM_SENSEDISTANCE_SELECTOR + currentPreset);

    for (byte n = 0; n < kSWITCHESnVariables; n++) {
        switches[n] = EEPROM.read(EEPROM_SWITCHES + n + (currentPreset * kSWITCHESnVariables));
    }

    //20231013 Bytes swapped - High First
    vibratoHolesSelector = readIntFromEEPROM(EEPROM_VIBRATOHOLE_SELECTOR + (currentPreset * 2));
    vibratoDepthSelector = readIntFromEEPROM(EEPROM_VIBRATODEPTH_SELECTOR + (currentPreset * 2));

    useLearnedPressureSelector = EEPROM.read(EEPROM_USE_LEARNPRESS_SELECTOR + currentPreset);

    for (byte j = 0; j < 5; j++) {
        for (byte k = 0; k < 8; k++) {
            buttonPrefs[k][j] = EEPROM.read(EEPROM_BUTTON_PREFS + (currentPreset * EEPROM_BUTTON_PREFS_SLOT) + (j * EEPROM_BUTTON_PREFS_NUMBER) + k);
        }
    }

    for (byte h = 0; h < 3; h++) {
        momentary[h] = EEPROM.read(EEPROM_MOMENTARY_ACTIONS + (currentPreset * 3) + h);
    }

    for (byte m = 0; m < 12; m++) {
        pressureSelector[m] = EEPROM.read(EEPROM_PRESSURE_SELECTOR + m + (currentPreset * EEPROM_PRESSURE_SELECTOR_SLOT));
    }

    //20231013 Swapped Bytes
    learnedPressureSelector = readIntFromEEPROM(EEPROM_LEARNPRESS_SELECTOR + (currentPreset * 2));

    pitchBendModeSelector = EEPROM.read(EEPROM_PB_MODE_SELECTOR + currentPreset);
    breathModeSelector = EEPROM.read(EEPROM_BREATH_MODE_SELECTOR + currentPreset);

    midiBendRangeSelector = EEPROM.read(EEPROM_BEND_RANGE_SELECTOR + currentPreset);
    midiBendRangeSelector = midiBendRangeSelector > 96 ? 2 : midiBendRangeSelector;    // sanity check in case uninitialized

    midiChannelSelector = EEPROM.read(EEPROM_MIDI_CHANNEL_SELECTOR + currentPreset);
    midiChannelSelector = midiChannelSelector > 16 ? 1 : midiChannelSelector;    // sanity check in case uninitialized

    for (byte n = 0; n < kEXPRESSIONnVariables; n++) {
        ED[n] = EEPROM.read(EEPROM_EXPRESSION_VARS + n + (currentPreset * kEXPRESSIONnVariables));
    }

    //GLB Half Hole Detection Parameters
    loadHalfHoleConfig();
}





//send all settings for current instrument to the WARBL Configuration Tool.
void sendSettings(bool dump) {

    if (!dump) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SW_VERSION, VERSION);                            //send software version
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SW_VERSION, BUILD_VERSION);                //send custom build    version for default config tool
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SW_BUILD_VERSION, BUILD_VERSION);    //send custom build    version

        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_CURRENT_INSTR_OS + currentPreset);    //send current instrument
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_DEFAULT_INSTR_OS + defaultPreset);    //send default instrument

        //Sends fingering pattern for all three presets, for TAB names
        for (byte i = 0; i < PRESET_NUMBER; i++) {
            sendIntValue(MIDI_SEND_MODE_SELECTOR + i, EEPROM.read(EEPROM_FINGERING_SELECTOR + i));
        }

        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_BELL_SENSOR_OS + bellSensor);    //send bell sensor state

    } else {
        sendIntValue(MIDI_SEND_MODE_SELECTOR, fingeringSelector);
    }


    if (noteShiftSelector >= 0) {
        sendIntValue(MIDI_SEND_KEY_SELECT, noteShiftSelector);

    }    //send noteShift, with a transformation for sending negative values over MIDI.
    else {
        sendIntValue(MIDI_SEND_KEY_SELECT, noteShiftSelector + 127);
        // sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_12, noteShiftSelector + 127);
    }

    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_03, senseDistance);    //send sense distance

    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_17, vibratoDepth * 100UL / 8191);             //send vibrato depth, scaled down to cents
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_PB_MODE_OS + pitchBendMode);     //send current pitchBend mode
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_BREATH_MODE_OS + breathMode);    //send current breathMode

    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_06, MIDI_CALIB_OPTION_OS + useLearnedPressure);    //send calibration option

    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_LSB_LEARN_PRESS_OS);    //indicate that LSB of learned pressure is about to be sent
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, learnedPressure & 0x7F);                //send LSB of learned pressure

    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_MSB_LEARN_PRESS_OS);    //indicate that MSB of learned pressure is about to be sent
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, learnedPressure >> 7);                    //send MSB of learned pressure

    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_BEND_RANGE_OS);    // indicate midi bend range is about to be sent
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, midiBendRange);                        //midi bend range

    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_MIDI_CHAN_OS);    // indicate midi channel is about to be sent
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, mainMidiChannel);                 //midi bend range



    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_06, MIDI_EN_VIBRATO_HOLES_OS + i + (10 * (bitRead(vibratoHolesSelector, i))));    //send enabled vibrato holes
    }

    for (byte i = 0; i < 8; i++) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_BUTTON_PREF_OS + i);                                        //indicate that we'll be sending data for button commands row i (click 1, click 2, etc.)
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_BUTTON_PREF_ACTION_OS + buttonPrefs[i][0]);    //send action (i.e. none, send MIDI message, etc.)
        //20230927 GLB
        if (buttonPrefs[i][0] == ACTION_MIDI || buttonPrefs[i][0] == ACTION_TRANSPOSE || (buttonPrefs[i][0] >= ACTION_HARMONIZER_1 && buttonPrefs[i][0] < ACTION_HARMONIZER_1 + HARMONIZER_VOICES)) {    //if the action is a MIDI command OR an Transposer/Harmonizer, send the rest of the MIDI info for that row.
                                                                                                                                                                                                                                                                                                                                                                                                     //END GLB
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_BUTTON_PREF_MIDI_CMD_OS + buttonPrefs[i][1]);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_06, buttonPrefs[i][2]);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_07, buttonPrefs[i][3]);
            sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_08, buttonPrefs[i][4]);
        }
    }

    for (byte i = 0; i < kSWITCHESnVariables; i++) {    //send settings for switches in the slide/vibrato and register control panels
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_SWITCH_VARS_OS + i);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, switches[i]);
    }

    for (byte i = 0; i < 21; i++) {    //send settings for expression and drones control panels
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_EXPRESSION_VARS_1_OS + i);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, ED[i]);
    }

    for (byte i = 21; i < kEXPRESSIONnVariables; i++) {    //more settings for expression and drones control panels
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_EXPRESSION_VARS_2_OS + i);
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, ED[i]);
    }

    for (byte i = 0; i < 3; i++) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_SEND_MOMENTARY_OS + i);    //indicate that we'll be sending data for momentary
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_MOMENTARY_OFF_OS + momentary[i]);
    }

    for (byte i = MIDI_SEND_PRESSURE_VARS_OS; i < 12; i++) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, i + 1);                                //indicate which pressure variable we'll be sending data for
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, pressureSelector[i]);    //send the data
    }

    sendCustomFingering();

    //Half hole detection settings
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_HALFHOLE_BUFFER);
    sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, fingering.halfHole.buffer);

    if (dump) {
        //20231014 GLB We send this message to signal the end of setting sending (export function)
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_DUMP_SETTINGS_CURRENT);
    } else {
        //20231003 GLB - Sends Harmonizer status
        sendHarmonizerConfiguration();
    }
    //END OF SETTINGS
}


void blink()    //blink LED given number of times
{

    if ((millis() - ledTimer) >= 200) {
        ledTimer = millis();

        if (LEDon) {
            digitalWrite2(ledPin, LOW);
            blinkNumber--;
            LEDon = 0;
            return;
        } else {
            digitalWrite2(ledPin, HIGH);
            LEDon = 1;
        }
    }
}




//interpret button presses. If the button is being used for momentary MIDI messages we ignore other actions with that button (except "secret" actions involving the toneholes).
void handleButtons() {


    //first, some housekeeping

    if (shiftState == 1 && released[1] == 1) {    //if button 1 was only being used along with another button, we clear the just-released flag for button 1 so it doesn't trigger another control change.
        released[1] = 0;
        buttonUsed = 0;    //clear the button activity flag, so we won't handle them again until there's been new button activity.
        shiftState = 0;
    }

    //then, a few hard-coded actions that can't be changed by the configuration tool:
    //_______________________________________________________________________________

    if (justPressed[0] && !pressed[2] && !pressed[1]) {
        if (ED[DRONES_CONTROL_MODE] == 1) {
            if (holeCovered >> 1 == 0b00001000) {    //turn drones on/off if button 0 is pressed and fingering pattern is 0 0001000.
                justPressed[0] = 0;
                specialPressUsed[0] = 1;
                if (!dronesOn) {
                    startDrones();
                } else {
                    stopDrones();
                }
            }
        }

        if (switches[SECRET]) {
            if (holeCovered >> 1 == 0b00010000) {    //change pitchbend mode if button 0 is pressed and fingering pattern is 0 0000010.
                justPressed[0] = 0;
                specialPressUsed[0] = 1;
                changePitchBend();
            }

            else if (holeCovered >> 1 == 0b00000010) {    //change instrument if button 0 is pressed and fingering pattern is 0 0000001.
                justPressed[0] = 0;
                specialPressUsed[0] = 1;
                changeInstrument();
            }
        }
    }

    //now the button actions that can be changed with the configuration tool.
    //_______________________________________________________________________________


    for (byte i = 0; i < 3; i++) {


        if (released[i] && (momentary[i] || (pressed[0] + pressed[1] + pressed[2] == 0))) {    //do action for a button release ("click") NOTE: button array is zero-indexed, so "button 1" in all documentation is button 0 here (same for others).
            if (!specialPressUsed[i]) {                                                                                                                //we ignore it if the button was just used for a hard-coded command involving a combination of fingerholes.
                performAction(i);
            }
            released[i] = 0;
            specialPressUsed[i] = 0;
        }


        if (longPress[i] && (pressed[0] + pressed[1] + pressed[2] == 1) && !momentary[i]) {    //do action for long press, assuming no other button is pressed.
            performAction(5 + i);
            // if ( !(5+i == ACTION_TRANSPOSE && buttonPrefs[5 + i][2] == 1)) { //Not a progressive transpose
            longPressUsed[i] = 1;
            // }
            longPress[i] = 0;
            longPressCounter[i] = 0;
        }


        //presses of individual buttons (as opposed to releases) are special cases used only if we're using buttons to send MIDI on/off messages and "momentary" is selected. We'll handle these in a separate function.
        if (justPressed[i]) {
            justPressed[i] = 0;
            handleMomentary(i);    //do action for button press.
        }
    }


    if (pressed[1]) {
        if (released[0] && !momentary[0]) {    //do action for button 1 held and button 0 released
            released[0] = 0;
            shiftState = 1;
            performAction(3);
        }

        if (released[2] && !momentary[1]) {    //do action for button 1 held and button 2 released
            released[2] = 0;
            shiftState = 1;
            performAction(4);
        }
    }


    buttonUsed = 0;    // Now that we've caught any important button acticity, clear the flag so we won't enter this function again until there's been new activity.
}



//perform desired action in response to buttons
void performAction(byte action) {


    switch (buttonPrefs[action][0]) {

        case ACTION_NONE:
            break;    //if no action desired for button combination

        case ACTION_MIDI:    //MIDI command
            switch (buttonPrefs[action][1]) {
                case 0:
                    {
                        if (noteOnOffToggle[action] == 0) {
                            sendUSBMIDI(NOTE_ON, buttonPrefs[action][2], buttonPrefs[action][3], buttonPrefs[action][4]);
                            noteOnOffToggle[action] = 1;
                        } else if (noteOnOffToggle[action] == 1) {
                            sendUSBMIDI(NOTE_OFF, buttonPrefs[action][2], buttonPrefs[action][3], buttonPrefs[action][4]);
                            noteOnOffToggle[action] = 0;
                        }
                        break;
                    }

                case 1:
                    {
                        sendUSBMIDI(CC, buttonPrefs[action][2], buttonPrefs[action][3], buttonPrefs[action][4]);
                        break;
                    }

                case 2:
                    {
                        sendUSBMIDI(PROGRAM_CHANGE, buttonPrefs[action][2], buttonPrefs[action][3]);
                        break;
                    }

                case 3:
                    {    //increase program change
                        if (program < 127) {
                            program++;
                        } else {
                            program = 0;
                        }
                        sendUSBMIDI(PROGRAM_CHANGE, buttonPrefs[action][2], program);
                        blinkNumber = 1;
                        break;
                    }

                case 4:
                    {    //decrease program change
                        if (program > 0) {
                            program--;
                        } else {
                            program = 127;
                        }
                        sendUSBMIDI(PROGRAM_CHANGE, buttonPrefs[action][2], program);
                        blinkNumber = 1;
                        break;
                    }
            }

            break;

        case ACTION_VIBRATO_MODE:    //set vibrato/slide mode
            changePitchBend();
            break;

        case ACTION_CHANGE_INSTRUMENT:
            changeInstrument();
            break;

        case ACTION_PLAY_STOP:
            play = !play;    //turn sound on/off when in bagless mode
            break;

            // case ACTION_RESTART:
            //         wdt_enable(WDTO_15MS);     //restart the device in order to trigger resaving default settings
            //         while (true) {}
            // break;

            //20230927 GLB
        case ACTION_TRANSPOSE:                                    //Transpose
            if (!momentary[action]) {                         // transpose, unless we're in momentary mode, otherwise transpose is off
                if (buttonPrefs[action][2] == 1) {    //Progressive
                    harmonizer.transposeShift += buttonPrefs[action][3] - 12;
                } else {
                    if (harmonizer.transposeShift != 0) {
                        harmonizer.transposeShift = 0;
                    } else {
                        harmonizer.transposeShift = buttonPrefs[action][3] - 12;    //transpose if we're not in momentary mode
                    }
                }
            } else {
                harmonizer.transposeShift = harmonizer.prevTransposeShift;
                harmonizer.prevTransposeShift = 0;
            }
            //Checks bounds for harmonizer.transposeShift
            if (harmonizer.transposeShift < -12 * 4) {
                harmonizer.transposeShift += 12;
            } else if (harmonizer.transposeShift > 12 * 4) {
                harmonizer.transposeShift -= 12;
            }
            if (communicationMode) {
                sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_TRANSPOSE_SHIFT);
                sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.transposeShift + 12);
            }
            break;

        case ACTION_FIXED_NOTE:                        //Set Fixed Note from current Note
            if (harmonizer.fixedNote > 0) {    //Turn off
                setHarmonizerFixedNote(-1);
            } else {
                setHarmonizerFixedNote(notePlaying);
            }
            break;

            //END GLB

        case ACTION_MIDI_PANIC:
            //20230927 GLB
            {
                for (byte i = 1; i < 17; i++) {    //send MIDI panic
                    sendUSBMIDI(CC, i, 123, 0);
                    dronesOn = 0;             //remember that drones are off, because MIDI panic will have most likely turned them off in all apps.
                    HarmonizerReset();    //remember that harmonizer is off, because MIDI panic will have most likely turned them off in all apps.
                }
            }
            //END GLB
            break;

        case ACTION_REGISTER_MODE:
            breathModeSelector++;    //set breath mode
            if (breathModeSelector == kPressureNModes) {
                breathModeSelector = kPressureSingle;
            }
            loadPrefs();
            play = 0;
            blinkNumber = abs(breathMode) + 1;
            if (communicationMode) {
                sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_BREATH_MODE_OS + breathMode);    //send current breathMode
            }
            break;


        case ACTION_TOGGLE_DRONE:    //toggle drones
            blinkNumber = 1;
            if (!dronesOn) {
                startDrones();
            } else {
                stopDrones();
            }
            break;


        //20230927 GLB
        case ACTION_HARMONIZER_1:    //Harmonize voice 1
        case ACTION_HARMONIZER_2:    //Harmonize voice 2
        case ACTION_HARMONIZER_3:    //Harmonize voice 3
            {
                byte voice = buttonPrefs[action][0] - ACTION_HARMONIZER_1;
                if (!momentary[action] && harmonizer.harmonizers[voice].interval == 0) {    //harmonize unless we're in momentary mode, otherwise shift up
                    setHarmonizerInterval(voice, buttonPrefs[action][3] - 12);                            //harmonize if we're not in momentary mode;
                    setHarmonizerScale(voice, buttonPrefs[action][4]);
                    if (noteon) {
                        setHarmonizerTonic(voice, notePlaying);    // The current note is memorized as tonic, diatonic mode enabled
                        harmonizerNoteON(voice, notePlaying, velocity);
                        // sendUSBMIDI(NOTE_ON, mainMidiChannel, notePlaying + harmonizerInterval1, velocity);    //send the new note
                    }
                } else {
                    harmonizerNoteOFF(voice);
                    setHarmonizerInterval(voice, 0);
                    setHarmonizerTonic(voice, -1);
                }
            }
            break;

            //END GLB

        case ACTION_CALIBRATE:    //autocalibrate
            calibration = 1;
            break;

        default:
            return;
    }
}









//cycle through pitchbend modes
void changePitchBend() {
    pitchBendModeSelector++;
    if (pitchBendModeSelector == kPitchBendNModes) {
        pitchBendModeSelector = kPitchBendSlideVibrato;
    }
    loadPrefs();
    blinkNumber = abs(pitchBendMode) + 1;
    if (communicationMode) {
        sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_02, MIDI_PB_MODE_OS + pitchBendMode);    //send current pitchbend mode to configuration tool.
    }
}






//cycle through instruments
void changeInstrument() {
    currentPreset++;    //set instrument
    if (currentPreset == 3) {
        currentPreset = 0;
    }
    play = 0;
    loadPrefs();    //load the correct user settings based on current instrument.
    blinkNumber = abs(currentPreset) + 1;
    if (communicationMode) {
        sendSettings(false);    //tell communications tool to switch currentPreset and send all settings for current instrument.
    }
}





void handleMomentary(byte button) {

    if (momentary[button]) {
        if (buttonPrefs[button][0] == ACTION_MIDI && buttonPrefs[button][1] == 0) {    //handle momentary press if we're sending a MIDI message
            sendUSBMIDI(NOTE_ON, buttonPrefs[button][2], buttonPrefs[button][3], buttonPrefs[button][4]);
            noteOnOffToggle[button] = 1;
        }

        //20230927 LGB
        //handle temporary presses for transpose and harmonize
        if (buttonPrefs[button][0] == ACTION_TRANSPOSE) {
            if (buttonPrefs[button][2] == 1) {    //Progressive
                harmonizer.prevTransposeShift = harmonizer.transposeShift;
                harmonizer.transposeShift += buttonPrefs[button][3] - 12;
            } else {
                harmonizer.transposeShift = buttonPrefs[button][3] - 12;    //transpose if we're not in momentary mode
            }

            if (communicationMode) {
                sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_04, MIDI_SEND_TRANSPOSE_SHIFT);
                sendUSBMIDI(CC, MIDI_CONF_CHANNEL, MIDI_SLOT_05, harmonizer.transposeShift + 12);
            }
        }

        if (buttonPrefs[button][0] >= ACTION_HARMONIZER_1 && buttonPrefs[button][0] <= ACTION_HARMONIZER_1) {
            byte voice = buttonPrefs[button][0] - ACTION_HARMONIZER_1;
            setHarmonizerInterval(voice, buttonPrefs[button][3] - 12);
            if (noteon) {
                setHarmonizerTonic(voice, notePlaying);    // The current note is memorized as tonic, diatonic mode enabled
                harmonizerNoteON(voice, notePlaying, velocity);
            }
        }

        //END GLB
    }
}





// find leftmost unset bit, used for finding the uppermost uncovered hole when reading from some fingering charts, and for determining the slidehole.
byte findleftmostunsetbit(uint16_t n) {

    if ((n & (n + 1)) == 0) {
        return 127;    // if number contains all 0s then return 127
    }

    int pos = 0;
    for (int temp = n, count = 0; temp > 0; temp >>= 1, count++)    // Find position of leftmost unset bit.

        if ((temp & 1) == 0)    // if temp L.S.B is zero then unset bit pos is
            pos = count;

    return pos;
}




// Send a debug MIDI message with a value up 16383 (14 bits)
// void debug_log(int msg) {
//         sendIntValue(MIDI_SEND_DEBUG, msg);
// }


void startDrones() {
    dronesOn = 1;
    switch (ED[DRONES_ON_COMMAND]) {
        case 0:
            sendUSBMIDI(NOTE_ON, ED[DRONES_ON_CHANNEL], ED[DRONES_ON_BYTE2], ED[DRONES_ON_BYTE3]);
            break;
        case 1:
            sendUSBMIDI(NOTE_OFF, ED[DRONES_ON_CHANNEL], ED[DRONES_ON_BYTE2], ED[DRONES_ON_BYTE3]);
            break;
        case 2:
            sendUSBMIDI(CC, ED[DRONES_ON_CHANNEL], ED[DRONES_ON_BYTE2], ED[DRONES_ON_BYTE3]);
            break;
    }
}



void stopDrones() {
    dronesOn = 0;
    switch (ED[DRONES_OFF_COMMAND]) {
        case 0:
            sendUSBMIDI(NOTE_ON, ED[DRONES_OFF_CHANNEL], ED[DRONES_OFF_BYTE2], ED[DRONES_OFF_BYTE3]);
            break;
        case 1:
            sendUSBMIDI(NOTE_OFF, ED[DRONES_OFF_CHANNEL], ED[DRONES_OFF_BYTE2], ED[DRONES_OFF_BYTE3]);
            break;
        case 2:
            sendUSBMIDI(CC, ED[DRONES_OFF_CHANNEL], ED[DRONES_OFF_BYTE2], ED[DRONES_OFF_BYTE3]);
            break;
    }
}







//load the correct user settings for the current instrument. This is used at startup and any time settings are changed.
void loadPrefs() {

    vibratoHoles = vibratoHolesSelector;
    noteShift = noteShiftSelector;
    pitchBendMode = pitchBendModeSelector;
    useLearnedPressure = useLearnedPressureSelector;
    learnedPressure = learnedPressureSelector;
    senseDistance = senseDistanceSelector;
    vibratoDepth = vibratoDepthSelector;
    breathMode = breathModeSelector;
    midiBendRange = midiBendRangeSelector;
    mainMidiChannel = midiChannelSelector;
    transientFilter = (pressureSelector[9] + 1) / 1.25;    //this variable was formerly used for vented dropTime (unvented is now unused). Includes a correction for milliseconds

    //set these variables depending on whether "vented" is selected
    offset = pressureSelector[(switches[VENTED] * 6) + 0];
    multiplier = pressureSelector[(switches[VENTED] * 6) + 1];
    hysteresis = pressureSelector[(switches[VENTED] * 6) + 2];
    jumpTime = ((pressureSelector[(switches[VENTED] * 6) + 4]) + 1) / 1.25;    //Includes a correction for milliseconds
    dropTime = ((pressureSelector[(switches[VENTED] * 6) + 5]) + 1) / 1.25;    //Includes a correction for milliseconds

    pitchBend = 8192;
    expression = 0;
    sendUSBMIDI(PITCH_BEND, mainMidiChannel, pitchBend & 0x7F, pitchBend >> 7);

    baselineAverage = 0;
    for (byte i = 0; i < TONEHOLE_SENSOR_NUMBER; i++) {
        iPitchBend[i] = 0;    //turn off pitchbend
        pitchBendOn[i] = 0;

        toneholeScale[i] = ((8 * (16383 / midiBendRange)) / (toneholeCovered[i] - 50 - senseDistance) / 2);                        // Precalculate scaling factors for pitchbend. This one is for sliding. We multiply by 8 first to reduce rounding errors. We'll divide again later.
        vibratoScale[i] = ((8 * 2 * (vibratoDepth / midiBendRange)) / (toneholeCovered[i] - 50 - senseDistance) / 2);    //This one is for vibrato

        baselineAverage += toneholeBaseline[i];    //Calculates baseline Average
        toneholeBaselineCurrent[i] = toneholeBaseline[i];
        if (toneholeBaseline[i] > maxBaseline) {
            maxBaseline = toneholeBaseline[i];
        }
    }

    baselineAverage = (baselineAverage / (float)TONEHOLE_SENSOR_NUMBER) * BASELINE_MACRO_FACTOR;


    if (switches[CUSTOM] && pitchBendMode != kPitchBendNone) {
        customEnabled = 1;
    } else (customEnabled = 0);    //decide here whether custom vibrato can currently be used, so we don't have to do it every time we need to check pitchBend.

    if (switches[FORCE_MAX_VELOCITY]) {
        velocity = 127;    //set velocity
    } else {
        velocity = 64;
    }

    if (!useLearnedPressure) {
        sensorThreshold[0] = (sensorCalibration + soundTriggerOffset);    //pressure sensor calibration at startup. We set the on/off threshhold just a bit higher than the reading at startup.
    }

    else {
        sensorThreshold[0] = (learnedPressure + soundTriggerOffset);
    }

    sensorThreshold[1] = sensorThreshold[0] + (offset << 2);    //threshold for move to second octave

    adjvibdepth = vibratoDepth / midiBendRange;    //precalculations for pitchbend range
    pitchBendPerSemi = 8192 / midiBendRange;

    inputPressureBounds[0][0] = (ED[INPUT_PRESSURE_MIN] * 9);    //precalculate input and output pressure ranges for sending pressure as CC
    inputPressureBounds[0][1] = (ED[INPUT_PRESSURE_MAX] * 9);
    inputPressureBounds[1][0] = (ED[VELOCITY_INPUT_PRESSURE_MIN] * 9);    //precalculate input and output pressure ranges for sending pressure as velocity
    inputPressureBounds[1][1] = (ED[VELOCITY_INPUT_PRESSURE_MAX] * 9);
    inputPressureBounds[2][0] = (ED[AFTERTOUCH_INPUT_PRESSURE_MIN] * 9);    //precalculate input and output pressure ranges for sending pressure as aftertouch
    inputPressureBounds[2][1] = (ED[AFTERTOUCH_INPUT_PRESSURE_MAX] * 9);
    inputPressureBounds[3][0] = (ED[POLY_INPUT_PRESSURE_MIN] * 9);    //precalculate input and output pressure ranges for sending pressure as poly
    inputPressureBounds[3][1] = (ED[POLY_INPUT_PRESSURE_MAX] * 9);

    for (byte j = 0; j < 4; j++) {                                                                                                                                    // CC, velocity, aftertouch, poly
        pressureInputScale[j] = (1048576 / (inputPressureBounds[j][1] - inputPressureBounds[j][0]));    //precalculate scaling factors for pressure input, which will be used to scale it up to a range of 1024.
        inputPressureBounds[j][2] = (inputPressureBounds[j][0] * pressureInputScale[j]) >> 10;
    }

    outputBounds[0][0] = ED[OUTPUT_PRESSURE_MIN];    //move all these variables to a more logical order so they can be accessed in FOR loops
    outputBounds[0][1] = ED[OUTPUT_PRESSURE_MAX];
    outputBounds[1][0] = ED[VELOCITY_OUTPUT_PRESSURE_MIN];
    outputBounds[1][1] = ED[VELOCITY_OUTPUT_PRESSURE_MAX];
    outputBounds[2][0] = ED[AFTERTOUCH_OUTPUT_PRESSURE_MIN];
    outputBounds[2][1] = ED[AFTERTOUCH_OUTPUT_PRESSURE_MAX];
    outputBounds[3][0] = ED[POLY_OUTPUT_PRESSURE_MIN];
    outputBounds[3][1] = ED[POLY_OUTPUT_PRESSURE_MAX];

    curve[0] = ED[CURVE];
    curve[1] = ED[VELOCITY_CURVE];
    curve[2] = ED[AFTERTOUCH_CURVE];
    curve[3] = ED[POLY_CURVE];
}






//calculate pressure data for CC, velocity, channel pressure, and key pressure if those options are selected
void calculatePressure(byte pressureOption) {

    long scaledPressure = sensorValue - 100;    // input pressure range is 100-1000. Bring this down to 0-900
    scaledPressure = constrain(scaledPressure, inputPressureBounds[pressureOption][0], inputPressureBounds[pressureOption][1]);
    scaledPressure = (((scaledPressure * pressureInputScale[pressureOption]) >> 10) - inputPressureBounds[pressureOption][2]);    //scale input pressure up to a range of 0-1024 using the precalculated scale factor

    if (curve[pressureOption] == 1) {    //for this curve, cube the input and scale back down.
        scaledPressure = ((scaledPressure * scaledPressure * scaledPressure) >> 20);
    }

    else if (curve[pressureOption] == 2) {    //approximates a log curve with a piecewise linear function, avoiding division
        switch (scaledPressure >> 6) {
            case 0:
                scaledPressure = scaledPressure << 3;
                break;
            case 1 ... 2:
                scaledPressure = (scaledPressure << 1) + 376;
                break;
            case 3 ... 5:
                scaledPressure = scaledPressure + 566;
                break;
            default:
                scaledPressure = (scaledPressure >> 3) + 901;
                break;
        }
        if (scaledPressure > 1024) {
            scaledPressure = 1024;
        }
    }

    //else curve 0 is linear, so no transformation

    inputPressureBounds[pressureOption][3] = (scaledPressure * (outputBounds[pressureOption][1] - outputBounds[pressureOption][0]) >> 10) + outputBounds[pressureOption][0];    //map to output pressure range


    if (pressureOption == 1) {    //set velocity to mapped pressure if desired
        velocity = inputPressureBounds[pressureOption][3];
        if (velocity == 0) {    //use a minumum of 1 for velocity so a note is still turned on (changed in v. 2.1)
            velocity = 1;
        }
    }
}





//send pressure data
void sendPressure(bool force) {

    if (ED[SEND_PRESSURE] == 1 && (inputPressureBounds[0][3] != prevCCPressure || force)) {
        sendUSBMIDI(CC, ED[PRESSURE_CHANNEL], ED[PRESSURE_CC], inputPressureBounds[0][3]);    //send MSB of pressure mapped to the output range
        prevCCPressure = inputPressureBounds[0][3];
    }

    if ((switches[SEND_AFTERTOUCH] & 1)) {
        // hack
        int sendm = (!noteon && sensorValue <= 100) ? 0 : inputPressureBounds[2][3];
        if (sendm != prevChanPressure || force) {
            sendUSBMIDI(CHANNEL_PRESSURE, mainMidiChannel, sendm);    //send MSB of pressure mapped to the output range
            prevChanPressure = sendm;
        }
    }

    // poly aftertouch uses 2nd lowest bit of ED flag
    if ((switches[SEND_AFTERTOUCH] & 2) && noteon) {
        // hack
        int sendm = (!noteon && sensorValue <= 100) ? 0 : inputPressureBounds[3][3];
        if (sendm != prevPolyPressure || force) {
            sendUSBMIDI(KEY_PRESSURE, mainMidiChannel, notePlaying, sendm);    //send MSB of pressure mapped to the output range
            prevPolyPressure = sendm;
        }
    }
}