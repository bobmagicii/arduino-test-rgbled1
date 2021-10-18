#pragma once

#include "../Shed.fwd.h"

#include <Array.h>
#include "LEDMode.h"
#include "../Util/RGB.h"

using Taskable = Local::Shed::Taskable;
using Engine = Local::Shed::Engine;
using RGB = Local::Util::RGB;

namespace Local::Device { class LED: public Taskable {

	private: LEDMode
	Mode = LEDMode::Off;

	private: Engine*
	Sh;

	private: int
	PinRed;

	private: int
	PinGrn;

	private: int
	PinBlu;

	private: unsigned short
	R = 0;

	private: unsigned short
	G = 0;

	private: unsigned short
	B = 0;

	private: unsigned short
	A = 64;

	private: bool
	Ready = FALSE;

	private: unsigned short
	SeqKey;

	private: unsigned short
	SeqMax;

	private: unsigned short
	SeqLen;

	private: Array<RGB*, 32>*
	SeqVal;

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public:
	LED(Engine *Sh, int PinRed, int PinGrn, int PinBlu, bool Init=TRUE) {

		this->Sh = Sh;
		this->PinRed = PinRed;
		this->PinGrn = PinGrn;
		this->PinBlu = PinBlu;

		this->SeqKey = 0;
		this->SeqVal = new Array<RGB*, 32>;

		if(Init)
		this->InitPins();

		return;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: virtual bool
	OnTaskUpdate(Engine* Sh) {

		KNOWN(Sh);

		switch(this->Mode) {
			case LEDMode::SequenceOnce:
			case LEDMode::SequenceLoop:
				#ifdef DEBUG_DEVICE_LED_TASK
				this->PrintDebug("Sequence","OnTaskUpdate");
				#endif

				this->OnSequenceStep();
				return TRUE;
			break;
			case LEDMode::Off:
				#ifdef DEBUG_DEVICE_LED_TASK
				this->PrintDebug("Off","OnTaskUpdate");
				#endif

				this->SetRGBV(ColourArgvBlack);
			break;
			default:
				#ifdef DEBUG_DEVICE_LED_TASK
				this->PrintDebug("Normal","OnTaskUpdate");
				#endif

				this->SetRGBV(this->R, this->G, this->B);
			break;
		}

		return false;
	};

	public: bool
	OnSequenceStep() {

		// within range of our sequence list do the colour the sequence
		// says to do.

		if(this->SeqKey < this->SeqLen) {
			#ifdef DEBUG_DEVICE_LED_SEQUENCE
			this->PrintDebug(
				("SeqKey=" + String(this->SeqKey)),
				"OnSequenceStep"
			);
			#endif

			this->SetRGB(this->SeqVal->at(this->SeqKey));
			this->SeqKey++;
			return true;
		}

		// if we just iterated out of sequence range decide how to prepare
		// for the next step.

		if(this->SeqKey > this->SeqMax)
		switch(this->Mode) {
			case LEDMode::SequenceLoop:
				#ifdef DEBUG_DEVICE_LED_SEQUENCE
				this->PrintDebug("Restarted","OnSequenceStep");
				#endif

				this->SeqKey = 0;
				return true;
			break;
			default:
				#ifdef DEBUG_DEVICE_LED_SEQUENCE
				this->PrintDebug("Done","OnSequenceStep");
				#endif

				this->SeqKey = 0;
				this->Mode = LEDMode::Normal;
				return false;
			break;
		}

		return false;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: LED*
	InitPins(void) {

		pinMode(this->PinRed,OUTPUT);
		pinMode(this->PinGrn,OUTPUT);
		pinMode(this->PinBlu,OUTPUT);

		return this;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: bool
	IsMode(LEDMode Mode) {

		return this->Mode == Mode;
	};

	public: bool
	IsOff() {

		return (
			TRUE
			&& this->R == 0
			&& this->G == 0
			&& this->B == 0
		);
	};

	public: bool
	IsOn() {

		return (
			FALSE
			|| this->R != 0
			|| this->G != 0
			|| this->B != 0
		);
	};

	public: bool
	IsRGB(RGB* Input) {

		return (
			TRUE
			&& this->R == Input->R
			&& this->G == Input->G
			&& this->B == Input->B
		);
	};

	public: bool
	IsRGBV(unsigned short R, unsigned short G, unsigned short B) {

		return (
			TRUE
			&& this->R == R
			&& this->G == G
			&& this->B == B
		);
	};

	public: LED*
	SetRGB(RGB* Input) {

		return this->SetRGBV(Input->R, Input->G, Input->B);
	};

	public: LED*
	SetRGBV(unsigned short R, unsigned short G, unsigned short B) {

		analogWrite(
			this->PinRed,
			(this->R = (R * (this->A / 255.0)))
		);

		analogWrite(
			this->PinGrn,
			(this->G = (G * (this->A / 255.0)))
		);

		analogWrite(
			this->PinBlu,
			(this->B = (B * (this->A / 255.0)))
		);

		return this;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: void
	BeginTestRGB(unsigned short DelayMS=500, unsigned short SeqOffset=0) {

		this->Mode = LEDMode::SequenceOnce;

		this->SeqVal->clear();
		this->SeqVal->push_back(new RGB(ColourArgvRed));
		this->SeqVal->push_back(new RGB(ColourArgvGreen));
		this->SeqVal->push_back(new RGB(ColourArgvBlue));
		this->SeqVal->push_back(new RGB(ColourArgvBlack));
		this->SeqVal->push_back(new RGB(ColourArgvWhite));
		this->SeqVal->push_back(new RGB(ColourArgvBlack));
		this->SeqVal->push_back(new RGB(ColourArgvWhite));
		this->SeqVal->push_back(new RGB(ColourArgvBlack));

		this->SeqLen = this->SeqVal->size();
		this->SeqMax = this->SeqLen - 1;
		this->SeqKey = SeqOffset % this->SeqLen;

		this->Sh->AddTask(this,DelayMS);
		return;
	};

	public: void
	BeginLoopRGB(unsigned short DelayMS=50, unsigned short SeqOffset=0) {

		this->Mode = LEDMode::SequenceLoop;

		this->SeqVal->clear();
		this->SeqVal->push_back(new RGB(ColourArgvRed));
		this->SeqVal->push_back(new RGB(ColourArgvOrange));
		this->SeqVal->push_back(new RGB(ColourArgvYellow));
		this->SeqVal->push_back(new RGB(ColourArgvGreen));
		this->SeqVal->push_back(new RGB(ColourArgvSeafoam));
		this->SeqVal->push_back(new RGB(ColourArgvTeal));
		this->SeqVal->push_back(new RGB(ColourArgvBlue));
		this->SeqVal->push_back(new RGB(ColourArgvSky));
		this->SeqVal->push_back(new RGB(ColourArgvPurple));
		this->SeqVal->push_back(new RGB(ColourArgvPink));

		this->SeqLen = this->SeqVal->size();
		this->SeqMax = this->SeqLen - 1;
		this->SeqKey = SeqOffset % this->SeqLen;

		this->Sh->AddTask(this,DelayMS);
		return;
	};

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
			"[Device::LED::%s] %s\n",
			Prefix,
			Message
		);

		return;
	};

}; };

