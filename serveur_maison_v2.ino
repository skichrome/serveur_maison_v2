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
#include "src/WifiManager.h"
#include "src/MqttManager.h"

#define LED_PIN LED_BUILTIN

WiFiClient client;

Runnable* Runnable::headRunnable = NULL;

Led led = Led(LED_PIN);
WifiManager wifiManager = WifiManager(led);
MqttManager mqttManager = MqttManager(client, led, wifiManager, "esp8266/pubTest");

void setup()
{
	Runnable::setupAll();
}

unsigned long startTimeMs = 500;
boolean test = true;

void loop()
{
	Runnable::loopAll();

	if (millis() - startTimeMs > 5000)
	{
		mqttManager.sendMsg("Imotep");
		startTimeMs = millis();
	}
}