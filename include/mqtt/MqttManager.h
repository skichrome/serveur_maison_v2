#ifndef _MQTT_MANAGER_H
#define _MQTT_MANAGER_H

#include <Arduino.h>

#include <WiFi.h>
#include <ArduinoMqttClient.h>

#include "../utils/Runnable.h"
#include "../utils/ProjectCredentials.h"

#include "../utils/Led.h"
#include "../wifi/WifiManager.h"

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

	unsigned long timeoutDelayMs = 0L;
	const unsigned long TIMEOUT_DELAY_MS = 60000L;

	Led &led;
	WifiManager wifiManager;
	MqttClient mqttClient;

	uint8_t conn;
	uint8_t mqttTimeout = 4;


protected:
	virtual void setup();
	virtual void loop();

public:
	MqttManager(Led &mLed) : led(mLed),
							 wifiManager(WifiManager(mLed)),
							 mqttClient(wifiManager.getClient())
	{
	}

	MqttClient &getClient();

	boolean isMqttConnected();
};

#endif
