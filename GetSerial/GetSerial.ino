#include <GetSerial.h>

GetSerial s = GetSerial(9600);
int led = 13;

void setup() {
    pinMode(led, OUTPUT);
}

void loop() {
    //Read the data from the serial into a buffer
    char data = s.getData();
    if(s.notProcessed) {
        //Process the data for commands
        s.process(data);
        Serial.println(data);
        s.notProcessed = false;
    }
}
