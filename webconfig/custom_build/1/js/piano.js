/**
 * Copyright notice
 *
 * (c) 2016
 * Anna Neovesky  Anna.Neovesky@adwmainz.de
 * Gabriel Reimers g.a.reimers@gmail.com
 *
 * Digital Academy www.digitale-akademie.de
 * Academy of Sciences and Literatur | Mainz www.adwmainz.de
 *
 * Licensed under The MIT License (MIT)
 */


var octaves = {
    C0 : 0, //,,,
    C1 : 1, //,,,
    C2 : 2, //,,
    C3 : 3, //,
    C4 : 4, //'
    C5 : 5, //''
    C6 : 6, //'''
    C7 : 7,  //''''
    C8 : 8,  //''''
    C9 : 9  //''''
}

var clefs = {
    G4 : 'G-2',
    F3 : 'F-4'
}

var MAX_OCTAVES =  octaves.C9;
var KEYS_PER_OCTAVE = 12;
var _displayedOctaves = 3;
var _startOctave = 3;
var _selectedClef = clefs.G4

// var verovioToolkit = new verovio.toolkit()


// function getSelectedClef() {
//     return _selectedClef
// }

// function setSelectedClef(newClef) {
//     var isF3 = newClef == clefs.F3
//     var isG4 = newClef == clefs.G4
//     if (!isF3 && !isG4) {
//         console.log("Keyboard > setSelectedClef > clef not in predefined values")
//     }
//     _selectedClef = newClef

//     var radioGroup = $('input[name="clef"]')
//     radioGroup.val([_selectedClef]); //this does not work. dont know why

//     return _selectedClef
// }

function numberOfDisplayedOctaves() {
    return _displayedOctaves
}

function paeCodeForKeyAtIndex(keyIndex, baseOctave, duration) {
    var octaveOffset = Math.floor(keyIndex / KEYS_PER_OCTAVE)
    var octaveIndex = baseOctave + octaveOffset
    var octaveSigns = [",,,", ",,", ",", "'", "''", "'''", "''''"]
    var octaveSign = octaveSigns[octaveIndex]
    console.log("octaveInd = " + baseOctave + " + " + octaveOffset)
    var notes = [duration + "C",
        "x" + duration + "C",
        "b" + duration + "D",
        duration + "D",
        "x" + duration + "D",
        "b" + duration + "E",
        duration + "E",

        duration + "F",
        "x" + duration + "F",
        "b" + duration + "G",
        duration + "G",
        "x" + duration + "G",
        "b" + duration + "A",
        duration + "A",
        "x" + duration + "A",
        "b" + duration + "B",
        duration + "B"]
    var note = notes[keyIndex % KEYS_PER_OCTAVE]
    note = octaveSign + note
    console.log("paeCode = " + note)

    return note
}

// function svgNotesForPlaineEasieCode(paeCode, clef, width, scalePercent) {
//     if (typeof(clef)==='undefined') clef = _selectedClef
//     if (typeof(width)==='undefined') width = 400
//     if (typeof(scalePercent)==='undefined') scalePercent = 20

//     if (scalePercent < 5) {
//         console.log("svgNotesForPlaineEasieCode > your scale is very low. It should be between 5 and 100")
//     }

//     if (width < 100) {
//         console.log("svgNotesForPlaineEasieCode > your width is very low. Notes may be cut off.")
//     }

//     var data = "@clef:" + clef + "\n"
//     data += "@keysig:" + " " + "\n"
//     data += "@timesig:" + " " + "\n"
//     data += "@data:" + paeCode


    
//     console.log("svgNotesForPlaineEasieCode > data: \n" + data)
//     var pageWidth = width * 100/scalePercent //so the resulting width of the SVG element is always as defined in width

//     var options = JSON.stringify({
//         inputFormat: 'pae',
//         pageHeight: 500,
//         pageWidth: pageWidth,
//         ignoreLayout: 1,
//         border: 0,
//         scale: scalePercent,
//         adjustPageHeight: 1
//     })
//     console.log("svgNotesForPlaineEasieCode > options: \n" + options)


//     var notesSVG = verovioToolkit.renderData(data, options);
//     return notesSVG
// }


function htmlForKeyboardWithOctaves(numberOfOctaves, startOctave) {
    if (typeof(numberOfOctaves)==='undefined') numberOfOctaves = 3
    if (typeof(startOctave)==='undefined') startOctave = octaves.C4

    //back keys are seperated to fields sharp and flat; this enables specific input
    _displayedOctaves = limitToRange(numberOfOctaves, 1, MAX_OCTAVES)
    _startOctave = limitToRange(startOctave, octaves.C0, octaves.C7)

    var currentOctave = _startOctave

    var keyhoardHTML = '\
        <ul class="DA-PianoKeyboard">\n'
        keyhoardHTML += '\
        <li class="startKey"></li>\n'
        
    for (var i = 0; i < _displayedOctaves; i++) {

            keyhoardHTML += '\
            <li class="whiteKey" id="midiKey' + (0 + i*12 + startOctave*12) + '">' + ((0 + i*12 + startOctave*12) == 60 ? '<p>&#x2022;</p>':'') + '</li>\n\
            <li class="blackKey" id="midiKey' + (1 + i*12 + startOctave*12) + '"></li>\n\
            <li class="whiteKey" id="midiKey' + (2 + i*12 + startOctave*12) + '"></li>\n\
            <li class="blackKey" id="midiKey' + (3 + i*12 + startOctave*12) + '"></li>\n\
            <li class="whiteKey" id="midiKey' + (4 + i*12 + startOctave*12) + '"></li>\n\
            <li class="whiteKey" id="midiKey' + (5 + i*12 + startOctave*12) + '"></li>\n\
            <li class="blackKey" id="midiKey' + (6 + i*12 + startOctave*12) + '"></li>\n\
            <li class="whiteKey" id="midiKey' + (7 + i*12 + startOctave*12) + '"></li>\n\
            <li class="blackKey" id="midiKey' + (8 + i*12 + startOctave*12) + '"></li>\n\
            <li class="whiteKey" id="midiKey' + (9 + i*12 + startOctave*12) + '"></li>\n\
            <li class="blackKey" id="midiKey' + (10 + i*12 + startOctave*12) + '"></li>\n\
            <li class="whiteKey" id="midiKey' + (11 + i*12 + startOctave*12) + '"></li>\n'
        currentOctave++
    }
    keyhoardHTML += '\
    <li class="endKey"></li>\n'
    keyhoardHTML += '\
        </ul>\n'

    var html = '\
        <div class="DA-Keyboardcontainer">'
        html +=  keyhoardHTML
    html += '\
        </div>'

    return html
}


function setPianoKeyColor(note, color) {
    var key = document.getElementById("midiKey" + note);

    if (key) {
        key.style.background = color;
    }
}

function pressPianoKey(note) {
    var key = document.getElementById("midiKey" + note);

    if (key) {
        key.style.background = '#60f775';
    }
}

function releasePianoKey(note) {
    var key = document.getElementById("midiKey" + note);

    if (key) {
        if (key.classList.contains("whiteKey")) {
            key.style.background = '#ffffff';

        } else {
            key.style.background = '#000000';
        }
    }

}
// function htmlForClefSelection() {
//     var html = ''

//     html += '\n\
//     <div id="DA-ClefSelection" class="DA-NoteClefSelection">\n\
//         <input type="radio" name="clef" id="clef-g" value="G-2">\n\
//         <label for="clef-g" >&#x1d11e;</label>\n\
//         \
//         <input type="radio" name="clef" id="clef-f" value="F-4">\n\
//         <label for="clef-f" >&#x1d122;</label>\n\
//     </div>\n\n'

//     return html
// }

// function htmlForNotesSelection() {
//     var html = ''

//     html += '\n\
//     <div id="DA-NoteSelection" class="DA-NoteClefSelection">\n\
//         <input type="radio" name="notes" id="note-1-1" value="1">\n\
//         <label for="note-1-1" >1/1</label>\n\
//         \
//         <input type="radio" name="notes" id="note-1-2" value="2">\n\
//         <label for="note-1-2" >1/2</label>\n\
//         \
//         <input type="radio" name="notes" id="note-1-4" checked value="4">\n\
//         <label for="note-1-4" >1/4</label>\n\
//         \
//         <input type="radio" name="notes" id="note-1-8" value="8">\n\
//         <label for="note-1-8" >1/8</label>\n\
//         \
//         <input type="radio" name="notes" id="note-1-16" value="6">\n\
//         <label for="note-1-16" >1/16</label>\n\
//         \
//         <input type="radio" name="notes" id="note-1-32" value="3">\n\
//         <label for="note-1-32" >1/32</label>\n\
//     </div>'

//     return html
// }




// function bindClefSelectionToFunction(callback) {

//     $("#DA-ClefSelection input").click(function () {

//         var selectedRadioBox = $("#DA-ClefSelection input[type='radio']:checked")
//         if (selectedRadioBox.length > 0) {
//             _selectedClef = selectedRadioBox.val();
//         }

//         callback(this, _selectedClef)
//     })
    
// }

function bindKeysToFunction(callback) {

    $(".DA-PianoKeyboard li").click(function () {
        var indexOfKey = $(this).index()

        var noteDuration = 4;
        var selectedRadioBox = $("#DA-NoteSelection input[type='radio']:checked")
        if (selectedRadioBox.length > 0) {
            noteDuration = selectedRadioBox.val();
        }

        var paeNote = paeCodeForKeyAtIndex(indexOfKey, _startOctave, noteDuration)
        callback(this, paeNote)
    })

}

function raiseOctave() {
    _startOctave = Math.min(_startOctave + 1, MAX_OCTAVES - numberOfDisplayedOctaves() + 1)
    updateOctaveLabels()
    updateShiftOctaveButtonsEnabled()
}

function lowerOctave() {
    _startOctave = Math.max(_startOctave - 1, 0)
    updateOctaveLabels()
    updateShiftOctaveButtonsEnabled()
}

function updateShiftOctaveButtonsEnabled() {
    var isMax = _startOctave == MAX_OCTAVES - _displayedOctaves + 1
    var isMin = _startOctave == 0
    $("#raiseOctave").prop('disabled', isMax)
    $("#lowerOctave").prop('disabled', isMin)
}

function updateOctaveLabels(){
    $('.whiteKey>p').each(function(i, domLabel) {
        var label = $(domLabel)
        var currentOctave = _startOctave + 1 + i
        label.text("C" + currentOctave)
    })
}

function limitToRange(number, min, max) {
    return Math.min(Math.max(min, number), max)
}