// Changes LED brightness using voltage input instead of PWM
// Speaker tone and volume included

#include <SPI.h>

// When using the SPI library, you only have to worry
// about picking slave select.
// By default, 11 = MOSI, 12 = MISO, 13 = CLK
#define SLAVE1 10
#define SLAVE2 9

#define REG0 B00010001 // Register 0 Write command
#define REG1 B00010010 // Register 1 Write command

#define SHORT_PAUSE 10
#define LONG_PAUSE 300

#define SPEAKER 8 // Speaker Pin
#define FREQ_RISE 100 // The speed at which the frequency changes
int freq = 100;

void setLed(int SS, int reg, int level);

void setup() 
{
	pinMode(SLAVE1, OUTPUT);
	pinMode(SLAVE2, OUTPUT);

	// Initialize SPI
	SPI.begin();

	Serial.begin(9600);
}

void loop()
{
	Serial.println("Going up");
	tone(SPEAKER, freq); // Set speaker frequency
	for (int i = 0; i <= 128; i++)
	{
		setLed(SLAVE1, REG0, i);
		setLed(SLAVE1, REG1, i);
		setLed(SLAVE2, REG0, i);
		setLed(SLAVE2, REG1, i);
		delay(SHORT_PAUSE);

		if ((i % 32) == 0)
		{
			Serial.print("Current value: ");
			Serial.println(i);
		}
	}

	// Blech
	Serial.println("Up pause");
	delay(LONG_PAUSE);

	Serial.println("Going down");
	for (int i = 128; i >= 0; i--)
	{
		setLed(SLAVE1, REG0, i);
		setLed(SLAVE1, REG1, i);
		setLed(SLAVE2, REG0, i);
		setLed(SLAVE2, REG1, i);
		delay(SHORT_PAUSE);

		if ((i % 32) == 0)
		{
			Serial.print("Current value: ");
			Serial.println(i);
		}
	}

	// More blech
	Serial.println("Down pause");
	delay(LONG_PAUSE);

	freq = freq + 100;
	if (freq > 2000) freq = 100;
}

// SS10 Reg0 Red
// SS10 Reg1 Yellow
// SS9 Reg0 Green
// SS9 Reg1 White
void setLed(int SS, int reg, int level)
{
	digitalWrite(SS, LOW); // SS to low, lock
	SPI.transfer(reg); // Choose register to write to
	SPI.transfer(level); // Set the LED level (0-128)
	digitalWrite(SS, HIGH); // SS to high, release
}

