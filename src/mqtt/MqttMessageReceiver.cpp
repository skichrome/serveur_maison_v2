#include "MqttMessageReceiver.h"

void MqttMessageReceiver::setup()
{
	if (manager.isMqttConnected())
		state = MqttMessageReceiver::LISTENING;
	else
		state = MqttMessageReceiver::DISCONNECTED;
}

void MqttMessageReceiver::loop()
{
	switch (MqttMessageReceiver::state)
	{
	case MqttMessageReceiver::DISCONNECTED:
		if (manager.isMqttConnected())
		{
			mqttClient.subscribe(topic);
			state = MqttMessageReceiver::LISTENING;
		}
		break;
	case MqttMessageReceiver::LISTENING:
		if (!manager.isMqttConnected())
			state = MqttMessageReceiver::DISCONNECTED;
		else
			handleMessage();
		break;
	default:
		break;
	}
}

void MqttMessageReceiver::handleMessage()
{
	unsigned int msgSize = mqttClient.parseMessage();
	if (msgSize)
	{
		Serial.println(mqttClient.messageTopic());
		String msgStr = "";

		unsigned int position = 0;

		while (mqttClient.available())
		{	
			msgStr = mqttClient.readString();
		}
		onMessageReceived(msgStr);
	}
}