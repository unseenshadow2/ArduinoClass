#ifndef SHIFT_HEADER
#define SHIFT_HEADER

#define OUT_SERIAL 13
#define OUT_CLOCK 12
#define OUT_LATCH 11

#define IN_SERIAL 1
#define IN_CLOCK 1

#define OUT_SIZE 8
#define IN_SIZE 16

#include "arduino.h"

void shiftInit();
void setShift(uint8_t* data, uint8_t size);
void setQShift(uint8_t data);
uint16_t shiftRead();

#endif
