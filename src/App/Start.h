#pragma once

#define PINARGV_RGBLED1 7, 6, 5
#define PINARGV_RGBLED2 10, 9, 8
#define PINARGV_BUTTON1 3
#define PINARGV_BUTTON2 2
#define STATFPS 16000

#include "../Local/Common.h"
#include "../Local/Shed.h"
#include "../Local/Device/LED.h"
#include "../Local/Device/Button.h"

#include "Device/PowerButton.h"
#include "Device/CycleButton.h"

void
PrintDebugC(const char* Message, const char* Prefix=" DEBUG") {

	printf(
		"[App%s] %s\n",
		Prefix,
		Message
	);

	return;
};


void
PrintDebug(String Message, String Prefix="DEBUG") {

	PrintDebugC(Message.c_str(), Prefix.c_str());
	return;
};
