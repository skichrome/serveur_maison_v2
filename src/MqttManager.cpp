#include "MqttManager.h"

void MqttManager::setup()
{
	Serial.println("MqttManager setup called");
}

void MqttManager::loop()
{
	switch (wifiConnectState)
	{
	case MqttManager::WIFI_DISCONNECTED:
		WiFi.begin(WIFI_SSID, WIFI_PASSWD);
		wifiConnectState = MqttManager::WIFI_CONNECTING;
		break;
	case MqttManager::WIFI_CONNECTING:
		if (millis() - connectDelayMs > CONNECT_DEBOUNCE_MS)
		{
			connectWifi();
			connectDelayMs = millis();
		}
		break;
	case MqttManager::WIFI_CONNECTED:
		connectMqtt();
		break;
	default:
		break;
	}
}

void MqttManager::connectWifi()
{
	switch (WiFi.status())
	{
	case WL_IDLE_STATUS:          // Wifi is changing state
		Serial.println("Changing wifi state");
		break;
	case WL_NO_SSID_AVAIL:        // Configured SSID is not available
		Serial.println("SSID not available");
		break;
	case WL_CONNECT_FAILED:       // Password is incorrect
		Serial.println("incorrect password");
		break;
	case WL_DISCONNECTED:         // The module isn't configured in STA (station) mode
		Serial.println("Module not in STA mode");
		break;
	case WL_CONNECTED:            // Connexion successful
		wifiConnectState = MqttManager::WIFI_CONNECTED;
		Serial.println("Connected");
		break;
	}
}

void MqttManager::connectMqtt()
{
	if (mqtt.connected())
		return;

	switch (mqttConnectState)
	{
	case MqttManager::MQTT_DISCONNECTED:
		conn = mqtt.connect();
		if (conn == 0)
			mqttConnectState = MqttManager::MQTT_CONNECTED;
		else if (mqttTimeout-- <= 0)
			mqttConnectState = MqttManager::MQTT_TIMEOUT;
		break;
	case MqttManager::MQTT_CONNECTED:
		break;
	case MqttManager::MQTT_TIMEOUT:
		Serial.println("Could not connect to mqtt server");
		break;
	default:
		break;
	}
}

void MqttManager::sendMsg(char data[])
{
	if (mqttConnectState == MqttManager::MQTT_CONNECTED)
	{
		if (!publishTest.publish(data))
			Serial.println("An error occurred when sending to mqtt");
	}
}