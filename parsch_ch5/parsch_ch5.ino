#include "pitches.h"

#define SPEAKER 9 // The speaker pin
#define SONG_SIZE 20 // The length of our arrays

// Piano Buttons
#define BUTTON_C 7
#define BUTTON_D 6
#define BUTTON_E 5
#define BUTTON_G 4
#define BUTTON_A 3
#define BUTTON_OCTIVE 2

// What we are going to play
//int notes[] =
//{
//	NOTE_A4, NOTE_E3, NOTE_A4, 0,
//	NOTE_A4, NOTE_E3, NOTE_A4, 0,
//	NOTE_E4, NOTE_D4, NOTE_C4, NOTE_B4, NOTE_A4, NOTE_B4, NOTE_C4, NOTE_D4,
//	NOTE_E4, NOTE_E3, NOTE_A4, 0
//};
//
//// Duration in ms
//int times[] =
//{
//	250, 250, 250, 250,
//	250, 250, 250, 250,
//	125, 125, 125, 125, 125, 125, 125, 125,
//	250, 250, 250, 250
//};

void playTone(int toPlay);

void setup() 
{
	// Exersize 1
//	for (int i = 0; i < SONG_SIZE; i++)
//	{
//		tone(SPEAKER, notes[i], times[i]);
//		delay(times[i]);
//	}
}

void loop()
{
	// Exersize 2
	if (digitalRead(BUTTON_C)) tone(SPEAKER, NOTE_C4);
	else if (digitalRead(BUTTON_D)) playTone(NOTE_D4);
	else if (digitalRead(BUTTON_E)) playTone(NOTE_E4);
	else if (digitalRead(BUTTON_G)) playTone(NOTE_G4);
	else if (digitalRead(BUTTON_A)) playTone(NOTE_A4);
	else noTone(SPEAKER);
}

// This plays a tone. Allows me to make automatic modifications to the tone
// as code gets more complex.
void playTone(int toPlay)
{
	tone(SPEAKER, toPlay);
}

