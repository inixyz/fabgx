#pragma once

#include "cpu.hpp"

namespace fab8{
	class AddressingMode{
	public:
		static void imp(Cpu& cpu);
		static void imm(Cpu& cpu);
		static void dir(Cpu& cpu);
		static void dirx(Cpu& cpu);
		static void diry(Cpu& cpu);
		static void prei(Cpu& cpu);
		static void posi(Cpu& cpu);
		static void abs(Cpu& cpu);
		static void absx(Cpu& cpu);
		static void absy(Cpu& cpu);
	};
}