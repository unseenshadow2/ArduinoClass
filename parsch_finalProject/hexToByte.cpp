#include "hexToByte.h"

uint8_t charToHex(char value)
{
	uint8_t toReturn = 0;

	switch (value)
	{
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		toReturn = value - '0';
		break;
	case 'A':
	case 'a':
		toReturn = 10;
		break;
	case 'B':
	case 'b':
		toReturn = 11;
		break;
	case 'C':
	case 'c':
		toReturn = 12;
		break;
	case 'D':
	case 'd':
		toReturn = 13;
		break;
	case 'E':
	case 'e':
		toReturn = 14;
		break;
	case 'F':
	case 'f':
		toReturn = 15;
		break;
	}

	return toReturn;
}

uint8_t hexToByte(const char* value)
{
	uint8_t toReturn = 0;

	toReturn |= charToHex(value[1]);
	toReturn |= (charToHex(value[0]) << 4);

	return toReturn;
}

uint16_t hexTo16bit(const char* value)
{
	uint16_t toReturn = 0;

	toReturn |= hexToByte(value + 2);
	toReturn |= (hexToByte(value) << 8);

	return toReturn;
}
