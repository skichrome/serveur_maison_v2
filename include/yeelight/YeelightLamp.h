// YeelightLamp.h

#ifndef _YeelightLamp_h
#define _YeelightLamp_h

#include <Arduino.h>
#include <WiFi.h>
#include <ArduinoJson.h>

#include "../utils/Runnable.h"
#include "../utils/ProjectCredentials.h"

class YeelightLamp : Runnable
{
private:
	enum State
	{
		POWER_ON,
		POWER_OFF
	} state = POWER_OFF;

	unsigned long readLampStateDelayMs = 0L;
	const unsigned long READ_LAMP_DELAY_MS = 15000L;

	boolean isAutoEnabled = true;

	WiFiClient client;
	unsigned long requestId = 1;
	unsigned long requestStateId = 2;

	void toggleLight(const boolean lampState);
	String serializeJsonCommand(const boolean lampState);
	String serializeJsonStateCommand();
	void deserializeJsonStateCommand(String json);

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

