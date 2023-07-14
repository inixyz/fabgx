#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>
#include <stdlib.h>

FILE* assembly_code_file;
FILE* machine_code_file;

int write_if_one_byte(char mnemonic[256])
{
	uint8_t is_one_byte = 1;

	if(!strcmp(mnemonic, "nop")) fprintf(machine_code_file, "0x%.2x ", 0x00);
	else if(!strcmp(mnemonic, "tax")) fprintf(machine_code_file, "0x%x ", 0x28);
	else if(!strcmp(mnemonic, "tay")) fprintf(machine_code_file, "0x%x ", 0x29);
	else if(!strcmp(mnemonic, "txa")) fprintf(machine_code_file, "0x%x ", 0x2A);
	else if(!strcmp(mnemonic, "txy")) fprintf(machine_code_file, "0x%x ", 0x2B);
	else if(!strcmp(mnemonic, "txsp")) fprintf(machine_code_file, "0x%x ", 0x2C);
	else if(!strcmp(mnemonic, "txss")) fprintf(machine_code_file, "0x%x ", 0x2D); 
	else if(!strcmp(mnemonic, "tya")) fprintf(machine_code_file, "0x%x ", 0x2E);
	else if(!strcmp(mnemonic, "tyx")) fprintf(machine_code_file, "0x%x ", 0x2F);
	else if(!strcmp(mnemonic, "tyds")) fprintf(machine_code_file, "0x%x ", 0x30);
	else if(!strcmp(mnemonic, "tspx")) fprintf(machine_code_file, "0x%x ", 0x31);
	else if(!strcmp(mnemonic, "tssx")) fprintf(machine_code_file, "0x%x ", 0x32);
	else if(!strcmp(mnemonic, "tdsy")) fprintf(machine_code_file, "0x%x ", 0x33);
	else if(!strcmp(mnemonic, "ina")) fprintf(machine_code_file, "0x%x ", 0x34);
	else if(!strcmp(mnemonic, "inx")) fprintf(machine_code_file, "0x%x ", 0x35);
	else if(!strcmp(mnemonic, "iny")) fprintf(machine_code_file, "0x%x ", 0x36);
	else if(!strcmp(mnemonic, "dea")) fprintf(machine_code_file, "0x%x ", 0x3B);
	else if(!strcmp(mnemonic, "dex")) fprintf(machine_code_file, "0x%x ", 0x3C);
	else if(!strcmp(mnemonic, "dey"))fprintf(machine_code_file, "0x%x ", 0x3D);
	else if(!strcmp(mnemonic, "shla")) fprintf(machine_code_file, "0x%x ", 0x7E);
	else if(!strcmp(mnemonic, "shra")) fprintf(machine_code_file, "0x%x ", 0x83);
	else if(!strcmp(mnemonic, "rola")) fprintf(machine_code_file, "0x%x ", 0x88);
	else if(!strcmp(mnemonic, "rora")) fprintf(machine_code_file, "0x%x ", 0x8D);
	else if(!strcmp(mnemonic, "ret")) fprintf(machine_code_file, "0x%x ", 0xB6);
	else if(!strcmp(mnemonic, "clc")) fprintf(machine_code_file, "0x%x ", 0xB7);
	else if(!strcmp(mnemonic, "clz")) fprintf(machine_code_file, "0x%x ", 0xB8);
	else if(!strcmp(mnemonic, "cls")) fprintf(machine_code_file, "0x%x ", 0xB9);
	else if(!strcmp(mnemonic, "clo")) fprintf(machine_code_file, "0x%x ", 0xBA);
	else if(!strcmp(mnemonic, "cld")) fprintf(machine_code_file, "0x%x ", 0xBB);
	else if(!strcmp(mnemonic, "sec")) fprintf(machine_code_file, "0x%x ", 0xBC);
	else if(!strcmp(mnemonic, "sez")) fprintf(machine_code_file, "0x%x ", 0xBD);
	else if(!strcmp(mnemonic, "ses")) fprintf(machine_code_file, "0x%x ", 0xBE);
	else if(!strcmp(mnemonic, "seo")) fprintf(machine_code_file, "0x%x ", 0xBF);
	else if(!strcmp(mnemonic, "sed")) fprintf(machine_code_file, "0x%x ", 0xC0);
	else if(!strcmp(mnemonic, "pusha")) fprintf(machine_code_file, "0x%x ", 0xC2);
	else if(!strcmp(mnemonic, "pushx")) fprintf(machine_code_file, "0x%x ", 0xC3);
	else if(!strcmp(mnemonic, "pushy")) fprintf(machine_code_file, "0x%x ", 0xC4);
	else if(!strcmp(mnemonic, "pushf")) fprintf(machine_code_file, "0x%x ", 0xC5);
	else if(!strcmp(mnemonic, "pushall")) fprintf(machine_code_file, "0x%x ", 0xC6);
	else if(!strcmp(mnemonic, "popa")) fprintf(machine_code_file, "0x%x ", 0xC8);
	else if(!strcmp(mnemonic, "popx")) fprintf(machine_code_file, "0x%x ", 0xC9);
	else if(!strcmp(mnemonic, "popy")) fprintf(machine_code_file, "0x%x ", 0xCA);
	else if(!strcmp(mnemonic, "popf")) fprintf(machine_code_file, "0x%x ", 0xCB);
	else if(!strcmp(mnemonic, "popall")) fprintf(machine_code_file, "0x%x ", 0xCC);
	else if(!strcmp(mnemonic, "lods")) fprintf(machine_code_file, "0x%x ", 0xCF);
	else if(!strcmp(mnemonic, "stos")) fprintf(machine_code_file, "0x%x ", 0xD0);
	else if(!strcmp(mnemonic, "movs")) fprintf(machine_code_file, "0x%x ", 0xD1);
	else if(!strcmp(mnemonic, "tyes")) fprintf(machine_code_file, "0x%x ", 0xD2);
	else if(!strcmp(mnemonic, "tesy")) fprintf(machine_code_file, "0x%x ", 0xD3);
	else if(!strcmp(mnemonic, "stop")) fprintf(machine_code_file, "0x%x ", 0xFF);
	else is_one_byte = 0;

	return is_one_byte;
}

void process_mnemonic(char mnemonic[256])
{
	if(write_if_one_byte(mnemonic)) return;
	else
	{
		char word[256]; 
		fscanf(assembly_code_file, "%s", word);
	}
}

int main()
{
	assembly_code_file = fopen("code.faba", "r");
	machine_code_file = fopen("code.bin", "w");

	char word[256];
	while(fscanf(assembly_code_file, "%s", word) != EOF)
	{
		process_mnemonic(word);
	}

	fclose(assembly_code_file);
	fclose(machine_code_file);
}


