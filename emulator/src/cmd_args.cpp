#include "cmd_args.hpp"
#include "memory_view.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace fab8;

void arg_help(){
	std::cout << "Usage: fab-8 <filepath> ..." << std::endl;
	std::cout << std::endl;
	std::cout << "	--help		Show the help screen" << std::endl;
	std::cout << "	-memview	Show memory view window" << std::endl;

	exit(0);
}

void fab8::exit_info(const char* message){
	std::cout << message << std::endl;
	exit(1);
}

void fab8::process_cmd_args(int argc, char **argv, uint8_t* ram, MemoryView* memory_view, Cpu* cpu){
	if(argc == 1) arg_help();

	for(int i = 1; i < argc; i++){
		if(!strcmp(argv[i], "--help")) arg_help();
		else if(!strcmp(argv[i], "-memview")) memory_view = new fab8::MemoryView(cpu, 540, 380, "Memory");
		else{
			std::cout << "got here";
			std::ifstream file(argv[i], std::ifstream::binary);
			if(!file) exit_info("Could not find the specified file.");

			file.seekg(0, file.end);
	 		size_t length = file.tellg();
	 		file.seekg(0, file.beg);
	 		file.read((char*)ram, length);
	 		file.close();
		}
	}
}