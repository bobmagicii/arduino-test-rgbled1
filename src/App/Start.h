#pragma once

#define PINARGV_RGBLED1 5, 6, 7
#define PINARGV_RGBLED2 8, 9, 10

#include "../Local/Common.h"
#include "../Local/Shed.h"
#include "../Local/Device/LED.h"

void
PrintDebug(const char* Message, const char* Prefix=" DEBUG") {

	printf(
		"[App%s] %s\n",
		Prefix,
		Message
	);

	return;
};
