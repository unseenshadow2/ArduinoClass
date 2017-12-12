#include "pitches.h"

#define SPEAKER 9 // The speaker pin
#define NOTE_TIME 250 // How many milliseconds a note holds for
#define MAX_SONG 100 // The number of notes a song may have
#define MAX_LOADER_SIZE 200 // The number of characters the loader string may contain
#define READY_MESSAGE "Ready to play a song..." // The message that displays when ready

char song[MAX_SONG]; // Our current song
char loader[MAX_LOADER_SIZE]; // What we use to take data from the serial port

unsigned long nextNote = 0; // When we will play our next note
bool isPlaying = false; // Are we currently playing a song
int currentNote = 0; // The current position of the note we are playing

// Clears out our song
void resetSong();

// Load the values in our loader into our song
void loadSong();

// Check if ready for next note
bool playNextNote();

// Plays the note given to it
void playNote(char note);

void setup() 
{
	Serial.begin(9600);
	resetSong();
}

void loop() 
{
	if (isPlaying)
	{
		// Music logic
		if (playNextNote())
		{
			playNote(song[currentNote]);
		}
	}
	else
	{
		if (Serial.available()) // Check Serial for data
		{
			// Load music
			int bytesRead = Serial.readBytes(loader, MAX_LOADER_SIZE); // Read our music in

			// Null out unneeded data
			for (int i = bytesRead; i < MAX_LOADER_SIZE; i++) loader[i] = NULL;

			loadSong();
			
			// Begin our song
			Serial.println("Beginning your song...");
			nextNote = millis() + NOTE_TIME;
			playNote(song[0]);
		}
	}
}

// Clears out our song
void resetSong()
{
	isPlaying = false;
	for (int i = 0; i < MAX_SONG; i++) song[i] = NULL;
	
	Serial.println(READY_MESSAGE);
}

// Load the values in our loader into our song
void loadSong()
{
	// Tell the program we are starting a new song
	currentNote = 0;
	isPlaying = true;	

	// Translate the given string into the song
	int songpos = 0;
	for (int i = 0; i < MAX_LOADER_SIZE; i++)
	{
		// Only accept the notes that we allow
		switch(loader[i])
		{
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case '0':
				song[songpos] = loader[i];
				++songpos;
				break;
		}
	}
}

// Check if ready for next note
bool playNextNote()
{
	if (nextNote <= millis())
	{
		++currentNote;
		nextNote = millis() + NOTE_TIME;
		return true;
	}
	else return false;
}

// Plays the note given to it
void playNote(char note)
{
	switch(note)
	{
		case 'A':
			tone(SPEAKER, NOTE_A4);
			break;
		case 'B':
			tone(SPEAKER, NOTE_B4);
			break;
		case 'C':
			tone(SPEAKER, NOTE_C4);
			break;
		case 'D':
			tone(SPEAKER, NOTE_D4);
			break;
		case 'E':
			tone(SPEAKER, NOTE_E4);
			break;
		case 'F':
			tone(SPEAKER, NOTE_F4);
			break;
		case 'G':
			tone(SPEAKER, NOTE_G4);
			break;
		case '0':
			noTone(SPEAKER);
			break;
		case NULL:
			noTone(SPEAKER);
			resetSong();
			break;
	}
}

