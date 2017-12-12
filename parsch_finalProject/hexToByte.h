#ifndef HEX_HEADER
#define HEX_HEADER

#include "arduino.h"

uint8_t charToHex(char value);
uint8_t hexToByte(const char* value);
uint16_t hexTo16bit(const char* value);

#endif
