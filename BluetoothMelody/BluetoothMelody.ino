#include "pitches.h"

//durations: 4 = quarter note, 8 = eighth note, etc.:

int speaker = 13;
int ledPin = 12;
int data = 0;

void setup() {
    pinMode(ledPin, OUTPUT);
    digitalWrite(ledPin, LOW);
    Serial.begin(9600);
    
    int totalNotes = 8;
    //For each note
    for(int currentNote = 0; currentNote < totalNotes; currentNote++) {
        // to calculate the note duration, take one second 
        // divided by the note type.
        //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
        int noteDuration = 1000/noteDurations[currentNote];
        tone(speaker, melody[currentNote], noteDuration);
        
        // to distinguish the notes, set a minimum time between them.
        // the note's duration + 30% seems to work well:
        int pause = noteDuration * 1.30;
        delay(pause);
        // stop the tone playing:
        noTone(speaker);
    }
}

void loop() {
    Read the next two characters from the stream
    if(Serial.available() > 1) {
        int pitch = Serial.read();
        int duration = Serial.read();
        tone(speaker, state, 1000/duration);
    }
}
