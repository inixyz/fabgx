#include "cpu.h"
#include "instructions.h"

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	FILE* file = fopen("test.bin", "r");
	fseek(file, 0, SEEK_END);
	long filesize = ftell(file);
	rewind(file);

	

	//printf("%x %x", memory[0], memory[1]);
	init_instrset();
	reset();
	fread(memory, 1, filesize, file);

	while(running)
	{
		uint8_t opcode = readcurr();
		instrset[opcode].addr_mode();
		fetch();
		instrset[opcode].oper();
	}

	printf("%x\n", A);
}

