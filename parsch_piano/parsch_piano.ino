#include "pitches.h"
#include "debounce.h"

#define SPEAKER 9 // The speaker pin

// Piano Buttons
#define BUTTON_C 7
#define BUTTON_D 6
#define BUTTON_E 5
#define BUTTON_G 4
#define BUTTON_A 3
#define BUTTON_OCTAVE 2
#define HOLD_TIME 200 // The number of milliseconds before a press is counted as a hold

// Handle our octave shift
int8_t octave = 4; // The current octave between 3 and 5. 2 represents that it is dropping from a 5.
unsigned long isHoldAt = 0;
unsigned long moment = 0; // For the handleOctaveButton() function

void playTone(int toPlay);
void handleOctaveButton(int button);

// DEBUG
#define OCTAVE_CHECK_TIME 2500
unsigned long nextOctaveCheck = 0;

void setup() 
{
	Serial.begin(9600);
}

void loop()
{
	handleOctaveButton(BUTTON_OCTAVE);
	
	// Play our tones
	if (digitalRead(BUTTON_C)) tone(SPEAKER, NOTE_C4);
	else if (digitalRead(BUTTON_D)) playTone(NOTE_D4);
	else if (digitalRead(BUTTON_E)) playTone(NOTE_E4);
	else if (digitalRead(BUTTON_G)) playTone(NOTE_G4);
	else if (digitalRead(BUTTON_A)) playTone(NOTE_A4);
	else noTone(SPEAKER);

	// DEBUG
	if (nextOctaveCheck <= millis())
	{
		nextOctaveCheck = millis() + OCTAVE_CHECK_TIME;
		Serial.print("Octave check: ");
		Serial.println(octave);
	}
}

// This plays a tone. Allows me to make automatic modifications to the tone
// as code gets more complex.
void playTone(int toPlay)
{
	// Change our current octave
	if ((octave == 3) || (octave == 2)) toPlay /= 2;
	else if (octave == 5) toPlay *= 2;
	
	tone(SPEAKER, toPlay);
}

// Handle our complicated button logic for the octave button
void handleOctaveButton(int button)
{	
	moment = millis(); // The moment in time the function starts
	
	// Reset to the lowest octave
	if (checkButton(button))
	{
		octave = (octave == 5) ? 2 : 3; // Are we special octave or octave 3
		isHoldAt = moment + HOLD_TIME;
	}

	// If we aren't in a modified octave, not bother checking to change
	if (octave < 4)
	{
		// Button held being released
		if ((octave != 5) && (isHoldAt <= moment) && !digitalRead(button))
		{
			octave = 4;
		}
		// Release of button press
		else if ((moment >= debounceEnd) && (isHoldAt > moment) && !digitalRead(button))
		{
			octave = (octave == 3) ? 5 : 4; // 
		}
	}
}

