/**
 * Christopher Simon
 * Homework 4 - Arduino Music
 */

#include <NewTone.h>
#include "pitches.h"
#include "song.h"

#define SPEAKER 7
#define LEDPIN8	8
#define LEDPIN9	9

void setup() {
	// The speaker is an output from the arduino,
	// meaning that the board will be supplying output
	// voltage to the devices connected to that pin
	pinMode(SPEAKER, OUTPUT);
	
	// Get the number of notes in the song
	int musicLength = (sizeof(*music) / sizeof(int));
	// Iterate through each note of the song
	for(int n = 0; n < musicLength; n++) {
		// Get the current note and duration
		int note = music[n][MUSIC_NOTE];
		int duration = 1000/music[n][MUSIC_DURATION];
		// Play the note using it's corresponding duration
		NewTone(SPEAKER, note, duration);
		// Pause while the tone plays in the background
		delay((duration * 4) / 3);
		noNewTone(SPEAKER);
	}
}

void loop() {
	// Toggle both leds to alternitivly
	// turn them on and off after 500ms
	digitalWrite(LEDPIN8, HIGH);
	digitalWrite(LEDPIN9, LOW);
	delay(500);
	digitalWrite(LEDPIN8, LOW);
	digitalWrite(LEDPIN9, HIGH);
	delay(500);
}
