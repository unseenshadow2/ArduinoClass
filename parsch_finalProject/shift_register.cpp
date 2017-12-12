#include "shift_register.h"
#include "arduino.h"

void shiftInit()
{
	pinMode(OUT_SERIAL, OUTPUT);
	pinMode(OUT_CLOCK, OUTPUT);
	pinMode(OUT_LATCH, OUTPUT);
	pinMode(IN_SERIAL, INPUT);
	pinMode(IN_CLOCK, INPUT);
}

void setShift(uint8_t* data, uint8_t size)
{
	for (int i = 0; i < size; i++)
	{
		digitalWrite(OUT_LATCH, LOW);
		shiftOut(OUT_SERIAL, OUT_CLOCK, MSBFIRST, data[i]);
		digitalWrite(OUT_LATCH, HIGH);
	}
}

void setQShift(uint8_t data)
{
	setShift(&data, 1);
}

uint16_t shiftRead()
{
	uint16_t output = 0;
	uint8_t data = 0;

	// Handle setting up the output value
	// i is equivilent to position
	for (int i = 0; i < IN_SIZE; i++)
	{
		// TODO: Assign data to either 1 or 0
		output |= data << i;
	}
}

