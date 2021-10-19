#pragma once

#include "../Shed.fwd.h"

#include <Array.h>

using Taskable = Local::Shed::Taskable;
using Engine = Local::Shed::Engine;

namespace Local::Device { class Button: public Taskable {

	private: Engine*
	Sh;

	private: unsigned short
	Pin;

	private: bool
	WasOn = FALSE;

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public:
	Button(Engine *Sh, int Pin, bool Init=TRUE) {

		this->Sh = Sh;
		this->Pin = Pin;

		if(Init)
		this->InitPins();

		return;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: virtual bool
	OnTaskUpdate(Engine* Sh) {

		KNOWN(Sh);

		if(this->IsOn()) {
			if(!this->WasOn) {
				this->OnPress();
				this->WasOn = TRUE;
			}
		}

		else {
			if(this->WasOn) {
				this->OnRelease();
				this->WasOn = FALSE;
			}
		}

		return true;
	};

	public: virtual void
	OnPress(void) {
		this->PrintDebug("Button Pressed","OnPress");
		return;
	};

	public: virtual void
	OnRelease(void) {
		this->PrintDebug("Button Released","OnRelease");
		return;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: void
	InitPins(void) {

		pinMode(this->Pin, INPUT_PULLUP);
		this->BeginListening();

		return;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////


	public: bool
	IsOff() {

		return digitalRead(this->Pin) == HIGH;
	};

	public: bool
	IsOn() {

		return digitalRead(this->Pin) == LOW;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: void
	BeginListening(unsigned short DelayMS=0) {

		this->Sh->AddTask(this, DelayMS);
		return;
	}

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	protected: void
	PrintDebug(String Message, String Prefix="DEBUG") {

		this->PrintDebug(Message.c_str(), Prefix.c_str());
		return;
	};

	protected: void
	PrintDebug(const char* Message, const char* Prefix="DEBUG") {

		printf(
			"[Device::Button::%s] %s\n",
			Prefix,
			Message
		);

		return;
	};

}; };

