#pragma once

#include "Taskable.h"
#include "Engine.h"

namespace Local::Shed { class EngineTask {

	public: unsigned long
	TimeInterval = 1000;

	public: unsigned long
	TimePrev = 0;

	public: Taskable*
	Task;

	public:
	EngineTask(Taskable* Task, unsigned long TimeInterval) {

		this->Task = Task;
		this->TimeInterval = TimeInterval;

		return;
	};

	public: bool
	Update(Engine* Eng) {

		bool Result = (
			(this->Task)
			->OnTaskUpdate(Eng)
		);

		this->TimePrev = millis();

		return Result;
	};

	public: bool
	IsTime(unsigned long TimeArdu) {

		return (
			(TimeArdu - this->TimePrev) >= this->TimeInterval
		);
	};

}; };
