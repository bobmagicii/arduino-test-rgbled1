#pragma once

#include <Array.h>
#include "Taskable.h"
#include "EngineTask.h"

namespace Local::Shed { class Engine {

	private: unsigned long
	Time;

	private: unsigned long
	TimePrev;

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

		(this->Tasks)
		.push_back(EngTask);

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

		while(Iter < Max) {

			EngTask = (this->Tasks).at(Iter);

			if(EngTask->IsTime(this->Time)) {
				#ifdef DEBUG_SHED_ENGINE_UPDATE
				printf("[Shed::Engine::Update] Task ID: %d\n",Iter);
				#endif

				if(!EngTask->Update(this)) {
					(this->Tasks).remove(Iter);
				}
			}

			++Iter;
		}

		this->TimePrev = this->Time;
		return;
	};

}; };
