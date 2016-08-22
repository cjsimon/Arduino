//(Declare function prototypes for the following programmer defined functions, reference Chapter 5 lecture slides #7-#18)
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
//This function will take one integer input that represents one of the 4 digits on the 4-digit 7-segment display, and provides no output. 
void enableDigit(int); 
void showNumber(int);
void showStopWatch();

//(Reference Storage Classes and Scope from Chapter 5 lecture slides #25 - #33.)
//(Declare the following global variables.  Reference Storage Classes and Scope from Chapter 5 lecture slides #25 - #33.)
#define aPin 5;
#define bPin 7;
#define cPin 9;
#define dPin 11;
#define ePin 12;
#define fPin 6;
#define gPin 8;
#define dpPin 10;

#define digit1Pin 1;
#define digit2Pin 2;
#define digit3Pin 3;
#define digit4Pin 4;

#define button1Pin 13;
#define button2Pin 4;

#define buzPin 19;

unsigned long n 			= 0;
unsigned long startTime		= 0;
unsigned long currentTime	= 0;
unsigned long oldTime		= 0;

int del 					= 55;
int buttonDuration			= 200;
int buttonFrequency			= 3000;
int started					= 0;
int timeDivisionCounter		= 100;

//(The setup function runs once when you press reset.)
void setup()
{
   //(Reference the SainSmart UNO Starter Kits Tutorials, Chapter 4: LED Blink, to set the following pins to the output mode.)
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
   
   pinMode(button1Pin, INPUT);
   pinMode(button2Pin, INPUT);
   digitalWrite(button1Pin, HIGH);
   digitalWrite(button2Pin, HIGH);
}

//(The loop function will be called over and over again forever.)
void loop()
{
   int i;
   int a = 0;

   for(i = 0; i < timeDivisionCounter; i++)
   {
      //Call the showStopWatch function.
      showStopWatch();
   }  // end of for loop

   //Call the Arduino built-in analogRead function and provide button2Pin as function input.  Save the function output to a.
   a = analogRead(button2Pin);
   
   if(digitalRead(button1Pin) == LOW)
   {
      //Call the Arduino built-in tone function and provide buzPin, buttonFrequency, and buttonDuration as function inputs.
      //Call the Arduino built-in delay function and provide buttonDuration as function input.

      tone(buzPin, buttonFrequency, buttonDuration);
      delay(buttonDuration);

      if(started == 1)
      {
         //Set the value of started to 0.
         started = 0;
         //Save the value of n in oldTime.
         oldTime = n;
      }
      else
      {
         //Set the value of started to 1.
         started = 1;
         //Call the millis() function and save the function output to startTime.
         startTime = millis();
      }      
   }  // end of if button 1 is pressed
   else if(a == 0)
   {
      started = 0;
      n = 0;
      oldTime = 0;
      tone(buzPin, buttonFrequency, buttonDuration);
      delay(buttonDuration);  
   }  // end of else if button 2 is pressed

   if(started == 1)
   {
      //Call the Arduino built-in millis function and save the function output to currentTime.
      currentTime = millis();
      //Modify the value of n to be currentTime minus startTime plus oldTime.
      n = currentTime - startTime + oldTime;
   }

}  // end of loop forever function

//(The function body for the following programmer defined functions should be added below.  Reference Chapter 5 lecture slides #7-#18)
void clearSegments()
{
   digitalWrite(aPin, LOW);
   digitalWrite(bPin, LOW);
   digitalWrite(cPin, LOW);
   digitalWrite(dPin, LOW);
   digitalWrite(ePin, LOW);
   digitalWrite(fPin, LOW);
   digitalWrite(gPin, LOW);
   digitalWrite(dpPin, LOW);
}

//Display each number using the leds
void displayZero()
{
   digitalWrite(aPin, HIGH);
   digitalWrite(bPin, HIGH);
   digitalWrite(cPin, HIGH);
   digitalWrite(dPin, HIGH);
   digitalWrite(ePin, HIGH);
   digitalWrite(fPin, HIGH);
   digitalWrite(gPin, LOW);
   digitalWrite(dpPin, HIGH);
}
void displayOne()
{
   digitalWrite(aPin, HIGH);
   digitalWrite(bPin, HIGH);
   digitalWrite(cPin, LOW);
   digitalWrite(dPin, LOW);
   digitalWrite(ePin, LOW);
   digitalWrite(fPin, LOW);
   digitalWrite(gPin, LOW);
   digitalWrite(dpPin, HIGH);
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
   digitalWrite(dpPin, HIGH);
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
   digitalWrite(dpPin, HIGH);
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
   digitalWrite(dpPin, HIGH);
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
   digitalWrite(dpPin, HIGH);
}
void displaySix()
{
   digitalWrite(aPin, HIGH);
   digitalWrite(bPin, LOW);
   digitalWrite(cPin, HIGH);
   digitalWrite(dPin, HIGH);
   digitalWrite(ePin, HIGH);
   digitalWrite(fPin, HIGH);
   digitalWrite(gPin, LOW);
   digitalWrite(dpPin, HIGH);
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
   digitalWrite(dpPin, HIGH);
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
   digitalWrite(dpPin, HIGH);
}
void displayNine()
{
   digitalWrite(aPin, HIGH);
   digitalWrite(bPin, HIGH);
   digitalWrite(cPin, HIGH);
   digitalWrite(dPin, HIGH);
   digitalWrite(ePin, LOW);
   digitalWrite(fPin, HIGH);
   digitalWrite(gPin, LOW);
   digitalWrite(dpPin, HIGH);
}

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
   }  // end of switch statement
}  // end of enableDigit function

void showNumber(int x)
{
	//Write a switch statement to call the displayZero function, displayOne function, and so on…, based on the value of x.
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

void showStopWatch()
{
   //(Declare the following local variables to be used in this function.)
   unsigned long minutes;
   unsigned long seconds;
   int m1; //the first digit of the minute.
   int m2; //the second digit of the minute.
   int s1; //the first digit of the second.
   int s2; //the second digit of the second.

   minutes = (n / 1000) / 60;
   seconds = (n / 1000) % 60;
   m1 = minutes / 10;
   m2 = minutes % 10;
   s1 = seconds / 10;
   s2 = seconds % 10; 

   //Call the clearSegments function to turn off the lights in the previous digit.
   clearSegments();
   //Call the enableDigit function to enable digit 1.
   enableDigit(1);
   //Call the showNumber function to show m1.
   showNumber(m1);
   //Call the Arduino built-in delayMicroseconds function and provide del as the function input to lit the LEDs on digit 1 for del microseconds.
   delayMicroseconds(del);

   //Call the clearSegments function to turn off the lights in the previous digit.
   clearSegments();
   //Call the enableDigit function to enable digit 2.
   enableDigit(2);
   //Call the showNumber function to show m2.
   showNumber(m2);
   //Call the Arduino built-in delayMicroseconds function and provide del as the function input to lit the LEDs on digit 2 for del microseconds.
   delayMicroseconds(del);

   //Call the clearSegments function to turn off the lights in the previous digit.
   clearSegments();
   //Call the enableDigit function to enable digit 3.
   enableDigit(3);
   //Call the showNumber function to show s1.
   showNumber(s1);
   //Call the Arduino built-in delayMicroseconds function and provide del as the function input to lit the LEDs on digit 3 for del microseconds.
   delayMicroseconds(del);
   
   //Call the clearSegments function to turn off the lights in the previous digit.
   clearSegments();
   //Call the enableDigit function to enable digit 4.
   enableDigit(4);
   //Call the showNumber function to show s2.
   showNumber(s2);
   //Call the Arduino built-in delayMicroseconds function and provide del as the function input to lit the LEDs on digit 4 for del microseconds.
   delayMicroseconds(del);
   
}  // end of showMicrowaveTimer function