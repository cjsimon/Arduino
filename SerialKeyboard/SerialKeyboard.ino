
#define CTRL 128;
#define ALT  386;
#define DEL  212;
char inChar;

void setup() {
    Serial.begin(9600);
    Keyboard.begin();
}

void loop() {
    if(Serial.available() > 0) {
        inChar = Serial.read();
        if(incomingByte == '`') {
            Keyboard.press(CTRL);
            Keyboard.press(ALT);
            Keyboard.press(DEL);
            Keyboard.releaseAll();
        } else {
            Keyboard.write(inChar);
        }
    }
}
