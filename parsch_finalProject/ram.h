#ifndef RAM_HEADER
#define RAM_HEADER

#include "arduino.h"

extern uint16_t activeAddress;

uint8_t readRam();
void writeRam(uint8_t value);

#endif 
