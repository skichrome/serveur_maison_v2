#include "MotionSensor.h"

void MotionSensor::setup()
{
	pinMode(pin, INPUT_PULLUP);
}

void MotionSensor::loop()
{
	if (millis() - timeBetweenReadsMs > TIME_BETWEEN_READS_MS)
	{
	
		if (digitalRead(pin))
			state = MotionSensor::TRIGGERED;
		else
			state = MotionSensor::WAITING_TRIGGER;
		
		if (state != previousState)
		{
			switch (state)
			{
			case MotionSensor::TRIGGERED:
				onStateChanged(true);
				break;
			case MotionSensor::WAITING_TRIGGER:
				onStateChanged(false);
				break;
			default:
				break;
			}
			previousState = state;
		}

		timeBetweenReadsMs = millis();
	}
}