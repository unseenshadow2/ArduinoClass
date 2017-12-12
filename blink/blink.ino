#define BLINK_PIN 7
#define BLINK_PAUSE 1000

// Current value
int value = HIGH;

// When do we blink next?
unsigned long next_blink = 0;

void setup() 
{
	pinMode(BLINK_PIN, OUTPUT);
}

void loop() 
{
	// Our pulse
	if (millis() > next_blink)
	{
		// Setup our next time set
		next_blink = millis() + BLINK_PAUSE;
		digitalWrite(BLINK_PIN, value);
	
		// Flip the value every pulse
		value = (value == HIGH) ? LOW : HIGH;
	}

}
