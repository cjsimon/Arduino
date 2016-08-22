/**
 * IR Remote
 * Plays sounds based on ir remote input
 */

// Includes
#include <IRremote.h>
#include <NewTone.h>

// HEX IR Constants
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

// Function prototypes
int parseRemoteDigit(int);
void playMusic();

// Pin defenitions
#define RECV_PIN	2
#define L1_PIN		8
#define L2_PIN		9
#define BUZ_PIN		7

// Set up the reciever and decoder
IRrecv irrecv(RECV_PIN);
decode_results results;

// Frequency values
int freq[] = {
	0, 1047, 1175, 1319, 1397,
	1568, 1760, 1976, 2093, 2349
};

int duration            = 500;
int isFirstDigitZero    = 0;
int isLight1On          = 0;
int isLight2On          = 0;
int areBothLightsOn     = 0;

// Setup
void setup() {
	// Start the serial connection
	Serial.begin(9600);
	// Set the leds to OUTPUT
	pinMode(L1_PIN, OUTPUT);
	pinMode(L2_PIN, OUTPUT);
	// Enable the IRreceiver
	irrecv.enableIRIn();
}

// Loop
void loop() {
	// The current keyVal
	int keyVal = -1;
	
	// If results exist
	if(irrecv.decode(&results) != 0) {
		// DEBUG: Print the results in HEX
		Serial.println(results.value, HEX);
		// Set the current keyVal to the parsed result value
		keyVal = parseRemoteDigit(results.value);
		
		if(keyVal == -1) {
			// keyVal is not a pressed button
		} else if(keyVal == 0) {
			// Is this the first zero?
			if(isFirstDigitZero != 0) {
				// Seconde Zero. Indicate so
				isFirstDigitZero = 0;
			} else {
				// First Zero. Indicate so
				isFirstDigitZero = 1;
			}
		} else if(isFirstDigitZero == 1) { // Lights
			if(keyVal == 1) { // First Light
				if(isLight1On == 1) {
					digitalWrite(L1_PIN, LOW);
				}
				isLight1On = 0;
				if(isLight2On == 0) { // if Light 2 is off
					areBothLightsOn = 0;
				} else { // Light 1 Currently Off
					digitalWrite(L1_PIN, HIGH);
					isLight1On = 1;
					if(isLight2On != 0) { // Light 2 already on
						areBothLightsOn = 1;
					}
				}
			} else if(keyVal == 2) {
				if(isLight2On != 0) {
					digitalWrite(L2_PIN, LOW);
					isLight2On = 0;
					if(isLight1On == 0) {
						areBothLightsOn = 0;
					}
				} else {
					digitalWrite(L2_PIN, HIGH);
					isLight2On = 1;
					if(isLight1On == 1) {
						areBothLightsOn = 1;
					}
				}
			} else if(keyVal == 3) {
				if(areBothLightsOn != 0) {
					digitalWrite(L1_PIN, LOW);
					digitalWrite(L2_PIN, LOW);
					isLight1On = 0;
					isLight2On = 0;
					areBothLightsOn = 0;
				} else {
					digitalWrite(L1_PIN, HIGH);
					digitalWrite(L2_PIN, HIGH);
					isLight1On = 1;
					isLight2On = 1;
					areBothLightsOn = 1;
				}
			} else if(keyVal == 4) {
				playMusic();
			}
			isFirstDigitZero = 0;
		} else {
			NewTone(BUZ_PIN, freq[keyVal], duration);
		}
					
		// Continue to receive ir readings
		irrecv.resume();
	}
	delay(100);
}

// Write a parseRemoteDigit function to parse the remote control value.
// The function input is an integer, the remote control button value after decode.
// The function output is the integer digit of the remote button.  -1 for buttons not 0-9.
int parseRemoteDigit(int hexCode)
{
	int buttonVal = -1;
	switch(hexCode)
	{
		case ZERO:	buttonVal = 0;	break;
		case ONE:	buttonVal = 1;	break;
		case TWO:	buttonVal = 2;	break;
		case THREE: buttonVal = 3;	break;
		case FOUR:	buttonVal = 4;	break;
		case FIVE:	buttonVal = 5;	break;
		case SIX:	buttonVal = 6;	break;
		case SEVEN: buttonVal = 7;	break;
		case EIGHT: buttonVal = 8;	break;
		case NINE:	buttonVal = 9;	break;
   }  // end of switch
   return buttonVal;
}
