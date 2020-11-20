/*
 Name:		serveur_maison_v2.ino
 Created:	20/11/2020 12:11:01
 Author:	Toni
*/

// Reformat code: ctrl K + D
// Comment code: ctrl + K + C
// Uncomment code: ctrl + K + U

#include "src/Runnable.h"
#include "src/Led.h"

Runnable* Runnable::headRunnable = NULL;

#define LED_PIN LED_BUILTIN
Led led(LED_PIN);

void setup()
{
	Runnable::setupAll();
}

unsigned long startTimeMs = 500;
boolean test = true;

void loop()
{
	Runnable::loopAll();

	if (test)
	{
		test = false;
		led.blinkErrorCode(10);
		startTimeMs = millis();
	}
}