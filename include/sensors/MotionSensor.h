#ifndef _MotionDetector_h
#define _MotionDetector_h

#include <Arduino.h>

#include "../utils/Runnable.h"

class MotionSensor : Runnable
{
private:
	byte pin;

	enum State
	{
		TRIGGERED,
		WAITING_TRIGGER,
	} state;

	State previousState = WAITING_TRIGGER;

	unsigned long timeBetweenReadsMs = 0L;
	const unsigned long TIME_BETWEEN_READS_MS = 500L;

protected:
	virtual void setup();
	virtual void loop();

	virtual void onStateChanged(boolean state) = 0;

public:
	MotionSensor(byte attachTo) :
		pin(attachTo)
	{}
};

#endif