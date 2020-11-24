/*
 Name:		serveur_maison_v2.ino
 Created:	20/11/2020 12:11:01
 Author:	Toni
*/

// Reformat code: ctrl K + D
// Comment code: ctrl + K + C
// Uncomment code: ctrl + K + U

#include <ArduinoMqttClient.h>

#include "src/utils/Runnable.h"
#include "src/Led.h"

#include "src/mqtt/MqttManager.h"
#include "src/mqtt/MqttMessageSender.h"

#include "src/yeelight/YeelightLamp.h"
#include "src/yeelight/YeelightReceiver.h"
#include "src/sensors/LampControlMotionSensor.h"

#define LED_PIN LED_BUILTIN
#define MOTION_SENSOR_GPIO 5
#define MQTT_TOPIC_PREFIX "esp8266-server-home/"

Runnable* Runnable::headRunnable = NULL;

Led led = Led(LED_PIN);
MqttManager mqttManager = MqttManager(led);

MqttMessageSender publisher = MqttMessageSender(mqttManager, MQTT_TOPIC_PREFIX "pubTest", led);

YeelightLamp lamp = YeelightLamp();
YeelightReceiver lampReceiver = YeelightReceiver(mqttManager, lamp, MQTT_TOPIC_PREFIX "yeelight", led);
LampControlMotionSensor lampMotionSensor = LampControlMotionSensor(MOTION_SENSOR_GPIO, lamp);

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