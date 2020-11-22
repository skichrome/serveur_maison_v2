#include "MqttManager.h"

void MqttManager::setup()
{
	mqttConnectState = MqttManager::DISCONNECTED;

	if (wifiManager.isWifiConnected())
	{
		do
		{
			delay(20);
		} while (!mqttClient.connect(MQTT_SERVER, MQTT_PORT));

		mqttConnectState = MqttManager::CONNECTED;
	}
}

void MqttManager::loop()
{
	if (wifiManager.isWifiConnected())
	{
		switch (mqttConnectState)
		{
		case MqttManager::DISCONNECTED:
			conn = mqttClient.connect(MQTT_SERVER, MQTT_PORT);
			if (conn)
			{
				mqttConnectState = MqttManager::CONNECTED;
				mqttTimeout = 4;
			}
			else if (mqttTimeout-- <= 0)
			{
				mqttConnectState = MqttManager::TIMEOUT;
				timeoutDelayMs = millis();
			}
			break;
		case MqttManager::CONNECTED:
			if (!mqttClient.connected())
				mqttConnectState = MqttManager::DISCONNECTED;

			if (millis() - pingDelayMs > PING_DELAY_MS)
			{
				pingDelayMs = millis();
				mqttClient.poll(); // Ping server
			}
			break;
		case MqttManager::TIMEOUT:
			if (millis() - timeoutDelayMs >= TIMEOUT_DELAY_MS)
			{
				mqttConnectState = MqttManager::DISCONNECTED;
				timeoutDelayMs = millis();
			}
			led.blinkErrorCode(9);
			break;
		default:
			break;
		}
	}
}

boolean MqttManager::isMqttConnected()
{
	return mqttConnectState == MqttManager::CONNECTED;
}

MqttClient& MqttManager::getClient()
{
	return mqttClient;
}