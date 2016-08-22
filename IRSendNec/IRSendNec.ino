#include "IRremote.h"
IRsend irsend;

void setup()
{
    Serial.begin(115200);
    pinMode(13, OUTPUT);
}

//The length of the code
int codeLen;
//The code value as HEC or DEC
unsigned long codeValue;
//The buffer from the serial as a string
unsigned long buffer = 0;

void sendCode(boolean repeat, long codeValue, int codeLen)
{
    if(repeat)
    {
        irsend.sendNEC(REPEAT, codeLen);
        Serial.println("Sent NEC repeat");
    } 
    else
    {
        irsend.sendNEC(codeValue, codeLen);
        Serial.print("Sent NEC: ");
        Serial.println(codeValue, HEX);
    }
}

void loop()
{
    //Values are all of same length so check for hardcoded NEC length of remote
    while(Serial.available() > 0)
    {
        //For each of the eight characters currently in serial
        buffer += Serial.parseInt();
    }
    
    if(buffer != 0)
    {
        //Send the HEX/DEC Value for as the IRCode and the DEC value for the CodeLength!
        sendCode(false, buffer, 32);
        //Clear the existing strBuffer
        buffer = 0; 
    }
}
