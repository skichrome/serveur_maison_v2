#ifndef _YeelightManager_h
#define _YeelightManager_h

#include <Arduino.h>

#include "../mqtt/MqttMessageReceiver.h"

#include "YeelightLamp.h"

class YeelightReceiver : public MqttMessageReceiver
{
private:
	YeelightLamp& lamp;
	Led& led;

protected:
	virtual void onMessageReceived(String message);

public:
	YeelightReceiver(MqttManager& mManager, YeelightLamp& mLamp, const char topic[], Led& mLed) :
		MqttMessageReceiver(mManager, topic, mLed),
		lamp(mLamp),
		led(mLed)
	{}
};

#endif

