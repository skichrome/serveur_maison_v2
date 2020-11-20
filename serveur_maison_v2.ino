/*
 Name:		serveur_maison_v2.ino
 Created:	20/11/2020 12:11:01
 Author:	Toni
*/

// Reformat code: ctrl K + D
// Comment code: ctrl + K + C
// Uncomment code: ctrl + K + U

#include <ESP8266WiFi.h>
#include <Adafruit_MQTT_Client.h>
#include "src/Runnable.h"
#include "src/Led.h"
#include "src/MqttManager.h"

Runnable* Runnable::headRunnable = NULL;

#define LED_PIN LED_BUILTIN
Led led = Led(LED_PIN);
MqttManager manager = MqttManager("esp8266/pubTest");

void setup()
{
	Serial.begin(115200);
	Serial.println("main setup called");
	Runnable::setupAll();
}

unsigned long startTimeMs = 500;
boolean test = true;

void loop()
{
	Runnable::loopAll();

	if (test)
	{
		test = false;
		led.blinkErrorCode(10);
		startTimeMs = millis();
	}

	if (millis() - startTimeMs > 5000)
	{
		manager.sendMsg("Imotep");
		startTimeMs = millis();
	}
}