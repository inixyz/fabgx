#pragma once

#include "window.hpp"
#include "cpu.hpp"

namespace fab8{
	class MemoryView : public Window{
	private:
		Cpu* cpu;

	public:
		MemoryView(Cpu* cpu, unsigned int width, unsigned int height, float scale, std::string title);

	private:
		void draw();
	};
}