#ifndef _MQTT_MANAGER_H
#define _MQTT_MANAGER_H

#include "arduino.h"

#include <ESP8266WiFi.h>
#include <ArduinoMqttClient.h>

#include "../Runnable.h"
#include "../utils/ProjectCredentials.h"

#include "../Led.h"
#include "../WifiManager.h"

class MqttManager : public Runnable
{
private:
	enum MqttState
	{
		DISCONNECTED = 0,
		TIMEOUT = 1,
		CONNECTED = 2
	} mqttConnectState;

	unsigned long pingDelayMs = 0L;
	const unsigned long PING_DELAY_MS = 1000L;

	WifiManager wifiManager;

	uint8_t conn;
	uint8_t mqttTimeout = 4;

protected:
	virtual void setup();
	virtual void loop();
	
	Led& led;
	MqttClient mqttClient;

public:
	MqttManager(Led& mLed) :
		led(mLed),
		wifiManager(WifiManager(mLed)),
		mqttClient(wifiManager.getClient())
	{}

	MqttClient& getClient();

	boolean isMqttConnected();
};

#endif

