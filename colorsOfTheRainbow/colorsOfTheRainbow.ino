/*
 * Project: LED Colors of the Rainbow
 * Author: Anthony Parsch
 */

#define BUTTON 2
#define LED_MODE_MAX 3
#define BAUD_SPEED 9600

#include "debounce.h"
#include "colors.h"
#include "patterns.h"

//bool ledOn = false; // on or off
int ledMode = 1;

// Changes the display mode
void runMode(int mode);

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

	// Set our default mode
	runMode(ledMode);
}

void loop() 
{
	// If the button is pressed, change our current mode
	if (checkButton(BUTTON))
	{
		ledMode++;

		// Validate that we are not outside our maximum mode value
		if (ledMode > LED_MODE_MAX) ledMode = 0;
	}

	runMode(ledMode);
}

// Changes the display mode
void runMode(int mode)
{
	switch(mode)
	{
		case 1:
			flash();
			break;
		case 2:
			fade();
			break;
		case 3:
			fadeToBlack();
			break;
		default:
			offState();
	}
}

