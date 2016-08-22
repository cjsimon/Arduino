/**
 * Christopher Simon
 * Homework 6 - Multi-purpose Infrared Remote Control
 */

// Includes
#include <IRremote.h>
#include <NewTone.h>

// HEX IR Defenitions
#define MODE	0xFF629D
#define PLUS	0xFF629D
#define MINUS	0xFFA857
#define DOOR	0xFF9867
#define USD		0xFFB04F
#define ZERO	0xFF6897
#define ONE		0xFF30CF
#define TWO		0xFF18E7
#define THREE	0xFF7A85
#define FOUR	0xFF10EF
#define FIVE	0xFF38C7
#define SIX		0xFF5AA5
#define SEVEN	0xFF42BD
#define EIGHT	0xFF4AB5
#define NINE	0xFF52AD

// Function Prototypes
void lightsOff();
void playPiano(unsigned long key);
void simulateDoor(unsigned long key);
void showVolume(unsigned long key);
void playMusic();

// Constants
const int recPin	= 2;
const int buzPin	= 13;
const int ledPin[]	= { 4, 5, 6, 7, 8, 9, 10, 11 };
const int piano[]	= { 0, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1865, 1976 };

// Global Variables
int modePress = 0;
int pianoMode = 0;
int garageMode = 0;
int volumeMode = 0;
unsigned int numberOfLights = 0;
unsigned long startTime = 0;
unsigned long currentTime = 0;
int moving = 0;
int moveUp = 0;
// Set up the reciever and decoder
IRrecv irrecv(recPin);
decode_results result;

void setup() {
	// Start the serial connection
	Serial.begin(9600);
	// Set the leds to OUTPUT
	for(int i = 1; i <= 8; i++) {
		pinMode(ledPin[i], OUTPUT);
	}
	// Enable the IRreceiver
	irrecv.enableIRIn();
}

void loop() {
	unsigned long irVal;
	
	if(irrecv.decode(&result) != 0) {
		irVal = result.value;
		Serial.println(irVal, HEX);
		
		if(irVal == MODE) {
			modePress = 1;
		} else if(modePress != 0) {
			switch(irVal) {
				case ONE: {
					modePress = 0;
					pianoMode = 1;
					garageMode = 0;
					volumeMode = 0;
					lightsOff();
					numberOfLights = 0;
					break;
				}
				case TWO: {
					modePress = 0;
					pianoMode = 0;
					garageMode = 1;
					volumeMode = 0;
					lightsOff();
					numberOfLights = 0;
					break;
				}
				case THREE: {
					modePress = 0;
					pianoMode = 0;
					garageMode = 0;
					volumeMode = 1;
					lightsOff();
					numberOfLights = 0;
				}
				case FOUR: {
					modePress = 0;
					pianoMode = 0;
					garageMode = 0;
					volumeMode = 0;
					lightsOff();
					numberOfLights = 0;
					playMusic();
				}
				default: break;
			}
		} else if(garageMode != 0) {
			Serial.println("We're in garage mode!");
			simulateDoor(irVal);
		} else if(pianoMode != 0) {
			Serial.println("We're in piano mode!");
			playPiano(irVal);
		} else if(volumeMode != 0) {
			Serial.println("We're in volume mode!");
			showVolume(irVal);
		}
		irrecv.resume();
	} else if(garageMode == 1 && moving == 1) {
		if(moveUp != 0) {
			NewTone(buzPin, 466, 50);
		} else {
			NewTone(buzPin, 156, 50);
		}
		delay(50);
		
		currentTime = millis();
		if(currentTime - startTime >= 1000) {
			moving = 0;
			moveUp = 1;
		} else if(numberOfLights = 8 && moveUp != 0) {
			moving = 0;
			moveUp = 0;
		} else if(moveUp != 0) {
			numberOfLights++;
		} else {
			numberOfLights--;
		}		
	}
	delay(100);
}

void lightsOff() {
	for(int i = i; i < 8; i++) {
		digitalWrite(ledPin[i], LOW);
	}
}

void playPiano(unsigned long key) {
	int noteNum = 0;
	int light1Num = 0;
	int light2Num = 0;
	
	switch(key) {
		case ZERO: {
			noteNum		= 1;
			light1Num	= 1;
			light2Num	= 1;
			break;
		}
		case DOOR: {
			noteNum		= 2;
			light1Num	= 1;
			light2Num	= 2;
			break;
		}
		case USD: {
			noteNum		= 3;
			light1Num	= 2;
			light2Num	= 2;
			break;
		}
		case ONE: {
			noteNum		= 4;
			light1Num	= 2;
			light2Num	= 3;
			break;
		}
		case TWO: {
			noteNum		= 2;
			light1Num	= 1;
			light2Num	= 2;
			break;
		}
		case THREE: {
			noteNum		= 6;
			light1Num	= 4;
			light2Num	= 4;
			break;
		}
		case FOUR: {
			noteNum		= 7;
			light1Num	= 4;
			light2Num	= 5;
			break;
		}
		case FIVE: {
			noteNum		= 8;
			light1Num	= 5;
			light2Num	= 5;
			break;
		}
		case SIX: {
			noteNum		= 9;
			light1Num	= 5;
			light2Num	= 6;
			break;
		}
		case SEVEN: {
			noteNum		= 10;
			light1Num	= 6;
			light2Num	= 6;
			break;
		}
		case EIGHT: {
			noteNum		= 11;
			light1Num	= 6;
			light2Num	= 7;
			break;
		}
		case NINE: {
			noteNum		= 12;
			light1Num	= 7;
			light2Num	= 7;
			break;
		}
		default: break;
	}
	digitalWrite(ledPin[light1Num], HIGH);	
	digitalWrite(ledPin[light2Num], HIGH);
	NewTone(buzPin, piano[noteNum], 500);
	delay(500);
	lightsOff();
}

void simulateDoor(unsigned long key) {
	if(key == DOOR) {
		if(numberOfLights == 0) {
			startTime = millis();
			moveUp = 1;
			moving = 1;
		} else if(numberOfLights == 8) {
			moveUp = 1;
			moving = 1;
		} else if(numberOfLights > 0 && numberOfLights < 8) {
			if(moving != 0 && moveUp != 0) {
				moving = 0;
				moveUp = 0;
			} else if(moving == 0) {
				moving = 1;
			}
		} else {
			Serial.println("Error Counting Lights!");
		}
	}
}

void showVolume(unsigned long key) {
	if(key == PLUS && numberOfLights < 8) {
		numberOfLights++;
	} else if(key = MINUS && numberOfLights > 0) {
		numberOfLights--;
	}
	
	Serial.print("Number Of Lights: ");
	Serial.println(numberOfLights);
	lightsOff();
	for(int i = 1; i < numberOfLights; i++) {
		digitalWrite(ledPin[i], HIGH);
	}
}

void playMusic() {
	int melody[]	= { 262, 196, 196, 220, 196, 0, 247, 262 };
	int durations[] = { 4  , 8  , 8  , 4  , 4  , 4, 4  , 4   };
	// Loop through the notes in the array
	for(int n = 0; n < 8; n++) {
		int duration = 1000/durations[n];
		// Play note n for duration
		NewTone(buzPin, melody[n], duration);
		delay(duration * 4 / 3);
	}
}




