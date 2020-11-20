/*
 Name:		serveur_maison_v2.ino
 Created:	20/11/2020 12:11:01
 Author:	Toni
*/

// Reformat code: ctrl K + D

#include "Led.h"

#define LED_PIN LED_BUILTIN

Led led(LED_PIN);

void setup()
{
	led.setup();
}

unsigned long startTimeMs = 500;
boolean test = true;

void loop()
{
	led.loop();

	if (test)
	{
		test = false;
		led.blinkErrorCode(10);
		startTimeMs = millis();
	}
}