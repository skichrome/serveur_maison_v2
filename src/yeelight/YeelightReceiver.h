#ifndef _YeelightManager_h
#define _YeelightManager_h

#include "arduino.h"
#include "../mqtt/MqttMessageReceiver.h"

#include "YeelightLamp.h"

class YeelightReceiver : public MqttMessageReceiver
{
private:
	YeelightLamp lamp;
	Led& led;

protected:
	virtual void onMessageReceived(String message);

public:
	YeelightReceiver(MqttManager& mManager, char topic[], Led& mLed) :
		MqttMessageReceiver(mManager, topic, mLed),
		lamp(YeelightLamp()),
		led(mLed)
	{}
};

#endif

