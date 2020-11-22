#include "YeelightReceiver.h"

void YeelightReceiver::onMessageReceived(String message)
{
	Serial.print("OnMessageReceived: ");
	Serial.println(message);
	led.blinkErrorCode(1);
}