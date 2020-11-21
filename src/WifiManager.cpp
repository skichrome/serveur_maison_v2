#include "WifiManager.h"

void WifiManager::setup()
{
}

void WifiManager::loop()
{
	switch (wifiConnectState)
	{
	case WifiManager::DISCONNECTED:
		WiFi.begin(WIFI_SSID, WIFI_PASSWD);
		wifiConnectState = WifiManager::CONNECTING;
		break;
	case WifiManager::CONNECTING:
		if (millis() - connectDelayMs > CONNECT_DEBOUNCE_MS)
		{
			connectWifi();
			connectDelayMs = millis();
		}
		break;
	case WifiManager::CONNECTED:
		break;
	default:
		break;
	}
}

void WifiManager::connectWifi()
{
	switch (WiFi.status())
	{
	case WL_IDLE_STATUS:          // Wifi is changing state
		break;
	case WL_NO_SSID_AVAIL:        // Configured SSID is not available
		led.blinkErrorCode(10);
		break;
	case WL_CONNECT_FAILED:       // Password is incorrect
		led.blinkErrorCode(10);
		break;
	case WL_DISCONNECTED:         // The module isn't configured in STA (station) mode
		break;
	case WL_CONNECTED:            // Connexion successful
		wifiConnectState = WifiManager::CONNECTED;
		led.blinkErrorCode(1);
		break;
	}
}

boolean WifiManager::isWifiConnected()
{
	return wifiConnectState == WifiManager::CONNECTED;
}