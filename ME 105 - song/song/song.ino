/**
 * Christopher Simon
 * Homework 4 - Arduino Music
 */
#include "pitches.h"

// Pins
#define SPEAKER 7
#define LEDPIN1 8
#define LEDPIN2 9
// The hardcoded size of the melody
#define SIZE	8

// The notes of the song
int melody[SIZE] = { NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, NOTE_PS, NOTE_B3, NOTE_C4 };

// Note durations: 4 = quarter note, 8 = eighth note
int time[SIZE] = { 8, 4, 4, 8, 4, 4, 8, 4 };

void setup()
{
	// Play each note
	for(int i = 0; i < SIZE; i++)
	{
		int length = 1000 / time[i];
		// Play the current melody
		tone(SPEAKER, melody[i], length);
		// The tone function can also be used to light up leds
		tone(LEDPIN1, melody[i], length);
		tone(LEDPIN2, melody[i], length);
		
		// Pause the arduino to play the note
		delay(length * 1.30);
		
		// Stop the sound from the speaker
		// Also stop the leds
		noTone(SPEAKER);
		noTone(LEDPIN1);
		noTone(LEDPIN2);
	}
}

void loop()
{
	digitalWrite(LEDPIN1, HIGH);
	digitalWrite(LEDPIN2, LOW);
	delay(500);
	digitalWrite(LEDPIN1, LOW);
	digitalWrite(LEDPIN2, HIGH);
	delay(500);
}
