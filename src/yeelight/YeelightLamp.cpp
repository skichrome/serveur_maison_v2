#include "YeelightLamp.h"

void YeelightLamp::setup()
{
}

void YeelightLamp::loop()
{
}

void YeelightLamp::powerOn()
{
	toggleLight(true);
}

void YeelightLamp::powerOff()
{
	toggleLight(false);
}

void YeelightLamp::toggleLight(const boolean lampState)
{
	if (client.connect(YEELIGHT_IP, YEELIGHT_PORT))
	{
		client.println(serializeJsonCommand(lampState));
		client.stop();
	}
}

String YeelightLamp::serializeJsonCommand(const boolean lampState)
{
	const size_t capacity = JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(3);
	DynamicJsonDocument doc(capacity);

	doc["id"] = ++requestId;
	doc["method"] = "set_power";

	JsonArray params = doc.createNestedArray("params");
	params.add(lampState ? "on" : "off");
	params.add("smooth");
	params.add(500);
	if (lampState)
		params.add(1);

	String output = "";
	serializeJson(doc, output);
	return output;
}