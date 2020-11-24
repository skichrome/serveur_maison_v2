#include "YeelightLamp.h"

void YeelightLamp::setup()
{
}

void YeelightLamp::loop()
{
	if (millis() - readLampStateDelayMs > READ_LAMP_DELAY_MS)
	{
		if (client.connect(YEELIGHT_IP, YEELIGHT_PORT))
		{
			client.println(serializeJsonStateCommand());
			client.stop();
		}
		
		readLampStateDelayMs = millis();
	}

	if (client.available())
	{
		String response = "";
		do
		{
			response = client.readStringUntil('\n');
		} while (client.available());
		deserializeJsonStateCommand(response);
		client.stop();
	}	
}

// --- Commands --- //

void YeelightLamp::powerOn()
{
	toggleLight(true);
	state = YeelightLamp::POWER_ON;
}

void YeelightLamp::powerOff()
{
	toggleLight(false);
	state = YeelightLamp::POWER_OFF;
}

void YeelightLamp::toggleLight(const boolean lampState)
{
	if (client.connect(YEELIGHT_IP, YEELIGHT_PORT))
	{
		client.println(serializeJsonCommand(lampState));
		client.stop();
	}
}

// --- Mode Auto --- //

void YeelightLamp::setModeAuto(boolean isAuto)
{
	isAutoEnabled = isAuto;
}

boolean YeelightLamp::isInModeAuto()
{
	return isAutoEnabled;
}

// --- Json --- //

String YeelightLamp::serializeJsonCommand(const boolean lampState)
{
	const size_t capacity = JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(3);
	DynamicJsonDocument doc(capacity);

	doc["id"] = requestId;
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

String YeelightLamp::serializeJsonStateCommand()
{
	const size_t capacity = JSON_ARRAY_SIZE(4) + JSON_OBJECT_SIZE(3);
	DynamicJsonDocument doc(capacity);

	doc["id"] = requestStateId;
	doc["method"] = "get_prop";

	JsonArray params = doc.createNestedArray("params");
	params.add("power");

	String output = "";
	serializeJson(doc, output);
	return output;
}

void YeelightLamp::deserializeJsonStateCommand(String json)
{
	const size_t capacity = JSON_ARRAY_SIZE(2) + JSON_OBJECT_SIZE(3);
	DynamicJsonDocument doc(capacity);

	DeserializationError error = deserializeJson(doc, json);
	if (error)
	{
		Serial.println(error.f_str());
		return;
	}

	const int id = doc["id"];
	const String currentState = doc["result"][0];

	if (id == requestStateId)
	{
		switch (state)
		{
		case YeelightLamp::POWER_ON:
			if (currentState == "off")
			{
				powerOn();
			}
			break;
		case YeelightLamp::POWER_OFF:
			if (currentState == "on")
			{
				powerOff();
			}
			break;
		default:
			break;
		}
	}
	
}