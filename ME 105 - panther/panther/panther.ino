/**
 * Christopher Simon
 * Midterm 2: Panther
 */
#include <Keypad.h>

void checkHit(int);
void playPink();
void showScore();

// The table of keypad buttons
const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
	{'1','2','3','A'},
	{'4','5','6','B'},
	{'7','8','9','C'},
	{'*','0','#','D'}
};
// Create the keypad indicating which and how many keys are on the rows and columns
byte rowPins[ROWS] = {9, 8, 7, 6};
byte colPins[COLS] = {5, 4, 3, 2};
Keypad pad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// The buzzer pin
const int buzPin = 10;
// Use 0 for the first ledPin index to create a base one array
int ledPin[] = {0, 11, 12, 13, 16, 17, 18, 19, 15};

// Keep track of when the game starts,
// the current light that's on,
// the interval of changing from each light,
// the number of panthers hit and the score
int gameStart = 0;
unsigned long startTime	= 0;
unsigned long currentTime = 0;
int currentLight = 0;
unsigned long delta = 1000;
int hit = 0;
int score = 0;

void setup(){
	// Start the serial COM port
	// so that data can sent and received
	// via the COM port that the Arduino is connected to
	Serial.begin(9600);
	// Set each ledPin as an output pin
	for(int i = 1; i <= 8; i++) {
		pinMode(ledPin[i], OUTPUT);
	}
}

void loop(){
	// Get the current key that is pressed.
	// NO_KEY is returned if no key is currently
	// being pressed
	char key = pad.getKey();
	
	// If a key is currently being pressed down
	if(key != NO_KEY) {
		// Print out what key is being pressed
		Serial.println(key);
		// Depending on the key pressed
		// Either check if the led corresponding
		// to that key is on, as to check for a hit
		// Or start or end the game.
		switch(key) {
			case '6': { 
				checkHit(1);
				break;
			}
			case '3': { 
				checkHit(2);
				break;
			}
			case '2': {
				checkHit(3);
				break;
			}
			case '1': {
				checkHit(4);
				break;
			}
			case '4': { 
				checkHit(5);
				break;
			}
			case '7': { 
				checkHit(6);
				break;
			}
			case '8': { 
				checkHit(7);
				break;
			}
			case '9': { 
				checkHit(8);
				break;
			}
			case 'A': {
				// Start the game
				// Turn the current light off
				digitalWrite(ledPin[currentLight], LOW);
				score = 0;
				gameStart = 1;
				delta = 1000;
				currentLight = 1;
				digitalWrite(ledPin[currentLight], HIGH);
				break;
			}
			case 'D': {
				// End the game
				gameStart = 0;
				digitalWrite(ledPin[currentLight], LOW);
				showScore();
				break;
			}
			// Testing: Light up or turn off all the pins
			case '*': {
				// Light up all the pins
				for(int i = 1; i <= 8; i++) {
					digitalWrite(ledPin[i], HIGH);
				}
				break;
			}
			case '0': {
				// Turn all the pins off
				for(int i = 1; i <= 8; i++) {
					digitalWrite(ledPin[i], LOW);
				}
				break;
			}
			default: break;
		}
	} else if(gameStart == 1){ // No Key is pressed
		// Get the currentTime according to the internal clock of the Arduino.
		// This internal clock works through the 16MHz crystal oscillator
		currentTime = millis();
		// The actual time since the start of the game
		// is retrieved by subtracting the startingTime
		// minus the time that's passed since then.
		// This will give the time elapsed since the
		// start of the game
		unsigned long elapsedTime = currentTime - startTime;
		// On every interval, delta, that passes since the last startTime
		if(elapsedTime >= delta) {
			// Turn off the current light.
			// We will be switching to the next one
			digitalWrite(ledPin[currentLight], LOW);
			// The light was not hit on time.
			// Indicate that the user did not press the button
			// while this light was on
			hit = 0;
			// If the next light has reached the bound of the array,
			// wrap around to the first light in the array.
			// Also decrease the delta interval every time
			// each of the lights have been lit up in a full circle
			if(++currentLight > 8) {
				currentLight = 1;
				// This decreases the delta time slightly,
				// making the interval between switching
				// lights faster
				delta = (delta*90)/100;
			}
			// Light up the next light and play the game for that light
			digitalWrite(ledPin[currentLight], HIGH);
			playPink();
			// Update the startTime so that the timeElapsed
			// since the previous delta starts back at 0 and
			// works it's way up back to the delta value again
			startTime = currentTime;
		}
	}
}

/**
 * Checks if the light specified can be hit,
 * depending on whether it is currently on and
 * if is not already hit
 * @param int lightIndex The light being checked for
 */
void checkHit(int lightIndex) {
	if(lightIndex == currentLight /*&& hit == 0*/) {
		// The light has successfully been hit.
		// Indicate this while turning off the
		// light playing a tone from the speaker
		// momentarily pausing the game and increasing
		// the user's score by 1 point
		hit = 1;
		digitalWrite(ledPin[currentLight], LOW);
		tone(buzPin, 262, 25);
		delay(25);
		score++;
	}
}

// Plays the game with the currentLight
void playPink() {
	// Depending on the currentLight that is lit up
	// play different tones and pause to give the user
	// a chance to hit it before switching to the next
	// light through the delta interval
	// that is lit up
	switch(currentLight) {
		case 1:
			tone(buzPin, 1109, 25);
			delay(25);
			tone(buzPin, 1175, 75);
			delay(75);
		case 2:
			tone(buzPin, 1319, 25);
			delay(25);
			tone(buzPin, 1397, 75);
			delay(75);
		case 3:
			tone(buzPin, 1109, 25);
			delay(25);
			tone(buzPin, 1175, 75);
			delay(75);
		case 4:
			tone(buzPin, 1319, 25);
			delay(25);
			tone(buzPin, 1397, 75);
			delay(75);
		case 5:
			tone(buzPin, 1865, 25);
			delay(25);
			tone(buzPin, 1760, 75);
			delay(75);
		case 6:
			tone(buzPin, 1175, 25);
			delay(25);
			tone(buzPin, 1397, 75);
			delay(75);
		case 7:
			tone(buzPin, 1760, 25);
			delay(25);
			tone(buzPin, 1661, 75);
			delay(75);
		case 8:
			tone(buzPin, 1760, 25);
			delay(25);
			tone(buzPin, 1661, 75);
			delay(75);
		default: break;
	}
}

void showScore() {
	delay(500);
	// Count up the number of panthers caught, one at a time
	for(int i = 0; i <= score; i++) {
		digitalWrite(ledPin[1], HIGH);
		tone(buzPin, 262+ (i * 100), 50);
		delay(100);
		digitalWrite(ledPin[1], LOW);
		delay(250);
	}
}
