#include "MqttManager.h"

void MqttManager::setup()
{
}

void MqttManager::loop()
{
	if (wifiManager.isWifiConnected())
		connectMqtt();
}

void MqttManager::connectMqtt()
{
	if (mqtt.connected())
		return;

	switch (mqttConnectState)
	{
	case MqttManager::DISCONNECTED:
		conn = mqtt.connect();
		if (conn == 0)
			mqttConnectState = MqttManager::CONNECTED;
		else if (mqttTimeout-- <= 0)
			mqttConnectState = MqttManager::TIMEOUT;
		break;
	case MqttManager::CONNECTED:
		break;
	case MqttManager::TIMEOUT:
		led.blinkErrorCode(9);
		break;
	default:
		break;
	}
}

void MqttManager::sendMsg(char data[])
{
	if (mqttConnectState == MqttManager::CONNECTED)
	{
		if (!publishTest.publish(data))
			led.blinkErrorCode(5);
	}
}