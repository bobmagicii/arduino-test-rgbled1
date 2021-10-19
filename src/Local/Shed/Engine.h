#pragma once

#include <Array.h>
#include "Taskable.h"
#include "EngineTask.h"

namespace Local::Shed { class Engine {

	private: unsigned long
	Iter = 0;

	private: unsigned long
	IterPrev = 0;

	private: unsigned long
	Time = 0;

	private: unsigned long
	TimePrev = 0;

	private: unsigned long
	TimeLast = 0;

	private: Array<EngineTask*, 32>
	Tasks;

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public:
	Engine() {
	/*//
	@date 2021-10-17
	//*/

		this->Time     =
		this->TimePrev = millis();

		return;
	};

	////////////////////////////////////////////////////////////////
	////////////////////////////////////////////////////////////////

	public: unsigned long
	GetTime(void) {
	/*//
	@date 2021-10-17
	//*/

		return this->Time;
	};

	public: unsigned long
	GetTimePrev(void) {
	/*//
	@date 2021-10-17
	//*/

		return this->TimePrev;
	};

	public: Engine*
	AddTask(Taskable* Task, int TimeInterval) {
	/*//
	@date 2021-10-17
	//*/

		EngineTask *EngTask = new EngineTask(Task, TimeInterval);

		this->RemoveTask(Task);

		(this->Tasks)
		.push_back(EngTask);

		return this;
	};

	public: Engine*
	RemoveTask(Taskable* Task) {

		size_t Iter = (this->Tasks).size();

		while(Iter > 0) {
			--Iter;

			if(this->Tasks.at(Iter)->Task == Task) {
				this->Tasks.remove(Iter);
			}
		}

		return this;
	};

	public: void
	Update() {
	/*//
	@date 2021-10-17
	//*/

		size_t Iter = 0;
		size_t Max = this->Tasks.size();
		EngineTask *EngTask;

		this->Time = millis();
		this->Iter += 1;

		while(Iter < Max) {

			EngTask = (this->Tasks).at(Iter);

			if(EngTask->IsTime(this->Time)) {
				if(!EngTask->Update(this)) {
					(this->Tasks).remove(Iter);

					// since the task has been removed, all the
					// tasks that came after have been promoted
					// one slot. so we need to reduce the max
					// and retry this iter.
					Max--;
					continue;
				}
			}

			++Iter;
		}

		if((this->Iter % STATFPS) == 0) {
			this->PrintStats();
		}

		this->TimeLast = this->Time;
		return;
	};

	protected: void
	PrintStats() {

		unsigned long TimeDiff = this->Time - this->TimePrev;
		unsigned long IterDiff = this->Iter - this->IterPrev;
		float Framerate = ((float)IterDiff / (float)TimeDiff) * 1000;

		printf(
			"[Shed::Engine::Update] FPS=%.0f, Iter=%lu, Time=%lu, TimeDiff=%lu\n",
			Framerate,
			this->Iter,
			this->Time,
			TimeDiff
		);

		this->IterPrev = this->Iter;
		this->TimePrev = this->Time;
		return;
	}

}; };
