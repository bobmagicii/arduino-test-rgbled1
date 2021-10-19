//#define DEBUG_SHED_ENGINE_UPDATE
//#define DEBUG_DEVICE_LED_SEQUENCE
//#define DEBUG_DEVICE_LED_TASK

#define LocalSerialBaudRate 9600

#include "App/Start.h"

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

Local::Shed::Engine* Shed;
Local::Device::LED* RGBLED[2];
Local::Device::Button* Btn[2];

bool Ready = FALSE;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void setup() {

	Serial.begin(LocalSerialBaudRate);

	// this is what is going to run all the things that need to be done.
	Shed = new Local::Shed::Engine;

	// our two rgb leds
	RGBLED[0] = new Local::Device::LED(Shed, PINARGV_RGBLED1);
	RGBLED[1] = new Local::Device::LED(Shed, PINARGV_RGBLED2);

	// our two digital buttons
	Btn[0] = new App::Device::PowerButton(Shed, PINARGV_BUTTON1);
	Btn[1] = new App::Device::CycleButton(Shed, PINARGV_BUTTON2);

	PrintDebug("Prepare LEDs", " setup()");
	RGBLED[0]->BeginTestRGB();
	RGBLED[1]->BeginTestRGB();

	PrintDebug("Prepare Buttons", " setup()");
	((App::Device::PowerButton *)Btn[0])->SetLEDs(RGBLED);
	((App::Device::CycleButton *)Btn[1])->SetLEDs(RGBLED);

	return;
};

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

void loop() {
	Shed->Update();

	if(!Ready)
	if(RGBLED[0]->IsMode(Local::Device::LEDMode::Normal))
	if(RGBLED[1]->IsMode(Local::Device::LEDMode::Normal)) {
		Ready = TRUE;
		PrintDebug("All LEDs Ready"," loop()");
		RGBLED[0]->BeginLoopRGB(50, 2);
		RGBLED[1]->BeginLoopRGB(50, 0);
	}

	//delay(900);
	return;
};
