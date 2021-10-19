#pragma once

#include "../../Local/Shed/Engine.h"
#include "../../Local/Device/Button.h"
#include "../../Local/Device/LED.h"

using Engine = Local::Shed::Engine;
using Button = Local::Device::Button;
using LED = Local::Device::LED;
using LEDMode = Local::Device::LEDMode;

namespace App::Device { class CycleButton: public Button {

	private: LED**
	LEDs;

	private: unsigned short
	SeqKey = 0;

	public:
	CycleButton(Engine* Sh, unsigned short Pin, bool Init=TRUE):
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

			if(this->LEDs[Iter]->GetMode() == LEDMode::Off)
			continue;

			switch(this->SeqKey) {
				case 0:
					this->LEDs[Iter]->BeginTestRGB();
					this->LEDs[Iter]->SetMode(LEDMode::SequenceLoop);
				break;
				case 1:
					this->LEDs[Iter]->BeginLoopRGB();
					this->LEDs[Iter]->SetMode(LEDMode::SequenceLoop);
				break;
			}

		}

		this->SeqKey = (this->SeqKey + 1) % 2;

		this->PrintDebug("Cycle Pressed","OnPress");
		return;
	};

	public: virtual void
	OnRelease(void) {
		this->PrintDebug("Cycle Released","OnRelease");
		return;
	};

}; };
