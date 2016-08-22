#include <IRremote.h>
#include <NewTone.h>

#define ZERO  0
#define ONE   1
#define TWO   2
#define THREE 3
#define FOUR  4
#define FIVE  5
#define SIX   6
#define SEVEN 7
#define EIGHT 8
#define NINE  9

int parseRemoteDigit(int);
void playMusic();

#define RECV_PIN 2
#define L1_PIN 8
#define L2_PIN 9
#define BUZ_PIN	7

IRrecv irrecv(RECV_PIN);
decode_results results;

int freq[] = {0, 1047, 1175, 1319, 1397, 1568, 1760, 1976, 2093, 2349};

int duration = 500;
int isFirstDigitZero = 0;
int isLight1On = 0;
int isLight2On = 0;
int areBothLightsOn = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(L1_PIN, OUTPUT);
    pinMode(L2_PIN, OUTPUT);
    irrecv.enableIRIn();
}

void loop()
{
    int keyVal = -1;

    if(irrecv.decode(&results) != 0) {
        Serial.println(results.value, HEX);
        keyVal = parseRemoteDigit(results.value);
        
        if(keyVal == -1)
        {
            // keyVal is not a pressed button
        }
        else if(keyVal == 0)
        {
            // Is this the first zero?
            if(isFirstDigitZero != 0)
            {
                // Second Zero
                isFirstDigitZero = 0;
            }
            else
            {
                // First Zero
                isFirstDigitZero = 1;
            }
        }
        else if(isFirstDigitZero == 1)
        { // Lights
            if(keyVal == 1)
            { // First Light
                if(isLight1On == 1)
                {
                    digitalWrite(L1_PIN, LOW);
                }
                isLight1On = 0;
                if(isLight2On == 0)
                { // if Light 2 is off
                    areBothLightsOn = 0;
                }
                else
                { // Light 1 Currently Off
                    digitalWrite(L1_PIN, HIGH);
                    isLight1On = 1;
                    if(isLight2On != 0)
                    { // Light 2 already on
                        areBothLightsOn = 1;
                    }
                }
            }
            else if(keyVal == 2)
            {
                if(isLight2On != 0)
                {
                    digitalWrite(L2_PIN, LOW);
                    isLight2On = 0;
                    if(isLight1On == 0)
                    {
                        areBothLightsOn = 0;
                    }
                }
                else
                {
                    digitalWrite(L2_PIN, HIGH);
                    isLight2On = 1;
                    if(isLight1On == 1)
                    {
                        areBothLightsOn = 1;
                    }
                }
            }
            else if(keyVal == 3)
            {
                if(areBothLightsOn != 0) 
                {
                    digitalWrite(L1_PIN, LOW);
                    digitalWrite(L2_PIN, LOW);
                    isLight1On = 0;
                    isLight2On = 0;
                    areBothLightsOn = 0;
                }
                else
                {
                    digitalWrite(L1_PIN, HIGH);
                    digitalWrite(L2_PIN, HIGH);
                    isLight1On = 1;
                    isLight2On = 1;
                    areBothLightsOn = 1;
                }
            }
            else if(keyVal == 4)
            {
                playMusic();
            }
            
            isFirstDigitZero = 0;
        }
        else
        {
            NewTone(BUZ_PIN, freq[keyVal], duration);
        }
        
        // Continue to receive ir readings
        irrecv.resume();
    }
    delay(100);
}


// Write a parseRemoteDigit function to parse the remote control value.
// The function input is an integer, the remote control button value after decode.
// The function output is the integer digit of the remote button. -1 for buttons not 0-9.
int parseRemoteDigit(int hexCode)
{
   int buttonVal = -1;
   switch(hexCode)
   {
      case ZERO: buttonVal = 0; break;
      case ONE: buttonVal = 1; break;
      case TWO: buttonVal = 2; break;
      case THREE: buttonVal = 3; break;
      case FOUR: buttonVal = 4; break;
      case FIVE: buttonVal = 5; break;
      case SIX: buttonVal = 6; break;
      case SEVEN: buttonVal = 7; break;
      case EIGHT: buttonVal = 8; break;
      case NINE: buttonVal = 9; break;
   }  // end of switch
   return buttonVal;
}

void playMusic() {
    int whole   = 1000;
    int half    = 1000/2;
    int fourth  = 1000/4;
    int eighth  = 1000/8;
    
    for(int i = 0; i < 6; i++) {
        digitalWrite(L1_PIN, HIGH);
        NewTone(7, 2637);
        delay(fourth);
        noNewTone(7);
       
       digitalWrite(L1_PIN, LOW);
        digitalWrite(L2_PIN,HIGH);
        NewTone(7, 2637);
        delay(fourth);
        noNewTone(7);
        
        NewTone(7, 3951);
        delay(fourth);
        noNewTone(7);

        digitalWrite(L2_PIN, HIGH);
        NewTone(7, 2217);
        delay(eighth);
        noNewTone(7);

        digitalWrite(L2_PIN, LOW);
        digitalWrite(L1_PIN,HIGH);
        NewTone(7, 3520);
        delay(fourth);
        noNewTone(7);
        digitalWrite(L1_PIN,LOW);
    }
}
