#include "wifi/WifiManager.h"

void WifiManager::setup()
{
	wifiConnectState = WifiManager::DISCONNECTED;

	do
	{
		connectWifi();
		delay(20);
	} while (wifiConnectState != WifiManager::CONNECTED);
}

void WifiManager::loop()
{
	connectWifi();
}

void WifiManager::connectWifi()
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
			handleWifiError();
			connectDelayMs = millis();
		}
		break;
	case WifiManager::CONNECTED:
		if (WiFi.status() != WL_CONNECTED)
			wifiConnectState = WifiManager::DISCONNECTED;
		break;
	default:
		break;
	}
}

void WifiManager::handleWifiError()
{
	switch (WiFi.status())
	{
	case WL_NO_SSID_AVAIL: // Configured SSID is not available
		led.blinkErrorCode(10);
		break;
	case WL_CONNECT_FAILED: // Password is incorrect
		led.blinkErrorCode(10);
		break;
	case WL_CONNECTED: // Connexion successful
		wifiConnectState = WifiManager::CONNECTED;
		led.blinkErrorCode(1);
		break;
	default:
		break;
	}
}

boolean WifiManager::isWifiConnected()
{
	return wifiConnectState == WifiManager::CONNECTED;
}

WiFiClient &WifiManager::getClient()
{
	return client;
}