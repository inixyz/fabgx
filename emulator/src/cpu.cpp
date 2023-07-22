#include "cpu.hpp"
#include "instruction.hpp"

using namespace fab8;

void Cpu::set_memory(uint8_t* memory){
	this->memory = memory;
}

void Cpu::reset(){
	a = 0x00;
	x = 0x00;
	y = 0x00;
	sp = 0x00;
	ss = 0x00;
	ds = 0x00;
	es = 0x00;
	f = 0x00;
	pc = 0x0000;
	fetched = 0x00;
	location = 0x0000;
	active = false;
}

void Cpu::start(){
	uint8_t opcode;

	active = true;
	while(active){
		opcode = read_next();
		instruction_set[opcode].addressing_mode(*this);
		fetch();
		instruction_set[opcode].operation(*this);
	}
}

void Cpu::set_flag(Flag flag, bool value){
	if(value) f |= flag;
	else f &= ~flag;
}

bool Cpu::get_flag(Flag flag){
	return (f & flag) ? true : false;
}

void Cpu::update_result_flags(uint8_t value){
	set_flag(Flag::ZERO, value == 0);
	set_flag(Flag::SIGN, value & 0b10000000);
}

uint8_t Cpu::read_next(){
	return memory[pc++];
}

void Cpu::fetch(){
	fetched = memory[location];
}