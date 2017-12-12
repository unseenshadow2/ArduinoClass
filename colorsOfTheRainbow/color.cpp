#include "colors.h"
#include "arduino.h"

// Displays the color as given
void displayColor(int red, int green, int blue)
{
	analogWrite(RLED, red);
	analogWrite(GLED, green);
	analogWrite(BLED, blue);
}

void displayColor(Color color) // Overload, see above
{
	analogWrite(RLED, color.red);
	analogWrite(GLED, color.green);
	analogWrite(BLED, color.blue);
}

// Convert RGB to Color
Color getColor(int red, int green, int blue)
{
	Color toReturn;
	
	toReturn.red = red;
	toReturn.green = green;
	toReturn.blue = blue;

	return toReturn;
}

// Get the color from colorList
Color getColor(colorList reference)
{
	Color toReturn;

	switch (reference)
	{
		case 1:
			toReturn = getColor(RED);
			break;
		case 2:
			toReturn = getColor(GREEN);
			break;
		case 3:
			toReturn = getColor(BLUE);
			break;
		case 4:
			toReturn = getColor(PURPLE);
			break;
		case 5:
			toReturn = getColor(TEAL);
			break;
		case 6:
			toReturn = getColor(ORANGE);
			break;
		case 7:
			toReturn = getColor(WHITE);
			break;
		default:
			toReturn = getColor(OFF);
	}

	return toReturn; 
}

void printColor(Color toPrint) // Print a color out to the serial port
{
	Serial.print("R: "); Serial.print(toPrint.red);
	Serial.print(" | G: "); Serial.print(toPrint.green);
	Serial.print(" | B: "); Serial.println(toPrint.blue);
}

