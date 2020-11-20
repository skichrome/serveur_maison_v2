// Led.h

#ifndef _LED_h
#define _LED_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

class Led
{
private:
	byte pin;

	enum LedState
	{
		ENABLED = LOW,
		DISABLED = HIGH
	} ledState;

	enum CycleState
	{
		WAITING = 0,
		POWER_ON = 1,
		POWER_OFF = 2,
		PAUSING = 3
	} cycleState;

	unsigned int cycleCount = 0;

	const unsigned long HIGH_DURATION_MS = 250L;
	const unsigned long LOW_DURATION_MS = 500L;
	const unsigned long PAUSING_DURATION_MS = 1000L;

	unsigned long startDurationMs = 0L;

public:
	Led(byte pin);

	void setup();
	void loop();

	void blinkErrorCode(unsigned int code);
};

#endif
