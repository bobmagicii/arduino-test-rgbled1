#pragma once

#include "../../Local/Shed/Engine.h"
#include "../../Local/Device/Button.h"
#include "../../Local/Device/LED.h"

using Engine = Local::Shed::Engine;
using Button = Local::Device::Button;
using LED = Local::Device::LED;
using LEDMode = Local::Device::LEDMode;

namespace App::Device { class PowerButton: public Button {

	private: LED**
	LEDs;

	public:
	PowerButton(Engine* Sh, unsigned short Pin, bool Init=TRUE):
	Button(Sh, Pin, Init) {

		return;
	};

	public: void
	SetLEDs(LED** InputList) {

		this->LEDs = InputList;

		return;
	};

	public: virtual void
	OnPress(void) {

		unsigned short Iter = sizeof(this->LEDs);

		while(Iter > 0) {
			Iter--;

			switch(this->LEDs[Iter]->GetMode()) {
				case LEDMode::Off:
					this->LEDs[Iter]->SetMode(LEDMode::Normal);
					this->LEDs[Iter]->SetRGBV(ColourArgvRed);
				break;
				default:
					this->LEDs[Iter]->SetMode(LEDMode::Off);
				break;
			}
		}

		this->PrintDebug("Power Pressed","OnPress");
		return;
	};

	public: virtual void
	OnRelease(void) {
		this->PrintDebug("Power Released","OnRelease");
		return;
	};

}; };
