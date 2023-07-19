#pragma once

#include <cstdint>

namespace fab8{
	uint16_t phy_addr(uint8_t seg_addr, uint8_t eff_addr);
	bool sign_bit(uint8_t value);
}