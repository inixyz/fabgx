#pragma once

#include <cstdint>

namespace fab8{
	class Cpu{
		enum Flag{
			CARRY = (1 << 0),
			ZERO = (1 << 1),
			SIGN = (1 << 2),
			OVERFLOW = (1 << 3),
			DIRECTION = (1 << 4)
		};

	public:
		friend class AddressingMode;
		friend class Instruction;
		friend class MemoryView;
		static const unsigned int MEMORY_SIZE = 65536;

	private:
		bool active = false;
		uint8_t a, x, y, sp, ss, ds, es, f, *memory, fetched;
		uint16_t pc, location;

	public:
		void set_memory(uint8_t* memory);
		void reset();
		void start();

	private:
		void set_flag(Flag flag, bool value);
		bool get_flag(Flag flag);
		void update_result_flags(uint8_t value);
		uint8_t read_next();
		void fetch();
	};
}