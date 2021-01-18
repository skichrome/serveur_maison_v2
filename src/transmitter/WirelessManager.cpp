#include "transmitter/WirelessManager.h"

void WirelessManager::setup()
{
    while (!radio.begin())
    {
        state = WirelessManager::NOT_FOUND;
    }

    radio.setPALevel(RF24_PA_LOW);
    radio.openWritingPipe(addresses[0]);
    radio.openReadingPipe(1, addresses[1]);
    radio.startListening();

    state = WirelessManager::LISTENING;
}

void WirelessManager::loop()
{
    switch (state)
    {
    case WirelessManager::NOT_FOUND:
        break;
    case WirelessManager::LISTENING:
        if (radio.available())
        {
            do
            {
                Serial.println("Reading incoming msg");
                
                radio.read(&response, sizeof(response));
            } while (radio.available());

            state = WirelessManager::RESPONDING;
        }
        break;
    case WirelessManager::RESPONDING:
        radio.stopListening();
        radio.write(&response, sizeof(response));
        radio.startListening();

        Serial.println("Sent response");

        state = WirelessManager::LISTENING;
        break;
    default:
        break;
    }
}