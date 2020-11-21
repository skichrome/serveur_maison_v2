#ifndef _SendMessageMqttManager_h
#define _SendMessageMqttManager_h

#include "arduino.h"

#include "MqttManager.h"

class SendMessageMqttManager: MqttManager
{
private:
	Adafruit_MQTT_Publish publisher;

public:
	SendMessageMqttManager(WiFiClient& mClient, Led& mLed, WifiManager& mManager, char topic[]) :
		MqttManager(mClient, mLed, mManager),
		publisher(&mqtt, topic)
	{}

	void sendMessage(char message[]);
};

#endif