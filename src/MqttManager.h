#ifndef _MQTT_MANAGER_H
#define _MQTT_MANAGER_H

#include "arduino.h"

#include <Adafruit_MQTT_Client.h>
#include <ESP8266WiFi.h>

#include "Runnable.h"
#include "utils/ProjectCredentials.h"

class MqttManager : public Runnable
{
private:
	enum WifiState
	{
		WIFI_DISCONNECTED = 0,
		WIFI_CONNECTING = 1,
		WIFI_CONNECTED = 2
	} wifiConnectState;

	enum MqttState
	{
		MQTT_DISCONNECTED = 0,
		MQTT_TIMEOUT = 1,
		MQTT_CONNECTED = 2
	} mqttConnectState;

	unsigned long connectDelayMs = 0L;
	const unsigned long CONNECT_DEBOUNCE_MS = 10L;

	uint8_t conn;
	uint8_t mqttTimeout = 4;

	WiFiClient client;
	Adafruit_MQTT_Client mqtt;
	Adafruit_MQTT_Publish publishTest;

	void connectWifi();
	void connectMqtt();

public:
	MqttManager(char topic[]) :
		mqtt(Adafruit_MQTT_Client(&client, MQTT_SERVER, MQTT_PORT, MQTT_USERNAME, MQTT_PWD)),
		publishTest(&mqtt, topic)
	{}

	void sendMsg(char data[]);

protected:
	void setup();
	void loop();
};

#endif

