#include <Keypad.h>

#define MOLENUM     5
#define TIMESTAGE_1 10000
#define TIMESTAGE_2 25000
#define TIMESTAGE_3 45000
#define TIMESTAGE_4 60000
#define MOLE_NUM_1  1
#define MOLE_NUM_2  2
#define MOLE_NUM_3  3
#define MOLE_NUM_4  4
#define UPTIME_1    5000
#define UPTIME_2    4000
#define UPTIME_3    3000
#define UPTIME_4    2000
#define DURATION_1  50
#define DURATION_2  100
#define DURATION_3  200
#define FREQ_HIT    165
#define FREQ_FAIL_1 2794
#define FREQ_FAIL_2 3136


// 4x4 keypad
const byte ROWS = 4;
const byte COLS = 4;

// The keypad mapping
const char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};//closes the matrix

// The buzpin
const int BUZPIN = 10;
// Array of pins
const int LPINS[ MOLENUM + 1 ] = { 0, 11, 12, 13, 18, 19 };
// The array of freqs
const int FREQPOP[] = { 0, 330, 330, 554, 659, 880 };

// The rows and cols
byte rowPins[ROWS] = { 9, 8, 7, 6 };
byte colPins[COLS] = { 5, 4, 3, 2 };

// Create the keypad
Keypad aKeyPad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// The startTick
unsigned long startTick;
unsigned long popTick[ MOLENUM+1 ] = { 0, 0, 0, 0, 0, 0 };

// Counter
int counter[MOLENUM+1] = {0, 0, 0, 0, 0, 0,};

// The score and upTime
int score = 0;
int isScoreShown = 0;
int upTime = UPTIME_1;

void setup()
{
    // Begin serial
    Serial.begin(9600);
    for(int i = 1; i < MOLENUM; i++)
    {
        //Set all pins to output
        pinMode( LPINS[i], OUTPUT );
    }
    // Get a random number
    randomSeed(analogRead(0));
    // Start the timer
    startTick = millis();
}

void loop()
{
// The char key
char key;
// Current Moles
int currentMoles = 0;
// More moles
int moreMoles = 0;
// The random number
int randNum = 0;
// The pressed kry
int keyNum = -1;
// Number of moles
int numberOfMoles;
// Current tick
unsigned long currentTick;

// CurrentTime - OriginalTime
currentTick = millis() - startTick;

if(currentTick >= TIMESTAGE_4)
{
    numberOfMoles = 0;
    for (int i = 1; i < MOLENUM; i++)
    {
        if(counter[i] != 0)
        {
            digitalWrite(LPINS[i], LOW);
            counter[i] = 0;
            popTick[i] = 0;
            tone(BUZPIN, FREQ_FAIL_2, DURATION_2);
            delay(DURATION_3);
        }
    }

    if(isScoreShown == 0)
    {
        reportScore();
        isScoreShown = 1;
    }
}
else if(currentTick >= TIMESTAGE_3)
{
    numberOfMoles = MOLE_NUM_4;
    upTime = UPTIME_4;
}
else if(currentTick >= TIMESTAGE_2)
{
    numberOfMoles = MOLE_NUM_3;
    upTime = UPTIME_3;
}
else if(currentTick >= TIMESTAGE_1)
{
    numberOfMoles = MOLE_NUM_2;
    upTime = UPTIME_2;
}
else
{
    numberOfMoles = MOLE_NUM_1;
    upTime = UPTIME_1;
}

for(int i=1; i < MOLENUM; i++)
{
    if(counter[i] != 0 && currentTick - popTick[i] > upTime)
    {
        counter[i] = 0;
        popTick[i] = 0;
        digitalWrite(LPINS[i], LOW);
        tone(BUZPIN, FREQ_FAIL_2, DURATION_2);
        delay(DURATION_3);
    }
    currentMoles = currentMoles + counter[i];
}

moreMoles = numberOfMoles - currentMoles;
for(int i = 0; i < moreMoles; i++)
{
    randNum = random(1, MOLENUM+1);

    if(counter[randNum] == 0)
    {
        counter[randNum] = 1;
        popTick[randNum] = currentTick;
        digitalWrite(LPINS[randNum], HIGH);// is it LPINS(randNum)
        tone(BUZPIN, FREQPOP[randNum], DURATION_1);
        delay(DURATION_1);
  }
}

// Get the keypad key
key = aKeyPad.getKey();

if(key != NO_KEY)
{
  Serial.println(key);
  keyNum = parseInputKey(key);

  if(keyNum == -1)
  {
      tone(BUZPIN, FREQ_FAIL_1, DURATION_1);
      delay(DURATION_1);
  }
  else if(counter[keyNum] > 0)
  {
      counter[keyNum] = 0;
      popTick[keyNum] = 0;
      digitalWrite(LPINS[keyNum], LOW);
      tone(BUZPIN, FREQ_HIT, DURATION_2);
      delay(DURATION_3);
      score = score + 10;
  }
  else
  {
      tone(BUZPIN, FREQ_FAIL_1, DURATION_1);
      delay(DURATION_1);
  }
}

}

// Get the key from the user
int parseInputKey(char userinput)
{
    int number = -1;
    
    switch (userinput)
    {
       case '1':
           number = 1;
           break;
       case '3':
           number = 2;
           break;
       case '5':
           number = 3;
           break;
       case '7':
           number = 4;
           break;
       case '9':
           number = 5;
           break;
    }
    return number;
}

void reportScore()
{
    int points = 0;
    Serial.print("Score ");
    Serial.print(score);
    int digit1 = 0;
    int digit2 = 0;
    int i;

    tone(BUZPIN, FREQPOP[1],DURATION_1);
    tone(BUZPIN, FREQPOP[3],DURATION_1);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    tone(BUZPIN, FREQPOP[1],1000);
    tone(BUZPIN, FREQPOP[3],1000);
    delay(1000);

    points = score/10;
    Serial.print(points);
    digit1 = points/10;
    digit2 = points%10;

    for(i = 0; i < digit1; i++)
    {
        digitalWrite(LPINS[1], HIGH);
        tone(BUZPIN, FREQPOP[1], DURATION_1);
        delay(DURATION_3);
        digitalWrite(LPINS[1], LOW);
        delay(DURATION_3);
    }
}
