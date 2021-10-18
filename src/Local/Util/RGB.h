#pragma once

namespace Local::Util { class RGB {

	public: unsigned short
	R;

	public: unsigned short
	G;

	public: unsigned short
	B;

	public:
	RGB(unsigned short R, unsigned short G, unsigned short B) {
		this->R = R;
		this->G = G;
		this->B = B;
		return;
	};

}; };
