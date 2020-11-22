/*
 Name:		serveur_maison_v2.ino
 Created:	20/11/2020 12:11:01
 Author:	Toni
*/

// Reformat code: ctrl K + D
// Comment code: ctrl + K + C
// Uncomment code: ctrl + K + U

#include <ArduinoMqttClient.h>

#include "src/Runnable.h"
#include "src/Led.h"

#include "src/mqtt/MqttManager.h"
#include "src/mqtt/MqttMessageSender.h"

#include "src/yeelight/YeelightLamp.h"
#include "src/yeelight/YeelightReceiver.h"

#define LED_PIN LED_BUILTIN
#define MQTT_TOPIC_PREFIX "esp8266-server-home/"

Runnable* Runnable::headRunnable = NULL;

Led led = Led(LED_PIN);
MqttManager mqttManager = MqttManager(led);

MqttMessageSender publisher = MqttMessageSender(mqttManager, MQTT_TOPIC_PREFIX "pubTest", led);

YeelightReceiver lampReceiver = YeelightReceiver(mqttManager, MQTT_TOPIC_PREFIX "yeelight", led);

void setup()
{
	Serial.begin(115200);
	Runnable::setupAll();
}

unsigned long startTimeMs = 500;
boolean test = true;

MqttClient client = mqttManager.getClient();

void loop()
{
	Runnable::loopAll();

	if (millis() - startTimeMs > 5000)
	{
		publisher.sendMessage("Imotep");
		startTimeMs = millis();
	}
}