#pragma once

#include "window.hpp"
#include "cpu.hpp"

namespace fab8{
	class MemoryView : public Window{
	private:
		Cpu* cpu;
		uint8_t seg_addr;
		char seg_str[3] = "ds";

	public:
		MemoryView(Cpu* cpu, unsigned int width, unsigned int height, std::string title, float scale = 1);

	private:
		void process();
	};
}