#ifndef _MQTT_MANAGER_H
#define _MQTT_MANAGER_H

#include "arduino.h"

#include <Adafruit_MQTT_Client.h>
#include <ESP8266WiFi.h>

#include "Runnable.h"
#include "utils/ProjectCredentials.h"

#include "Led.h"
#include "WifiManager.h"

class MqttManager : public Runnable
{
private:
	enum MqttState
	{
		DISCONNECTED = 0,
		TIMEOUT = 1,
		CONNECTED = 2
	} mqttConnectState;

	uint8_t conn;
	uint8_t mqttTimeout = 4;

	WifiManager& wifiManager;
	WiFiClient& client;

	void connectMqtt();

protected:
	Led& led;
	Adafruit_MQTT_Client mqtt;

	void setup();
	void loop();

	boolean isMqttConnected();

public:
	MqttManager(WiFiClient& mClient, Led& mLed, WifiManager& mManager) :
		client(mClient),
		led(mLed),
		wifiManager(mManager),
		mqtt(Adafruit_MQTT_Client(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PWD))
	{}
};

#endif

