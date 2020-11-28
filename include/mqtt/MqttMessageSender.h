#ifndef _SendMessageMqttManager_h
#define _SendMessageMqttManager_h

#include <Arduino.h>

#include "../utils/Runnable.h"
#include "MqttManager.h"

class MqttMessageSender : public Runnable
{
private:
	MqttManager& manager;
	MqttClient mqttClient;
	Led& led;

	const char* topic;

protected:
	virtual void setup();
	virtual void loop();

public:
	MqttMessageSender(MqttManager& mManager, const char mTopic[], Led mLed) :
		manager(mManager),
		mqttClient(mManager.getClient()),
		led(mLed),
		topic(mTopic)
	{}

	void sendMessage(const char message[]);
};

#endif