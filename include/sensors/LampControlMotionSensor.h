#ifndef _LampControlMotionSensor_h
#define _LampControlMotionSensor_h

#include <Arduino.h>

#include "MotionSensor.h"
#include "../yeelight/YeelightLamp.h"

class LampControlMotionSensor : public MotionSensor
{
private:
	YeelightLamp& lamp;

protected:
	virtual void onStateChanged(boolean state);

public:
	LampControlMotionSensor(byte attachTo, YeelightLamp& mLamp) :
		MotionSensor(attachTo),
		lamp(mLamp)
	{}
};

#endif

