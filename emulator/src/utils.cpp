#include "utils.hpp"

uint16_t fab8::phy_addr(uint8_t seg_addr, uint8_t eff_addr){
	return (uint16_t)seg_addr << 8 | eff_addr;
}

bool fab8::sign_bit(uint8_t value){
	return (value & 0b10000000) ? true : false;
}