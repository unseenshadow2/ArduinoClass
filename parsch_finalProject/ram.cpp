#include "ram.h"

uint16_t activeAddress = 0;

uint8_t activeValue = 0;

uint8_t readRam()
{
	return activeValue;
}

void writeRam(uint8_t value)
{
	activeValue = value;
}

