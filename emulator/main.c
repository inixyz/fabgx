#include "cpu.h"
#include "instructions.h"

#include <stdio.h>

int main(int argc, char** argv){
	FILE* file = fopen(argv[1], "r");
	fseek(file, 0, SEEK_END);
	unsigned int file_size = ftell(file);
	rewind(file);

	init_instrset();
	clear_memory();
	reset();
	load_memory_file(file, file_size);
	run();
}