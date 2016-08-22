/**
 * Christopher Simon
 * ENGR 50 SPR 2016
 * HW 5 - FM Radio
 */
void clearSegments();
void displayZero();
void displayOne();
void displayTwo();
void displayThree();
void displayFour();
void displayFive();
void displaySix();
void displaySeven();
void displayEight();
void displayNine();
void showDecimal();
void enableDigit(int); 
void showNumber(int);
void showRadio(int);

#define aPin      5
#define bPin      7
#define cPin      9
#define dPin      11
#define ePin      12
#define fPin      6
#define gPin      8
#define dpPin     10
#define digit1Pin 1
#define digit2Pin 2
#define digit3Pin 3
#define digit4Pin 4
#define potPin    A0
#define ledPin    13

// Define the radio stations to search for
int stations[] = {889, 909, 925, 969, 1025, 1079};

// Define the number of samples to keep track of. The higher the number,
// the more the readings will be smoothed, but the slower the output will
// respond to the input. Using a constant rather than a normal variable lets
// use this value to determine the size of the readings array.
const int numReadings = 10;

// The readings from the analog input
int readings[numReadings];
// The index of the current reading
int readIndex = 0;
// The total and average of the readings
int total = 0;
int average = 0;

void setup() {
	pinMode(digit1Pin, OUTPUT);
	pinMode(digit2Pin, OUTPUT);
	pinMode(digit3Pin, OUTPUT);
	pinMode(digit4Pin, OUTPUT);
	pinMode(aPin, OUTPUT);
	pinMode(bPin, OUTPUT);
	pinMode(cPin, OUTPUT);
	pinMode(dPin, OUTPUT);
	pinMode(ePin, OUTPUT);
	pinMode(fPin, OUTPUT);
	pinMode(gPin, OUTPUT);
	pinMode(dpPin, OUTPUT);
	pinMode(ledPin, OUTPUT);
	
  	// Initialize all the readings to 0
	for (int thisReading = 0; thisReading < numReadings; thisReading++) {
		readings[thisReading] = 0;
	}
	
	Serial.begin(9600);
}

void loop() {
	int i;
	unsigned int freq = 0;
	int lightOn = 0;
	int timeDivisionCounter = 100;

	// Read the value of the knob
	// The freq is calculated as a number between 875 and 1080
	int val = analogRead(potPin);
	
	// Subtract the last
	total -= readings[readIndex];
	// Get the sensor value
	readings[readIndex] = val;
	// Add the currentReading to the total
	total += readings[readIndex];
	// Advance to the next position in the array
	readIndex++;
	
	// Wrap to the first element if at the end
	if (readIndex >= numReadings) readIndex = 0;
	
	// Get the average reading
	average = total / numReadings;

	// Map the average value to a frequency value between 889 and 1085
	//freq = (((val * 205) / 1023) + 875);
	freq = map(average, 0, 1023, 889, 1085);
	Serial.println(freq);
	
	// Check if the freq is one of the stations
	for(int i = 0; i < 6; i++) {
		if(freq == stations[i]) {
			lightOn++;
			break;
		}
	}

	// Turn the light on if a station is found
	// Otherwise turn it of
	if(lightOn != 0) {
		digitalWrite(ledPin, HIGH);
	} else {
		digitalWrite(ledPin, LOW);
	}

	// Show the frequency number on the display
	for(int i = 0; i < timeDivisionCounter; i++) {
		showRadio(freq);
	}
}

// Clears the display
void clearSegments() {
	digitalWrite(aPin, LOW);
	digitalWrite(bPin, LOW);
	digitalWrite(cPin, LOW);
	digitalWrite(dPin, LOW);
	digitalWrite(ePin, LOW);
	digitalWrite(fPin, LOW);
	digitalWrite(gPin, LOW);
	digitalWrite(dpPin, LOW);
}

// Display each number using the corresponding segments
void displayZero() {
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, HIGH);
	digitalWrite(ePin, HIGH);
	digitalWrite(fPin, HIGH);
	digitalWrite(gPin, LOW);
	digitalWrite(dpPin, LOW);
}
void displayOne() {
	digitalWrite(aPin, LOW);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, LOW);
	digitalWrite(ePin, LOW);
	digitalWrite(fPin, LOW);
	digitalWrite(gPin, LOW);
	digitalWrite(dpPin, LOW);
}
void displayTwo()
{
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, LOW);
	digitalWrite(dPin, HIGH);
	digitalWrite(ePin, HIGH);
	digitalWrite(fPin, LOW);
	digitalWrite(gPin, HIGH);
	digitalWrite(dpPin, LOW);
}
void displayThree()
{
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, HIGH);
	digitalWrite(ePin, LOW);
	digitalWrite(fPin, LOW);
	digitalWrite(gPin, HIGH);
	digitalWrite(dpPin, LOW);
}
void displayFour()
{
	digitalWrite(aPin, LOW);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, LOW);
	digitalWrite(ePin, LOW);
	digitalWrite(fPin, HIGH);
	digitalWrite(gPin, HIGH);
	digitalWrite(dpPin, LOW);
}
void displayFive()
{
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, LOW);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, HIGH);
	digitalWrite(ePin, LOW);
	digitalWrite(fPin, HIGH);
	digitalWrite(gPin, HIGH);
	digitalWrite(dpPin, LOW);
}
void displaySix()
{
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, LOW);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, HIGH);
	digitalWrite(ePin, HIGH);
	digitalWrite(fPin, HIGH);
	digitalWrite(gPin, HIGH);
	digitalWrite(dpPin, LOW);
}
void displaySeven()
{
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, LOW);
	digitalWrite(ePin, LOW);
	digitalWrite(fPin, LOW);
	digitalWrite(gPin, LOW);
	digitalWrite(dpPin, LOW);
}
void displayEight()
{
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, HIGH);
	digitalWrite(ePin, HIGH);
	digitalWrite(fPin, HIGH);
	digitalWrite(gPin, HIGH);
	digitalWrite(dpPin, LOW);
}
void displayNine()
{
	digitalWrite(aPin, HIGH);
	digitalWrite(bPin, HIGH);
	digitalWrite(cPin, HIGH);
	digitalWrite(dPin, HIGH);
	digitalWrite(ePin, LOW);
	digitalWrite(fPin, HIGH);
	digitalWrite(gPin, HIGH);
	digitalWrite(dpPin, LOW);
}

void showDecimal() {
	digitalWrite(dpPin, HIGH);
}

// Pick the digit currently being shown
void enableDigit(int x)
{
	switch(x)
	{
		case 1:
			digitalWrite(digit1Pin, LOW);
			digitalWrite(digit2Pin, HIGH);
			digitalWrite(digit3Pin, HIGH);
			digitalWrite(digit4Pin, HIGH);
			break;
		case 2:
			digitalWrite(digit1Pin, HIGH);
			digitalWrite(digit2Pin, LOW);
			digitalWrite(digit3Pin, HIGH);
			digitalWrite(digit4Pin, HIGH);
			break;
		case 3:
			digitalWrite(digit1Pin, HIGH);
			digitalWrite(digit2Pin, HIGH);
			digitalWrite(digit3Pin, LOW);
			digitalWrite(digit4Pin, HIGH);
			break;
		case 4:
			digitalWrite(digit1Pin, HIGH);
			digitalWrite(digit2Pin, HIGH);
			digitalWrite(digit3Pin, HIGH);
			digitalWrite(digit4Pin, LOW);
			break;
		default:
			digitalWrite(digit1Pin, HIGH);
			digitalWrite(digit2Pin, HIGH);
			digitalWrite(digit3Pin, HIGH);
			digitalWrite(digit4Pin, HIGH);
	}
}

// Show a number for the selected digit
void showNumber(int x) {
	switch(x) {
		case 1:
			displayOne();
			break;
		case 2:
			displayTwo();
			break;
		case 3:
			displayThree();
			break;
		case 4:
			displayFour();
			break;
		case 5:
			displayFive();
			break;
		case 6:
			displaySix();
			break;
		case 7:
			displaySeven();
			break;
		case 8:
			displayEight();
			break;
		case 9:
			displayNine();
			break;
		case 0:
			displayZero();
			break;
	}
}

// Show the radio freqency along with decimal point
void showRadio(int f) {
	int del = 55;
	enableDigit(1);
	
	if(f > 999) {
		showNumber(f/1000);
		delayMicroseconds(del);
		f %= 1000; 
	}
	clearSegments();
	
	enableDigit(2);
	showNumber(f/100);
	delayMicroseconds(del);
	f %= 100;
	clearSegments();
	
	enableDigit(3);
	showNumber(f/10);
	showDecimal();
	delayMicroseconds(del);
	f %= 10;
	clearSegments();
	
	enableDigit(4);
	showNumber(f);
	delayMicroseconds(del);
	clearSegments();
}
