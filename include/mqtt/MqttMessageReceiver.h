#ifndef _ReceiveMessageMqttManager_h
#define _ReceiveMessageMqttManager_h

#include <Arduino.h>

#include "../utils/Runnable.h"
#include "MqttManager.h"

class MqttMessageReceiver : public Runnable
{
private:
	enum State
	{
		DISCONNECTED,
		LISTENING
	}state;

	MqttManager& manager;
	MqttClient mqttClient;
	Led& led;

	const char* topic;

	void handleMessage();

protected:
	virtual void setup();
	virtual void loop();

	virtual void onMessageReceived(String message) = 0;

public:
	MqttMessageReceiver(MqttManager& mManager, const char mTopic[], Led& mLed) :
		manager(mManager),
		mqttClient(mManager.getClient()),
		led(mLed),
		topic(mTopic)
	{}
};

#endif

