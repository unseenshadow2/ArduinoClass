#include "patterns.h"

#define COLOR_SWAP_TIME 5000 // 5 seconds between color changes
const unsigned long halfSwap = COLOR_SWAP_TIME / 2; // Half of our COLOR_SWAP_TIME

colorList currentColor = 1; // Our current color, default red
colorList nextColor = 2; // Our next color...

unsigned long lastCheck = 0; // When we made our last check

// Private function to determine when to update the color
void updateColor()
{
	lastCheck = millis(); // Get our time and store it

	// Determine which iteration of color we are on, and what color it comes out to
	// ((Get which itteration of color swap time we are on) Determine the color we are using the remainder) Offset the value to avoid the off value)
	currentColor = ((lastCheck / COLOR_SWAP_TIME) % COLOR_COUNT) + 1;

	// Determine our next color. Mainly important to fades.
	if (currentColor < COLOR_COUNT) nextColor = currentColor + 1; // When not equal to or greater than the number of colors, we can just add 1 to get the next color
	else nextColor = 1; // Otherwise, go back to the first color
}

// This function flashes each color for a certain amount of time
void flash()
{
	updateColor();

	// Just display the color 
	displayColor(getColor(currentColor));
}

// This function fades between colors
void fade()
{
	updateColor();

	// Determine the difference percent
	uint8_t percentDifference = ((lastCheck % COLOR_SWAP_TIME) * 100) / COLOR_SWAP_TIME;

	// Display our color with the distance given
	displayColor(getMedian(currentColor, nextColor, percentDifference));
}

// This function fades to black then to a color
void fadeToBlack()
{
	updateColor();

	// Our time between swaps
	int intermediaryTime = lastCheck % COLOR_SWAP_TIME;

	// From currentColor to OFF
	if (intermediaryTime < halfSwap)
	{
		// Determine the difference percent
		uint8_t percentDifference = ((lastCheck % halfSwap) * 100) / halfSwap;
	
		// Display our color with the distance given
		displayColor(getMedian(currentColor, off, percentDifference));
	}
	else // from OFF to nextColor
	{
		// Determine the difference percent
		uint8_t percentDifference = ((lastCheck % halfSwap) * 100) / halfSwap;
	
		// Display our color with the distance given
		displayColor(getMedian(off, nextColor, percentDifference));
	}
}

// Do nothing function
void offState()
{
	//updateColor();
	displayColor(OFF);
}

// Handles the fading math between two colors. Distance is from the first value, 0 to 100 percent.
Color getMedian(Color from, Color to, uint8_t distance)
{
	Color toReturn;

	toReturn.red = dist(from.red, to.red, distance);
	toReturn.green = dist(from.green, to.green, distance);
	toReturn.blue = dist(from.blue, to.blue, distance);

	return toReturn;
}

Color getMedian(colorList from, colorList to, uint8_t distance)
{
	return getMedian(getColor(from), getColor(to), distance);
}

// Get's the absolute value of the difference of two numbers
uint8_t diff(uint8_t first, uint8_t second)
{
	if (first == second) return 0;
	else if (first > second) return first - second;
	else return second - first;
}

// Get's the value between two values at the percentage given
uint8_t dist(uint8_t from, uint8_t to, uint8_t distance)
{
	int difference = diff(from, to);

	if (difference == 0) return from; // If our difference is 0, then the values are equal and distance is irrelivent

	// Get the change value
	difference = (difference * distance) / 100;

	// Change the from value
	if (from > to) return from - difference; // Moving down
	else return from + difference; // Moving up
}

