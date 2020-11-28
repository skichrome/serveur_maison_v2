#include <Arduino.h>

/*
 * Auto indent in VSCode on Linux: ctrl + shift + i
 * Auto indent in VSCode on Windows: shift + alt + F ?
*/

#include <ArduinoMqttClient.h>

#include "utils/Runnable.h"
#include "utils/Led.h"

#include "mqtt/MqttManager.h"
#include "mqtt/MqttMessageSender.h"

#include "yeelight/YeelightLamp.h"
#include "yeelight/YeelightReceiver.h"
#include "sensors/LampControlMotionSensor.h"

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