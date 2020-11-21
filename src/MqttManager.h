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

	Led& led;
	WifiManager& wifiManager;
	WiFiClient& client;

	Adafruit_MQTT_Client mqtt;
	Adafruit_MQTT_Publish publishTest;

	void connectMqtt();

public:
	MqttManager(WiFiClient& mClient, Led& mLed, WifiManager& mManager, char topic[]) :
		client(mClient),
		led(mLed),
		wifiManager(mManager),
		mqtt(Adafruit_MQTT_Client(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PWD)),
		publishTest(&mqtt, topic)
	{}

	void sendMsg(char data[]);

protected:
	void setup();
	void loop();
};

#endif

