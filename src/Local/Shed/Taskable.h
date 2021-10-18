#pragma once

namespace Local::Shed { class Taskable {

	public: virtual bool
	OnTaskUpdate(Engine* Eng) {

		KNOWN(Eng);

		return false;
	};

}; };
