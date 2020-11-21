#include "SendMessageMqttManager.h"

void SendMessageMqttManager::sendMessage(char message[])
{
	if (SendMessageMqttManager::isMqttConnected())
	{
		if (!publisher.publish(message))
			led.blinkErrorCode(5);
	}
}