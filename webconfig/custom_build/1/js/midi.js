
// WARBL Web Configuration Tool MIDI Support Routines
//

//debugger;
//Defines in common with defines.h of Arduino prj
var MIDI_CONF_CHANNEL = 7; //Midi channel

var MIDI_SLOT_02 = 102; //base CC
var MIDI_SAVE_CALIB = 19; //Data
var MIDI_CALIB_SLOW_OS = 20; //Data
// var MIDI_SEND_FINGER_PATTERN_OS = 30; //Offset
// var MIDI_SEND_MODE_SELECTOR_OS = 33; //Offset
var MIDI_CURRENT_INSTR_OS = 60; //Offset
var MIDI_PB_MODE_OS = 63; //Offset
var MIDI_BREATH_MODE_OS = 68; //Offset
var MIDI_DEFAULT_INSTR_OS = 73; //Offset
var MIDI_SEND_BUTTON_PREF_OS = 76; //Offset
var MIDI_SEND_MOMENTARY_OS = 76; //Offset
var MIDI_SEND_CUSTOM_FINGERING	= 84; //Activates the trasmission of a custom fingering scheme
var MIDI_SEND_CUSTOM_FINGERING_NOTE	= 85;	//Note corresponding to current fingerPAttern
var MIDI_SEND_CUSTOM_FINGERING_CURRENT	= 86;	// Number of custom fignering for current schema
var MIDI_SEND_CUSTOM_FINGERING_TOTAL	= 87;	//Total number of custom fingerings
var MIDI_DELETE_CUSTOM_FINGERING_CURRENT = 88; //Delete all custom fignerings for current selector
var MIDI_DELETE_CUSTOM_FINGERING  = 89; //Delete all custom fingerings

var MIDI_TURN_OFF_COMM =90; //Offset
var MIDI_BUTTON_PREF_ACTION_OS = 91; //Offset
var MIDI_BUTTON_PREF_MIDI_CMD_OS = 110; //Offset
var MIDI_MOMENTARY_OFF_OS = 115; //Offset
var MIDI_MOMENTARY_ON_OS = 116; //Offset
var MIDI_BUTTON_AUTO_CALIB_OS = 117; //Offset
var MIDI_BELL_SENSOR_OS = 118; //Offset
var MIDI_DUMP_SETTINGS_CURRENT = 121; //Offset
var MIDI_DUMP_EEPROM = 122; //Offset
var MIDI_SAVE_SETTING_CURRENT = 123; //Offset
var MIDI_SAVE_SETTING_ALL = 124; //Offset
var MIDI_RESTORE_FACTORY_SETTING = 125; //Offset
var MIDI_SEND_SETTINGS = 126; //Offset
var MIDI_AUTO_CALIB = 127; //Offset


var MIDI_SLOT_03 = 103; //base CC

var MIDI_SLOT_04 = 104; //base CC
var MIDI_SEND_EXPRESSION_VARS_1_OS = 13; //Offset
var MIDI_SEND_EXPRESSION_DEPTH = 14;
var MIDI_SEND_LSB_LEARN_DRONE_PRESS_OS = 32; //Offset
var MIDI_SEND_MSB_LEARN_DRONE_PRESS_OS = 33; //Offset
var MIDI_SEND_LSB_LEARN_PRESS_OS = 34; //Offset
var MIDI_SEND_MSB_LEARN_PRESS_OS = 35; //Offset
var MIDI_SEND_SWITCH_VARS_OS = 40; //Offset
var MIDI_SEND_EXPRESSION_VARS_2_OS = 49; //Offset
var MIDI_SEND_BEND_RANGE_OS = 61; //Offset
var MIDI_SEND_MIDI_CHAN_OS = 62; //Offset

var MIDI_SEND_TRANSPOSE_SHIFT =                   100; //Offset 0=-12 ... 24=+12
var MIDI_SEND_HARMONIZER_FIXED_NOTE  =            101; //Offset +2
var MIDI_SEND_HARMONIZER_INTERVAL  =              102; //Offset +2  0=-12 ... 24=+12
var MIDI_SEND_HARMONIZER_TONIC =                  105; //Offset +2 0=C ... 11=B
var MIDI_SEND_HARMONIZER_SCALE =                  108; //Offset +2 
var MIDI_SEND_HARMONIZER_BASE_NOTE =              111; //Offset +2  0=C ... 11=B
var MIDI_SEND_HARMONIZER_BASE_NOTE_DIATONIC =     114; //Offset +2 0/1
var MIDI_SEND_HARMONIZER_CURRENT_NOTE =           117; //Offset +2  0=C ... 11=B
var MIDI_SEND_HARMONIZER_CURRENT_NOTE_DIATONIC =  120; //Offset +2 0/1

var MIDI_SEND_HALFHOLE_BUFFER = 				  123; //size of the buffer
var MIDI_SEND_HALFHOLE_CURRENT =                  124 //current hole
var MIDI_SEND_HALFHOLE_SAVE =          			  125 //saves calibration and buffer size
// var MIDI_SEND_HALFHOLE_MIN =                      126 //lowerBound
// var MIDI_SEND_HALFHOLE_MAX =                      127 //upperBound

var MIDI_SLOT_05 = 105; //base CC

var MIDI_SLOT_06 = 106; //base CC
var MIDI_EN_VIBRATO_HOLES_OS = 20; //Offset
var MIDI_CALIB_OPTION_OS = 39; //Offset
var MIDI_USE_LEARN_PRESS_OFF = 39; //Offset
var MIDI_USE_LEARN_PRESS_ON = 40; //Offset
var MIDI_SEND_LEARN_PRESS = 41; //Offset
var MIDI_AUTO_CALIB_BELL = 42; //Offset
var MIDI_SEND_LEARN_PRESS_DRONE = 43; //Offset
var MIDI_SAVE_CALIB_AS_FACTORY = 45; //Offset

// var MIDI_SEND_DEBUG_LSB_OS = 48; //Offset
// var MIDI_SEND_DEBUG_MSB_OS = 49; //Offset
// var MIDI_DEBUG_2BYTE_MSG_OS = 51; //Offset

var MIDI_SLOT_07 = 107; //base CC
var MIDI_SLOT_08 = 108; //base CC

var MIDI_SLOT_09 = 109; //base CC

var MIDI_SW_VERSION = 110; //CC
var MIDI_SW_BUILD_VERSION = 111; //CC

var MIDI_SLOT_12 = 112; //base CC - keySelect (base transpose) - Not used anymore

var MIDI_SLOT_13 = 113; //intValue selector

	var MIDI_SEND_HOLE_COVERED = 10 // Current holeCovered Value	
	var MIDI_SEND_KEY_SELECT = 12 // keySelect / noteShiftSelector

	
	var MIDI_SEND_MODE_SELECTOR = 30; //30-32 int value for fingering scheme index

	// var MIDI_SEND_HALFHOLE_CALIBRATION = 90; //calibration value for selected hole
	var MIDI_SEND_HALFHOLE_MIN =    	 80; //lowerBound
	var MIDI_SEND_HALFHOLE_MAX =    	 81; //upperBound

	var MIDI_SEND_TONE_BASELINE_0 = 90 // Calibration for hole 0
	var MIDI_SEND_TONE_BASELINE_1 = 91 // Calibration for hole 1
	var MIDI_SEND_TONE_BASELINE_2 = 92 // Calibration for hole 2
	var MIDI_SEND_TONE_BASELINE_3 = 93 // Calibration for hole 3
	var MIDI_SEND_TONE_BASELINE_4 = 94 // Calibration for hole 4
	var MIDI_SEND_TONE_BASELINE_5 = 95 // Calibration for hole 5
	var MIDI_SEND_TONE_BASELINE_6 = 96 // Calibration for hole 6
	var MIDI_SEND_TONE_BASELINE_7 = 97 // Calibration for hole 7
	var MIDI_SEND_TONE_BASELINE_8 = 98 // Calibration for hole 8

	var MIDI_SEND_TONE_COVERED_0 = 100 // Calibration for hole 0
	var MIDI_SEND_TONE_COVERED_1 = 101 // Calibration for hole 1
	var MIDI_SEND_TONE_COVERED_2 = 102 // Calibration for hole 2
	var MIDI_SEND_TONE_COVERED_3 = 103 // Calibration for hole 3
	var MIDI_SEND_TONE_COVERED_4 = 104 // Calibration for hole 4
	var MIDI_SEND_TONE_COVERED_5 = 105 // Calibration for hole 5
	var MIDI_SEND_TONE_COVERED_6 = 106 // Calibration for hole 6
	var MIDI_SEND_TONE_COVERED_7 = 107 // Calibration for hole 7
	var MIDI_SEND_TONE_COVERED_8 = 108 // Calibration for hole 8

	var MIDI_SEND_TONE_READ_0 = 110 // Sensor read value for hole 0
	var MIDI_SEND_TONE_READ_1 = 111 // Sensor read value for hole 1
	var MIDI_SEND_TONE_READ_2 = 112 // Sensor read value for hole 2
	var MIDI_SEND_TONE_READ_3 = 113 // Sensor read value for hole 3
	var MIDI_SEND_TONE_READ_4 = 114 // Sensor read value for hole 4
	var MIDI_SEND_TONE_READ_5 = 115 // Sensor read value for hole 5
	var MIDI_SEND_TONE_READ_6 = 116 // Sensor read value for hole 6
	var MIDI_SEND_TONE_READ_7 = 117 // Sensor read value for hole 7
	var MIDI_SEND_TONE_READ_8 = 118 // Sensor read value for hole 8

	var MIDI_SEND_BASELINE_AVERAGE       =         120 //Debug Info
	var MIDI_SEND_BASELINE_CURRENT_AVERAGE       = 121 //Debug Info
	var MIDI_SEND_MAX_BASELINE = 				   122; //DEbug Info

var MIDI_SLOT_14 = 114; //intValue H byte
var MIDI_SLOT_15 = 115; //intValue L byte

var MIDI_SLOT_16 = 116; //base CC FREE
var MIDI_SLOT_17 = 117; //base CC vibratoDepth
var MIDI_SLOT_18 = 118; //base CC FREE
var MIDI_SLOT_19 = 119; //base CC FREE

/*
Harmonizer  vars
*/

var currentNote = -1;
var fixedNote = -1;
var harmonizerCurrentNotes = [-1, -1, -1];
var harmonizerIntervals = [12, 12, 12];
var harmonizerScale = [0, 0, 0];

/******/

var mapSelection; //keeps track of which pressure output we're mapping (CC, vel, aftertouch, poly)
var curve = [0,0,0,0]; //which curve is selected for CC, vel, aftertouch, poly
var inputSliderMin = [0,0,0,0]; //settings for sliders
var inputSliderMax = [100,100,100,100];
var outputSliderMin = [0,0,0,0];
var outputSliderMax = [127,127,127,127];
var consoleEntries = 0; //number of lines in MIDI console
var customFingeringFills = [[null,null,null,null,null,null,null,null,null,null,null],[0,74,73,72,71,69,67,66,64,62,61],[0,74,72,72,70,68,67,65,64,62,61],[0,74,74,72,72,69,68,67,65,62,60]];
var communicationMode = false; //if we're communicating with WARBL

//20231005 GLB New Custom Fingering
var customFingeringLearningON = true;
var customFingeringMidiNote = -1;
var defaultMidiNote = -1;
var overrideMidiNote = -1;
var currentCustomFingeringNumber = 0;
var totalCustomFingeringNumber = 0;

var customFingeringReceivingCustomMidiNote = false;
var customFingeringReceivingCurrentNumber = false;
var customFingeringReceivingTotalNumber = false;

var holeCovered = 0;
var halfHoles = 0;
var maxCustomFingering = 30;
let customFingering = new Array(); //Stores the custom fingerings sent by WARBL
var customFingeringReceivingStatus = false; // false = normal communication
							 	 // true = receiving custom Fingering Info
								 // It's toggled by cc 102/68
//END GLB
var midiNotes = [];

var currentVersion = 23

var midiAccess = null; // the MIDIAccess object.
var WARBLin = null; //WARBL input port

var WARBLout = null; // WARBL output port

var gExportProxy = null; // Export received message proxy
var exportingPhase = false; //exporting phase active

// For pressure graphing
var gPressureGraphEnabled = false; // When true, proxy pressure messages to graphing code
var gCurrentPressure = 0.0;
var gGraphInterval = null;
var gNPressureReadings = 100;
var gMaxPressure = 25;
var gPressureReadings = [];

//20231014 GLB Settings Management
var settingsDirty = false; //to prompt for save

var on,off;


var deviceName;

var volume = 0;

var currentNote = 62;

var sensorValue = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0];

var buttonRowWrite; //used to indicate which button command row we'll be writing to below.

var jumpFactorWrite; //to indicate which pressure variably is going to be sent or received

var fingeringWrite; //indicates the instrument for which a fingering pattern is being sent.

var intValueWrite; //to indicate which int Value is going to be sent or received
var intValueWriteH; //high byte of int Value being sent or received

var version = "Unknown";
var build_version = 0;

var currentPreset = 0; //currently selected instrument tab

var ping = 0;

var lsb = 0; //used for reassembling pressure bytes from WARBL

var defaultPreset = 0; //default instrument

var modals = new Array();

for (var w = 1; w <= 23; w++) {

	modals[w] = document.getElementById("open-modal" + w);

}

if (typeof platform == "undefined") {
	var platform = "app";
}

//hide some stuff for app version
if (platform == "app") {
	document.getElementById("myTopnav").style.display = "none";
	document.getElementById("topLogo").style.display = "none";
	//document.getElementById("importexport").style.display = "none";
}

//Flutter
function postMessage(channel, message) {
	window[channel] ? window[channel].postMessage(message) : console.log(message);
}

// When the user clicks anywhere outside of the modal, close it
window.onclick = function(event) {
	
	for (var i = 1; i <= 23; i++) {

		if (event.target == modals[i]) {

			modalclose(i);

		}
	}
	event.stopPropagation();
}

window.addEventListener('load', function() {
	
	//console.log("window onLoad");

	// Clear the WARBL output port
	WARBLout = null;
	WARBLin = null;

	
	populateSelects(); //populates various selects

	updateCells(); // set selects and radio buttons to initial values and enabled/disabled states
	
	for (var i = 1; i < 13; i++) { //trigger input event for sliders to display values
		var k = document.getElementById("jumpFactor" + (i));
		k.dispatchEvent(new Event('input'));
		if (i == 10) {
			var k = document.getElementById("jumpFactor10b"); //special case for key delay slider
			k.dispatchEvent(new Event('input'));
		}
		
	}
	
	depth.dispatchEvent(new Event('input'));

	$(".volume").click(function() {
		toggleOn();
		$(this).find('i').toggleClass('fa-volume-up fa-volume-off')
	});

	
	if (navigator.requestMIDIAccess) {
		console.log("navigator.requestMIDIAccess", true);
		navigator.requestMIDIAccess({
			sysex: false
		}).then(onMIDIInit, onMIDIReject);
	} else {
		console.log("navigator.requestMIDIAccess", false);

		alert("Your browser does not support MIDI. Please use Chrome or Opera, or the free WARBL iOS app.")
	}

});

/*
20231003 GLB
Utility functions
*/
var NOTE_NAMES = [ 'C', 'Db', 'D', 'Eb', 'E', 'F', 'Gb', 'G', 'Ab', 'A', 'Bb', 'B' ]
function getNoteName(note, octave = true) {
	
	if (isNaN(note) || note > 127) return null
	if (note <= 0) {
		return "Silent position";
	}
	var name = NOTE_NAMES[note % 12]
	if (octave) {
		var oct = Math.floor(note / 12) - 1
		return name + oct
	}
	return name;
  }

  function dec2bin(dec) {
	return (dec >>> 0).toString(2);
  }
//
// Common function to show the "WARBL not detected" message
//
function showWARBLNotDetected(){

	communicationMode = false; //make sure we know we're not connected
	document.getElementById("status").innerHTML = "WARBL not detected.";
	document.getElementById("status").style.color = "#F78339";
	document.getElementById("version").style.color = "#F78339";
	document.getElementById("connect").innerHTML = "Connect to WARBL";	//make sure the connect button shows the correct text
	document.getElementById("pressure").innerHTML = "";
	for (var m = 0; m < 9; m++) { //turn off toneholes
		document.getElementById("dot" + m).style.backgroundColor = "#333";
		if (m == 0) {
			document.getElementById("dot0").style.opacity = "0";					
		}
	}



	
	// Disable the import preset button
	$('#importPreset').attr('disabled','disabled');
	document.getElementById("topcontrolbox").style.height = "10px";
	document.getElementById("middleControlBox").style.display = "none";
	document.getElementById("performanceBox").style.display = "none";
	document.getElementById("calibrationBox").style.display = "none";
	document.getElementById("halfHoleDetection").style.display = "none";

	document.getElementById("importexport").style.display = "none";

}

//
// Common function to show the "Unknown" version message
//
function showWARBLUnknown(){

	document.getElementById("version").innerHTML = "Unknown";
	document.getElementById("current").style.visibility = "hidden";
	document.getElementById("status").style.visibility = "visible";
	document.getElementById("connect").innerHTML = "Connect to WARBL";	//make sure the connect button shows the correct text
	

	// Disable the import preset button
	$('#importPreset').attr('disabled','disabled');

}

function connect() {
	
	if (communicationMode && version > 2.0) {
		sendToAll(MIDI_SLOT_02, MIDI_TURN_OFF_COMM); //tell WARBL to exit communications mode if the "connect" button currently reads "Disconnect"
		communicationMode = false;
		showWARBLNotDetected();
		showWARBLUnknown();

		document.getElementById("connect").innerHTML = "Connect to WARBL";	//make sure the connect button shows the correct text
		if (midiAccess){
			//20231015 GLB - Close the ports to release them. Clearing the callbacks isn't enough

			if (WARBLin) {
				WARBLin.onmidimessage = null;
				WARBLin.close();
			}
			//console.log("connect: Have a midiAccess, clearing the receive callbacks");

			// // Walk the inputs and clear any receive callbacks
			// var inputs = midiAccess.inputs.values();

			// for (var input = inputs.next(); input && !input.done; input = inputs.next()) {

			// 	//input.value.onmidimessage = null;

			// }
		}

		WARBLout = null;
		WARBLin = null;
		midiAccess = null;

		ping = 0;
	
	} else {
		//debugger;

		//console.log("connect");
		//alert("connect");
		// Clear the midiAccess object callbacks
		if (midiAccess){

			//20231015 GLB - Close the ports to release them. Clearing the callbacks isn't enough
			if (WARBLin) {
				WARBLin.onmidimessage = null;
				WARBLin.close();
			}
			//console.log("connect: Have a midiAccess, clearing the receive callbacks");

			// Walk the inputs and clear any receive callbacks
			// var inputs = midiAccess.inputs.values();

			// for (var input = inputs.next(); input && !input.done; input = inputs.next()) {

			// 	//input.value.onmidimessage = null;

			// }
		}

		midiAccess = null;

		// Clear the WARBL output port
		WARBLout = null;

		ping = 0;

		// Setup initial detection and version messages
		showWARBLNotDetected();
		showWARBLUnknown();

		// If availabe in the browser, request MIDI access with sysex support
		if (navigator.requestMIDIAccess) {
			navigator.requestMIDIAccess({
				sysex: false
			}).then(onMIDIInit, onMIDIReject);
		} else {
			alert("Your browser does not support MIDI. Please use Chrome or Opera, or the free WARBL iOS app.");
		}
	}
}

//
// Callback when first requesting WebMIDI support
//
function onMIDIInit(midi) {

	//debugger;

	//console.log("onMIDIInit");
//alert("onMiDIInitl");
	// Save off the MIDI access object
	midiAccess = midi;

	// Null the WARBL MIDI output port
	WARBLout = null;
	WARBLin = null;

	var foundMIDIInputDevice = false;
	
	// Walk the inputs and see if a WARBL is connected
	var inputs = midiAccess.inputs.values();

	for (var input = inputs.next(); input && !input.done; input = inputs.next()) {

		deviceName = input.value.name;

		//console.log("deviceName = "+deviceName);
		//alert("deviceName = "+deviceName);
			
		setPing(); //start checking to make sure WARBL is still connected   
		if (deviceName == "WARBL" || deviceName == "hemiolaWARBL") {
			WARBLin = input.value;
			WARBLin.onmidimessage = WARBL_Receive;
			foundMIDIInputDevice = true;
		}
	}

	if (foundMIDIInputDevice){
		
		if (!communicationMode || version < 2.1 || version == "Unknown"){

			sendToAll(MIDI_SLOT_02, MIDI_SEND_SETTINGS); //tell WARBL to enter communications mode
			
			document.getElementById("topcontrolbox").style.height = "1785px";
			document.getElementById("middleControlBox").style.display = "block";
			document.getElementById("performanceBox").style.display = "block";
			document.getElementById("calibrationBox").style.display = "block";
			document.getElementById("importexport").style.display = "block";
		
		} 
		

	}
	else{

		showWARBLNotDetected();
		
		
	}

	midi.onstatechange = midiOnStateChange;

}

function onMIDIReject(err) {

	alert("The MIDI system failed to start. Please refresh the page.");

}

function midiOnStateChange(event) {
	
	//console.log("state change");

	if (ping == 1) {

		showWARBLNotDetected();
		showWARBLUnknown();
		WARBLout = null;
		WARBLin = null;	
		document.getElementById("connect").innerHTML = "Connect to WARBL";	//make sure the connect button shows the correct text

	}

}

function setPing() {

	//change ping to 1 after 3 seconds, after which we'll show a disconnnect if the MIDI state changes.
	setTimeout(function() {

		ping = 1;

	}, 3000);
}

//
// Common message handler for sendToAll and sendToWARBL to build send message
//
function buildMessage(byte2, byte3){

	if (!(byte2 == MIDI_SLOT_02 && byte3 == MIDI_AUTO_CALIB) && !(byte2 == MIDI_SLOT_06 && byte3 == MIDI_AUTO_CALIB_BELL)) {
		blink(1);
	} //blink once if we aren't doing autocalibration, which requires the LED to be on longer.

	if (byte2 == MIDI_SLOT_02) {
		if (byte3 == MIDI_SAVE_CALIB) { //send message to save sensor calibration
			blink(3);
			for (var i = 1; i < 10; i++) {
				document.getElementById("v" + (i)).innerHTML = "0";
			}
			for (var i = 0; i < 19; i++) {
				sensorValue[i] = 0;
			}
		}

		if (isEven(byte3) && byte3 < MIDI_SAVE_CALIB) { //send sensor calibration values
			sensorValue[byte3 - 2]++;
			document.getElementById("v" + (byte3 >> 1)).innerHTML = sensorValue[byte3 - 2];
		}

		if (isOdd(byte3) && byte3 < MIDI_SAVE_CALIB) {
			sensorValue[byte3 - 1]--;
			document.getElementById("v" + ((byte3 + 1) >> 1)).innerHTML = sensorValue[byte3 - 1];
			checkMax((byte3 + 1) >> 1);
		}
	}

	cc = [0xB6, byte2, byte3]; //prepare message

	return cc;
}

//
// Send to all connected MIDI devices
//
function sendToAll(byte2, byte3) {

	//console.log("sendToAll");

	var cc = buildMessage(byte2,byte3);

	// Send to all MIDI output ports
	var iter = midiAccess.outputs.values();

	for (var o = iter.next(); !o.done; o = iter.next()) {

		//console.log("o.value.name: "+o.value.name);

		o.value.send(cc, window.performance.now()); //send CC message

	}

}

//20231006 GLB
//send value as PitchBend message to WARBL
// function sendPBToWARBL(value) {
// 	if(communicationMode) {

// 		var msg = [0xE6,  value & 0x7F, value >> 7]; //prepare message

// 		if (platform = "app") {
// 			var iter = midiAccess.outputs.values();
// 			for (var o = iter.next(); !o.done; o = iter.next()) {
// 				o.value.send(msg, window.performance.now()); //send message
// 			}
// 		} else {
// 			// Make sure we have a WARBL output port
// 			if (!WARBLout){

// 				console.error("sendToWARBL: No MIDI port selected!")
			
// 				return;

// 			}		
// 			// Send to only WARBL MIDI output port
// 			WARBLout.send(msg, window.performance.now()); //send CC message
// 		}
// 	}
// }

// Send a command to only the WARBL output port
function sendToWARBL(byte2, byte3) {
	if(communicationMode){
		if (platform = "app") {
			var cc = buildMessage(byte2,byte3);
			var iter = midiAccess.outputs.values();
			for (var o = iter.next(); !o.done; o = iter.next()) {
				o.value.send(cc, window.performance.now()); //send CC message
			}
		} else {
			// Make sure we have a WARBL output port
			if (!WARBLout){
				console.error("sendToWARBL: No MIDI port selected!")
				return;
			}
			var cc = buildMessage(byte2,byte3);
			// Send to only WARBL MIDI output port
			WARBLout.send(cc, window.performance.now()); //send CC message
		}

		settingsDirty = true;
		// console.log("sendToWARBL",byte2,byte3);
	}
}


function WARBL_Receive(event) {
	
	//debugger;
	
	//alert("received");

	var data0 = event.data[0];
	var data1 = event.data[1];
	var data2 = event.data[2];
	
	//alert(WARBLout);

	// If we're exporting a preset, send the data to the exporter instead
	if (gExportProxy){
		if ( ((data0 & 0xf0) == 0xB0)  //CC
			&& (data1 == MIDI_SLOT_02) 
			&& (data2 == MIDI_DUMP_SETTINGS_CURRENT)) { //exiting settings sending
				exportingPhase = false;
		}
		gExportProxy(data0,data1,data2);
		return;
	}

	//console.log("WARBL_Receive");
	//console.log("WARBL_Receive target = "+event.target.name);
	//console.log("WARBL_Receive: "+data0+" "+data1+" "+data2);

	// If we haven't established the WARBL output port and we get a received message on channel 7
	// find the port by name by walking the output ports and matching the input port name
	if ((!WARBLout) && ((data0 & 0x0F) == MIDI_CONF_CHANNEL-1)){
		//alert(data0 & 0x0F);
		

	if (platform == "web"){

		//alert(input.value.name);
	 	var inputName = event.target.name;


	 	// Strip any [] postfix
	 	
	 	var inputBracketIndex = inputName.indexOf("[");

	 	if (inputName.indexOf("[")!=-1){

	 		inputName = inputName.substr(0,inputBracketIndex);
	 		
	 	}

		//console.log("Searching for WARBL output port matching input port name: "+targetName);
//alert("Searching for WARBL output port matching input port name: "+targetName);
		// Send to all MIDI output ports
		var iter = midiAccess.outputs.values();

		for (var o = iter.next(); !o.done; o = iter.next()) {

			var outputName = o.value.name;

		 	// Strip any [] postfix
		 	
		 	var outputBracketIndex = outputName.indexOf("[");

		 	if (outputName.indexOf("[")!=-1){

		 		outputName = outputName.substr(0,outputBracketIndex);

		 	}

			if (outputName == inputName){

				//console.log("Found the matching WARBL output port!")

				WARBLout = o.value;
				
				break;
			}
		}	

		if (!WARBLout){

			//console.error("Failed to find the WARBL output port!")
			
			showWARBLNotDetected();
			if (WARBLin) {
				WARBLin.close();
			}

		} 	
	}
	
	else{ //app version
	WARBLout = 1; //for app version we don't worry about the device name or port, just that it's sending on channel 7.
	}
	
	
	}

	var e;
	var f;
	var g;
	
	if (isNaN(data2)) {
		f = " ";
	} else {
		f = data2;
	}

	if ((data0 & 0xf0) == 144) {
		e = "On";
		//20231005 GLB- New Custom Fingering - Toggles learnign mode
		customFingeringLearningON = !customFingeringLearningON;
		if (customFingeringLearningON) { //Resets the holes
			for (i = 1; i<9; i++) {
				document.getElementById("fingeringDot" + i).style.fill = "#a3a0a0";
			}
		}
		document.getElementById("customFingeringReset").disabled = customFingeringLearningON;
		document.getElementById("customFingeringModify").disabled = customFingeringLearningON;

		
	} //update the MIDI console
	if ((data0 & 0xf0) == 128) {
		e = "Off";
	}
	if ((data0 & 0xf0) == 176) {
		e = "CC";
	}
	if ((data0 & 0xf0) == 224) {
		e = "PB";
	}
	if ((data0 & 0xf0) == 192) {
		e = "PC";
	}
	if ((data0 & 0xf0) == 208) {
		e = "CP";
	}	
	if ((data0 & 0xf0) == 160) {
		e = "KP";
	}
	
	
	
	if (!(e == "CC" && ((parseFloat(data0 & 0x0f) == MIDI_CONF_CHANNEL-1)))) { //as long as it's not a CC on channel 7, show in the MIDI console.
		consoleEntries++;
			if(consoleEntries < 301){
				document.getElementById("console").innerHTML += (e + " " + ((data0 & 0x0f) + 1) + " " + data1 + " " + f);
				document.getElementById("console").innerHTML += "<br>";	 
			}
			else if (consoleEntries == 301) {document.getElementById("console").innerHTML += "max lines reached";
			}
			var elem2 = document.getElementById("console");
		elem2.scrollTop = elem2.scrollHeight;	
	}

	// Mask off the lower nibble (MIDI channel, which we don't care about yet)
	switch (data0 & 0xf0) {
		case 0x90:
			if (data2 != 0) { // if velocity != 0, this is a note-on message
				noteOn(data1);
				logKeys;
				pressPianoKey(data1);
				return;
			}
			// if velocity == 0, fall thru: it's a note-off.
		case 0x80:
			noteOff(data1);
			logKeys;
			releasePianoKey(data1);
			return;

		case 0xE0: //Incoming PitchBend from Warbl 
			if (parseFloat(data0 & 0x0f) == MIDI_CONF_CHANNEL -1) { //if it's channel 7 it's from WARBL 
			
			}

			return;
		case 0xB0: //incoming CC from WARBL

			if (parseFloat(data0 & 0x0f) == MIDI_CONF_CHANNEL -1) { //if it's channel 7 it's from WARBL 

				// Enable the import preset button
				$('#importPreset').removeAttr('disabled')

				if (data1 == MIDI_SLOT_09) { //current fingered note info from WARBL
					if (customFingeringReceivingStatus) {
						customFingeringMidiNote = data2;
					} else {
						if (customFingeringReceivingCurrentNumber) {
							currentCustomFingeringNumber = data2;
							customFingeringReceivingCurrentNumber = false;
							document.getElementById("customFingeringCustomNumber").innerHTML = currentCustomFingeringNumber;

						} else if (customFingeringReceivingTotalNumber) {
							totalCustomFingeringNumber = data2;
							customFingeringReceivingTotalNumber = false;
							document.getElementById("customFingeringTotalNumber").innerHTML = totalCustomFingeringNumber;

						}
						if (customFingeringLearningON)  {
							if (customFingeringReceivingCustomMidiNote) {
								overrideMidiNote = data2;
								customFingeringReceivingCustomMidiNote = false;
							} else {
								defaultMidiNote = data2;
								if (overrideMidiNote < 0x7f && defaultMidiNote != overrideMidiNote) {
									document.getElementById("customFingeringInput").value = overrideMidiNote;
								}  else  {
									document.getElementById("customFingeringInput").value = defaultMidiNote;
								}
								
								customFingeringInput();
							}
						}
					}

				} else if (data1 == MIDI_SLOT_02) { //parse based on received CC
					if (data2 >= MIDI_CALIB_SLOW_OS && data2 < MIDI_CALIB_SLOW_OS + 10) {
						document.getElementById("v" + (data2 - MIDI_SAVE_CALIB)).innerHTML = "MAX"; //set sensor value field to max if message is received from WARBL
						checkMax((data2 - MIDI_SAVE_CALIB));
					}

					//Moved to int value
					// for (var i = 0; i < 3; i++) { // update the three selected fingering patterns if prompted by the tool.
					// 	if (data2 == MIDI_SEND_FINGER_PATTERN_OS + i) {
					// 		fingeringWrite = i;
					// 	}

					// 	if (data2 >= MIDI_SEND_MODE_SELECTOR_OS && data2 < MIDI_CURRENT_INSTR_OS) {
					// 		if (fingeringWrite == i) {
					// 			document.getElementById("fingeringSelect" + i).value = data2 - MIDI_SEND_MODE_SELECTOR_OS;
					// 		}
					// 		updateCells();
					// 	} //update any dependant fields	
					// }



					if (data2 >= MIDI_CURRENT_INSTR_OS && data2 <= MIDI_CURRENT_INSTR_OS + 2) {
						for (var i = 0; i< 3; i++) {
							if (i == data2-MIDI_CURRENT_INSTR_OS) {
								currentPreset = i;
								document.getElementById("fingering" + i).checked = true;
								document.getElementById("instrument" + i).style.display = "block";
								document.getElementById("key" + i).style.display = "block";
							} else {
								document.getElementById("instrument" + i).style.display = "none";
								document.getElementById("key" + i).style.display = "none";
							}
						}
						handleDefault();
						advancedOkay(); //turn off the advanced tab	
						pressureOkay();	
						updateCells();
						okayCCmap();
						okayOverride();
						advancedOkayPB();
						customFingeringOkay();
						halfHoleDetectionOkay();
					}
					

					if (data2 == MIDI_DEFAULT_INSTR_OS) { //receive and handle default instrument settings
						defaultPreset = 0;
						handleDefault();
					}
					if (data2 == MIDI_DEFAULT_INSTR_OS +1) {
						defaultPreset = 1;
						handleDefault();
					}
					if (data2 == MIDI_DEFAULT_INSTR_OS +2) {
						defaultPreset = 2;
						handleDefault();
					}

					if (data2 == MIDI_PB_MODE_OS) {
						document.getElementById("pitchbendradio0").checked = true;
						updateCustom();
						updateCustom();
					}
					if (data2 == MIDI_PB_MODE_OS+1) {
						document.getElementById("pitchbendradio1").checked = true;
						updateCustom();
						updateCustom();
					}
					if (data2 == MIDI_PB_MODE_OS+2) {
						document.getElementById("pitchbendradio2").checked = true;
						updateCustom();
						updateCustom();
					}
					if (data2 == MIDI_PB_MODE_OS+3) {
						document.getElementById("pitchbendradio3").checked = true;
						updateCustom();
						updateCustom();
					}

					//20231006 GLB new custom fingering flags
					if (data2 == MIDI_SEND_CUSTOM_FINGERING) {
						customFingeringReceivingStatus = !customFingeringReceivingStatus;

						//Clears the array before filling it up
						if (customFingeringReceivingStatus) {
							customFingering = [];
						} else {
							//updates the interface
							customFingering.forEach(logCustomFingering);

							function logCustomFingering(item) {
								console.log(item.midi_note, dec2bin(item.holeCovered));
							}
						}
					}

					if (data2 == MIDI_SEND_CUSTOM_FINGERING_NOTE) {
						customFingeringReceivingCustomMidiNote = true;
					}

					if (data2 == MIDI_SEND_CUSTOM_FINGERING_CURRENT) {
						customFingeringReceivingCurrentNumber = true;
					}

					if (data2 == MIDI_SEND_CUSTOM_FINGERING_TOTAL) {
						customFingeringReceivingTotalNumber = true;
					}

					//End glb

					if (data2 == MIDI_BREATH_MODE_OS) {
						document.getElementById("sensorradio0").checked = true;
					}
					if (data2 == MIDI_BREATH_MODE_OS+1) {
						document.getElementById("sensorradio1").checked = true;
					}
					if (data2 == MIDI_BREATH_MODE_OS+2) {
						document.getElementById("sensorradio2").checked = true;
					}
					if (data2 == MIDI_BREATH_MODE_OS+3) {
						document.getElementById("sensorradio3").checked = true;
					}

					if (data2 == MIDI_BELL_SENSOR_OS+1) {
						document.getElementById("bellSensor").style.opacity = 1;
						document.getElementById("1").disabled = false;
						document.getElementById("2").disabled = false;
						document.getElementById("v1").classList.add("sensorValueEnabled");

					}
					if (data2 == MIDI_BELL_SENSOR_OS) {
						document.getElementById("bellSensor").style.opacity = 0.1;
						document.getElementById("1").disabled = true;
						document.getElementById("2").disabled = true;
						document.getElementById("v1").classList.remove("sensorValueEnabled");
					}

					for (var i = 0; i < 8; i++) { //update button configuration	   
						if (data2 == MIDI_SEND_BUTTON_PREF_OS + i) {
							buttonRowWrite = i;
						}
					}

					for (var j = 0; j < 8; j++) { //update button configuration	
						if (buttonRowWrite == j) {

							// if (data2 == MIDI_BUTTON_AUTO_CALIB_OS) { //special case for initiating autocalibration
							// 	document.getElementById("row" + (buttonRowWrite)).value = 19;
							// }

							for (var k = 0; k < 18; k++) {
								if (data2 == (MIDI_BUTTON_PREF_ACTION_OS + k)) {
									//20230927 GLB
									// if (k == 5) {
									// 	document.getElementById("row" + (buttonRowWrite)).value = 30;
									// } 
									// else if (k == 6) {
									// 	document.getElementById("row" + (buttonRowWrite)).value = 32;
									// } else if (k == 10) {
									// 	document.getElementById("row" + (buttonRowWrite)).value = 33;
									// } else if (k == 11) {
									// 	document.getElementById("row" + (buttonRowWrite)).value = 34;
									// } else if (k == 12) {
									// 	document.getElementById("row" + (buttonRowWrite)).value = 35;
									// } 
									// else{
										document.getElementById("row" + (buttonRowWrite)).value = k;
									// }
									//END GLB
								}
								if (k < 5 && data2 == MIDI_BUTTON_PREF_MIDI_CMD_OS + k) {
									document.getElementById("MIDIrow" + (buttonRowWrite)).value = k;
									updateCells();
								}
							}
						}
					} //update any dependant fields}						


					for (var l = 0; l < 3; l++) { //update momentary switches
						if (buttonRowWrite == l) {
							if (data2 == MIDI_MOMENTARY_OFF_OS) {
								document.getElementById("checkbox" + l).checked = false;
							}
							if (data2 == MIDI_MOMENTARY_ON_OS) {
								document.getElementById("checkbox" + l).checked = true;
							}

						}
					}

				} else if (data1 == MIDI_SLOT_03) {
					document.getElementById("senseDistance").value = 0 - data2;
					
				} //set sensedistance  
				else if (data1 == MIDI_SLOT_17) {
					document.getElementById("depth").value = data2 + 1;
					var output = document.getElementById("demo14");
					depth.dispatchEvent(new Event('input'));
					output.innerHTML = data2 + 1;
				} //set vibrato depth  
				else if (data1 == MIDI_SLOT_04) {
					jumpFactorWrite = data2;
				} // so we know which pressure setting is going to be received.
				else if (data1 == MIDI_SLOT_05 && jumpFactorWrite < 13) {	
					document.getElementById("jumpFactor" + jumpFactorWrite).value = data2;
					if (jumpFactorWrite == 10) {
						document.getElementById("jumpFactor10b").value = data2; //special case for hysteresis			
					}
					for (var i = 1; i < 13; i++) {
						var k = document.getElementById("jumpFactor" + (i));		
						k.dispatchEvent(new Event('input'));
						if (i == 10) {
							var k = document.getElementById("jumpFactor10b"); //special case for key delay slider
							k.dispatchEvent(new Event('input'));
						}
					}
				}

				if (data1 == MIDI_SLOT_05) {

					if (jumpFactorWrite == 13) {
						document.getElementById("checkbox6").checked = data2;
					} else if (jumpFactorWrite == 14) {
						document.getElementById("expressionDepth").value = data2;
					} else if (jumpFactorWrite == 15) {
						document.getElementById("checkbox7").checked = data2;
						updateCustom();
					} else if (jumpFactorWrite == 16) {
						curve[0] = data2;
					} else if (jumpFactorWrite == 17) {
						document.getElementById("pressureChannel").value = data2;
					} else if (jumpFactorWrite == 18) {
						document.getElementById("pressureCC").value = data2;
					} else if (jumpFactorWrite == 19) {
						inputSliderMin[0] = data2;
						slider.noUiSlider.set([data2, null]);
					} else if (jumpFactorWrite == 20) {
						inputSliderMax[0] = data2;
						slider.noUiSlider.set([null, data2]);
					} else if (jumpFactorWrite == 21) {
						outputSliderMin[0] = data2;
						slider2.noUiSlider.set([data2, null]);
					} else if (jumpFactorWrite == 22) {
						outputSliderMax[0] = data2;
						slider2.noUiSlider.set([null, data2]);
					} else if (jumpFactorWrite == 23) {
						document.getElementById("dronesOnCommand").value = data2;
					} else if (jumpFactorWrite == 24) {
						document.getElementById("dronesOnChannel").value = data2;
					} else if (jumpFactorWrite == 25) {
						document.getElementById("dronesOnByte2").value = data2;
					} else if (jumpFactorWrite == 26) {
						document.getElementById("dronesOnByte3").value = data2;
					} else if (jumpFactorWrite == 27) {
						document.getElementById("dronesOffCommand").value = data2;
					} else if (jumpFactorWrite == 28) {
						document.getElementById("dronesOffChannel").value = data2;
					} else if (jumpFactorWrite == 29) {
						document.getElementById("dronesOffByte2").value = data2;
					} else if (jumpFactorWrite == 30) {
						document.getElementById("dronesOffByte3").value = data2;
					} else if (jumpFactorWrite == 31 && data2 == 0) {
						document.getElementById("dronesRadio0").checked = true;
					} else if (jumpFactorWrite == 31 && data2 == 1) {
						document.getElementById("dronesRadio1").checked = true;
					} else if (jumpFactorWrite == 31 && data2 == 2) {
						document.getElementById("dronesRadio2").checked = true;
					} else if (jumpFactorWrite == 31 && data2 == 3) {
						document.getElementById("dronesRadio3").checked = true;
					} else if (jumpFactorWrite == 32) {
						lsb = data2;
					} else if (jumpFactorWrite == 33) {
						var x = parseInt((data2 << 7) | lsb); //receive pressure between 100 and 900
						x = (x - 100) * 24 / 900; //convert to inches of water. 100 is the approximate minimum sensor value.
						var p = x.toFixed(1); //round to 1 decimal
						p = Math.min(Math.max(p, 0), 24); //constrain
						document.getElementById("dronesPressureInput").value = p;
					} else if (jumpFactorWrite == 34) {
						lsb = data2;

					} else if (jumpFactorWrite == 35) {
						var x = parseInt((data2 << 7) | lsb); //receive pressure between 100 and 900
						x = (x - 100) * 24 / 900; //convert to inches of water.  100 is the approximate minimum sensor value.
						var p = x.toFixed(1); //round to 1 decimal
						p = Math.min(Math.max(p, 0), 24); //constrain
						document.getElementById("octavePressureInput").value = p;
					} else if (jumpFactorWrite == 43) {
						document.getElementById("checkbox9").checked = data2;
					} //invert											
					else if (jumpFactorWrite == 44) {
						document.getElementById("checkbox5").checked = data2; //custom
						updateCustom();
					} else if (jumpFactorWrite == 42) {
						document.getElementById("checkbox3").checked = data2;
					} //secret										
					else if (jumpFactorWrite == 40) {
						updateSelected();
						document.getElementById("checkbox4").checked = data2;
						if (data2 == 0) {
							document.getElementById("bagBreath0").checked = true;
						} else {document.getElementById("bagBreath1").checked = true;}
					} //vented							 			
					else if (jumpFactorWrite == 41) {
						document.getElementById("checkbox8").checked = data2;
					} //bagless						 	
					else if (jumpFactorWrite == 45) {
						document.getElementById("checkbox10").checked = data2;
					} //velocity	
					else if (jumpFactorWrite == 46) {						
						document.getElementById("checkbox11").checked = (data2 & 0x1);
						document.getElementById("checkbox13").checked = (data2 & 0x2);
					} //aftertouch	
					else if (jumpFactorWrite == 47) {
						document.getElementById("checkbox12").checked = data2;
					} //force max velocity
					
					else if (jumpFactorWrite == 48) {
						document.getElementById("checkbox14").checked = data2;
					} //immediate pitchbend
					
					else if (jumpFactorWrite == 49) {
						document.getElementById("checkbox15").checked = data2;
					} //legato
	
					else if (jumpFactorWrite == 50) {
						document.getElementById("checkbox16").checked = data2;
					} //override expression pressure range
					
					else if (jumpFactorWrite == 51) {
						document.getElementById("checkbox17").checked = data2;
					} //both thumb and overblow
					
					else if (jumpFactorWrite == 52) {
						document.getElementById("checkbox18").checked = data2;
						updateCustom();
					} //R4 flattens
					
					else if (jumpFactorWrite == 53) {
						document.getElementById("checkbox19").checked = data2;
						updateCustom();
					} //R4 Invert
						
					else if (jumpFactorWrite == 61) {
						document.getElementById("midiBendRange").value = data2;
					}
					else if (jumpFactorWrite == 62) {
						document.getElementById("noteChannel").value = data2;
					}
					else if (jumpFactorWrite == 70) {
						inputSliderMin[1] = data2;
						slider.noUiSlider.set([data2, null]);
					}
					else if (jumpFactorWrite == 71) {
						inputSliderMax[1] = data2;
						slider.noUiSlider.set([null, data2]);
					}
					else if (jumpFactorWrite == 72) {
						outputSliderMin[1] = data2;
						slider2.noUiSlider.set([data2, null]);
					}
					else if (jumpFactorWrite == 73) {
						outputSliderMax[1] = data2;
						slider2.noUiSlider.set([null, data2]);
					}
					else if (jumpFactorWrite == 74) {
						inputSliderMin[2] = data2;
						slider.noUiSlider.set([data2, null]);
					}
					else if (jumpFactorWrite == 75) {
						inputSliderMax[2] = data2;
						slider.noUiSlider.set([null, data2]);
					}
					else if (jumpFactorWrite == 76) {
						outputSliderMin[2] = data2;
						slider2.noUiSlider.set([data2, null]);
					}
					else if (jumpFactorWrite == 77) {
						outputSliderMax[2] = data2;
						slider2.noUiSlider.set([null, data2]);
					}
					else if (jumpFactorWrite == 78) {
						inputSliderMin[3] = data2;
						slider.noUiSlider.set([data2, null]);
					}
					else if (jumpFactorWrite == 79) {
						inputSliderMax[3] = data2;
						slider.noUiSlider.set([null, data2]);
					}
					else if (jumpFactorWrite == 80) {
						outputSliderMin[3] = data2;
						slider2.noUiSlider.set([data2, null]);
					}
					else if (jumpFactorWrite == 81) {
						outputSliderMax[3] = data2;
						slider2.noUiSlider.set([null, data2]);
					}
					else if (jumpFactorWrite == 85) {
						slider3.noUiSlider.set([data2, null]);
					}
					else if (jumpFactorWrite == 86) {
						slider3.noUiSlider.set([null, data2]);
					}
					else if (jumpFactorWrite == 82) {
						curve[1] = data2;
					}
					else if (jumpFactorWrite == 83) {
						curve[2] = data2;
					}
					else if (jumpFactorWrite == 84) {
						curve[3] = data2;
					}
					
					else if (jumpFactorWrite > 86 && jumpFactorWrite < 98) { //custom fingering chart inputs
						document.getElementById("fingeringInput" + (jumpFactorWrite - 86)).value = data2;								
					}

					//Harmonizer Params
					//Tranposer
					else if (jumpFactorWrite == MIDI_SEND_TRANSPOSE_SHIFT) {
						var value = data2 -12;
						if (value > 48) {
							value = -(127-value+1); 
						}
						document.getElementById("transposeShift").innerHTML = value;
					}
					//Fixed Note
					else if (jumpFactorWrite == MIDI_SEND_HARMONIZER_FIXED_NOTE) {
						fixedNote = data2;
						document.getElementById("fixedNote").innerHTML = (data2 == 0x7F) ? "-" : getNoteName(data2);
					}
					//Interval
					else if (jumpFactorWrite >= MIDI_SEND_HARMONIZER_INTERVAL && jumpFactorWrite < MIDI_SEND_HARMONIZER_TONIC) {
						var voice = jumpFactorWrite - MIDI_SEND_HARMONIZER_INTERVAL;

						harmonizerIntervals[voice] = data2;

						if ((harmonizerIntervals[0] == 0x7F || harmonizerIntervals[0] == 12) &&
							(harmonizerIntervals[1] == 0x7F || harmonizerIntervals[1] == 12) && 
							(harmonizerIntervals[2] == 0x7F || harmonizerIntervals[2] == 12) ) {
							document.getElementById("interval" + voice).innerHTML = "-";	
							document.getElementById("harmonizerLegendTableLabel").style.display = "none";
							document.getElementById("harmonizerLegendTableCurrentDiatonic").style.display = "none";
							document.getElementById("harmonizerLegendTableHarmonizerDiatonic").style.display = "none";
						} else if (harmonizerIntervals[voice] != 0x7F && harmonizerIntervals[voice] != 12) {
							var scaleSelect = document.getElementById("HARMrow0");
							document.getElementById("harmonizerLegendTableLabel").style.display = "block";
							document.getElementById("interval" + voice).innerHTML = scaleSelect.options[data2].text;	
							document.getElementById("harmonizerLegendTableCurrentDiatonic").style.display = "block";
							document.getElementById("harmonizerLegendTableHarmonizerDiatonic").style.display = "block";
						} else {
							document.getElementById("interval" + voice).innerHTML = "-";	
						}

							
					}
					//Scale
					else if (jumpFactorWrite >= MIDI_SEND_HARMONIZER_SCALE && jumpFactorWrite < MIDI_SEND_HARMONIZER_BASE_NOTE) {
						harmonizerScale[(jumpFactorWrite - MIDI_SEND_HARMONIZER_SCALE)] = data2;
					}
					//Scale tonic
					else if (jumpFactorWrite >= MIDI_SEND_HARMONIZER_TONIC && jumpFactorWrite < MIDI_SEND_HARMONIZER_SCALE) {
						var voice = jumpFactorWrite - MIDI_SEND_HARMONIZER_TONIC;

						if ((data2 == 0x7F)) {
							document.getElementById("scale" + voice).innerHTML = "-";
							document.getElementById("harmonizerLegendTableCurrentChromatic").style.display = "none";
							document.getElementById("harmonizerLegendTableHarmonizerChromatic").style.display = "none";
							
						} else {
							var scaleSelect = document.getElementById("HarmScaleRow0");
							document.getElementById("scale" + voice).innerHTML = getNoteName(data2, false) + " " + scaleSelect.options[harmonizerScale[voice]].text;	
							document.getElementById("harmonizerLegendTableCurrentChromatic").style.display = "block";
							document.getElementById("harmonizerLegendTableHarmonizerChromatic").style.display = "block";
						}
							
					}
					//Base note
					else if (jumpFactorWrite >= MIDI_SEND_HARMONIZER_BASE_NOTE && jumpFactorWrite < MIDI_SEND_HARMONIZER_BASE_NOTE_DIATONIC) {
						currentNote = data2;
						document.getElementById("currentNoteLabel").innerHTML = data2 == 0 ? "-" : getNoteName(currentNote);
					} 
					//Base note is diatonic
					else if (jumpFactorWrite >= MIDI_SEND_HARMONIZER_BASE_NOTE_DIATONIC && jumpFactorWrite < MIDI_SEND_HARMONIZER_CURRENT_NOTE) {
						setPianoKeyColor(currentNote, data2 == 0 ?  '#e51c23' : '#60f775');

					} 
					//HArmonizer current note
					else if (jumpFactorWrite >= MIDI_SEND_HARMONIZER_CURRENT_NOTE && jumpFactorWrite < MIDI_SEND_HARMONIZER_CURRENT_NOTE_DIATONIC) {
						harmonizerCurrentNotes[(jumpFactorWrite - MIDI_SEND_HARMONIZER_CURRENT_NOTE)] = data2;
					} 
					//HArmonizer current note is diatonic
					else if (jumpFactorWrite >= MIDI_SEND_HARMONIZER_CURRENT_NOTE_DIATONIC && jumpFactorWrite < MIDI_SEND_HARMONIZER_CURRENT_NOTE_DIATONIC +3) {
						setPianoKeyColor(harmonizerCurrentNotes[(jumpFactorWrite - MIDI_SEND_HARMONIZER_CURRENT_NOTE_DIATONIC)] , data2 == 0 ?  '#fed330' : '#d1cafa');

					} 

					//HAlf Hole Detection Feedback
					//Current Buffer size
					else if (jumpFactorWrite == MIDI_SEND_HALFHOLE_BUFFER ) {
						document.getElementById("bufferSizeHH").value = data2;
						document.getElementById("bufferSizeValueHH").innerHTML = data2;
					} 
					//Current hole monitored
					else if (jumpFactorWrite == MIDI_SEND_HALFHOLE_CURRENT ) {
						document.getElementById("halfHoleSelect").value = data2;
					} 
				} 
				else if (data1 == MIDI_SLOT_13) {
  					intValueWrite = data2;
				} // so we know which int Value is going to be received.
				
				else if (data1 == MIDI_SLOT_14) {
					intValueWriteH = data2;
				} 
				else if (data1 == MIDI_SLOT_15) {
					var value = parseInt((intValueWriteH << 7) | data2) -8192;

					//current holeCovered
					if (intValueWrite == MIDI_SEND_HOLE_COVERED) {
						// var tmp_holeCovered = (( data2 << 7) | (data1 & 0x7F)); 
						// var tmp_halfHoles = (data2 & 0b11111100) >> 2;
						var tmp_holeCovered = value; 
						var tmp_halfHoles = (intValueWriteH & 0b11111100) >> 2;

						// console.log("PB: " + tmp_holeCovered);

						if (customFingeringReceivingStatus)  { //We received all the info, add them to the array
							if (customFingeringMidiNote >= 0) {
								let fingering  = {
									midi_note: customFingeringMidiNote, 
									holeCovered: tmp_holeCovered
								}
								customFingering.push(fingering);
								customFingeringMidiNote = -1;
							}

						} else   {
			
							//Updates Perfomance Monitor
							//Manages Half Holes

							var halfHoleCurrent = document.getElementById("halfHoleSelect").value;
							if (halfHoleCurrent == 8) {
								halfHoleCurrent = 0;
							}
							if (bit_test(tmp_halfHoles, halfHoleCurrent) == 1) { //Half hole detection
								document.getElementById("fingeringDotHH").style.display = "none";
								document.getElementById("fingeringDotHalfAHH").style.display = "block";
								document.getElementById("fingeringDotHalfBHH").style.display = "block";
							} else {
								document.getElementById("fingeringDotHH").style.display = "block";
								document.getElementById("fingeringDotHalfAHH").style.display = "none";
								document.getElementById("fingeringDotHalfBHH").style.display = "none";		
							}


							if (bit_test(tmp_halfHoles, 0) == 1) { //Thumb hole
								document.getElementById("fingeringDotMon8").style.display = "none";
								document.getElementById("fingeringDotMonHalfA8").style.display = "block";
								document.getElementById("fingeringDotMonHalfB8").style.display = "block";

							} else {
								document.getElementById("fingeringDotMon8").style.display = "block";
								document.getElementById("fingeringDotMonHalfA8").style.display = "none";
								document.getElementById("fingeringDotMonHalfB8").style.display = "none";
							}

							if (bit_test(tmp_halfHoles, 1) == 1) { //R4
								document.getElementById("fingeringDotMon1").style.display = "none";
								document.getElementById("fingeringDotMonHalfA1").style.display = "block";
								document.getElementById("fingeringDotMonHalfB1").style.display = "block";

							} else {
								document.getElementById("fingeringDotMon1").style.display = "block";
								document.getElementById("fingeringDotMonHalfA1").style.display = "none";
								document.getElementById("fingeringDotMonHalfB1").style.display = "none";
							}

							if (bit_test(tmp_halfHoles, 2) == 1) { //R3
								document.getElementById("fingeringDotMon2").style.display = "none";
								document.getElementById("fingeringDotMonHalfA2").style.display = "block";
								document.getElementById("fingeringDotMonHalfB2").style.display = "block";

							} else {
								document.getElementById("fingeringDotMon2").style.display = "block";
								document.getElementById("fingeringDotMonHalfA2").style.display = "none";
								document.getElementById("fingeringDotMonHalfB2").style.display = "none";
							}

							if (customFingeringLearningON) { //dots in custom fingering
								holeCovered = tmp_holeCovered;
								halfHoles = tmp_halfHoles;

								//Manages Half Holes
								if (bit_test(halfHoles, 0) == 1) { //Thumb hole
									document.getElementById("fingeringDot8").style.display = "none";
									document.getElementById("fingeringDotHalfA8").style.display = "block";
									document.getElementById("fingeringDotHalfB8").style.display = "block";

								} else {
									document.getElementById("fingeringDot8").style.display = "block";
									document.getElementById("fingeringDotHalfA8").style.display = "none";
									document.getElementById("fingeringDotHalfB8").style.display = "none";
								}

								if (bit_test(halfHoles, 1) == 1) { //R4
									document.getElementById("fingeringDot1").style.display = "none";
									document.getElementById("fingeringDotHalfA1").style.display = "block";
									document.getElementById("fingeringDotHalfB1").style.display = "block";

								} else {
									document.getElementById("fingeringDot1").style.display = "block";
									document.getElementById("fingeringDotHalfA1").style.display = "none";
									document.getElementById("fingeringDotHalfB1").style.display = "none";
								}

								if (bit_test(halfHoles, 2) == 1) { //R3
									document.getElementById("fingeringDot2").style.display = "none";
									document.getElementById("fingeringDotHalfA2").style.display = "block";
									document.getElementById("fingeringDotHalfB2").style.display = "block";

								} else {
									document.getElementById("fingeringDot2").style.display = "block";
									document.getElementById("fingeringDotHalfA2").style.display = "none";
									document.getElementById("fingeringDotHalfB2").style.display = "none";
								}
							}
							//Manages the rest of the holes
							for (var m = 0; m < 9; m++) {
								if (bit_test(tmp_holeCovered, m) == 1) {
									document.getElementById("dot" + m).style.backgroundColor = "blue";

									if (m == document.getElementById("halfHoleSelect").value) {
										document.getElementById("fingeringDotHH").style.fill = "#262626";
									}

									if (m > 0 ) {
										document.getElementById("fingeringDotMon" + m).style.fill = "#262626";
									}
									if (m > 0 && customFingeringLearningON) {
										document.getElementById("fingeringDot" + m).style.fill = "#262626";
									}
									if (m == 0) {
										document.getElementById("dot0").style.opacity = "0.8";
									}
								} else {
									document.getElementById("dot" + m).style.backgroundColor = "#333";
									if (m == document.getElementById("halfHoleSelect").value) {
										document.getElementById("fingeringDotHH").style.fill = "#C3C0C0";
									}
									if (m > 0 ) {
										document.getElementById("fingeringDotMon" + m).style.fill = "#C3C0C0";
									}
									if (m > 0 && customFingeringLearningON) {
										document.getElementById("fingeringDot" + m).style.fill = "#C3C0C0";
									}
									if (m == 0) {
										document.getElementById("dot0").style.opacity = "0";
									}
								}
							}
						}
					} else 
					
					//Current keySelect / noteShiftSelector
					if (intValueWrite == MIDI_SEND_KEY_SELECT) {
						document.getElementById("keySelect" + currentPreset).value = value;
					}
					
					//Current fingering schema
					if (intValueWrite >= MIDI_SEND_MODE_SELECTOR && intValueWrite <= MIDI_SEND_MODE_SELECTOR+2) {
						var presetSelected = intValueWrite - MIDI_SEND_MODE_SELECTOR;
						document.getElementById("fingeringSelect" + presetSelected).value = value;
						updateCells();
					}

					//current read value for hole sensors
					if (intValueWrite >= MIDI_SEND_TONE_READ_0 && intValueWrite <= MIDI_SEND_TONE_READ_8) {
						// current half hole calibration selected hole
						if ( (intValueWrite - MIDI_SEND_TONE_READ_0) == document.getElementById("halfHoleSelect").value) {
							document.getElementById("currentReadRangeHH").value = value;
							document.getElementById("currentReadValueHH").innerHTML =  value;
						}
					} else

					//current hole calibration baseline
					if (intValueWrite >= MIDI_SEND_TONE_BASELINE_0 && intValueWrite <= MIDI_SEND_TONE_BASELINE_8) {
						// current half hole calibration selected hole
						if ( (intValueWrite - MIDI_SEND_TONE_BASELINE_0) == document.getElementById("halfHoleSelect").value) {
								document.getElementById("currentCalibrationBaselineHH").innerHTML = value;
							} 
						//console.log("toneholeBaseline[" + (intValueWrite - MIDI_SEND_TONE_BASELINE_0) + "]: " +value);
					} else		


					// calibration baseline average
					if (intValueWrite == MIDI_SEND_BASELINE_AVERAGE) {
						console.log("toneholeBaseline Average: " +value, intValueWrite);
					} else		
	
					// calibration current baseline average
					if (intValueWrite == MIDI_SEND_BASELINE_CURRENT_AVERAGE) {
						console.log("toneholeBaseline CURRENT Average: " +value/10);
					} else	

					// calibration current baseline average
					if (intValueWrite == MIDI_SEND_MAX_BASELINE) {
						console.log("toneholeBaseline MAX: " +value);
					} else	

					//current hole calibration
					if (intValueWrite >= MIDI_SEND_TONE_COVERED_0 && intValueWrite <= MIDI_SEND_TONE_COVERED_8) {
						// current half hole calibration selected hole
						if ( (intValueWrite - MIDI_SEND_TONE_COVERED_0) == document.getElementById("halfHoleSelect").value) {
							 document.getElementById("currentCalibrationOpenHH").innerHTML = value -54;
							 document.getElementById("currentCalibrationClosedHH").innerHTML = value -50;
							}
						//console.log("toneholeCovered[" + (intValueWrite - MIDI_SEND_TONE_COVERED_0) + "]: " +value);

					} else		

					//current lowerBound for hole sensors
					if (intValueWrite == MIDI_SEND_HALFHOLE_MIN) {
						document.getElementById("lowerBoundRangeHH").value = value;
						fillSliderAuto();
					} else
					//current upperBound for hole sensors
					if (intValueWrite == MIDI_SEND_HALFHOLE_MAX) {
						//console.log("upperBound: "+ value);	
						if (value >= 1024) {
							document.getElementById("halfHoleParamsDiv").style.display = 'none';
							document.getElementById("customfingeringDotsHH").style.display = 'none';
							document.getElementById("halfHoleToggleButton").innerHTML = 'Switch on';
						} else {
							document.getElementById("halfHoleParamsDiv").style.display = 'block';
							document.getElementById("customfingeringDotsHH").style.display = 'block';
							document.getElementById("halfHoleToggleButton").innerHTML = 'Switch off';

						}

						document.getElementById("upperBoundRangeHH").value = value;
						fillSliderAuto();

					} 
				} 

				else if (data1 == MIDI_SW_VERSION) { //receiving firmware version from WARBL

					//20231010 GLB Detects a custom build
					if (version != "Unknown" && data2 > 0 && data2 < 10 && data2 != version) { //Only the eventual second message from WARBL
						switch (data2) {
							case 1: //Barbaro
								return;
							default:
								window.location.href = "../../configure.html";
							break;
						}
					}

					version = data2;
					
					if (version == currentVersion) { //display the appropriate messages
						document.getElementById("current").innerHTML = "Your firmware is up to date.";
						document.getElementById("current").style.left = "710px";
						document.getElementById("current").style.visibility = "visible";
						document.getElementById("status").style.visibility = "hidden";
						document.getElementById("current").style.color = "#f7c839";
					}
					else {
						document.getElementById("current").innerHTML = "There is a firmware update available.";				
						document.getElementById("current").style.left = "690px";
						document.getElementById("current").style.visibility = "visible";
						document.getElementById("status").style.visibility = "hidden";
						document.getElementById("current").style.color = "#F78339";
					}
					
					
					version = version / 10;
					var n = version.toFixed(1)
					document.getElementById("version").innerHTML = n ;
					document.getElementById("version").style.color = "#f7c839";
					
					
					//show that the WARBL is connected when we receive the firmware version.
					document.getElementById("status").innerHTML = "WARBL Connected.";
					document.getElementById("status").style.color = "#f7c839";
					communicationMode = true;

					if(version > 2.0){
						document.getElementById("connect").innerHTML = "Disconnect";
					}
					
					
					//Lots of UI changes based on the current firmware version of the connected WARBL
					if (version > 2.1){ //add new items that should only be visible with newer software versions
				
						//add medieval pipes and bansuri fingering for custom version
						for (i = 0; i < document.getElementById("fingeringSelect0").length; ++i){
							if (document.getElementById("fingeringSelect0").options[i].value == "23"){
								 var a = 1;    
							}
						}
		
						  if (a != 1){
							var x = document.getElementById("fingeringSelect0"); 		
							  var option = document.createElement("option");
							  option.text = "Medieval bagpipes";
							  option.value = 22;
							  x.add(option);
				
							var y = document.getElementById("fingeringSelect1");
							var option = document.createElement("option");
							  option.text = "Medieval bagpipes";
							  option.value = 22;
							y.add(option);
				
							var z = document.getElementById("fingeringSelect2");
							var option = document.createElement("option");
							  option.text = "Medieval bagpipes";
							  option.value = 22;
							z.add(option);
							
							var x = document.getElementById("fingeringSelect0"); 		
							  var option = document.createElement("option");
							  option.text = "Barbaro's EWI";
							  option.value = 23;
							  x.add(option);
				
							var y = document.getElementById("fingeringSelect1");
							var option = document.createElement("option");
							  option.text = "Barbaro's EWI";
							  option.value = 23;
							y.add(option);
				
							var z = document.getElementById("fingeringSelect2");
							var option = document.createElement("option");
							  option.text = "Barbaro's EWI";
							  option.value = 23;
							z.add(option);
							
							var x = document.getElementById("fingeringSelect0"); 		
							  var option = document.createElement("option");
							  option.text = "Bansuri";
							  option.value = 9;
							  x.add(option);
				
							var y = document.getElementById("fingeringSelect1");
							var option = document.createElement("option");
							  option.text = "Bansuri";
							  option.value = 9;
							y.add(option);
				
							var z = document.getElementById("fingeringSelect2");
							var option = document.createElement("option");
							  option.text = "Bansuri";
							  option.value = 9;
							z.add(option);
		
							}
						}

						if (version < 2.1) {
						document.getElementById("jumpfactor10Container").style.visibility = "visible";
						document.getElementById("jumpfactor4Container").style.visibility = "visible";
						document.getElementById("jumpValue4").style.visibility = "visible";
						document.getElementById("jumpValue10").style.visibility = "visible";				
						document.getElementById("jumpfactor10bContainer").style.visibility = "hidden";
						document.getElementById("jumpLabel8").style.visibility = "hidden";
						document.getElementById("jumpLabel5").style.visibility = "visible";									
						document.getElementById("demo10b").style.visibility = "hidden";				
						document.getElementById("jumpLabel4").innerHTML = "Jump";
						document.getElementById("jumpfactor5Container").style.top = "240px";											
						document.getElementById("jumpfactor6Container").style.top = "275px";						
						document.getElementById("jumpfactor11Container").style.top = "240px";											
						document.getElementById("jumpfactor12Container").style.top = "275px";														
						document.getElementById("jumplabel6").style.top = "242px";						
						document.getElementById("jumplabel7").style.top = "277px";												
						document.getElementById("jumpValue5").style.top = "225px";						
						document.getElementById("jumpValue6").style.top = "260px";												
						document.getElementById("jumpValue11").style.top = "225px";						
						document.getElementById("jumpValue12").style.top = "260px";
						document.getElementById("jumpFactor3").min = "1";										
						document.getElementById("jumpFactor3").max = "175";		
						document.getElementById("jumpFactor9").min = "1";										
						document.getElementById("jumpFactor9").max = "175";	
						document.getElementById("jumpFactor5").min = "1";											
						document.getElementById("jumpFactor6").min = "1";											
						document.getElementById("jumpFactor11").min = "1";												
						document.getElementById("jumpFactor12").min = "1";										
						document.getElementById("breathSlider").classList.remove('slider2');
						document.getElementById("breathSlider").classList.add('slider');
						document.getElementById("pressureGroup").style.top = "0px";
						document.getElementById("ventedLabel").style.visibility = "visible";
						document.getElementById("switch4").style.visibility = "visible";
						document.getElementById("radioGroup10").style.visibility = "hidden";
						document.getElementById("jumplabel10").innerHTML = "Closed";
						document.getElementById("jumplabel11").innerHTML = "Vented";
						document.getElementById("jumplabel10").style.left = "170px";
						document.getElementById("jumplabel11").style.left = "340px";
						document.getElementById("advancedSliders").style.top = "-125px";
						document.getElementById("selectedSettings").style.visibility = "hidden";
							

											
						
						//disable bombarde and baroque flute fingering option
						document.getElementById("fingeringSelect0").options[19].disabled = true;
						document.getElementById("fingeringSelect1").options[19].disabled = true;
						document.getElementById("fingeringSelect2").options[19].disabled = true;
						document.getElementById("fingeringSelect0").options[20].disabled = true;
						document.getElementById("fingeringSelect1").options[20].disabled = true;
						document.getElementById("fingeringSelect2").options[20].disabled = true;
																																
					}
					
					

					if (version < 2.0) {
						document.getElementById("overrideExpression").disabled = true;
						document.getElementById("polyMapButton").disabled = true;
						document.getElementById("velocityMapButton").disabled = true;
						document.getElementById("aftertouchMapButton").disabled = true;
						document.getElementById("noteChannel").disabled = true;
						document.getElementById("checkbox13").disabled = true;
						document.getElementById("switch13").style.cursor = "default";
						document.getElementById("advancedPBbutton").disabled = true;
						document.getElementById("pitchbendradio3").disabled = true;
						document.getElementById("configureCustomFingering").disabled = true;
					}
					
					

					if (version < 1.5) {
						document.getElementById("fingeringSelect0").options[2].disabled = true;
						document.getElementById("fingeringSelect1").options[2].disabled = true;
						document.getElementById("fingeringSelect2").options[2].disabled = true;
						document.getElementById("checkbox10").disabled = true;
						for (var i = 0; i < 8; i++) {
							document.getElementById("row" + i).options[7].disabled = true;
							document.getElementById("row" + i).options[8].disabled = true;
						}
					}

					if (version < 1.6) {
						for (var i = 0; i < 8; i++) {
							document.getElementById("row" + i).options[12].disabled = true;
						}
						document.getElementById("fingeringSelect0").options[6].disabled = true;
						document.getElementById("fingeringSelect1").options[6].disabled = true;
						document.getElementById("fingeringSelect2").options[6].disabled = true;
						document.getElementById("fingeringSelect0").options[11].disabled = true;
						document.getElementById("fingeringSelect1").options[11].disabled = true;
						document.getElementById("fingeringSelect2").options[11].disabled = true;
					}


					if (version < 1.7) {
						document.getElementById("checkbox11").disabled = true;
						document.getElementById("checkbox12").disabled = true;

						document.getElementById("fingeringSelect0").options[12].disabled = true;
						document.getElementById("fingeringSelect1").options[12].disabled = true;
						document.getElementById("fingeringSelect2").options[12].disabled = true;

						document.getElementById("fingeringSelect0").options[13].disabled = true;
						document.getElementById("fingeringSelect1").options[13].disabled = true;
						document.getElementById("fingeringSelect2").options[13].disabled = true;

						document.getElementById("fingeringSelect0").options[14].disabled = true;
						document.getElementById("fingeringSelect1").options[14].disabled = true;
						document.getElementById("fingeringSelect2").options[14].disabled = true;

						document.getElementById("fingeringSelect0").options[15].disabled = true;
						document.getElementById("fingeringSelect1").options[15].disabled = true;
						document.getElementById("fingeringSelect2").options[15].disabled = true;
					}
					
					
					if (version < 2.0) {
						document.getElementById("fingeringSelect0").options[16].disabled = true;
						document.getElementById("fingeringSelect1").options[16].disabled = true;
						document.getElementById("fingeringSelect2").options[16].disabled = true;
												
						document.getElementById("fingeringSelect0").options[17].disabled = true;
						document.getElementById("fingeringSelect1").options[17].disabled = true;
						document.getElementById("fingeringSelect2").options[17].disabled = true;
						
						document.getElementById("fingeringSelect0").options[18].disabled = true;
						document.getElementById("fingeringSelect1").options[18].disabled = true;
						document.getElementById("fingeringSelect2").options[18].disabled = true;
					}
					
				
					

				} if (data1 == MIDI_SW_BUILD_VERSION) { //receiving build firmware version from WARBL
					build_version = data2;

					switch (build_version) {
						case 0: //Original

						break;
						case 1: //Barbaro
							document.getElementById("version").innerHTML += "/BARBARO" ;
							
						break;
					}

					if (build_version != 1 || version < 2.3) {
						console.log("build_version", version, build_version);
						alert("This configuration tool is for special Barbaro WARBL Firmware only.\nPlease use the official configuration tool;");
						connect();
					} 

				} else if (data1 == MIDI_SLOT_17+1) {
					var x = parseInt((data2 << 7) | lsb); //receive pressure between 100 and 900
					x = (x - 100) * 24 / 900; //convert to inches of water.  105 is the approximate minimum sensor value.
					p = Math.min(Math.max(p, 0), 24); //constrain
					var p = x.toFixed(1); //round to 1 decimal
					if (p < 0.2) {
						p = 0
					};

					// Are we graphing pressure values?
					if (gPressureGraphEnabled){
						capturePressure(p);
					}
					else{
						document.getElementById("pressure").innerHTML = (p);
						document.getElementById("pressure1").innerHTML = (p);
					}
				}

				for (var i = 0; i < 8; i++) {
					if (buttonRowWrite == i) {
						//20230927 GLB
						var a = document.getElementById("row" + i).value;

						if (a == 5 || a == 30 || a == 10 || a == 11 || a == 12) { //Transpose/Harmonize
							if (data1 == MIDI_SLOT_07) {
								document.getElementById("HARMrow" + i).value = data2;
							} 
							if (data1 == MIDI_SLOT_08) {
								document.getElementById("HarmScaleRow" + i).value = data2;
							} 
							
							if (a == 5 && data1 == MIDI_SLOT_06) { //Channel / Progressivo or not
								if (data2 != 1) {
									document.getElementById("row" + (buttonRowWrite)).value = 30;
								}
							}
						
						} else {
							if (data1 == MIDI_SLOT_06 && data2 < 16) {
								document.getElementById("channel" + (buttonRowWrite)).value = data2;
							}
							if (data1 == MIDI_SLOT_07) {
								document.getElementById("byte2_" + (buttonRowWrite)).value = data2;
							}
							if (data1 == MIDI_SLOT_08) {
								document.getElementById("byte3_" + (buttonRowWrite)).value = data2;
							}
						}
						//END GLB
					}
				}

				if (data1 == MIDI_SLOT_06 && data2 > 15) {

					if (data2 >= MIDI_EN_VIBRATO_HOLES_OS && data2 < 29) {
						document.getElementById("vibratoCheckbox" + (data2 - 20)).checked = false;
					}

					if (data2 > 29 && data2 < MIDI_CALIB_OPTION_OS) {
						document.getElementById("vibratoCheckbox" + (data2 - 30)).checked = true;
					}

					if (data2 == MIDI_CALIB_OPTION_OS) {
						document.getElementById("calibrateradio0").checked = true;
					}
					if (data2 == MIDI_USE_LEARN_PRESS_ON) {
						document.getElementById("calibrateradio1").checked = true;
					}

					if (data2 == 53) { //add an option for the uilleann regulators fingering pattern if a message is received indicating that it is supported.

						for (i = 0; i < document.getElementById("fingeringSelect0").length; ++i) {
							if (document.getElementById("fingeringSelect0").options[i].value == "9") {
								var a = 1;
							}
						}

						if (a != 1) {
							var x = document.getElementById("fingeringSelect0");
							var option = document.createElement("option");
							option.text = "Uilleann regulators";
							option.value = 9;
							x.add(option);

							var y = document.getElementById("fingeringSelect1");
							var option = document.createElement("option");
							option.text = "Uilleann regulators";
							option.value = 9;
							y.add(option);

							var z = document.getElementById("fingeringSelect2");
							var option = document.createElement("option");
							option.text = "Uilleann regulators";
							option.value = 9;
							z.add(option);

						}
					}


				}

			}
	}

	updateCells(); //keep enabled/disabled cells updated.

}



function bit_test(num, bit) {
	return ((num >> bit) % 2 != 0)
}

//Sends an int value
function sendIntToWARBL(index, value) {
	// if (index == MIDI_SEND_KEY_SELECT) {
	// 	console.log("sendIntToWARBL", value);
	// }
	value += 8192;
	console.log("sendIntToWARBL", index, (value >> 7) & 0x7F, value & 0x7F);
	sendToWARBL(MIDI_SLOT_13, index);
	sendToWARBL(MIDI_SLOT_14, (value >> 7) & 0x7F);
	sendToWARBL(MIDI_SLOT_15, value & 0x7F);
}


function sendCustomFingeringFill(){
	
	modalclose(22);	
	var value = document.getElementById("customFingeringFill").value;
	for (i = 1; i < 12; ++i) {
		document.getElementById("fingeringInput" + i).value = customFingeringFills[value][i - 1];
		fingeringInput(i, customFingeringFills[value][i - 1]);
	}
}


function sendFingeringSelect(row, selection) {
	selection = parseFloat(selection);
	updateCells();
	updateCustom();
	blink(1);
	//default keys
	var key;
	if (selection == 2) {
		key = 8;
	} //GHB
	else if (selection == 3) {
		key = 3;
	} //Northumbrian
	else if (selection == 5 || selection == 13) {
		key = 125;
	} //Gaita
	else if (selection == 6) {
		key = 122;
	} //NAF
	else if (selection == 8) {
		key = 125;
	} //Recorder
	else if (selection == 11) {
		key = 113;
	} //Xiao
	else if (selection == 12 || selection == 14 || selection == 15) {
		key = 123;
	} //Sax
	else if (selection == 17 || selection == 18) {
		key = 2;
	} //Sackpipa
		else if (selection == 20) {
		key = 123;
	} //Bombarde
	else {
		key = 0;
	} //default key of D for many patterns
	document.getElementById("keySelect" + row).value = key; //set key menu

	//console.log("sendFingeringSelect",row, selection, key);
	//send the fingering pattern
	sendIntToWARBL(MIDI_SEND_MODE_SELECTOR + row, selection);
	// sendToWARBL(MIDI_SLOT_02, MIDI_SEND_FINGER_PATTERN_OS + row);
	// sendToWARBL(MIDI_SLOT_02, MIDI_SEND_MODE_SELECTOR_OS + selection);

	sendKey(row, key);
}

function customFingeringInput() {

	var x = document.getElementById("customFingeringInput").value;

	if (x < 0 || x > 127 || isNaN(x)) {
		alert("Value must be 0-127.");
		document.getElementById("customFingeringInput").value = null;
		// document.getElementById("customFingeringInputNote" ).innerHTML = "";

	}		
	else {
		// document.getElementById("customFingeringInputNote" ).innerHTML = getNoteName(x);
	}

	
	document.getElementById("customFingeringInputNoteLabel" ).innerHTML = getNoteName(x);
	document.getElementById("defaultMidiNote" ).innerHTML = defaultMidiNote + " (" + getNoteName(defaultMidiNote) + ")";
	document.getElementById("overrideMidiNote" ).innerHTML = overrideMidiNote < 0x7f ? overrideMidiNote + " (" + getNoteName(overrideMidiNote) + ")" : "-";


}

function fingeringInput(input, selection) { 	//send the custom fingering input entry

		var x = document.getElementById("fingeringInput" + input).value;
		if (x < 0 || x > 127 || isNaN(x)) {
			alert("Value must be 0-127.");
			document.getElementById("fingeringInput" + input).value = null;
		}		
		else{
	blink(1);
	document.getElementById("customFingeringFill").value = "12";
	sendToWARBL(MIDI_SLOT_04, 86 + input);
	sendToWARBL(MIDI_SLOT_05, selection);
		}
}


function defaultInstrument() { //tell WARBL to set the current instrument as the default

	defaultPreset = currentPreset;
	handleDefault();
	sendToWARBL(MIDI_SLOT_02, MIDI_DEFAULT_INSTR_OS);

}

function handleDefault() { //display correct default instrument and "set default" buttons	

	if (version > 1.6 || version == "Unknown") {

		if (defaultPreset != 0) {
			document.getElementById("instrument1Label").innerHTML = "Preset 1:";
		}
		if (defaultPreset != 1) {
			document.getElementById("instrument2Label").innerHTML = "Preset 2:";
		}
		if (defaultPreset != 2) {
			document.getElementById("instrument3Label").innerHTML = "Preset 3:";
		}

		if (defaultPreset == 0) {
			document.getElementById("instrument1Label").innerHTML = "Preset 1 (default):";
		}
		if (defaultPreset == 1) {
			document.getElementById("instrument2Label").innerHTML = "Preset 2 (default):";
		}
		if (defaultPreset == 2) {
			document.getElementById("instrument3Label").innerHTML = "Preset 3 (default):";
		}

		if (defaultPreset != currentPreset) {
			document.getElementById("defaultInstrument").style.visibility = "visible";

			if (currentPreset == 0) {
				document.getElementById("defaultInstrument").style.left = "130px";
			}
			if (currentPreset == 1) {
				document.getElementById("defaultInstrument").style.left = "430px";
			}
			if (currentPreset == 2) {
				document.getElementById("defaultInstrument").style.left = "730px";
			}
		} else {
			document.getElementById("defaultInstrument").style.visibility = "hidden";

		}
	}
}

function sendKey(row, selection) {
	selection = parseFloat(selection);
	// row = parseFloat(row);
	updateCells();
	blink(1);
	// sendToWARBL(MIDI_SLOT_12 + row, selection);
	sendIntToWARBL(MIDI_SEND_KEY_SELECT, selection);
	// sendToWARBL(MIDI_SLOT_12, selection);
}


function sendFingeringRadio(radioBox) { //change instruments, showing the correct tab for each instrument.

	if (settingsDirty) {
		if (!confirm("Your settings for the current preset have changed but were not saved.\nAll your changes will be lost!\nDo you want to switch Preset anyway?")) {
			radioBox.checked = false;
			document.getElementById("fingering"+currentPreset).checked = true;
			return;
		}
	}

	settingsDirty = false;
	var tab = radioBox.value;
	currentPreset = tab;
	updateCustom();
	advancedOkay(); //turn off the advanced tab
	pressureOkay();	
	handleDefault(); //display correct default instrument and "set default" buttons	
	customFingeringOkay();
	halfHoleDetectionOkay();
	if (tab == 0) {
		document.getElementById("instrument0").style.display = "block";
		document.getElementById("instrument1").style.display = "none";
		document.getElementById("instrument2").style.display = "none";

		document.getElementById("key0").style.display = "block";
		document.getElementById("key1").style.display = "none";
		document.getElementById("key2").style.display = "none";

		var prevDirty = settingsDirty; //This sends a message, but doesn't change settings
		sendToWARBL(MIDI_SLOT_02, MIDI_CURRENT_INSTR_OS);
		settingsDirty = prevDirty; //restore previous state
		
	} else if (tab == 1) {
		document.getElementById("instrument0").style.display = "none";
		document.getElementById("instrument1").style.display = "block";
		document.getElementById("instrument2").style.display = "none";

		document.getElementById("key0").style.display = "none";
		document.getElementById("key1").style.display = "block";
		document.getElementById("key2").style.display = "none";
		blink(2);

		var prevDirty = settingsDirty; //This sends a message, but doesn't change settings
		sendToWARBL(MIDI_SLOT_02, MIDI_CURRENT_INSTR_OS+1);
		settingsDirty = prevDirty; //restore previous state

	} else if (tab == 2) {
		document.getElementById("instrument0").style.display = "none";
		document.getElementById("instrument1").style.display = "none";
		document.getElementById("instrument2").style.display = "block";

		document.getElementById("key0").style.display = "none";
		document.getElementById("key1").style.display = "none";
		document.getElementById("key2").style.display = "block";
		blink(3);
		var prevDirty = settingsDirty; //This sends a message, but doesn't change settings
		sendToWARBL(MIDI_SLOT_02, MIDI_CURRENT_INSTR_OS+2);
		settingsDirty = prevDirty; //restore previous state
	}
	updateCells();
	updateCustom();
}


//move selection box for advanced overblowing settings based on whether bag or breath is selected
function updateSelected() {
	if (document.getElementById("bagBreath0").checked == true) {
		document.getElementById("selectedSettings").style.left = "125px";
		document.getElementById("selectedSettings").style.width = "162px";
	} else {
		document.getElementById("selectedSettings").style.left = "285px";
		document.getElementById("selectedSettings").style.width = "162px";	
	}
}


//HalfHole Detection Settings

function sendHalfHoleBuffer(selection) {
	document.getElementById("bufferSizeValueHH").innerHTML = selection;	
	blink(1);
	selection = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_HALFHOLE_BUFFER);
	sendToWARBL(MIDI_SLOT_05, selection);
}
function sendHalfHoleSelect(selection) {
	blink(1);
	selection = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_HALFHOLE_CURRENT);
	sendToWARBL(MIDI_SLOT_05, selection);
}

// function sendHalfHoleLowerBound (selection) {
// 	blink(1);
// 	selection = parseFloat(selection);
// 	sendIntToWARBL(MIDI_SEND_HALFHOLE_MIN, selection);
// }

function sendHalfHoleUpperBound (selection) {
	blink(1);
	selection = parseFloat(selection);
	console.log("sendHalfHoleUpperBound: " + selection);
	sendIntToWARBL(MIDI_SEND_HALFHOLE_MAX, selection);
}

function sendSenseDistance(selection) {
	blink(1);
	selection = parseFloat(selection);
	x = 0 - parseFloat(selection);

	sendToWARBL(MIDI_SLOT_03, x);
}


function sendDepth(selection) {
	blink(1);
	selection = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_17, selection);
}

function sendExpressionDepth(selection) {
	blink(1);
	selection = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_04, 14);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendCurveRadio(selection) {
	blink(1);
	selection = parseFloat(selection);
	curve[mapSelection] = selection;
	if(mapSelection == 0){
	sendToWARBL(MIDI_SLOT_04, 16);
	}
	else{
		sendToWARBL(MIDI_SLOT_04, 81 + mapSelection);
	}
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendPressureChannel(selection) {
	blink(1);
	var x = parseFloat(selection);
	if (x < 1 || x > 16 || isNaN(x)) {
		alert("Value must be 1-16.");
		document.getElementById("pressureChannel").value = null;
	} else {
		sendToWARBL(MIDI_SLOT_04, 17);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendPressureCC(selection) {
	blink(1);
	selection = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_04, 18);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendBendRange(selection) {
	blink(1);
	var x = parseFloat(selection);
	if (x < 1 || x > 96 || isNaN(x)) {
		alert("Value must be 1-96.");
		document.getElementById("midiBendRange").value = null;
	} else {
		sendToWARBL(MIDI_SLOT_04, 61);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendNoteChannel(selection) {
	blink(1);
	var x = parseFloat(selection);
	if (x < 1 || x > 16 || isNaN(x)) {
		alert("Value must be 1-16.");
		document.getElementById("noteChannel").value = null;
	} else {
		sendToWARBL(MIDI_SLOT_04, 62);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}


//pressure input slider
slider.noUiSlider.on('change', function(values) {
	blink(1);
	if(mapSelection == 0){
	inputSliderMin[0] = parseInt(values[0]);
	inputSliderMax[0] = parseInt(values[1]);	
	sendToWARBL(MIDI_SLOT_04, 19);
	sendToWARBL(MIDI_SLOT_05, parseInt(values[0]));
	sendToWARBL(MIDI_SLOT_04, 20);
	sendToWARBL(MIDI_SLOT_05, parseInt(values[1]));
	}
	else {
	inputSliderMin[mapSelection] = parseInt(values[0]);
	inputSliderMax[mapSelection] = parseInt(values[1]);
	sendToWARBL(MIDI_SLOT_04, 70 + ((mapSelection-1)*4));
	sendToWARBL(MIDI_SLOT_05, parseInt(values[0]));
	sendToWARBL(MIDI_SLOT_04, 71 + ((mapSelection-1)*4));
	sendToWARBL(MIDI_SLOT_05, parseInt(values[1]));		
	}
});

//pressure output slider
slider2.noUiSlider.on('change', function(values) {
	blink(1);
	if(mapSelection == 0){
	outputSliderMin[0] = parseInt(values[0]);
	outputSliderMax[0] = parseInt(values[1]);
	sendToWARBL(MIDI_SLOT_04, 21);
	sendToWARBL(MIDI_SLOT_05, parseInt(values[0]));
	sendToWARBL(MIDI_SLOT_04, 22);
	sendToWARBL(MIDI_SLOT_05, parseInt(values[1]));
	}
	else {
	outputSliderMin[mapSelection] = parseInt(values[0]);
	outputSliderMax[mapSelection] = parseInt(values[1]);
	sendToWARBL(MIDI_SLOT_04, 72 + ((mapSelection-1)*4));
	sendToWARBL(MIDI_SLOT_05, parseInt(values[0]));
	sendToWARBL(MIDI_SLOT_04, 73 + ((mapSelection-1)*4));
	sendToWARBL(MIDI_SLOT_05, parseInt(values[1]));		
	}
});

//expression override slider
slider3.noUiSlider.on('change', function(values) {
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 85);
	sendToWARBL(MIDI_SLOT_05, parseInt(values[0]));
	sendToWARBL(MIDI_SLOT_04, 86);
	sendToWARBL(MIDI_SLOT_05, parseInt(values[1]));
});


slider.noUiSlider.on('update', function (values, handle) {
	var marginMin = document.getElementById('slider-value-min'),
    marginMax = document.getElementById('slider-value-max');

    if (handle) {
			var min = parseFloat(values[handle] * 0.24).toFixed(1);
        marginMax.innerHTML = min;
    } else {
			var max = parseFloat(values[handle] * 0.24).toFixed(1);
        marginMin.innerHTML = max;
    }

});

slider2.noUiSlider.on('update', function (values, handle) {
	var marginMin = document.getElementById('slider2-value-min'),
    marginMax = document.getElementById('slider2-value-max');
    if (handle) {
        marginMax.innerHTML = parseInt(values[handle]);
    } else {
        marginMin.innerHTML = parseInt(values[handle]);
    }
});

slider3.noUiSlider.on('update', function (values, handle) {
	var marginMin = document.getElementById('slider3-value-min'),
    marginMax = document.getElementById('slider3-value-max');

    if (handle) {
			var min = parseFloat(values[handle] * 0.24).toFixed(1);
        marginMax.innerHTML = min;
    } else {
			var max = parseFloat(values[handle] * 0.24).toFixed(1);
        marginMin.innerHTML = max;
    }

});


function sendDronesOnCommand(selection) {
	blink(1);
	selection = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_04, 23);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendDronesOnChannel(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 16 || isNaN(x)) {
		alert("Value must be 1-16.");
		document.getElementById("dronesOnChannel").value = null;
	} else {
		blink(1);
		sendToWARBL(MIDI_SLOT_04, 24);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendDronesOnByte2(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 127 || isNaN(x)) {
		alert("Value must be 0 - 127.");
		document.getElementById("dronesOnByte2").value = null;
	} else {
		blink(1);
		sendToWARBL(MIDI_SLOT_04, 25);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendDronesOnByte3(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 127 || isNaN(x)) {
		alert("Value must be 0 - 127.");
		document.getElementById("dronesOnByte3").value = null;
	} else {
		blink(1);
		sendToWARBL(MIDI_SLOT_04, 26);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendDronesOffCommand(selection) {
	blink(1);
	var y = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_04, 27);
	sendToWARBL(MIDI_SLOT_05, y);
}

function sendDronesOffChannel(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 16 || isNaN(x)) {
		alert("Value must be 1-16.");
		document.getElementById("dronesOffChannel").value = null;
	} else {
		blink(1);
		sendToWARBL(MIDI_SLOT_04, 28);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendDronesOffByte2(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 127 || isNaN(x)) {
		alert("Value must be 0 - 127.");
		document.getElementById("dronesOffByte2").value = null;
	} else {
		blink(1);
		sendToWARBL(MIDI_SLOT_04, 29);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendDronesOffByte3(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 127 || isNaN(x)) {
		alert("Value must be 0 - 127.");
		document.getElementById("dronesOffByte3").value = null;
	} else {
		blink(1);
		sendToWARBL(MIDI_SLOT_04, 30);
		sendToWARBL(MIDI_SLOT_05, x);
	}
}

function sendDronesRadio(selection) {
	blink(1);
	selection = parseFloat(selection);
	sendToWARBL(MIDI_SLOT_04, 31);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function learnDrones() {
	blink(1);
	document.getElementById("dronesPressureInput").style.backgroundColor = "#32CD32";
	setTimeout(blinkDrones, 500);
	sendToWARBL(MIDI_SLOT_06, MIDI_SEND_LEARN_PRESS_DRONE);

}

function blinkDrones() {
	document.getElementById("dronesPressureInput").style.backgroundColor = "#FFF";
}


function blinkOctave() {
	document.getElementById("octavePressureInput").style.backgroundColor = "#FFF";
}

function sendDronesPressure(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 24 || isNaN(x)) {
		alert("Value must be 0.0 - 24.0.");
		document.getElementById("dronesPressureInput").value = null;
	} else {
		x = parseInt(x * 900 / 24 + 100);
		blink(1);
		document.getElementById("dronesPressureInput").style.backgroundColor = "#32CD32";
		setTimeout(blinkDrones, 500);
		sendToWARBL(MIDI_SLOT_04, 32);
		sendToWARBL(MIDI_SLOT_05, x & 0x7F);
		sendToWARBL(MIDI_SLOT_04, 33);
		sendToWARBL(MIDI_SLOT_05, x >> 7);
	}
}

function sendOctavePressure(selection) {
	var x = parseFloat(selection);
	if (x < 0 || x > 24 || isNaN(x)) {
		alert("Value must be 0.0 - 24.0.");
		document.getElementById("octavePressureInput").value = null;
	} else {
		x = parseInt(x * 900 / 24 + 100);
		blink(1);
		document.getElementById("octavePressureInput").style.backgroundColor = "#32CD32";
		setTimeout(blinkOctave, 500);
		sendToWARBL(MIDI_SLOT_04, 34);
		sendToWARBL(MIDI_SLOT_05, x & 0x7F);
		sendToWARBL(MIDI_SLOT_04, 35);
		sendToWARBL(MIDI_SLOT_05, x >> 7);
	}

}

function learn() {
	blink(1);
	document.getElementById("octavePressureInput").style.backgroundColor = "#32CD32";
	setTimeout(blinkOctave, 500);
	sendToWARBL(MIDI_SLOT_06, MIDI_SEND_LEARN_PRESS);
}

function sendCalibrateRadio(selection) {
	selection = parseFloat(selection);
	blink(1);
	sendToWARBL(MIDI_SLOT_06, MIDI_CALIB_OPTION_OS + selection);
}

function sendPitchbendRadio(selection) {
	updateCustom();
	updateCustom();
	selection = parseFloat(selection);
	if (selection > 0) {
		blink(selection + 1);
	}
	sendToWARBL(MIDI_SLOT_02, MIDI_PB_MODE_OS + selection);
}

function sendVibratoHoles(holeNumber, selection) {
	selection = +selection; //convert true/false to 1/0
	sendToWARBL(MIDI_SLOT_06, (30 - (selection * 10)) + holeNumber);
}

function updateCustom() { //keep correct settings enabled/disabled with respect to the custom vibrato switch and send pressure as CC switches.


	var a = document.getElementById("fingeringSelect" + currentPreset).value;

	if (document.getElementById("pitchbendradio2").checked == false && (((a == 0 || a == 1 || a == 4 || a == 10) && ((document.getElementById("pitchbendradio1").checked == true && version < 1.6) || (version == "Unknown" || version > 1.5))) || (version == "Unknown" || version > 1.5) && (a == 3 || a == 2))) {
		document.getElementById("checkbox5").disabled = false;
		document.getElementById("switch5").style.cursor = "pointer";
	} else {
		//document.getElementById("checkbox5").checked = false;
		document.getElementById("checkbox5").disabled = true;
		document.getElementById("switch5").style.cursor = "default";
		//sendToWARBL(MIDI_SLOT_04,44); //if custom is disabled, tell WARBL to turn it off
		//sendToWARBL(MIDI_SLOT_05, 0);
		//blink(1);
	}
	if (document.getElementById("checkbox5").checked == true && document.getElementById("checkbox5").disabled == false) {
		for (var i = 0; i < 9; i++) {
			document.getElementById("vibratoCheckbox" + i).disabled = true;
			document.getElementById("vibratoCheckbox" + i).style.cursor = "default";
		}
	} else {
		for (var i = 0; i < 9; i++) {
			document.getElementById("vibratoCheckbox" + i).disabled = false;
			document.getElementById("vibratoCheckbox" + i).style.cursor = "pointer";
		}
	}
	
		if (document.getElementById("checkbox18").checked == true) {
			document.getElementById("fingeringInput11").disabled = true;
			document.getElementById("fingeringInput11").style.cursor = "default";
		
	} else {
	
			document.getElementById("fingeringInput11").disabled = false;
			document.getElementById("fingeringInput11").style.cursor = "pointer";
		
	}
}

function sendBreathmodeRadio(selection) {
	selection = parseFloat(selection);
	if (selection > 0) {
		blink(selection + 1);
	}
	if(document.getElementById("sensorradio1").checked == true) { //update override
		document.getElementById("checkbox16").disabled = true;
	}
	else {
		document.getElementById("checkbox16").disabled = false;
	}
	sendToWARBL(MIDI_SLOT_02, MIDI_BREATH_MODE_OS + selection);

}

function advanced() {
	document.getElementById("box2").style.display = "block";
	document.getElementById("box1").style.display = "none";
	updateSelected();
}

function advancedOkay() {
	document.getElementById("box2").style.display = "none";
	document.getElementById("box1").style.display = "block";
}

function advancedPB() {
	if(version > 1.8 || version == "Unknown"){
		document.getElementById("box4").style.display = "block";
		document.getElementById("box5").style.display = "none";
	}
}


function overRideExpression() {
	if(version > 1.8 || version == "Unknown"){
		if(document.getElementById("sensorradio1").checked == true) {
			document.getElementById("checkbox16").disabled = true;
		}
		else {
			document.getElementById("checkbox16").disabled = false;
		}
		document.getElementById("box8").style.display = "block";
		document.getElementById("box6").style.display = "none";
	}
}

function okayOverride() {
	document.getElementById("box8").style.display = "none";
	document.getElementById("box6").style.display = "block";
}


function advancedOkayPB() {
	document.getElementById("box4").style.display = "none";
	document.getElementById("box5").style.display = "block";
}

function configureCustomFingering() {
	customFingeringLearningON = true;
	document.getElementById("topControls").style.display = "none";
	document.getElementById("customFingering").style.display = "block";
	// document.getElementById("customControls").style.display = "block";
	document.getElementById("box1").style.top = "740px";
	document.getElementById("box2").style.top = "740px";
	document.getElementById("box4").style.top = "740px";
	document.getElementById("box5").style.top = "740px";
	document.getElementById("pressuregraph").style.top = "740px";
	document.getElementById("box3").style.top = "1200px";
	document.getElementById("box6").style.top = "1200px";
	document.getElementById("box7").style.top = "1200px";
	document.getElementById("box8").style.top = "1200px";
	document.getElementById("buttonBox").style.top = "1690px";
	document.getElementById("topcontrolbox").style.height = "2085px";

	document.getElementById("customFingeringReset").disabled = customFingeringLearningON;
	document.getElementById("customFingeringModify").disabled = customFingeringLearningON;

}

function customFingeringOkay() {
	customFingeringLearningON = false;
	document.getElementById("customFingering").style.display = "none";
	// document.getElementById("customControls").style.display = "none";
	document.getElementById("topControls").style.display = "block";
	document.getElementById("box1").style.top = "440px";
	document.getElementById("box2").style.top = "440px";
	document.getElementById("box4").style.top = "440px";
	document.getElementById("box5").style.top = "440px";
	document.getElementById("pressuregraph").style.top = "440px";
	document.getElementById("box3").style.top = "900px";
	document.getElementById("box6").style.top = "900px";
	document.getElementById("box7").style.top = "900px";
	document.getElementById("box8").style.top = "900px";
	document.getElementById("buttonBox").style.top = "1390px";
	document.getElementById("topcontrolbox").style.height = "1785px";
	document.getElementById("customFingeringFill").value = "12";
}

function configureHalfHoleDetection() {
	sendHalfHoleSelect(document.getElementById("halfHoleSelect").value); //enables it

	document.getElementById("calibrationBox").style.display = "none";
	document.getElementById("halfHoleDetection").style.display = "block";

	// document.getElementById("topcontrolbox").style.height = "2085px";
}

// function halfHoleAutoCalibrate() {
// 	var calibValue = parseInt(document.getElementById("currentCalibrationOpenHH").innerHTML);

// 	document.getElementById("lowerBoundRangeHH").value = calibValue -100;
// 	document.getElementById("upperBoundRangeHH").value = calibValue +5;

// 	slider_getVals();
// 	sendHalfHoleSelect(document.getElementById("halfHoleSelect").value);

// }

function halfHoleToggle() {
	var upperBound = parseInt(document.getElementById("upperBoundRangeHH").value);

	if (upperBound >= 500) { //disabled
		sendHalfHoleUpperBound(300); //Random value to re-enable it
		slider_getVals();

	} else {
		document.getElementById("upperBoundRangeHH").value = 500;
		sendHalfHoleUpperBound(1024);
	}
	console.log("Toggle: half hole", parseInt(document.getElementById("upperBoundRangeHH").value))

	sendHalfHoleSelect(document.getElementById("halfHoleSelect").value);

}

function halfHoleDetectionOkay() {
	var prevDirty = settingsDirty; //This sends a message, but doesn't change settings
	sendHalfHoleSelect("99"); //disables it
	settingsDirty = prevDirty; //restore previous state

	document.getElementById("halfHoleDetection").style.display = "none";
	document.getElementById("calibrationBox").style.display = "block";
}

function halfHoleDetectionSave() {

	//sendToWARBL(MIDI_SLOT_02, MIDI_SAVE_CALIB); //Saves calibration and buffer
	saveAsDefaults();
	halfHoleDetectionOkay();
}


function mapCC() {
	mapSelection = 0;

	slider.noUiSlider.set([inputSliderMin[0], inputSliderMax[0]]);
	slider2.noUiSlider.set([outputSliderMin[0], outputSliderMax[0]]);
	document.getElementById("pressureChannel").style.visibility = "visible";
	document.getElementById("pressureCC").style.visibility = "visible";
	document.getElementById("expressionChannel").style.visibility = "visible";
	document.getElementById("highByte").style.visibility = "visible";	
	document.getElementById("box7").style.display = "block";
	document.getElementById("box6").style.display = "none";
	if(curve[0] < 3) {document.getElementById("curveRadio" + curve[0]).checked = true;
	}
	if (version > 1.8){
		document.getElementById("pressureMappingHeader").innerHTML="CC Mapping";
	}
}

function mapVelocity() {
	mapSelection = 1;
	slider.noUiSlider.set([inputSliderMin[1], inputSliderMax[1]]);
	slider2.noUiSlider.set([outputSliderMin[1], outputSliderMax[1]]);
	if(curve[1] < 3) {document.getElementById("curveRadio" + curve[1]).checked = true;
	}
	document.getElementById("box7").style.display = "block";
	document.getElementById("box6").style.display = "none";	
	document.getElementById("pressureMappingHeader").innerHTML="Velocity Mapping";
	//console.log(mapSelection);
}

function mapAftertouch() {
	mapSelection = 2;
	slider.noUiSlider.set([inputSliderMin[2], inputSliderMax[2]]);
	slider2.noUiSlider.set([outputSliderMin[2], outputSliderMax[2]]);
	if(curve[2] < 3) {document.getElementById("curveRadio" + curve[2]).checked = true;
	}
	document.getElementById("box7").style.display = "block";
	document.getElementById("box6").style.display = "none";
	document.getElementById("pressureMappingHeader").innerHTML="Channel Pressure Mapping";	
}

function mapPoly() {
	mapSelection = 3;
	slider.noUiSlider.set([inputSliderMin[3], inputSliderMax[3]]);
	slider2.noUiSlider.set([outputSliderMin[3], outputSliderMax[3]]);
	if(curve[3] < 3) {document.getElementById("curveRadio" + curve[3]).checked = true;
	}
	document.getElementById("box7").style.display = "block";
	document.getElementById("box6").style.display = "none";	
	document.getElementById("pressureMappingHeader").innerHTML="Key Pressure Mapping";
}


function okayCCmap() {
	mapSelection = 4;
	document.getElementById("box7").style.display = "none";
	document.getElementById("box6").style.display = "block";
	document.getElementById("pressureChannel").style.visibility = "hidden";
	document.getElementById("pressureCC").style.visibility = "hidden";
	document.getElementById("expressionChannel").style.visibility = "hidden";
	document.getElementById("highByte").style.visibility = "hidden";
}



function pressureGraph() {
    

	// Show the pressure graph
	document.getElementById("pressuregraph").style.display = "block";
	document.getElementById("box1").style.display = "none";

	// Start graphing the incoming pressure
	startPressureGraph();
}

function pressureOkay() {

	// Stop graphing the incoming pressure
	stopPressureGraph();

	// Hide the pressure
	document.getElementById("pressuregraph").style.display = "none";
	document.getElementById("box1").style.display = "block";
}

function advancedDefaults() {
	if (version > 2.0 || version == "Unknown"){
	document.getElementById("jumpFactor7").value = "3";
	document.getElementById("jumpFactor8").value = "7";
	document.getElementById("jumpFactor9").value = "20";
	document.getElementById("jumpFactor11").value = "12";
	document.getElementById("jumpFactor12").value = "50";
	for (var i = 7; i < 10; i++) {
		var k = document.getElementById("jumpFactor" + (i));
			k.dispatchEvent(new Event('input'));
		var j = document.getElementById("jumpFactor" + (i)).value;
		sendJumpFactor(i, j);
	}
	for (var i = 11; i < 13; i++) {
		var k = document.getElementById("jumpFactor" + (i));
			k.dispatchEvent(new Event('input'));
		var j = document.getElementById("jumpFactor" + (i)).value;
		sendJumpFactor(i, j);
	}		
	}
	
	else{
	document.getElementById("jumpFactor1").value = "25";
	document.getElementById("jumpFactor2").value = "15";
	document.getElementById("jumpFactor3").value = "15";
	document.getElementById("jumpFactor4").value = "15";
	document.getElementById("jumpFactor5").value = "30";
	document.getElementById("jumpFactor6").value = "60";
	document.getElementById("jumpFactor7").value = "3";
	document.getElementById("jumpFactor8").value = "7";
	document.getElementById("jumpFactor9").value = "100";
	document.getElementById("jumpFactor10").value = "7";
	document.getElementById("jumpFactor11").value = "9";
	document.getElementById("jumpFactor12").value = "9";

	for (var i = 1; i < 13; i++) {
		var k = document.getElementById("jumpFactor" + (i));
			k.dispatchEvent(new Event('input'));
		var j = document.getElementById("jumpFactor" + (i)).value;
		sendJumpFactor(i, j);
	}
	}
}

function advancedBagDefaults() {
	
	
	if (version > 2.0 || version == "Unknown"){
	document.getElementById("jumpFactor1").value = "50";
	document.getElementById("jumpFactor2").value = "20";
	document.getElementById("jumpFactor3").value = "20";
	document.getElementById("jumpFactor4").value = "50";
	document.getElementById("jumpFactor6").value = "75";

	for (var i = 1; i < 7; i++) {
		var k = document.getElementById("jumpFactor" + (i));
			k.dispatchEvent(new Event('input'));
		var j = document.getElementById("jumpFactor" + (i)).value;
		sendJumpFactor(i, j);
	}
	}
	
	
	else{
	document.getElementById("jumpFactor1").value = "75";
	document.getElementById("jumpFactor2").value = "25";
	document.getElementById("jumpFactor3").value = "15";
	document.getElementById("jumpFactor4").value = "15";
	document.getElementById("jumpFactor5").value = "30";
	document.getElementById("jumpFactor6").value = "60";
	document.getElementById("jumpFactor7").value = "50";
	document.getElementById("jumpFactor8").value = "20";
	document.getElementById("jumpFactor9").value = "28";
	document.getElementById("jumpFactor10").value = "7";
	document.getElementById("jumpFactor11").value = "15";
	document.getElementById("jumpFactor12").value = "22";


	for (var i = 1; i < 13; i++) {
		var k = document.getElementById("jumpFactor" + (i));
			k.dispatchEvent(new Event('input'));
		var j = document.getElementById("jumpFactor" + (i)).value;
		sendJumpFactor(i, j);

	}
	}
}


function sendJumpFactor(factor, selection) {
	selection = parseFloat(selection);
	blink(1);
	sendToWARBL(MIDI_SLOT_04, factor);
	sendToWARBL(MIDI_SLOT_05, selection);
}


function sendRow(rowNum) {
	blink(1);
	updateCells();
	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_BUTTON_PREF_OS + rowNum);

	//20290927 GLB
	document.getElementById("HARMrow" + rowNum).value = 12;
	var a = document.getElementById("row" + rowNum).value;
	var b = a;
	if (a == 30) { //Transpose
		b = 5;
	} 
	//END GLB

	var y = (MIDI_BUTTON_PREF_ACTION_OS) + parseFloat(b);
	sendToWARBL(MIDI_SLOT_02, y);
	sendMIDIrow(rowNum);

	//20230928 GLB
	if (a == 30) { //Transpose
		document.getElementById("channel" + (rowNum)).value = 0;
		sendChannel(rowNum);
		document.getElementById("channel" + (rowNum)).value = null;
	} else if (a == 5) { // Progressive Transpose
		document.getElementById("channel" + (rowNum)).value = 1;
		sendChannel(rowNum);
		document.getElementById("channel" + (rowNum)).value = null;
	} else {
		sendChannel(rowNum);
	}
	//END GLB

	sendByte2(rowNum);
	sendByte3(rowNum);
	if (rowNum < 3) {
		sendMomentary(rowNum);
	}
}

//20230927 GLB
//Action 30 - Transpose - Channel = 0 - Byte2 = interval //WARBL Action 5
//Action 31 - Progressive Transpose - Channel = 1 - Byte 2  = interval //WARBL Action 5
//Action 6 - Set Fixed Note  //WARBL Action 6
//Action 10 - Harmonizer voice 1 - Byte 2  = interval - Byte 3  = scale //WARBL Action 10
//Action 11 - Harmonizer voice 2 - Byte 2  = interval - Byte 3  = scale //WARBL Action 11
//Action 12 - Harmonizer voice 3 - Byte 2  = interval - Byte 3  = scale //WARBL Action 11

function sendHARMrow(HARMrowNum) {
	document.getElementById("byte2_" + (HARMrowNum)).value = parseFloat(document.getElementById("HARMrow" + HARMrowNum).value);
	sendByte2(HARMrowNum);
	document.getElementById("byte2_" + (HARMrowNum)).value = null;

	document.getElementById("byte3_" + (HARMrowNum)).value = parseFloat(document.getElementById("HarmScaleRow" + HARMrowNum).value);
	sendByte3(HARMrowNum);
	document.getElementById("byte3_" + (HARMrowNum)).value = null;
}

//New custom fingering
function onCustomFingeringDeleteAllCurrent() {

	if (confirm("Are you sure you want to delete all custom fingerings for the current fingering scheme?")) {
		sendToWARBL(MIDI_SLOT_02, MIDI_DELETE_CUSTOM_FINGERING_CURRENT); 
	}
}
function onCustomFingeringDeleteAll() {
	if (confirm("Are you sure you want to delete all custom fingerings?")) {
		sendToWARBL(MIDI_SLOT_02, MIDI_DELETE_CUSTOM_FINGERING); 
	}
}
function onCustomFingeringReset() {
	document.getElementById("customFingeringInput").value = defaultMidiNote;
	sendCustomFingering();
}
function sendCustomFingering() {
	var midiNote = document.getElementById("customFingeringInput").value

	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING); //Enters custon fingering communication mode
	sendToWARBL(MIDI_SLOT_09,midiNote);
	sendIntToWARBL(MIDI_SEND_HOLE_COVERED, holeCovered);
	// sendPBToWARBL(holeCovered);
	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_CUSTOM_FINGERING); //Exits custon fingering communication mode
	customFingeringLearningON = true;
	document.getElementById("customFingeringReset").disabled = customFingeringLearningON;
	document.getElementById("customFingeringModify").disabled = customFingeringLearningON;

	document.getElementById("defaultMidiNote").innerHTML = "-";
	document.getElementById("overrideMidiNote").innerHTML = "-";
	document.getElementById("customFingeringInput").value = "";
}
//END GLB

function sendMIDIrow(MIDIrowNum) {
	blink(1);
	updateCells();
	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_BUTTON_PREF_OS + MIDIrowNum);
	var y = (MIDI_BUTTON_PREF_MIDI_CMD_OS) + parseFloat(document.getElementById("MIDIrow" + MIDIrowNum).value);
	sendToWARBL(MIDI_SLOT_02, y);
	sendChannel(MIDIrowNum);
	sendByte2(MIDIrowNum);
	sendByte3(MIDIrowNum);
	if (MIDIrowNum < 3) {
		sendMomentary(MIDIrowNum);
	}
}

function sendChannel(rowNum) {
	blink(1);
	MIDIvalueChange();
	var y = parseFloat(document.getElementById("channel" + (rowNum)).value);
	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_BUTTON_PREF_OS + rowNum);
	sendToWARBL(MIDI_SLOT_06, y);
}

function sendByte2(rowNum) {
	blink(1);
	MIDIvalueChange();
	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_BUTTON_PREF_OS + rowNum);
	var y = parseFloat(document.getElementById("byte2_" + (rowNum)).value);
	sendToWARBL(MIDI_SLOT_07, y);
}

function sendByte3(rowNum) {
	blink(1);
	MIDIvalueChange();
	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_BUTTON_PREF_OS + rowNum);
	var y = parseFloat(document.getElementById("byte3_" + (rowNum)).value);
	sendToWARBL(MIDI_SLOT_08, y);
}

function sendMomentary(rowNum) { //send momentary
	blink(1);
	updateCells();
	var y = document.getElementById("checkbox" + rowNum).checked
	sendToWARBL(MIDI_SLOT_02, MIDI_SEND_BUTTON_PREF_OS + rowNum);
	if (y == false) {
		sendToWARBL(MIDI_SLOT_02, MIDI_MOMENTARY_OFF_OS);
	}
	if (y == true) {
		sendToWARBL(MIDI_SLOT_02, MIDI_MOMENTARY_ON_OS);
	}
}

//switches

function sendVented(selection) {
	selection = +selection; //convert true/false to 1/0
	blink(1);
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_SWITCH_VARS_OS);
	sendToWARBL(MIDI_SLOT_05, selection);
	updateSelected();
}

function sendBagless(selection) {
	selection = +selection; //convert true/false to 1/0
	blink(1);
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_SWITCH_VARS_OS+1);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendSecret(selection) {
	selection = +selection; //convert true/false to 1/0
	blink(1);
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_SWITCH_VARS_OS+2);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendInvert(selection) {
	selection = +selection; //convert true/false to 1/0
	blink(1);
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_SWITCH_VARS_OS+3);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendCustom(selection) {
	selection = +selection; //convert true/false to 1/0
	blink(1);
	updateCustom();
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_SWITCH_VARS_OS+4);
	sendToWARBL(MIDI_SLOT_05, selection);
}


function sendExpression(selection) {
	selection = +selection; //convert true/false to 1/0
	blink(1);
	//if (selection == 1) {
		//document.getElementById("overrideExpression").disabled = false;
	//} else (document.getElementById("overrideExpression").disabled = true);
	sendToWARBL(MIDI_SLOT_04, MIDI_SEND_EXPRESSION_VARS_1_OS);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendRawPressure(selection) {
	selection = +selection; //convert true/false to 1/0
	updateCustom();
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 15);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendVelocity(selection) {
	selection = +selection; //convert true/false to 1/0
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 45);
	sendToWARBL(MIDI_SLOT_05, selection);
	updateCells();
}

function sendAftertouch(selection, polyselection) {
	selection = +selection; //convert true/false to 1/0
    var val = selection | ((+polyselection) << 1);
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 46);
	sendToWARBL(MIDI_SLOT_05, val);
}

function sendForceVelocity(selection) {
	selection = +selection; 
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 47);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendHack1(selection) {
	selection = +selection; 
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 48);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendHack2(selection) {
	selection = +selection; 
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 49);
	sendToWARBL(MIDI_SLOT_05, selection);
}

function sendOverride(selection) {
	selection = +selection; 
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 50);
	sendToWARBL(MIDI_SLOT_05, selection);
}

// function sendBoth(selection) {
// 	selection = +selection; 
// 	blink(1);
// 	sendToWARBL(MIDI_SLOT_04, 51);
// 	sendToWARBL(MIDI_SLOT_05, selection);
// }

// function sendR4flatten(selection) {
// 	selection = +selection; 
// 	blink(1);
// 	updateCustom();
// 	sendToWARBL(MIDI_SLOT_04, 52);
// 	sendToWARBL(MIDI_SLOT_05, selection);
// }

/* //curently unused--can be used for an additional switch.
function sendInvertR4(selection) {
	selection = +selection;
	blink(1);
	sendToWARBL(MIDI_SLOT_04, 53);
	sendToWARBL(MIDI_SLOT_05, selection);
}
*/


//end switches



function saveAsDefaults() {
	modalclose(2);
	blink(3);
	sendToWARBL(MIDI_SLOT_02, MIDI_SAVE_SETTING_CURRENT);
	settingsDirty = false;
}

function saveAsDefaultsForAll() {
	modalclose(3);
	blink(3);
	sendToWARBL(MIDI_SLOT_02, MIDI_SAVE_SETTING_ALL);
	settingsDirty = false;
}

function restoreAll() {
	modalclose(4);
	blink(3);
	sendToWARBL(MIDI_SLOT_02, MIDI_RESTORE_FACTORY_SETTING);
	communicationMode = 0;
	if (version > 1.9) { //WARBL will restart, so try to reconnect to it.
		setTimeout(connect, 3000);
	}
	settingsDirty = false;
}

function autoCalibrateBell() {
	if(communicationMode){
	LEDon();}
	setTimeout(LEDoff, 5000);
	sendToWARBL(MIDI_SLOT_06, MIDI_AUTO_CALIB_BELL);
}

function autoCalibrate() {
	if(communicationMode){
	LEDon();}
	setTimeout(LEDoff, 10000);
	sendToWARBL(MIDI_SLOT_02, MIDI_AUTO_CALIB);
}

function frequencyFromNoteNumber(note) {
	return 440 * Math.pow(2, (note - 69) / 12);
}

function modal(modalId) {
	document.getElementById("open-modal" + modalId).classList.add('modal-window-open');
	if(modalId == 18){clearConsole()};
}

function modalclose(modalId) {
	document.getElementById("open-modal" + modalId).classList.remove('modal-window-open');
}

function blink(blinkNum) {
	if (communicationMode){
	LEDon();
	setTimeout(LEDoff, 200);
	if (blinkNum > 1) { //blink twice
		setTimeout(LEDon, 400);
		setTimeout(LEDoff, 600);
	}
	if (blinkNum > 2) { // blink thrice
		setTimeout(LEDon, 800);
		setTimeout(LEDoff, 1000);
	}
	if (blinkNum > 3) { //blink four times
		setTimeout(LEDon, 1200);
		setTimeout(LEDoff, 1400);
	}
	if (blinkNum > 4) { //blink five times
		setTimeout(LEDon, 1600);
		setTimeout(LEDoff, 1800);
	}
	}
}

function checkMax(field) { //disable the sensor value field if it has been set to MAX
	var x = document.getElementById("v" + field).textContent;
	if (x == "MAX") {
		document.getElementById(field * 2).disabled = true;
	}
	if (x != "MAX") {
		document.getElementById(field * 2).disabled = false;
	}
}

function isEven(n) {
	return n % 2 == 0;
}

function isOdd(n) {
	return Math.abs(n % 2) == 1;
}

function LEDoff() {
	//console.log("off");
	elements = document.getElementsByClassName("leddot");
	for (var i = 0; i < elements.length; i++) {
		elements[i].style.visibility = "hidden";
	}
}

function LEDon() {
	elements = document.getElementsByClassName("leddot");
	for (var i = 0; i < elements.length; i++) {
		elements[i].style.visibility = "visible";
	}
}


function toggleOn() {
	volume = +!volume;
	if (volume == 0) {
		noteOff(currentNote)
	}
	//else{context.resume();
	//}
}


function logKeys() {
	var s = 'Keys';
	for (var i = 0; i < midiNotes.length; i++) {
		s = s + ' ' + midiNotes[i].pitch;
	}
}

function noteOn(pitch) {
	noteOff(pitch);
	currentNote = pitch;
	if (volume) {
		for (var i = 0; i < _tone_0650_SBLive_sf2.zones.length; i++) {
			 _tone_0650_SBLive_sf2.zones[i].ahdsr = false;
		}
		var envelope = player.queueWaveTable(audioContext, audioContext.destination, _tone_0650_SBLive_sf2, 0, pitch, 999, 0.5, true);
		var note = {
			pitch: pitch,
			envelope: envelope
		};
		midiNotes.push(note);
	}
}

function noteOff(pitch) {
	for (var i = 0; i < midiNotes.length; i++) {
		if (midiNotes[i].pitch == pitch) {
			if (midiNotes[i].envelope) {
				midiNotes[i].envelope.cancel();
			}
			midiNotes.splice(i, 1);
			return;
		}
	}
}

var output14 = document.getElementById("demo14");
var depthSlider = document.getElementById('depth');
depthSlider.addEventListener('input', sliderChange);
function sliderChange() {
  output14.innerHTML = depthSlider.value;
}

var output1 = document.getElementById("demo1");
var jumpSlider1 = document.getElementById('jumpFactor1');
jumpSlider1.addEventListener('input', slider1Change);
function slider1Change() {
  output1.innerHTML = jumpSlider1.value;
}

var output2 = document.getElementById("demo2");
var jumpSlider2 = document.getElementById('jumpFactor2');
jumpSlider2.addEventListener('input', slider2Change);
function slider2Change() {
  output2.innerHTML = jumpSlider2.value;
}

var output3 = document.getElementById("demo3");
var jumpSlider3 = document.getElementById('jumpFactor3');
jumpSlider3.addEventListener('input', slider3Change);
function slider3Change() {
  output3.innerHTML = jumpSlider3.value;
}

var output4 = document.getElementById("demo4");
var jumpSlider4 = document.getElementById('jumpFactor4');
jumpSlider4.addEventListener('input', slider4Change);
function slider4Change() {
  output4.innerHTML = jumpSlider4.value;
}

var output5 = document.getElementById("demo5");
var jumpSlider5 = document.getElementById('jumpFactor5');
jumpSlider5.addEventListener('input', slider5Change);
function slider5Change() {
  output5.innerHTML = jumpSlider5.value;
}

var output6 = document.getElementById("demo6");
var jumpSlider6 = document.getElementById('jumpFactor6');
jumpSlider6.addEventListener('input', slider6Change);
function slider6Change() {
  output6.innerHTML = jumpSlider6.value;
}

var output7 = document.getElementById("demo7");
var jumpSlider7 = document.getElementById('jumpFactor7');
jumpSlider7.addEventListener('input', slider7Change);
function slider7Change() {
  output7.innerHTML = jumpSlider7.value;
}

var output8 = document.getElementById("demo8");
var jumpSlider8 = document.getElementById('jumpFactor8');
jumpSlider8.addEventListener('input', slider8Change);
function slider8Change() {
  output8.innerHTML = jumpSlider8.value;
}

var output9 = document.getElementById("demo9");
var jumpSlider9 = document.getElementById('jumpFactor9');
jumpSlider9.addEventListener('input', slider9Change);
function slider9Change() {
  output9.innerHTML = jumpSlider9.value;
}

var output10 = document.getElementById("demo10");
var jumpSlider10 = document.getElementById('jumpFactor10');
jumpSlider10.addEventListener('input', slider10Change);
function slider10Change() {
  output10.innerHTML = jumpSlider10.value;
}

var output10b = document.getElementById("demo10b");
var jumpSlider10b = document.getElementById('jumpFactor10b');
jumpSlider10b.addEventListener('input', slider10bChange);
function slider10bChange() {
  output10b.innerHTML = jumpSlider10b.value;
}

var output11 = document.getElementById("demo11");
var jumpSlider11 = document.getElementById('jumpFactor11');
jumpSlider11.addEventListener('input', slider11Change);
function slider11Change() {
  output11.innerHTML = jumpSlider11.value;
}

var output12 = document.getElementById("demo12");
var jumpSlider12 = document.getElementById('jumpFactor12');
jumpSlider12.addEventListener('input', slider12Change);
function slider12Change() {
  output12.innerHTML = jumpSlider12.value;
}



function clearConsole() { //clear MIDI console
document.getElementById("console").innerHTML = "";
consoleEntries = 0;	
}


//Populates Various Selects

//Populate functions
function populateSelects() {

	//Actions **** MAX 18 ****
    var actionsArray = [
        ["0","none"],
        ["1","Send MIDI message:"],
        ["2","Change slide/vibrato mode"],
        ["3","Change instrument"],
        ["4","Play/stop (bagless mode)"],
        ["5","Progressive Transposer:"],
        ["30","Transposer on/off:"],
        ["6","Set Fixed Note (on/off)"],
        ["7","MIDI Panic"],
        ["8","Change register control mode"],
        ["9","Turn drones on/off"],
        ["10","Harmonizer on/off (voice 1):"],
        ["11","Harmonizer on/off (voice 2):"],
        ["12","Harmonizer on/off (voice 3)"],
        ["13","Begin autocalibration"],
    ];

	//MIDI Messages
	var messagesArray = [
		["0","Note on/note off"],
		["1","CC"],
		["2","Send PC"],
		["3","Increase PC"],
		["4","Decrease PC"]
	]
	var transposeArray = [
		["0","-12 st (P8)"],
		["1","-11 st (M7)"],
		["2","-10 st (m7)"],
		["3","-9 st (M6)"],
		["4","-8 st (m6)"],
		["5","-7 st (P5)"],
		["6","-6 st (#4)"],
		["7","-5 st (P4)"],
		["8","-4 st (M3)"],
		["9","-3 st (m3)"],
		["10","-2 st (M2)"],
		["11","-1 st (m2)"],
		["12","0 st (P1)"],
		["13","+1 st (m2)"],
		["14","+2 st (M2)"],
		["15","+3 st (m3)"],
		["16","+4 st (M3)"],
		["17","+5 st (P4)"],
		["18","+6 st (#4)"],
		["19","+7 st (P5)"],
		["20","+8 st (m6)"],
		["21","+9 st (M6)"],
		["22","+10 st (m7)"],
		["23","+11 st (M7)"],
		["24","+12 st (P8)"]
	];

	var scalesArray = [
		["0","Major Scale"],
		["1","Melodic Minor Scale"],
		["2","Harmonic Minor Scale"],
		["3","Dimished Scale 1"],
		["4","Dimished Scale 2"],
		["5","Augmented Scale 1"],
		["7","Augmented Scale 2"],
		["7","Whole Tone Scale"],
		["8","Major Bebop Scale"],
		["9","Dominant Bebop Scale"],
		["10","Major Pentatonic Scale"],
		["11","Minor Pentatonic Scale"],
		["12","Blues Scale"]
	];

	//Button Prefs
	var actionsSelectDiv = document.getElementById("buttonPrefsSelectContainer");
	var messagesSelectDiv = document.getElementById("buttonPrefsMessageContainer");
	var channelSelectDiv = document.getElementById("channelInputContainer");

	    //Actions Select
    for (var i = 0; i<8;i++) {
        //Creates Actions Div
        var actionsDivEl = document.createElement("div");
        actionsDivEl.classList.add('styled-select', 'blue', 'semi-square');
		actionsSelectDiv.appendChild(actionsDivEl);

		//Creates Messages Div
		var messagesDivEl = document.createElement("div");
        messagesDivEl.classList.add('styled-select2', 'blue', 'semi-square');
		messagesSelectDiv.appendChild(messagesDivEl);

        //Creates actions Select
        var actionsSelectEl =  document.createElement("select");
        actionsSelectEl.setAttribute('id', 'row' + i);
        actionsSelectEl.setAttribute('onChange', 'sendRow(' + i + ')');
        actionsDivEl.appendChild(actionsSelectEl);

		//Creates messages Select
		var messagesSelectEl =  document.createElement("select");
		messagesSelectEl.setAttribute('id', 'MIDIrow' + i);
		messagesSelectEl.setAttribute('onChange', 'sendMIDIrow(' + i + ')');
		messagesDivEl.appendChild(messagesSelectEl);

		//Creates transpose Select
		var transposeSelectEl =  document.createElement("select");
		transposeSelectEl.setAttribute('id', 'HARMrow' + i);
		transposeSelectEl.setAttribute('onChange', 'sendHARMrow(' + i + ')');
		messagesDivEl.appendChild(transposeSelectEl);



		//Creates Channel Input
		var inputChannelEl = document.createElement("input");
		inputChannelEl.classList.add('channelInput');
		inputChannelEl.setAttribute('type', 'text');
		inputChannelEl.setAttribute('id', 'channel' + i);
		inputChannelEl.setAttribute('onChange', 'sendChannel(' + i + ')');
		inputChannelEl.setAttribute('value', '');
		channelSelectDiv.appendChild(inputChannelEl);

		//Creates Scale Div
		var scaleDivEl = document.createElement("div");
		scaleDivEl.classList.add('styled-select2', 'blue', 'semi-square');
		scaleDivEl.setAttribute('id', 'HarmScaleDiv' + i);
		channelSelectDiv.appendChild(scaleDivEl);

		//Creates scale Select
		var scaleSelectEl =  document.createElement("select");
		scaleSelectEl.setAttribute('id', 'HarmScaleRow' + i);
		scaleSelectEl.setAttribute('onChange', 'sendHARMrow(' + i + ')');
		scaleDivEl.appendChild(scaleSelectEl);

		//Adds action options
        for(var j = 0; j< actionsArray.length; j++) {
            var opt = actionsArray[j];
            var optionEl = document.createElement("option");
            optionEl.textContent = opt[1];
            optionEl.value = opt[0];
            actionsSelectEl.appendChild(optionEl);
        }

		//Adds message options
		for(var j = 0; j< messagesArray.length; j++) {
			var opt = messagesArray[j];
			var optionEl = document.createElement("option");
			optionEl.textContent = opt[1];
			optionEl.value = opt[0];
			messagesSelectEl.appendChild(optionEl);
		}

		//Adds tranpose options
		for(var j = 0; j< transposeArray.length; j++) {
			var opt = transposeArray[j];
			var optionEl = document.createElement("option");
			optionEl.textContent = opt[1];
			optionEl.value = opt[0];
			transposeSelectEl.appendChild(optionEl);
		}

		//Adds scale options
		for(var j = 0; j< scalesArray.length; j++) {
			var opt = scalesArray[j];
			var optionEl = document.createElement("option");
			optionEl.textContent = opt[1];
			optionEl.value = opt[0];
			scaleSelectEl.appendChild(optionEl);
		}
    }


	//keySelect
	var keySelectArray = [
		["113","C3"],
		["114","C#"],
		["115","D"],
		["116","Eb"],
		["117","E"],
		["118","F"],
		["119","F#"],
		["120","G"],
		["121","G#"],
		["122","A"],
		["123","Bb"],
		["124","B"],
		["125","C4"],
		["126","C#"],
		["0","D"],
		["1","Eb"],
		["2","E"],
		["3","F"],
		["4","F#"],
		["5","G"],
		["6","G#"],
		["7","A"],
		["8","Bb"],
		["9","B"],
		["10","C5"],
		["11","C#"],
		["12","D"]
	];
	var keySelectDiv = document.getElementById("keySelectContainer");
    for (var i = 0; i<3;i++) {
		//Creates keySelect Div
		var keySelectDivEl = document.createElement("div");
        keySelectDivEl.classList.add('styled-key-select', 'blue', 'semi-square');
		keySelectDivEl.setAttribute('id', 'key' + i);
		keySelectDiv.appendChild(keySelectDivEl);

		//Creates keySelect
		var keySelectEl =  document.createElement("select");
		keySelectEl.setAttribute('id', 'keySelect' + i);
		keySelectEl.setAttribute('onChange', 'sendKey(' + i + ',value)');
		keySelectDivEl.appendChild(keySelectEl);

		//Adds key options
		for(var j = 0; j< keySelectArray.length; j++) {
			var opt = keySelectArray[j];
			var optionEl = document.createElement("option");
			optionEl.textContent = opt[1];
			optionEl.value = opt[0];
			if (keySelectEl == 0) {
				optionEl.setAttribute('selected', 'selected');
			}
			keySelectEl.appendChild(optionEl);
		}

	}

}

//sets up initial values for selects/fields/radios and constantly keeps the proper options enabled/disabled
function updateCells() {

	if (version > 1.6) {
		var p = document.getElementById("checkbox10").checked;
		if (p == true) {
			document.getElementById("checkbox12").disabled = true;
			document.getElementById("switch12").style.cursor = "default";
		} else {
			document.getElementById("checkbox12").disabled = false;
			document.getElementById("switch12").style.cursor = "pointer";
		}
	}

	var q = document.getElementById("checkbox0").checked;
	if (q == true) {
		document.getElementById("row5").disabled = true;
	} else {
		document.getElementById("row5").disabled = false;
	}

	var r = document.getElementById("checkbox1").checked;
	if (r == true) {
		document.getElementById("row6").disabled = true;
	} else {
		document.getElementById("row6").disabled = false;
	}

	if (q == true || r == true) {
		document.getElementById("row3").disabled = true;
	} else {
		document.getElementById("row3").disabled = false;
	}

	var s = document.getElementById("checkbox2").checked;
	if (s == true) {
		document.getElementById("row7").disabled = true;
	} else {
		document.getElementById("row7").disabled = false;
	}

	if (r == true || s == true) {
		document.getElementById("row4").disabled = true;
	} else {
		document.getElementById("row4").disabled = false;
	}

	for (var i = 0; i < 8; i++) {
		var x = document.getElementById("row" + i).value;
		var t = document.getElementById("row" + i).disabled;

		if ((x != 1 || t == true)) {
			//20230927 GLB
			document.getElementById("MIDIrow" + i).disabled = true;
			document.getElementById("HARMrow" + i).disabled = t;

			if (x == 30 || x == 5) { //Transposer
				document.getElementById("MIDIrow" + i).style.display = 'none';
				document.getElementById("channel" + i).style.display = 'none';

				document.getElementById("HARMrow" + i).style.display = 'block';
				document.getElementById("HarmScaleDiv" + i).style.display = 'none';				

			} else if (x == 10 || x == 11 || x == 12) { // Harmonizer
				document.getElementById("MIDIrow" + i).style.display = 'none';
				document.getElementById("channel" + i).style.display = 'none';
				document.getElementById("byte2_" + i).style.zIndex = 0;

				document.getElementById("HARMrow" + i).style.display = 'block';
				document.getElementById("HarmScaleDiv" + i).style.display = 'block';
				document.getElementById("HarmScaleDiv" + i).style.zIndex = 100;
				

			}  else {
				document.getElementById("MIDIrow" + i).style.display = 'block';
				document.getElementById("channel" + i).style.display = 'block';
				document.getElementById("byte2_" + i).style.zIndex = 100;

				document.getElementById("HARMrow" + i).style.display = 'none';
				document.getElementById("HarmScaleDiv" + i).style.display = 'none';

			}
			//END GLB

			document.getElementById("channel" + i).disabled = true;
			document.getElementById("byte2_" + i).disabled = true;
			document.getElementById("byte3_" + i).disabled = true;
		} else {
			document.getElementById("MIDIrow" + i).disabled = false;
			
			//20230927 GLB
			document.getElementById("MIDIrow" + i).style.display = 'block';
			document.getElementById("channel" + i).style.display = 'block';
			document.getElementById("byte2_" + i).style.display = 'block';

			document.getElementById("HARMrow" + i).style.display = 'none';
			document.getElementById("HarmScaleDiv" + i).style.display = 'none';

			//END GLB

			document.getElementById("channel" + i).disabled = false;
			document.getElementById("byte2_" + i).disabled = false;
			document.getElementById("byte3_" + i).disabled = false;
		}

		var y = document.getElementById("MIDIrow" + i).value;
		if (y == 2) {
			document.getElementById("byte3_" + i).disabled = true;
		}
		if (y > 2) {
			document.getElementById("byte2_" + i).disabled = true;
			document.getElementById("byte3_" + i).disabled = true;
		}

		var z = document.getElementById("row" + i).value;

		//20230927 GLB
		if ((y == 0 && i < 3 && x == 1) || ((version > 1.4 || version == "Unknown") && i < 3 && (z == 30 || z == 5 || z == 10 || z == 11 || z == 12))) {
			document.getElementById("checkbox" + i).disabled = false;
			document.getElementById("switch" + i).style.cursor = "pointer";
		}

		if (((y != 0 && i < 3) || (i < 3 && (x == 0 || x > 1))) && !((version > 1.4 || version == "Unknown") && i < 3 && (z == 30 || z == 5 || z == 10 || z == 11 || z == 12))) {
			document.getElementById("checkbox" + i).disabled = true;
			document.getElementById("switch" + i).style.cursor = "default";
			document.getElementById("checkbox" + i).checked = false;
		}

		//END GLB
		var q = document.getElementById("checkbox0").checked;
		if (q == true) {
			document.getElementById("row5").disabled = true;
		} else {
			document.getElementById("row5").disabled = false;
		}

		var r = document.getElementById("checkbox1").checked;
		if (r == true) {
			document.getElementById("row6").disabled = true;
		} else {
			document.getElementById("row6").disabled = false;
		}

		if (q == true || r == true) {
			document.getElementById("row3").disabled = true;
		} else {
			document.getElementById("row3").disabled = false;
		}

		var s = document.getElementById("checkbox2").checked;
		if (s == true) {
			document.getElementById("row7").disabled = true;
		} else {
			document.getElementById("row7").disabled = false;
		}

		if (r == true || s == true) {
			document.getElementById("row4").disabled = true;
		} else {
			document.getElementById("row4").disabled = false;
		}

	}

	var z = $("#fingeringSelect0 option:selected").text();
	document.getElementById("fingeringLabel1").innerHTML = z;

	var z = $("#fingeringSelect1 option:selected").text();
	document.getElementById("fingeringLabel2").innerHTML = z;

	var z = $("#fingeringSelect2 option:selected").text();
	document.getElementById("fingeringLabel3").innerHTML = z;

}

//20230927 GLB
function MIDIvalueChange() {
	for (var i = 0; i < 8; i++) {

		var a = document.getElementById("row" + i).value;

		if (a == 30 || a == 5 || a == 10 || a == 11 || a == 12) { //Transposer/Harmonizer
			var x = document.getElementById("HARMrow" + i).value;

			if (x < 0 || x > 24 || isNaN(x)) {
				alert("Value must be 0-24.");
				document.getElementById("HARMrow" + i).value = 12;
			}

		} else {

			//Channel
			var x = document.getElementById("channel" + i).value;
			if (((x < 0 || x > 16 || isNaN(x)) && !document.getElementById("channel" + i).disabled)) {
				alert("Value must be 1-16.");
				document.getElementById("channel" + i).value = null;
			}

			//Byte2
			var y = document.getElementById("channel" + i).value;
			x = document.getElementById("byte2_" + i).value;
			if (x < 0 || x > 127 || isNaN(x)) {
				alert("Value must be 0-127.");
				document.getElementById("byte2_" + i).value = null;
			}
			if (y == 7 && x > 101 && x < 120) {
				alert("This CC range on channel 7 is reserved for the Configuration Tool.");
				document.getElementById("byte2_" + i).value = null;

			}

			//Byte3
			x = document.getElementById("byte3_" + i).value;
			if (x < 0 || x > 127 || isNaN(x)) {
				alert("Value must be 0-127.");
				document.getElementById("byte3_" + i).value = null;
			}
		}
	}
}
function MIDIvalueChange_old() {
	for (var i = 0; i < 8; i++) {
		var x = document.getElementById("channel" + i).value;
		if (((x < 0 || x > 16 || isNaN(x)) && !document.getElementById("channel" + i).disabled)) {
			alert("Value must be 1-16.");
			document.getElementById("channel" + i).value = null;
		}
	}
	for (var j = 0; j < 8; j++) {
		var y = document.getElementById("channel" + j).value;
		var x = document.getElementById("byte2_" + j).value;
		if (x < 0 || x > 127 || isNaN(x)) {
			alert("Value must be 0-127.");
			document.getElementById("byte2_" + j).value = null;
		}
		if (y == 7 && x > 101 && x < 120) {
			alert("This CC range on channel 7 is reserved for the Configuration Tool.");
			document.getElementById("byte2_" + j).value = null;

		}
	}

	for (var k = 0; k < 8; k++) {
		var x = document.getElementById("byte3_" + k).value;
		if (x < 0 || x > 127 || isNaN(x)) {
			alert("Value must be 0-127.");
			document.getElementById("byte3_" + k).value = null;
		}
	}

}	

function MIDIvalueChange() {
	for (var i = 0; i < 8; i++) {
		var x = document.getElementById("channel" + i).value;
		if (((x < 0 || x > 16 || isNaN(x)) && !document.getElementById("channel" + i).disabled)) {
			alert("Value must be 1-16.");
			document.getElementById("channel" + i).value = null;
		}
	}
	for (var j = 0; j < 8; j++) {
		var y = document.getElementById("channel" + j).value;
		var x = document.getElementById("byte2_" + j).value;
		if (x < 0 || x > 127 || isNaN(x)) {
			alert("Value must be 0-127.");
			document.getElementById("byte2_" + j).value = null;
		}
		if (y == 7 && x > 101 && x < 120) {
			alert("This CC range on channel 7 is reserved for the Configuration Tool.");
			document.getElementById("byte2_" + j).value = null;

		}
	}

	for (var k = 0; k < 8; k++) {
		var x = document.getElementById("byte3_" + k).value;
		if (x < 0 || x > 127 || isNaN(x)) {
			alert("Value must be 0-127.");
			document.getElementById("byte3_" + k).value = null;
		}
	}

}

//
// WebAudio related functionality
//
var AudioContextFunc = window.AudioContext || window.webkitAudioContext;

var audioContext = new AudioContextFunc();

var player = new WebAudioFontPlayer();

player.loader.decodeAfterLoading(audioContext, '_tone_0650_SBLive_sf2');

//
// Toggle between adding and removing the "responsive" class to topnav when the user clicks on the icon
//
function topNavFunction() {

	var x = document.getElementById("myTopnav");
	
	if (x.className === "topnav") {
		x.className += " responsive";
	} else {
		x.className = "topnav";
	}

}

//
// Preset import/export features
//

// 
// Synchronous sleep (returns Promise for async/await use)
//
function sleep(ms) {
  return new Promise(resolve => setTimeout(resolve, ms));
}

//
// Import a WARBL preset from a file
//


function importPreset(context){

	//console.log("importPreset");

	//console.log("current tab = "+instrument);

	// Put up error message if WARBL is not connected
	if (!WARBLout){
		
		document.getElementById("modal14-title").innerHTML="Preset import only allowed when WARBL is connected";

		document.getElementById("modal14-ok").style.opacity = 1.0;

		modal(14);

		return;

	}

	// For versioning preset files
	var maxSupportedPresetVersion = 1;

	// How long to wait in msec between sending commands
	var delay = 5;
     
    //debugger;

    // Make sure there is a file selected
    if (context.files && (context.files.length != 0)){

		// Show the import modal
		var fname = context.files[0].name;
		fname = fname.replace(".warbl","");
		fname = fname.replace(".WARBL","");

		document.getElementById("modal14-title").innerHTML="Importing: "+context.files[0].name;

		// Disable the OK button until after the import is complete
		document.getElementById("modal14-ok").style.opacity = 0.001;

		modal(14);

	  	var reader = new FileReader();

	    reader.onload = async function(){ 

	    	//debugger;

	    	// Parse the file
	    	try{

	    		var theImportObject = JSON.parse(reader.result);

	    	} catch(e){

				document.getElementById("modal14-title").innerHTML="Error: File is not a WARBL Preset";
				return;

	    	}

	    	// Sanity check the import file

	    	if (!theImportObject){

				document.getElementById("modal14-title").innerHTML="Error: File is not a WARBL Preset";
				return;

	    	}

	    	if ((!theImportObject.signature) || (theImportObject.signature != "WARBL")){

				document.getElementById("modal14-title").innerHTML="Error: File is not a WARBL Preset";
				return;

	    	}

	    	if (!theImportObject.version){

				document.getElementById("modal14-title").innerHTML="Error: File is not a WARBL Preset";
				return;

			}

			if (!theImportObject.custom_build){

				document.getElementById("modal14-title").innerHTML="Error: WARBL Preset Version "+theImportObject.version+" not supported by this version of the configuration tool";
				return;

			}

	    	if (theImportObject.version > maxSupportedPresetVersion){

				document.getElementById("modal14-title").innerHTML="Error: WARBL Preset Version "+theImportObject.version+" not supported by this version of the configuration tool";
				return;

			}

			if (theImportObject.custom_build != 1){ //BARBARO Build

				document.getElementById("modal14-title").innerHTML="Error: WARBL Preset Version "+theImportObject.version+" not supported by this version of the configuration tool";
				return;

			}
			//debugger;
			if (!confirm("These settings will be loaded into the currently selected preset.\nYou will have to save it them manually, if you wish so.")) {
				modalclose(14);
				$('#importPreset').val('');
				return;
			}
	    	// Send the data to the WARBL
	    	var nMessages = theImportObject.messages.length;

	    	var i;
	    	var byte0, byte1, byte2;

	    	// Send the firmware version
    		// byte0 = theImportObject.messages[0][0];
    		// byte1 = theImportObject.messages[0][1];
    		// byte2 = theImportObject.messages[0][2];
	    	// sendToWARBL(byte1, byte2);
	    	
    		// Synchronous sleep to allow command processing
    		// await sleep(delay);

			//
	    	// Determine the current instrument that was set at export
	    	//
	  		// var exportedInstrument =  theImportObject.messages[10][2] - 60;

	  		//
	  		// Determine the current target instrument tab
	  		//
	  		// var targetInstrument = 30 + currentPreset;

	  		// console.log("exportedInstrument = "+exportedInstrument);
	  		// console.log("targetInstrument = "+(targetInstrument-30));
	  		
	  		//
	  		// Determine the current target key shift
	  		//
	  		// var targetKey = 111 + currentPreset;

	    	// send the fingering and key shift for the current tab only
			// switch (exportedInstrument){

			// 	case 0:

		    // 		byte0 = theImportObject.messages[1][0];
		    // 		byte1 = theImportObject.messages[1][2];
		    // 		byte2 = targetInstrument;

			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);
		    		
		    // 		byte0 = theImportObject.messages[2][0];
		    // 		byte1 = theImportObject.messages[2][1];
		    // 		byte2 = theImportObject.messages[2][2];
			    	
			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);
		    		
		    // 		byte0 = theImportObject.messages[3][0];
		    // 		byte1 = targetKey;		
		    // 		byte2 = theImportObject.messages[3][2];
			    	
			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);
					
			// 		break;

			// 	case 1:

		    // 		byte0 = theImportObject.messages[4][0];
		    // 		byte1 = theImportObject.messages[4][1];
		    // 		byte2 = targetInstrument;

			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);
		    		
		    // 		byte0 = theImportObject.messages[5][0];
		    // 		byte1 = theImportObject.messages[5][1];
		    // 		byte2 = theImportObject.messages[5][2];
			    	
			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);
		    		
		    // 		byte0 = theImportObject.messages[6][0];
		    // 		byte1 = targetKey;		
		    // 		byte2 = theImportObject.messages[6][2];
			    	
			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);

			// 		break;

			// 	case 2:

		    // 		byte0 = theImportObject.messages[7][0];
		    // 		byte1 = theImportObject.messages[7][1];
		    // 		byte2 = targetInstrument;

			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);
		    		
		    // 		byte0 = theImportObject.messages[8][0];
		    // 		byte1 = theImportObject.messages[8][1];
		    // 		byte2 = theImportObject.messages[8][2];
			    	
			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);
		    		
		    // 		byte0 = theImportObject.messages[9][0];
		    // 		byte1 = targetKey;		
		    // 		byte2 = theImportObject.messages[9][2];
			    	
			//     	sendToWARBL(byte1, byte2);

		    // 		// Synchronous sleep to allow command processing
		    // 		await sleep(delay);

			// 		break;

			// }
	    	
			// Skip command 10 - Selected instrument at save time

	    	// Skip command 11 - Sets default

	    	// Send the rest of the data

	    	for (i=0;i<nMessages;++i){

	    		byte0 = theImportObject.messages[i][0];
	    		byte1 = theImportObject.messages[i][1];
	    		byte2 = theImportObject.messages[i][2];

				//console.log("Sending Message #"+i+":"+byte0+" "+byte1+" "+byte2);

	    		sendToWARBL(byte1, byte2);

	    		// Synchronous sleep to allow command processing
	    		await sleep(delay);

	    	}

	    	// Refresh the UI after a short delay by putting the device back in communications mode
	    	setTimeout(function(){

	    		//console.log("refreshing UI");

				sendToWARBL(MIDI_SLOT_02, MIDI_SEND_SETTINGS);

				// Show the import complete modal
				document.getElementById("modal14-title").innerHTML="Preset Import Complete!";

				// Show the OK button until after the import is complete
				document.getElementById("modal14-ok").style.opacity = 1.0;

				// Clear the file input selector after a delay
				setTimeout(function(){

					$('#importPreset').val('');

				},1000);

	    	},500);

	    } 

    	reader.readAsText(context.files[0]);

    } else {
		console.log("Invalid File");
		document.getElementById("modal14-title").innerHTML="Error: File is not a WARBL Preset";
		return;
	}

}

//
// Export the current WARBL preset to a file
//
function exportPreset(){

	//console.log("exportPreset");

	// Put up error message if WARBL is not connected
	if (!WARBLout){
		
		document.getElementById("modal14-title").innerHTML="Preset export only allowed when WARBL is connected";

		document.getElementById("modal14-ok").style.opacity = 1.0;

		modal(14);

		return;

	}

	var nMessages = 0;


	// Initialize the export structure
	var theExportObject = {
		signature:"WARBL",  // Used to sanity check imports
		version:"1",			// In case we need to version the export structure
		custom_build:"1",			// In case we need to version the export structure
		messages:[]			// Preset messages
	};

	// 
	// Download the exported preset to a file
	//
	function downloadPreset(content, filename, contentType){

		const a = document.createElement('a');

		const file = new Blob([content], {type: contentType});

		a.href= URL.createObjectURL(file);
		a.download = filename;
		a.click();

		URL.revokeObjectURL(a.href);

		// Tell the user that the export is complete
		document.getElementById("modal14-title").innerHTML="Preset Export Complete!";
		
		// Make sure the OK button is showing
		document.getElementById("modal14-ok").style.opacity = 1.0;
		
		modal(14);

	};

	//
	// Export message proxy
	//
	function exportMessageHandler(byte0,byte1,byte2){

		if (!exportingPhase) {
			
			//debugger;

			console.log("exportMessageHandler: All messages received (" + nMessages + ")");

			// Stringify the messsages array
			var theExportObjectJSON = JSON.stringify(theExportObject);

			// Clear the global export proxy
			gExportProxy = null;

			// Do the preset file export
			downloadPreset(theExportObjectJSON,"WARBL_Preset.warbl","text/plain");

			return;

		}

		//console.log("Message #"+nMessages+":"+byte0+" "+byte1+" "+byte2);

		// Add the message to the message array
		theExportObject.messages.push([byte0,byte1,byte2]);

		nMessages++;


	}


	// Setup the global export message proxy
	gExportProxy = exportMessageHandler;

	exportingPhase = true;
	nMessages = 0;

	// Tell WARBL to dump settings for current Preset
	// Received bytes will be forwarded to the export message handler instead
	sendToWARBL(MIDI_SLOT_02, MIDI_DUMP_SETTINGS_CURRENT); 

}

//
// Capture the incoming pressure
//
function capturePressure(val){
	
	//console.log("capturePressure: "+val);

	gCurrentPressure = val;

}

//
// Graph the incoming pressure
//
function graphPressure(){

	//console.log("graphPressure: "+gCurrentPressure);
	//debugger;

	// Drop the last element of the array
	gPressureReadings.pop();
	
	// Add the new value to the front of the array
	gPressureReadings.unshift(gCurrentPressure);

	//debugger;

	// Clear the graph
   	$("#d3PressureGraph").empty();

	// set the dimensions and margins of the graph
	var margin = {top: 10, right: 10, bottom: 100, left: 50},
	    width = 390,
	    height = 320 - margin.top - margin.bottom;

	// append the svg object to the body of the page
	var svg = d3.select("#d3PressureGraph")
	  .append("svg")
	    .attr("width", width + margin.left + margin.right)
	    .attr("height", height + margin.top + margin.bottom)
	  // translate this svg element to leave some margin.
	  .append("g")
	    .attr("transform", "translate(" + margin.left + "," + margin.top + ")");

	// X scale and Axis
	var x = d3.scaleLinear()
	    .domain([0, width])       // This is the min and the max of the data
	    .range([0, width]);   
	
	svg.append('g')
	  .attr("transform", "translate(0," + height + ")")
	  .call(d3.axisBottom(x).tickSize(0).tickFormat(""));

	// Y scale and Axis
	var y = d3.scaleLinear()
	    .domain([0, gMaxPressure])  // This is the min and the max of the data: 0 to gMaxPressure
	    .range([height, 0]); 

	svg.append('g')
	  .call(d3.axisLeft(y));

	// text label for the x axis
	svg.append("text")
	      .attr("y", (height + 4))
	      .attr("x",(width / 2) - (margin.left/2) + 10)
	      .attr("dy", "1em")
	      .style("text-anchor", "middle")
	      .style("fill","white")
	      .text("Time");      

	// text label for the y axis
	svg.append("text")
	      .attr("transform", "rotate(-90)")
	      .attr("y", 0 - (margin.left - 5))
	      .attr("x",0 - (height / 2))
	      .attr("dy", "1em")
	      .style("text-anchor", "middle")
	      .style("fill","white")
	      .text("Inches of H₂O");      

	// X scale will use the index of our data
	var xScale = d3.scaleLinear()
	    .domain([0, gNPressureReadings-1]) // input
	    .range([0, width]); // output

	// Y scale will use the pressure range from 0 - gMaxPressure 
	var yScale = d3.scaleLinear()
	    .domain([0, gMaxPressure]) // input 
	    .range([height, 0]); // output 

	// d3's line generator
	var line = d3.line()
	    .x(function(d, i) { return xScale(i); }) // set the x values for the line generator
	    .y(function(d) { return yScale(d.y); }) // set the y values for the line generator 
	    .curve(d3.curveMonotoneX); // apply smoothing to the line

	// An array of objects of length N. Each object has key -> value pair, the key being "y" and the value is a pressure reading
	var dataset = d3.range(gNPressureReadings).map(function(d) { return {"y":gPressureReadings[d] } });

	// Append the path, bind the data, and call the line generator 
	svg.append("path")
	    .datum(dataset) // Binds data to the line 
	    .attr("class", "pressureline") // Assign a class for styling 
	    .attr("d", line); // Calls the line generator 
}

//
// Start the pressure graph
//
function startPressureGraph(){

    //console.log("startPressureGraph");

    // Shunt the pressure messages to the graphing routine
    gPressureGraphEnabled = true;

    // Reset the pressure capture
    gCurrentPressure = 0.0;

    // Clear the pressure capture array
    var i;
    gPressureReadings = [];
    for (i=0;i<gNPressureReadings;++i){
    	gPressureReadings.push(0.0);
    }

    // Setup the graph redraw interval timer
    gGraphInterval = setInterval(graphPressure,100);

}

//
// Stop the pressure graph
//
function stopPressureGraph(){

	//console.log("stopPressureGraph");

	// Stop shunting the pressure messages to the graphing routine
    gPressureGraphEnabled = false;

    // Stop the interval timer
    clearInterval(gGraphInterval);

   	$("#d3PressureGraph").empty();

	return;
}

