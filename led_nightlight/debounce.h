#define DEBOUNCE_DELAY 200 // In milliseconds

bool debounce = false; // Are we currently in the debounce state (from user press to either DEBOUNCE_DELAY millis after or user release)
unsigned long debounceEnd = 0; // The time that we end the debounce

// ##### Exorcise 5 Function #####
// Because exorcise 5 mentioned this being a good time for functions,
// I shall handle my debounce in a function.
// NOTE: Only returns true on the rising edge
bool checkButton(int button)
{
	// When the button is release and the time has passed, exit debounce state
	if (debounce && (millis() >= debounceEnd) && (digitalRead(button) == LOW)) 
	{
		debounce = false;
		return false;
	}
	// Check for the button to go down and enter the debounce state
	else if (!debounce)
	{
		if (digitalRead(BUTTON) == HIGH) // Button is high, setup debounce state
		{
			unsigned long pauseTime = millis(); // Capture time for debug reasons
			
			debounce = true;
			debounceEnd = pauseTime + DEBOUNCE_DELAY;

			Serial.print("Button press detected at time ");
			Serial.print(pauseTime);
			Serial.print(". Button will become available at time ");
			Serial.println(debounceEnd);
			
			return true;
		}
		else return false; // Button is low, nothing is happening
	}
	else return false; // We are in the debounce state, but cannot currently exit it
}
