#include "cpu.h"

#include "string.h"

uint8_t A, X, Y, SP, SS, DS, ES, F;
uint16_t PC;

uint8_t memory[MEMSIZE];

uint8_t fetched;
uint16_t location;

uint8_t get_flag(Flag flag)
{
	return (F & flag) ? 1 : 0;
}

void set_flag(Flag flag, uint8_t val)
{
	if(val) F |= flag;
	else F &= ~flag;
}

void update_flagsZS(uint8_t val)
{
	set_flag(ZERO, val == 0);
	set_flag(SIGN, val & 0b10000000);
}

uint16_t addrcat(uint8_t seg_addr, uint8_t eff_addr)
{
	return (uint16_t)seg_addr << 8 | eff_addr;
}

void reset(void)
{
	A = 0x00; X = 0x00; Y = 0x00; SP = 0x00;
	SS = 0x00; DS = 0x00; ES = 0x00; F = 0x00; PC = 0x00;

	memset(memory, 0, MEMSIZE);
}

uint8_t readcurr(void)
{
	return memory[PC++];
}

void fetch(void)
{
	fetched = memory[location];
}