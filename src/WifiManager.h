#ifndef _WifiManager_h
#define _WifiManager_h

#include "arduino.h"
#include <ESP8266WiFi.h>

#include "utils/Runnable.h"
#include "utils/ProjectCredentials.h"

#include "Led.h"

class WifiManager : public Runnable
{
private:
	enum WifiState
	{
		DISCONNECTED = 0,
		CONNECTING = 1,
		CONNECTED = 2
	} wifiConnectState;

	unsigned long connectDelayMs = 0L;
	const unsigned long CONNECT_DEBOUNCE_MS = 10L;

	Led& led;
	WiFiClient client;

	void connectWifi();
	void handleWifiError();

protected:
	virtual void setup();
	virtual void loop();

public:
	WifiManager(Led& mLed) :
		led(mLed)
	{}

	boolean isWifiConnected();

	WiFiClient& getClient();
};

#endif