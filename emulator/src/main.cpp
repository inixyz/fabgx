#include <fstream>
#include "cpu.hpp"
#include "instruction.hpp"
#include "memory_view.hpp"
#include "string.h"

int main(int argc, char **argv){
	fab8::Cpu cpu;
	uint8_t* ram = new uint8_t[fab8::Cpu::MEMORY_SIZE];
	fab8::Instruction::init();
	cpu.set_memory(ram);
	cpu.reset();

	std::ifstream file;

	fab8::MemoryView* memory_view;

	for(int i = 1; i < argc; i++){
		if(!strcmp(argv[i], "-memview")){
			memory_view = new fab8::MemoryView(&cpu, 540, 380, "Memory");
		}
		else{
			file.open(argv[i], std::ifstream::binary);
			file.seekg(0, file.end);
	 		size_t length = file.tellg();
	 		file.seekg(0, file.beg);
	 		file.read((char*)ram, length);
	 		file.close();
		}
	}

	cpu.start();
	sf::sleep(sf::seconds(1000));

	delete[] ram;
	delete memory_view;
}