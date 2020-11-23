// YeelightLamp.h

#ifndef _YeelightLamp_h
#define _YeelightLamp_h

#include "arduino.h"
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>

#include "../utils/Runnable.h"
#include "../utils/ProjectCredentials.h"

class YeelightLamp : Runnable
{
private:
	enum State
	{
		POWER_ON,
		POWER_OFF
	} state;

	boolean isAutoEnabled = true;

	WiFiClient client;
	unsigned long requestId = 0;

	void toggleLight(const boolean lampState);
	String serializeJsonCommand(const boolean lampState);

protected:
	virtual void setup();
	virtual void loop();

public:
	YeelightLamp() :
		client(WiFiClient())
	{};

	void powerOn();
	void powerOff();
	void setModeAuto(boolean isAuto);

	boolean isInModeAuto();
};

#endif

