#include "mqtt/MqttMessageSender.h"

void MqttMessageSender::setup()
{
}

void MqttMessageSender::loop()
{
}

void MqttMessageSender::sendMessage(const char message[])
{
	if (manager.isMqttConnected())
	{
		mqttClient.beginMessage(topic);
		mqttClient.print(message);
		mqttClient.endMessage();
	}
}