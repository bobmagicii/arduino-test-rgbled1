//#define DEBUG_SHED_ENGINE_UPDATE
//#define DEBUG_DEVICE_LED_SEQUENCE
//#define DEBUG_DEVICE_LED_TASK

#include "src/App/Start.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Local::Shed::Engine* Shed;
Local::Device::LED* RGBLED[2];

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void setup() {

	Serial.begin(115200);

	Shed = new Local::Shed::Engine;
	RGBLED[0] = new Local::Device::LED(Shed, PINARGV_RGBLED1);
	RGBLED[1] = new Local::Device::LED(Shed, PINARGV_RGBLED2);

	PrintDebug("Prepare LEDs"," setup()");
	RGBLED[0]->BeginTestRGB();
	RGBLED[1]->BeginTestRGB();

	return;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void loop() {
	Shed->Update();

	if(RGBLED[0]->IsMode(Local::Device::LEDMode::Normal))
	if(RGBLED[1]->IsMode(Local::Device::LEDMode::Normal)) {
		PrintDebug("All LEDs Ready"," loop()");
		RGBLED[0]->BeginLoopRGB(50, 2);
		RGBLED[1]->BeginLoopRGB(50, 0);
	}

	return;
};
