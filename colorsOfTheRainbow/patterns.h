#ifndef PATTERNS_HEADER
#define PATTERNS_HEADER

#include "colors.h"
#include "arduino.h"

// This function flashes each color for a certain amount of time
void flash();

// This function fades between colors
void fade();

// This function fades to black then to a color
void fadeToBlack();

// Do nothing function
void offState();

// Handles the fading math between two colors. Distance is from the first value, 0 to 100 percent.
Color getMedian(Color from, Color to, uint8_t distance);
Color getMedian(colorList from, colorList to, uint8_t distance);

// Get's the absolute value of the difference of two numbers
uint8_t diff(uint8_t first, uint8_t second);

// Get's the value between two values at the percentage given
uint8_t dist(uint8_t from, uint8_t to, uint8_t distance);

#endif
