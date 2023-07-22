#pragma once

#include "memory_view.hpp"

namespace fab8{
	void exit_info(const char* message);
	void process_cmd_args(int argc, char **argv, uint8_t* ram, MemoryView* memory_view, Cpu* cpu);
}