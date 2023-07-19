#include "instruction.hpp"
#include "addressing_mode.hpp"
#include "utils.hpp"

using namespace fab8;

Instruction fab8::instruction_set[256];

void Instruction::nop(Cpu& cpu){}

void Instruction::stop(Cpu& cpu){
	cpu.active = false;
}

void Instruction::lda(Cpu& cpu){
	cpu.a = cpu.fetched;
	cpu.update_result_flags(cpu.a);
}

void Instruction::ldx(Cpu& cpu){
	cpu.x = cpu.fetched;
	cpu.update_result_flags(cpu.x);
}

void Instruction::ldy(Cpu& cpu){
	cpu.y = cpu.fetched;
	cpu.update_result_flags(cpu.y);
}

void Instruction::ldf(Cpu& cpu){
	cpu.f = cpu.fetched;
}

void Instruction::sta(Cpu& cpu){
	cpu.memory[cpu.location] = cpu.a;
}

void Instruction::stx(Cpu& cpu){
	cpu.memory[cpu.location] = cpu.x;
}

void Instruction::sty(Cpu& cpu){
	cpu.memory[cpu.location] = cpu.y;
}

void Instruction::tax(Cpu& cpu){
	cpu.a = cpu.x;
	cpu.update_result_flags(cpu.a);
}

void Instruction::tay(Cpu& cpu){
	cpu.a = cpu.y;
	cpu.update_result_flags(cpu.a);
}

void Instruction::txa(Cpu& cpu){
	cpu.x = cpu.a;
	cpu.update_result_flags(cpu.x);
}

void Instruction::txy(Cpu& cpu){
	cpu.x = cpu.y;
	cpu.update_result_flags(cpu.x);
}

void Instruction::txsp(Cpu& cpu){
	cpu.x = cpu.sp;
	cpu.update_result_flags(cpu.x);
}

void Instruction::txss(Cpu& cpu){
	cpu.x = cpu.ss;
	cpu.update_result_flags(cpu.x);
}

void Instruction::tya(Cpu& cpu){
	cpu.y = cpu.a;
	cpu.update_result_flags(cpu.y);
}

void Instruction::tyx(Cpu& cpu){
	cpu.y = cpu.x;
	cpu.update_result_flags(cpu.y);
}

void Instruction::tyds(Cpu& cpu){
	cpu.y = cpu.ds;
	cpu.update_result_flags(cpu.y);
}

void Instruction::tyes(Cpu& cpu){
	cpu.y = cpu.es;
	cpu.update_result_flags(cpu.y);
}

void Instruction::tspx(Cpu& cpu){
	cpu.sp = cpu.x;
	cpu.update_result_flags(cpu.sp);
}

void Instruction::tssx(Cpu& cpu){
	cpu.ss = cpu.x;
	cpu.update_result_flags(cpu.ss);
}

void Instruction::tdsy(Cpu& cpu){
	cpu.ds = cpu.y;
	cpu.update_result_flags(cpu.ds);
}

void Instruction::tesy(Cpu& cpu){
	cpu.es = cpu.y;
	cpu.update_result_flags(cpu.es);
}

void Instruction::ina(Cpu& cpu){
	cpu.a++;
	cpu.update_result_flags(cpu.a);
}

void Instruction::inx(Cpu& cpu){
	cpu.x++;
	cpu.update_result_flags(cpu.x);
}

void Instruction::iny(Cpu& cpu){
	cpu.y++;
	cpu.update_result_flags(cpu.y);
}

void Instruction::inc(Cpu& cpu){
	cpu.memory[cpu.location]++;
	cpu.update_result_flags(cpu.memory[cpu.location]);
}

void Instruction::dea(Cpu& cpu){
	cpu.a--;
	cpu.update_result_flags(cpu.a);
}

void Instruction::dex(Cpu& cpu){
	cpu.x--;
	cpu.update_result_flags(cpu.x);
}

void Instruction::dey(Cpu& cpu){
	cpu.y--;
	cpu.update_result_flags(cpu.y);
}

void Instruction::dec(Cpu& cpu){
	cpu.memory[cpu.location]--;
	cpu.update_result_flags(cpu.memory[cpu.location]);
}

void Instruction::adc(Cpu& cpu){
	uint16_t result = cpu.a + cpu.fetched + cpu.get_flag(Cpu::Flag::CARRY);
	cpu.set_flag(Cpu::Flag::CARRY, result > 255);

	bool overflow = sign_bit(cpu.a) && sign_bit(cpu.fetched) && !sign_bit(result);
	overflow |= !sign_bit(cpu.a) && !sign_bit(cpu.fetched) && sign_bit(result);
	cpu.set_flag(Cpu::Flag::OVERFLOW, overflow);

	cpu.a = result;
	cpu.update_result_flags(cpu.a);
}

void Instruction::sbb(Cpu& cpu){
	uint16_t result = cpu.a - cpu.fetched - cpu.get_flag(Cpu::Flag::CARRY);
	cpu.set_flag(Cpu::Flag::CARRY, result > 255);

	bool overflow = sign_bit(cpu.a) && !sign_bit(cpu.fetched) && !sign_bit(result);
	overflow |= !sign_bit(cpu.a) && sign_bit(cpu.fetched) && sign_bit(result);
	cpu.set_flag(Cpu::Flag::OVERFLOW, overflow);

	cpu.a = result;
	cpu.update_result_flags(cpu.a);
}

void Instruction::mul(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::CARRY, cpu.a * cpu.fetched > 255);
	cpu.a *= cpu.fetched;
	cpu.update_result_flags(cpu.a);
}

void Instruction::div(Cpu& cpu){
	cpu.a /= cpu.fetched;
	cpu.update_result_flags(cpu.a);
}

void Instruction::mod(Cpu& cpu){
	cpu.a %= cpu.fetched;
	cpu.update_result_flags(cpu.a);
}

void Instruction::_and(Cpu& cpu){
	cpu.a &= cpu.fetched;
	cpu.update_result_flags(cpu.a);
}

void Instruction::_or(Cpu& cpu){
	cpu.a |= cpu.fetched;
	cpu.update_result_flags(cpu.a);
}

void Instruction::_xor(Cpu& cpu){
	cpu.a ^= cpu.fetched;
	cpu.update_result_flags(cpu.a);
}

void Instruction::shla(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::CARRY, sign_bit(cpu.a));
	cpu.a <<= 1;
	cpu.update_result_flags(cpu.a);
}

void Instruction::shl(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::CARRY, sign_bit(cpu.memory[cpu.location]));
	cpu.memory[cpu.location] <<= 1;
	cpu.update_result_flags(cpu.memory[cpu.location]);
}

void Instruction::shra(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::CARRY, cpu.a & 0b00000001);
	cpu.a >>= 1;
	cpu.update_result_flags(cpu.a);
}

void Instruction::shr(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::CARRY, cpu.memory[cpu.location] & 0b00000001);
	cpu.memory[cpu.location] >>= 1;
	cpu.update_result_flags(cpu.memory[cpu.location]);
}

void Instruction::rola(Cpu& cpu){
	bool roll_bit = sign_bit(cpu.a);
	cpu.a <<= 1;
	cpu.a |= cpu.get_flag(Cpu::Flag::CARRY);
	cpu.set_flag(Cpu::Flag::CARRY, roll_bit);
	cpu.update_result_flags(cpu.a);
}

void Instruction::rol(Cpu& cpu){
	bool roll_bit = sign_bit(cpu.memory[cpu.location]);
	cpu.memory[cpu.location] <<= 1;
	cpu.memory[cpu.location] |= cpu.get_flag(Cpu::Flag::CARRY);
	cpu.set_flag(Cpu::Flag::CARRY, roll_bit);
	cpu.update_result_flags(cpu.memory[cpu.location]);
}

void Instruction::rora(Cpu& cpu){
	bool roll_bit = cpu.a & 0b00000001;
	cpu.a >>= 1;
	cpu.a |= cpu.get_flag(Cpu::Flag::CARRY) << 7;
	cpu.set_flag(Cpu::Flag::CARRY, roll_bit);
	cpu.update_result_flags(cpu.a);
}

void Instruction::ror(Cpu& cpu){
	bool roll_bit = cpu.memory[cpu.location] & 0b00000001;
	cpu.memory[cpu.location] >>= 1;
	cpu.memory[cpu.location] |= cpu.get_flag(Cpu::Flag::CARRY) << 7;
	cpu.set_flag(Cpu::Flag::CARRY, roll_bit);
	cpu.update_result_flags(cpu.memory[cpu.location]);
}

void Instruction::cmp(Cpu& cpu){
	uint16_t result = cpu.a - cpu.fetched;
	cpu.set_flag(Cpu::Flag::CARRY, result > 255);

	bool overflow = sign_bit(cpu.a) && !sign_bit(cpu.fetched) && !sign_bit(result);
	overflow |= !sign_bit(cpu.a) && sign_bit(cpu.fetched) && sign_bit(result);
	cpu.set_flag(Cpu::Flag::OVERFLOW, overflow);

	cpu.update_result_flags(result);
}

void Instruction::cpx(Cpu& cpu){
	uint16_t result = cpu.x - cpu.fetched;
	cpu.set_flag(Cpu::Flag::CARRY, result > 255);

	bool overflow = sign_bit(cpu.x) && !sign_bit(cpu.fetched) && !sign_bit(result);
	overflow |= !sign_bit(cpu.x) && sign_bit(cpu.fetched) && sign_bit(result);
	cpu.set_flag(Cpu::Flag::OVERFLOW, overflow);

	cpu.update_result_flags(result);
}

void Instruction::cpy(Cpu& cpu){
	uint16_t result = cpu.y - cpu.fetched;
	cpu.set_flag(Cpu::Flag::CARRY, result > 255);

	bool overflow = sign_bit(cpu.y) && !sign_bit(cpu.fetched) && !sign_bit(result);
	overflow |= !sign_bit(cpu.y) && sign_bit(cpu.fetched) && sign_bit(result);
	cpu.set_flag(Cpu::Flag::OVERFLOW, overflow);

	cpu.update_result_flags(result);
}

void Instruction::jmp(Cpu& cpu){
	cpu.pc = cpu.location;
}

void Instruction::jc(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::CARRY)) cpu.pc = cpu.location;
}

void Instruction::jnc(Cpu& cpu){
	if(!cpu.get_flag(Cpu::Flag::CARRY)) cpu.pc = cpu.location;
}

void Instruction::je(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::ZERO)) cpu.pc = cpu.location;
}

void Instruction::jne(Cpu& cpu){
	if(!cpu.get_flag(Cpu::Flag::ZERO)) cpu.pc = cpu.location;
}

void Instruction::js(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::SIGN)) cpu.pc = cpu.location;
}

void Instruction::jns(Cpu& cpu){
	if(!cpu.get_flag(Cpu::Flag::SIGN)) cpu.pc = cpu.location;
}

void Instruction::jo(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::OVERFLOW)) cpu.pc = cpu.location;
}

void Instruction::jno(Cpu& cpu){
	if(!cpu.get_flag(Cpu::Flag::OVERFLOW)) cpu.pc = cpu.location;
}

void Instruction::ja(Cpu& cpu){
	if(!cpu.get_flag(Cpu::Flag::CARRY) && !cpu.get_flag(Cpu::Flag::ZERO)) cpu.pc = cpu.location;
}

void Instruction::jna(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::CARRY) || cpu.get_flag(Cpu::Flag::ZERO)) cpu.pc = cpu.location;
}

void Instruction::jl(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::SIGN) != cpu.get_flag(Cpu::Flag::OVERFLOW)) cpu.pc = cpu.location;
}

void Instruction::jge(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::SIGN) == cpu.get_flag(Cpu::Flag::OVERFLOW)) cpu.pc = cpu.location;
}

void Instruction::jg(Cpu& cpu){
	if(!cpu.get_flag(Cpu::Flag::ZERO) && cpu.get_flag(Cpu::Flag::SIGN) == cpu.get_flag(Cpu::Flag::OVERFLOW)) cpu.pc = cpu.location;
}

void Instruction::jng(Cpu& cpu){
	if(cpu.get_flag(Cpu::Flag::ZERO) || cpu.get_flag(Cpu::Flag::SIGN) != cpu.get_flag(Cpu::Flag::OVERFLOW)) cpu.pc = cpu.location;
}

void Instruction::loop(Cpu& cpu){
	if(cpu.y){
		cpu.y--;
		cpu.pc = cpu.location;
	}
}

void Instruction::call(Cpu& cpu){
	cpu.memory[phy_addr(cpu.ss, --(cpu.sp))] = cpu.pc >> 8;
	cpu.memory[phy_addr(cpu.ss, --(cpu.sp))] = cpu.pc;
	cpu.pc = cpu.location;
}

void Instruction::ret(Cpu& cpu){
	cpu.pc = cpu.memory[phy_addr(cpu.ss, cpu.sp++)] << 8 | cpu.memory[phy_addr(cpu.ss, cpu.sp++)];
}

void Instruction::clc(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::CARRY, false);
}

void Instruction::clz(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::ZERO, false);
}

void Instruction::cls(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::SIGN, false);
}

void Instruction::clo(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::OVERFLOW, false);
}

void Instruction::cld(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::DIRECTION, false);
}

void Instruction::sec(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::CARRY, true);
}

void Instruction::sez(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::ZERO, true);
}

void Instruction::ses(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::SIGN, true);
}

void Instruction::seo(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::OVERFLOW, true);
}

void Instruction::sed(Cpu& cpu){
	cpu.set_flag(Cpu::Flag::DIRECTION, true);
}

void Instruction::pusha(Cpu& cpu){
	cpu.memory[phy_addr(cpu.ss, --(cpu.sp))] = cpu.a;
}

void Instruction::pushx(Cpu& cpu){
	cpu.memory[phy_addr(cpu.ss, --(cpu.sp))] = cpu.x;
}

void Instruction::pushy(Cpu& cpu){
	cpu.memory[phy_addr(cpu.ss, --(cpu.sp))] = cpu.y;
}

void Instruction::pushf(Cpu& cpu){
	cpu.memory[phy_addr(cpu.ss, --(cpu.sp))] = cpu.f;
}

void Instruction::pushall(Cpu& cpu){
	pusha(cpu);
	pushx(cpu);
	pushy(cpu);
	pushf(cpu);
}

void Instruction::push(Cpu& cpu){
	cpu.memory[phy_addr(cpu.ss, --(cpu.sp))] = cpu.fetched;
}

void Instruction::popa(Cpu& cpu){
	cpu.a = cpu.memory[phy_addr(cpu.ss, cpu.sp++)];
}

void Instruction::popx(Cpu& cpu){
	cpu.x = cpu.memory[phy_addr(cpu.ss, cpu.sp++)];
}

void Instruction::popy(Cpu& cpu){
	cpu.y = cpu.memory[phy_addr(cpu.ss, cpu.sp++)];
}

void Instruction::popf(Cpu& cpu){
	cpu.f = cpu.memory[phy_addr(cpu.ss, cpu.sp++)];
}

void Instruction::popall(Cpu& cpu){
	pushf(cpu);
	pushy(cpu);
	pushx(cpu);
	pusha(cpu);
}

void Instruction::pop(Cpu& cpu){
	cpu.memory[cpu.location] = cpu.memory[phy_addr(cpu.ss, cpu.sp++)];
}

void Instruction::lods(Cpu& cpu){
	cpu.a = cpu.memory[phy_addr(cpu.ds, cpu.x)];
	cpu.x = cpu.get_flag(Cpu::Flag::DIRECTION) ? cpu.x - 1 : cpu.x + 1;
}

void Instruction::stos(Cpu& cpu){
	cpu.memory[phy_addr(cpu.es, cpu.y)] = cpu.a;
	cpu.y = cpu.get_flag(Cpu::Flag::DIRECTION) ? cpu.y - 1 : cpu.y + 1;
}

void Instruction::movs(Cpu& cpu){
	cpu.memory[phy_addr(cpu.es, cpu.y)] = cpu.memory[phy_addr(cpu.ds, cpu.x)];
	cpu.x = cpu.get_flag(Cpu::Flag::DIRECTION) ? cpu.x - 1 : cpu.x + 1;
	cpu.y = cpu.get_flag(Cpu::Flag::DIRECTION) ? cpu.y - 1 : cpu.y + 1;
}

void Instruction::intr(Cpu& cpu){}

void Instruction::init(){
	instruction_set[0x00] = {AddressingMode::imp, nop};
	instruction_set[0x01] = {AddressingMode::imp, stop};

	instruction_set[0x02] = {AddressingMode::imm, lda};
	instruction_set[0x03] = {AddressingMode::dir, lda};
	instruction_set[0x04] = {AddressingMode::dirx, lda};
	instruction_set[0x05] = {AddressingMode::diry, lda};
	instruction_set[0x06] = {AddressingMode::prei, lda};
	instruction_set[0x07] = {AddressingMode::posi, lda};
	instruction_set[0x08] = {AddressingMode::abs, lda};
	instruction_set[0x09] = {AddressingMode::absx, lda};
	instruction_set[0x0a] = {AddressingMode::absy, lda};

	instruction_set[0x0b] = {AddressingMode::imm, ldx};
	instruction_set[0x0c] = {AddressingMode::dir, ldx};
	instruction_set[0x0d] = {AddressingMode::diry, ldx};
	instruction_set[0x0e] = {AddressingMode::posi, ldx};
	instruction_set[0x0f] = {AddressingMode::abs, ldx};
	instruction_set[0x10] = {AddressingMode::absy, ldx};

	instruction_set[0x11] = {AddressingMode::imm, ldy};
	instruction_set[0x12] = {AddressingMode::dir, ldy};
	instruction_set[0x13] = {AddressingMode::dirx, ldy};
	instruction_set[0x14] = {AddressingMode::prei, ldy};
	instruction_set[0x15] = {AddressingMode::abs, ldy};
	instruction_set[0x16] = {AddressingMode::absx, ldy};

	instruction_set[0x17] = {AddressingMode::imm, ldf};

	instruction_set[0x18] = {AddressingMode::dir, sta};
	instruction_set[0x19] = {AddressingMode::dirx, sta};
	instruction_set[0x1a] = {AddressingMode::diry, sta};
	instruction_set[0x1b] = {AddressingMode::prei, sta};
	instruction_set[0x1c] = {AddressingMode::posi, sta};
	instruction_set[0x1d] = {AddressingMode::abs, sta};
	instruction_set[0x1e] = {AddressingMode::absx, sta};
	instruction_set[0x1f] = {AddressingMode::absy, sta};
	
	instruction_set[0x20] = {AddressingMode::dir, stx};
	instruction_set[0x21] = {AddressingMode::diry, stx};
	instruction_set[0x22] = {AddressingMode::posi, stx};
	instruction_set[0x23] = {AddressingMode::abs, stx};
	instruction_set[0x24] = {AddressingMode::absy, stx};

	instruction_set[0x25] = {AddressingMode::dir, sty};
	instruction_set[0x26] = {AddressingMode::dirx, sty};
	instruction_set[0x27] = {AddressingMode::prei, sty};
	instruction_set[0x28] = {AddressingMode::abs, sty};
	instruction_set[0x29] = {AddressingMode::absx, sty};

	instruction_set[0x2a] = {AddressingMode::imp, tax};
	instruction_set[0x2b] = {AddressingMode::imp, tay};
	instruction_set[0x2c] = {AddressingMode::imp, txa};
	instruction_set[0x2d] = {AddressingMode::imp, txy};
	instruction_set[0x2e] = {AddressingMode::imp, txsp};
	instruction_set[0x2f] = {AddressingMode::imp, txss};
	instruction_set[0x30] = {AddressingMode::imp, tya};
	instruction_set[0x31] = {AddressingMode::imp, tyx};
	instruction_set[0x32] = {AddressingMode::imp, tyds};
	instruction_set[0x33] = {AddressingMode::imp, tyes};
	instruction_set[0x34] = {AddressingMode::imp, tspx};
	instruction_set[0x35] = {AddressingMode::imp, tssx};
	instruction_set[0x36] = {AddressingMode::imp, tdsy};
	instruction_set[0x37] = {AddressingMode::imp, tesy};

	instruction_set[0x38] = {AddressingMode::imp, ina};
	instruction_set[0x39] = {AddressingMode::imp, inx};
	instruction_set[0x3a] = {AddressingMode::imp, iny};
	instruction_set[0x3b] = {AddressingMode::dir, inc};
	instruction_set[0x3c] = {AddressingMode::dirx, inc};
	instruction_set[0x3d] = {AddressingMode::abs, inc};
	instruction_set[0x3e] = {AddressingMode::absy, inc};

	instruction_set[0x3f] = {AddressingMode::imp, dea};
	instruction_set[0x40] = {AddressingMode::imp, dex};
	instruction_set[0x41] = {AddressingMode::imp, dey};
	instruction_set[0x42] = {AddressingMode::dir, dec};
	instruction_set[0x43] = {AddressingMode::dirx, dec};
	instruction_set[0x44] = {AddressingMode::abs, dec};
	instruction_set[0x45] = {AddressingMode::absy, dec};
	
	instruction_set[0x46] = {AddressingMode::imm, adc};
	instruction_set[0x47] = {AddressingMode::dir, adc};
	instruction_set[0x48] = {AddressingMode::dirx, adc};
	instruction_set[0x49] = {AddressingMode::diry, adc};
	instruction_set[0x4a] = {AddressingMode::prei, adc};
	instruction_set[0x4b] = {AddressingMode::posi, adc};
	instruction_set[0x4c] = {AddressingMode::abs, adc};
	instruction_set[0x4d] = {AddressingMode::absx, adc};
	instruction_set[0x4e] = {AddressingMode::absy, adc};
	
	instruction_set[0x4f] = {AddressingMode::imm, sbb};
	instruction_set[0x50] = {AddressingMode::dir, sbb};
	instruction_set[0x51] = {AddressingMode::dirx, sbb};
	instruction_set[0x52] = {AddressingMode::diry, sbb};
	instruction_set[0x53] = {AddressingMode::prei, sbb};
	instruction_set[0x54] = {AddressingMode::posi, sbb};
	instruction_set[0x55] = {AddressingMode::abs, sbb};
	instruction_set[0x56] = {AddressingMode::absx, sbb};
	instruction_set[0x57] = {AddressingMode::absy, sbb};

	instruction_set[0x58] = {AddressingMode::imm, mul};
	instruction_set[0x59] = {AddressingMode::dir, mul};
	instruction_set[0x5a] = {AddressingMode::dirx, mul};
	instruction_set[0x5b] = {AddressingMode::abs, mul};
	instruction_set[0x5c] = {AddressingMode::absx, mul};

	instruction_set[0x5d] = {AddressingMode::imm, div};
	instruction_set[0x5e] = {AddressingMode::dir, div};
	instruction_set[0x5f] = {AddressingMode::dirx, div};
	instruction_set[0x60] = {AddressingMode::abs, div};
	instruction_set[0x61] = {AddressingMode::absx, div};

	instruction_set[0x62] = {AddressingMode::imm, mod};
	instruction_set[0x63] = {AddressingMode::dir, mod};
	instruction_set[0x64] = {AddressingMode::dirx, mod};
	instruction_set[0x65] = {AddressingMode::abs, mod};
	instruction_set[0x66] = {AddressingMode::absx, mod};

	instruction_set[0x67] = {AddressingMode::imm, _and};
	instruction_set[0x68] = {AddressingMode::dir, _and};
	instruction_set[0x69] = {AddressingMode::dirx, _and};
	instruction_set[0x6a] = {AddressingMode::diry, _and};
	instruction_set[0x6b] = {AddressingMode::prei, _and};
	instruction_set[0x6c] = {AddressingMode::posi, _and};
	instruction_set[0x6d] = {AddressingMode::abs, _and};
	instruction_set[0x6e] = {AddressingMode::absx, _and};
	instruction_set[0x6f] = {AddressingMode::absy, _and};

	instruction_set[0x70] = {AddressingMode::imm, _or};
	instruction_set[0x71] = {AddressingMode::dir, _or};
	instruction_set[0x72] = {AddressingMode::dirx, _or};
	instruction_set[0x73] = {AddressingMode::diry, _or};
	instruction_set[0x74] = {AddressingMode::prei, _or};
	instruction_set[0x75] = {AddressingMode::posi, _or};
	instruction_set[0x76] = {AddressingMode::abs, _or};
	instruction_set[0x77] = {AddressingMode::absx, _or};
	instruction_set[0x78] = {AddressingMode::absy, _or};
		
	instruction_set[0x79] = {AddressingMode::imm, _xor};
	instruction_set[0x7a] = {AddressingMode::dir, _xor};
	instruction_set[0x7b] = {AddressingMode::dirx, _xor};
	instruction_set[0x7c] = {AddressingMode::diry, _xor};
	instruction_set[0x7d] = {AddressingMode::prei, _xor};
	instruction_set[0x7e] = {AddressingMode::posi, _xor};
	instruction_set[0x7f] = {AddressingMode::abs, _xor};
	instruction_set[0x80] = {AddressingMode::absx, _xor};
	instruction_set[0x81] = {AddressingMode::absy, _xor};
	
	instruction_set[0x82] = {AddressingMode::imp, shla};
	instruction_set[0x83] = {AddressingMode::dir, shl};
	instruction_set[0x84] = {AddressingMode::dirx, shl};
	instruction_set[0x85] = {AddressingMode::abs, shl};
	instruction_set[0x86] = {AddressingMode::absx, shl};
	
	instruction_set[0x87] = {AddressingMode::imp, shra};
	instruction_set[0x88] = {AddressingMode::dir, shr};
	instruction_set[0x89] = {AddressingMode::dirx, shr};
	instruction_set[0x8a] = {AddressingMode::abs, shr};
	instruction_set[0x8b] = {AddressingMode::absx, shr};

	instruction_set[0x8c] = {AddressingMode::imp, rola};
	instruction_set[0x8d] = {AddressingMode::dir, rol};
	instruction_set[0x8e] = {AddressingMode::dirx, rol};
	instruction_set[0x8f] = {AddressingMode::abs, rol};
	instruction_set[0x90] = {AddressingMode::absx, rol};
	
	instruction_set[0x91] = {AddressingMode::imp, rora};
	instruction_set[0x92] = {AddressingMode::dir, ror};
	instruction_set[0x93] = {AddressingMode::dirx, ror};
	instruction_set[0x94] = {AddressingMode::abs, ror};
	instruction_set[0x95] = {AddressingMode::absx, ror};
	
	instruction_set[0x96] = {AddressingMode::imm, cmp};
	instruction_set[0x97] = {AddressingMode::dir, cmp};
	instruction_set[0x98] = {AddressingMode::dirx, cmp};
	instruction_set[0x99] = {AddressingMode::diry, cmp};
	instruction_set[0x9a] = {AddressingMode::prei, cmp};
	instruction_set[0x9b] = {AddressingMode::posi, cmp};
	instruction_set[0x9c] = {AddressingMode::abs, cmp};
	instruction_set[0x9d] = {AddressingMode::absx, cmp};
	instruction_set[0x9e] = {AddressingMode::absy, cmp};
	
	instruction_set[0x9f] = {AddressingMode::imm, cpx};
	instruction_set[0xa0] = {AddressingMode::dir, cpx};
	instruction_set[0xa1] = {AddressingMode::diry, cpx};
	instruction_set[0xa2] = {AddressingMode::abs, cpx};
	instruction_set[0xa3] = {AddressingMode::absy, cpx};
	
	instruction_set[0xa4] = {AddressingMode::imm, cpy};
	instruction_set[0xa5] = {AddressingMode::dir, cpy};
	instruction_set[0xa6] = {AddressingMode::dirx, cpy};
	instruction_set[0xa7] = {AddressingMode::abs, cpy};
	instruction_set[0xa8] = {AddressingMode::absx, cpy};
	
	instruction_set[0xa9] = {AddressingMode::abs, jmp};
	instruction_set[0xaa] = {AddressingMode::abs, jc};
	instruction_set[0xab] = {AddressingMode::abs, jnc};
	instruction_set[0xac] = {AddressingMode::abs, je};
	instruction_set[0xad] = {AddressingMode::abs, jne};
	instruction_set[0xae] = {AddressingMode::abs, js};
	instruction_set[0xaf] = {AddressingMode::abs, jns};
	instruction_set[0xb0] = {AddressingMode::abs, jo};
	instruction_set[0xb1] = {AddressingMode::abs, jno};
	instruction_set[0xb2] = {AddressingMode::abs, ja};
	instruction_set[0xb3] = {AddressingMode::abs, jna};
	instruction_set[0xb4] = {AddressingMode::abs, jl};
	instruction_set[0xb5] = {AddressingMode::abs, jge};
	instruction_set[0xb6] = {AddressingMode::abs, jg};
	instruction_set[0xb7] = {AddressingMode::abs, jng};
	
	instruction_set[0xb8] = {AddressingMode::abs, loop};

	instruction_set[0xb9] = {AddressingMode::abs, call};
	instruction_set[0xba] = {AddressingMode::imp, ret};
	
	instruction_set[0xbb] = {AddressingMode::imp, clc};
	instruction_set[0xbc] = {AddressingMode::imp, clz};
	instruction_set[0xbd] = {AddressingMode::imp, cls};
	instruction_set[0xbe] = {AddressingMode::imp, clo};
	instruction_set[0xbf] = {AddressingMode::imp, cld};
	
	instruction_set[0xc0] = {AddressingMode::imp, sec};
	instruction_set[0xc1] = {AddressingMode::imp, sez};
	instruction_set[0xc2] = {AddressingMode::imp, ses};
	instruction_set[0xc3] = {AddressingMode::imp, seo};
	instruction_set[0xc4] = {AddressingMode::imp, sed};

	instruction_set[0xc5] = {AddressingMode::imp, pusha};
	instruction_set[0xc6] = {AddressingMode::imp, pushx};
	instruction_set[0xc7] = {AddressingMode::imp, pushy};
	instruction_set[0xc8] = {AddressingMode::imp, pushf};
	instruction_set[0xc9] = {AddressingMode::imp, pushall};
	instruction_set[0xca] = {AddressingMode::imm, push};
	
	instruction_set[0xcb] = {AddressingMode::imp, popa};
	instruction_set[0xcc] = {AddressingMode::imp, popx};
	instruction_set[0xcd] = {AddressingMode::imp, popy};
	instruction_set[0xce] = {AddressingMode::imp, popf};
	instruction_set[0xcf] = {AddressingMode::imp, popall};
	instruction_set[0xd0] = {AddressingMode::dir, pop};
	instruction_set[0xd1] = {AddressingMode::abs, pop};

	instruction_set[0xd2] = {AddressingMode::imp, lods};
	instruction_set[0xd3] = {AddressingMode::imp, stos};
	instruction_set[0xd4] = {AddressingMode::imp, movs};

	instruction_set[0xd5] = {AddressingMode::imm, intr};
}