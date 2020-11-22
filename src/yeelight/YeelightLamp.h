// YeelightLamp.h

#ifndef _YeelightLamp_h
#define _YeelightLamp_h

#include "arduino.h"

#include "../Runnable.h"

class YeelightLamp : Runnable
{
private:
	enum State
	{
		POWER_ON,
		POWER_OFF
	};

protected:
	virtual void setup();
	virtual void loop();

public:
	YeelightLamp() {};

	void powerOn();
	void powerOff();
};

#endif

