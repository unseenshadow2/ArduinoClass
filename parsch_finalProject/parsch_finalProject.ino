/*
 * Commands:
 * paa 				 - Print Active Address
 * saa [2 hex bytes] - Set Active Address
 * pav				 - Print Active Value
 * sav [1 hex byte]  - Set Active Value
 * 
 * 
 */

#include "shift_register.h"
#include "ram.h"
#include "hexToByte.h"

#define DATA_SIZE 50
#define COMMAND_SIZE 3
#define NUMBER_START 4

char data[DATA_SIZE];
byte outdata;

void clearData();
bool commandCheck(const char* data, const char* command);

void setup() 
{
	shiftInit();
	setQShift(B10001000);
	Serial.begin(9600);
}

void loop() 
{
	// Serial input
	if (Serial.available())
	{
		Serial.readBytes(data, DATA_SIZE);

		if (commandCheck(data, "paa"))
		{
			Serial.print("Active Address: "); Serial.println(activeAddress, HEX);
		}
		else if (commandCheck(data, "saa"))
		{
			activeAddress = hexTo16bit(data+4);			
			Serial.print("Active Address set to "); Serial.println(activeAddress, HEX);
		}
		else if (commandCheck(data, "pav"))
		{
			Serial.print("Active Value: "); Serial.println(readRam(), HEX);
		}
		else if (commandCheck(data, "sav"))
		{
			writeRam(hexToByte(data+4));
			uint8_t temp = readRam();
			setQShift(temp);
			Serial.print("Active Value set to "); Serial.println(temp, HEX);
		}
	}
}

void clearData()
{
	for (int i = 0; i < DATA_SIZE; i++)
	{
		data[i] = '\0';
	}
}

bool commandCheck(const char* data, const char* command)
{
	bool isEqual = true;
	
	for (int i = 0; (i < COMMAND_SIZE) && (isEqual); i++)
	{
		isEqual = data[i] == command[i];
	}

	return isEqual;
}

