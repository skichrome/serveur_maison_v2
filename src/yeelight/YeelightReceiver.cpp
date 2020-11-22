#include "YeelightReceiver.h"

void YeelightReceiver::onMessageReceived(String message)
{
	Serial.print("OnMessageReceived: ");
	Serial.println(message);
	led.blinkErrorCode(1);

	if (message == "POWER_ON")
		lamp.powerOn();
	else if (message == "POWER_OFF")
		lamp.powerOff();
}