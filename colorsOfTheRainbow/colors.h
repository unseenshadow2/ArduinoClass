#ifndef COLOR_HEADER
#define COLOR_HEADER

#include "arduino.h"

// Our color definitions
#define RED 255,0,0
#define GREEN 0,255,0
#define BLUE 0,0,255
#define PURPLE 127,0,127
#define TEAL 0,127,127
#define ORANGE 127,127,0
#define WHITE 85,85,85
#define OFF 0,0,0

// The number of colors that we have
#define COLOR_COUNT 7

// Our LEDs
#define RLED 9
#define GLED 10
#define BLED 11

enum colorList {red = 1, green, blue, purple, teal, orange, white, off = 0}; // An enum that handles the colors

struct Color
{
	uint8_t red;
	uint8_t green;
	uint8_t blue;
};

void displayColor(int red, int green, int blue); // Displays the color as given
void displayColor(Color color); // Overload, see above
Color getColor(int red, int green, int blue); // Convert RGB to Color
Color getColor(colorList reference); // Get the color from colorList

void printColor(Color toPrint); // Print a color out to the serial port
#endif
