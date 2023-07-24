#include "memory_view.hpp"
#include "cmd_args.hpp"
#include "instruction.hpp"

int main(int argc, char **argv){
	fab8::Cpu cpu;
	uint8_t* ram = new uint8_t[fab8::Cpu::MEMORY_SIZE];

	fab8::MemoryView* memory_view;

	fab8::process_cmd_args(argc, argv, ram, memory_view, &cpu);

	cpu.set_memory(ram);
	cpu.reset();
	fab8::Instruction::init();
	cpu.start();

	sf::sleep(sf::seconds(1000));
	if(memory_view) delete memory_view;
	delete[] ram;
}