//#include <fstream>
#include "cpu.hpp"
#include "instruction.hpp"

#include "memory_view.hpp"

int main(int argc, char **argv){
	fab8::Cpu cpu;
	uint8_t* ram = new uint8_t[fab8::Cpu::MEMORY_SIZE];
	
	fab8::MemoryView memory_view(&cpu, 540, 380, "memory_view");

	fab8::Instruction::init();
	//cpu.set_memory(ram);
	//cpu.reset();

	
	sf::sleep(sf::seconds(1000));
	
	delete[] ram;

	// std::ifstream file(argv[1], std::ifstream::binary);
	// file.seekg(0, file.end);
	// size_t length = file.tellg();
	// file.seekg(0, file.beg);

	// uint8_t* ram = new uint8_t[fab8::Cpu::MEMORY_SIZE];

	// file.read((char*)ram, length);
	// file.close();

	// fab8::Cpu cpu;
	// fab8::Instruction::init();

	// cpu.set_memory(ram);
	// cpu.reset();
	// cpu.start();

	// delete[] ram;
}