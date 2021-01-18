#ifndef _WIRELESS_MANAGER_H
#define _WIRELESS_MANAGER_H

#include <Arduino.h>

#include <RF24.h>

#include "utils/Runnable.h"

class WirelessManager : public Runnable
{
private:
    enum State
    {
        NOT_FOUND,
        LISTENING,
        RESPONDING
    } state = NOT_FOUND;

    struct dataStruct
    {
        unsigned long id;
        long lux = -1;
    } response;

    byte addresses[2][6] = {"trsmt", "reciv"};
    RF24 radio;

protected:
    virtual void setup();
    virtual void loop();

public:
    WirelessManager(byte mCeAttach, byte mCsnAttach) : radio(RF24(mCeAttach, mCsnAttach))
    {
    }
};

#endif