#include "sensors/LampControlMotionSensor.h"

void LampControlMotionSensor::onStateChanged(boolean state)
{
	Serial.print("State changed: ");
	Serial.println(state);

	Serial.print("Lamp in auto mode ?: ");
	Serial.println(lamp.isInModeAuto());

	if (lamp.isInModeAuto())
	{
		if (state)
			lamp.powerOn();
		else
			lamp.powerOff();
	}
}