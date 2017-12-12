/*
 * Project: LED Nightlight
 * Author: Anthony Parsch
 */

//#define LED 9
#define RLED 9
#define GLED 10
#define BLED 11
#define BUTTON 2
#define LED_MODE_MAX 7
#define BAUD_SPEED 9600

#include "debounce.h"
#include "colors.h"

//bool ledOn = false; // on or off
int ledMode = 0;

// Displays the color as given
void displayColor(int red, int green, int blue);

// Changes the display mode
void setMode(int mode);

void setup() 
{
	// Serial debug setup
	Serial.begin(BAUD_SPEED);
	
	// put your setup code here, to run once:
	//pinMode(LED, OUTPUT);
	pinMode(RLED, OUTPUT);
	pinMode(BLED, OUTPUT);
	pinMode(GLED, OUTPUT);
	pinMode(BUTTON, INPUT);

	// ##### Exercise 1 #####
	//digitalWrite(LED, HIGH);

	// ##### Exercise 5 Default LED State #####
	//ledOn ? digitalWrite(LED, HIGH) : digitalWrite(LED, LOW);

	// ##### Exercise 6 Default LED State #####
	setMode(ledMode);
}

void loop() 
{
	// ##### Exercise 2 #####
//	for (int i = 100; i <= 1000; i+=100)
//	{
//		digitalWrite(LED, HIGH);
//		delay(i);
//		digitalWrite(LED, LOW);
//		delay(i);
//	}

	// ##### Exercise 3 #####
	// Rising
//	for (int i = 0; i < 256; i++)
//	{
//		analogWrite(LED, i);
//		delay(10);
//	}
//
//	// Falling
//	for (int i = 256; i >= 0; i--)
//	{
//		analogWrite(LED, i);
//		delay(10);
//	}

	// ##### Exercise 4 #####
//	if (digitalRead(BUTTON) == LOW) digitalWrite(LED, LOW);
//	else digitalWrite(LED, HIGH);

	// ##### Exercise 5 #####
	// I didn't follow the book on this Exercise because I don't like how it
	// handled debouncing.
//	if (checkButton(BUTTON))
//	{
//		ledOn = !ledOn; // Invert our LED's current value
//		ledOn ? digitalWrite(LED, HIGH) : digitalWrite(LED, LOW);
//		Serial.print("Button pressed! Current LED state: ");
//		Serial.println(ledOn);
//	}

	// ##### Exercise 6 #####
	if (checkButton(BUTTON))
	{
		ledMode++;

		// Validate that we are not outside our maximum mode value
		if (ledMode > LED_MODE_MAX) ledMode = 0;

		setMode(ledMode);
	}
}

// Displays the color as given
void displayColor(int red, int green, int blue)
{
	analogWrite(RLED, red);
	analogWrite(GLED, green);
	analogWrite(BLED, blue);
}

// Changes the display mode
void setMode(int mode)
{
	switch(mode)
	{
		case 1:
			displayColor(RED);
			break;
		case 2:
			displayColor(GREEN);
			break;
		case 3:
			displayColor(BLUE);
			break;
		case 4:
			displayColor(PURPLE);
			break;
		case 5:
			displayColor(TEAL);
			break;
		case 6:
			displayColor(ORANGE);
			break;
		case 7:
			displayColor(WHITE);
			break;
		default:
			displayColor(OFF);
	}
}

