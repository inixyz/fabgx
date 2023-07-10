#ifndef CPU_H
#define CPU_H

#include <stdint.h>

#define MEMSIZE 65536

extern uint8_t A, X, Y, SP, SS, DS, ES, F;
extern uint16_t PC;

extern uint8_t memory[MEMSIZE];

extern uint8_t fetched;
extern uint16_t location, temp;

typedef enum
{
	CARRY = (1 << 0),
	ZERO = (1 << 1),
	SIGN = (1 << 2),
	OVERFLOW = (1 << 3),
	DIRECTION = (1 << 4)
}Flag;

uint8_t get_flag(Flag flag);
void set_flag(Flag flag, uint8_t val);
void update_flagsZS(uint8_t val);

uint16_t addrcat(uint8_t seg_addr, uint8_t eff_addr);
uint8_t sign(uint8_t val);

void reset(void);
uint8_t readcurr(void);
void fetch(void);

#endif
