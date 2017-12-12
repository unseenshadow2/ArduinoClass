// Pins
#define SER 8
#define LATCH 9
#define CLK 10
#define DIST A0

// Animation stuff
#define ANIM_MIN 250
#define ANIM_MAX 5000

// Sensor stuff
#define SENSOR_MAX 650
#define SENSOR_MIN 0

// Etc.
#define VALS_SIZE 9

// Possible LED settings
int vals[] = {0,1,3,7,15,31,63,127,255};
unsigned long currentPause = 500; // The current time between animations
unsigned long lastRun = 0; // Our last runs
int pos = 0; // Our position in the animation
bool isGoingUp = true; // Are we traveling up or down

void shiftWrite(byte data);
void shiftWrite(byte* data, int size);
void lightRiderRun();
void advancePos();

void setup() 
{
	// Output pins
	pinMode(SER, OUTPUT);
	pinMode(LATCH, OUTPUT);
	pinMode(CLK, OUTPUT);

	shiftWrite(vals[pos]);

	Serial.begin(9600);
}

void loop()
{
	currentPause = analogRead(DIST);
	currentPause = map(currentPause, SENSOR_MIN, SENSOR_MAX, ANIM_MIN, ANIM_MAX);
	currentPause = constrain(currentPause, ANIM_MIN, ANIM_MAX);

	lightRiderRun();
}

void shiftWrite(byte data) { shiftWrite(&data, 1); }
void shiftWrite(byte* data, int size)
{
	for (int i = 0; i < size; i++)
	{
		digitalWrite(LATCH, LOW);
		shiftOut(SER, CLK, MSBFIRST, *(data + i));
		digitalWrite(LATCH, HIGH);
	}
}

// Handle the animation
void lightRiderRun()
{
	if (millis() >= (lastRun + currentPause)) // Timing
	{
		advancePos();
		shiftWrite(vals[pos]);
		lastRun = millis();
		Serial.print("Last Run: ");
		Serial.print(lastRun);
		Serial.print(" | Current Pause: ");
		Serial.print(currentPause);
		Serial.print(" | Sum: ");
		Serial.println(lastRun + currentPause);
	}
}

// Handle advancing the position
void advancePos()
{
	if (isGoingUp)
	{
		++pos;
		if (pos >= (VALS_SIZE - 1)) isGoingUp = false;
	}
	else
	{
		--pos;
		if (pos <= 0) isGoingUp = true;
	}
}

