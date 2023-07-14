#include "instructions.h"
#include "cpu.h"

instr instrset[256];

void init_instrset(void){
	instrset[0x00] = (instr){addrm_imp, nop};

	instrset[0x01] = (instr){addrm_imm, lda};
	instrset[0x02] = (instr){addrm_dir, lda};
	instrset[0x03] = (instr){addrm_dirx, lda};
	instrset[0x04] = (instr){addrm_diry, lda};
	instrset[0x05] = (instr){addrm_prei, lda};
	instrset[0x06] = (instr){addrm_posi, lda};
	instrset[0x07] = (instr){addrm_abs, lda};
	instrset[0x08] = (instr){addrm_absx, lda};
	instrset[0x09] = (instr){addrm_absy, lda};

	instrset[0x0A] = (instr){addrm_imm, ldx};
	instrset[0x0B] = (instr){addrm_dir, ldx};
	instrset[0x0C] = (instr){addrm_diry, ldx};
	instrset[0x0D] = (instr){addrm_posi, ldx};
	instrset[0x0E] = (instr){addrm_abs, ldx};
	instrset[0x0F] = (instr){addrm_absy, ldx};

	instrset[0x10] = (instr){addrm_imm, ldy};
	instrset[0x11] = (instr){addrm_dir, ldy};
	instrset[0x12] = (instr){addrm_dirx, ldy};
	instrset[0x13] = (instr){addrm_prei, ldy};
	instrset[0x14] = (instr){addrm_abs, ldy};
	instrset[0x15] = (instr){addrm_absx, ldy};

	instrset[0x16] = (instr){addrm_dir, sta};
	instrset[0x17] = (instr){addrm_dirx, sta};
	instrset[0x18] = (instr){addrm_diry, sta};
	instrset[0x19] = (instr){addrm_prei, sta};
	instrset[0x1A] = (instr){addrm_posi, sta};
	instrset[0x1B] = (instr){addrm_abs, sta};
	instrset[0x1C] = (instr){addrm_absx, sta};
	instrset[0x1D] = (instr){addrm_absy, sta};

	instrset[0x1E] = (instr){addrm_dir, stx};
	instrset[0x1F] = (instr){addrm_diry, stx};
	instrset[0x20] = (instr){addrm_posi, stx};
	instrset[0x21] = (instr){addrm_abs, stx};
	instrset[0x22] = (instr){addrm_absy, stx};

	instrset[0x23] = (instr){addrm_dir, sty};
	instrset[0x24] = (instr){addrm_dirx, sty};
	instrset[0x25] = (instr){addrm_prei, sty};
	instrset[0x26] = (instr){addrm_abs, sty};
	instrset[0x27] = (instr){addrm_absx, sty};

	instrset[0x28] = (instr){addrm_imp, tax};
	instrset[0x29] = (instr){addrm_imp, tay};
	instrset[0x2A] = (instr){addrm_imp, txa};
	instrset[0x2B] = (instr){addrm_imp, txy};
	instrset[0x2C] = (instr){addrm_imp, txsp};
	instrset[0x2D] = (instr){addrm_imp, txss};
	instrset[0x2E] = (instr){addrm_imp, tya};
	instrset[0x2F] = (instr){addrm_imp, tyx};
	instrset[0x30] = (instr){addrm_imp, tyds};
	instrset[0x31] = (instr){addrm_imp, tspx};
	instrset[0x32] = (instr){addrm_imp, tssx};
	instrset[0x33] = (instr){addrm_imp, tdsy};

	instrset[0x34] = (instr){addrm_imp, ina};
	instrset[0x35] = (instr){addrm_imp, inx};
	instrset[0x36] = (instr){addrm_imp, iny};
	instrset[0x37] = (instr){addrm_dir, inc};
	instrset[0x38] = (instr){addrm_dirx, inc};
	instrset[0x39] = (instr){addrm_abs, inc};
	instrset[0x3A] = (instr){addrm_asby, inc};

	instrset[0x3B] = (instr){addrm_imp, dea};
	instrset[0x3C] = (instr){addrm_imp, dex};
	instrset[0x3D] = (instr){addrm_imp, dey};
	instrset[0x3E] = (instr){addrm_dir, dec};
	instrset[0x3F] = (instr){addrm_dirx, dec};
	instrset[0x40] = (instr){addrm_abs, dec};
	instrset[0x41] = (instr){addrm_absy, dec};

	instrset[0x42] = (instr){addrm_imm, adc};
	instrset[0x43] = (instr){addrm_dir, adc};
	instrset[0x44] = (instr){addrm_dirx, adc};
	instrset[0x45] = (instr){addrm_diry, adc};
	instrset[0x46] = (instr){addrm_prei, adc};
	instrset[0x47] = (instr){addrm_posi, adc};
	instrset[0x48] = (instr){addrm_abs, adc};
	instrset[0x49] = (instr){addrm_absx, adc};
	instrset[0x4A] = (instr){addrm_absy, adc};

	instrset[0x4B] = (instr){addrm_imm, sbb};
	instrset[0x4C] = (instr){addrm_dir, sbb};
	instrset[0x4D] = (instr){addrm_dirx, sbb};
	instrset[0x4E] = (instr){addrm_diry, sbb};
	instrset[0x4F] = (instr){addrm_prei, sbb};
	instrset[0x50] = (instr){addrm_posi, sbb};
	instrset[0x51] = (instr){addrm_abs, sbb};
	instrset[0x52] = (instr){addrm_absx, sbb};
	instrset[0x53] = (instr){addrm_absy, sbb};

	instrset[0x54] = (instr){addrm_imm, mul};
	instrset[0x55] = (instr){addrm_dir, mul};
	instrset[0x56] = (instr){addrm_dirx, mul};
	instrset[0x57] = (instr){addrm_abs, mul};
	instrset[0x58] = (instr){addrm_absx, mul};

	instrset[0x59] = (instr){addrm_imm, divs};
	instrset[0x5A] = (instr){addrm_dir, divs};
	instrset[0x5B] = (instr){addrm_dirx, divs};
	instrset[0x5C] = (instr){addrm_abs, divs};
	instrset[0x5D] = (instr){addrm_absx, divs};

	instrset[0x5E] = (instr){addrm_imm, mod};
	instrset[0x5F] = (instr){addrm_dir, mod};
	instrset[0x60] = (instr){addrm_dirx, mod};
	instrset[0x61] = (instr){addrm_abs, mod};
	instrset[0x62] = (instr){addrm_absx, mod};

	instrset[0x63] = (instr){addrm_imm, and};
	instrset[0x64] = (instr){addrm_dir, and};
	instrset[0x65] = (instr){addrm_dirx, and};
	instrset[0x66] = (instr){addrm_diry, and};
	instrset[0x67] = (instr){addrm_prei, and};
	instrset[0x68] = (instr){addrm_posi, and};
	instrset[0x69] = (instr){addrm_abs, and};
	instrset[0x6A] = (instr){addrm_absx, and};
	instrset[0x6B] = (instr){addrm_absy, and};

	instrset[0x6C] = (instr){addrm_imm, or};
	instrset[0x6D] = (instr){addrm_dir, or};
	instrset[0x6E] = (instr){addrm_dirx, or};
	instrset[0x6F] = (instr){addrm_diry, or};
	instrset[0x70] = (instr){addrm_prei, or};
	instrset[0x71] = (instr){addrm_posi, or};
	instrset[0x72] = (instr){addrm_abs, or};
	instrset[0x73] = (instr){addrm_absx, or};
	instrset[0x74] = (instr){addrm_absy, or};

	instrset[0x75] = (instr){addrm_imm, xor};
	instrset[0x76] = (instr){addrm_dir, xor};
	instrset[0x77] = (instr){addrm_dirx, xor};
	instrset[0x78] = (instr){addrm_diry, xor};
	instrset[0x79] = (instr){addrm_prei, xor};
	instrset[0x7A] = (instr){addrm_posi, xor};
	instrset[0x7B] = (instr){addrm_abs, xor};
	instrset[0x7C] = (instr){addrm_absx, xor};
	instrset[0x7D] = (instr){addrm_absy, xor};

	instrset[0x7E] = (instr){addrm_imp, shla};
	instrset[0x7F] = (instr){addrm_dir, shl};
	instrset[0x80] = (instr){addrm_dirx, shl};
	instrset[0x81] = (instr){addrm_abs, shl};
	instrset[0x82] = (instr){addrm_absx, shl};

	instrset[0x83] = (instr){addrm_imp, shra};
	instrset[0x84] = (instr){addrm_dir, shr};
	instrset[0x85] = (instr){addrm_dirx, shr};
	instrset[0x86] = (instr){addrm_abs, shr};
	instrset[0x87] = (instr){addrm_absx, shr};

	instrset[0x88] = (instr){addrm_imp, rola};
	instrset[0x89] = (instr){addrm_dir, rol};
	instrset[0x8A] = (instr){addrm_dirx, rol};
	instrset[0x8B] = (instr){addrm_abs, rol};
	instrset[0x8C] = (instr){addrm_absx, rol};

	instrset[0x8D] = (instr){addrm_imp, rora};
	instrset[0x8E] = (instr){addrm_dir, ror};
	instrset[0x8F] = (instr){addrm_dirx, ror};
	instrset[0x90] = (instr){addrm_abs, ror};
	instrset[0x91] = (instr){addrm_absx, ror};

	instrset[0x92] = (instr){addrm_imm, cmp};
	instrset[0x93] = (instr){addrm_dir, cmp};
	instrset[0x94] = (instr){addrm_dirx, cmp};
	instrset[0x95] = (instr){addrm_diry, cmp};
	instrset[0x96] = (instr){addrm_prei, cmp};
	instrset[0x97] = (instr){addrm_posi, cmp};
	instrset[0x98] = (instr){addrm_abs, cmp};
	instrset[0x99] = (instr){addrm_absx, cmp};
	instrset[0x9A] = (instr){addrm_absy, cmp};

	instrset[0x9B] = (instr){addrm_imm, cpx};
	instrset[0x9C] = (instr){addrm_dir, cpx};
	instrset[0x9D] = (instr){addrm_diry, cpx};
	instrset[0x9E] = (instr){addrm_abs, cpx};
	instrset[0x9F] = (instr){addrm_absy, cpx};

	instrset[0xA0] = (instr){addrm_imm, cpy};
	instrset[0xA1] = (instr){addrm_dir, cpy};
	instrset[0xA2] = (instr){addrm_dirx, cpy};
	instrset[0xA3] = (instr){addrm_abs, cpy};
	instrset[0xA4] = (instr){addrm_absx, cpy};

	instrset[0xA5] = (instr){addrm_abs, jmp};
	instrset[0xA6] = (instr){addrm_abs, jc};
	instrset[0xA7] = (instr){addrm_abs, jnc};
	instrset[0xA8] = (instr){addrm_abs, je};
	instrset[0xA9] = (instr){addrm_abs, jne};
	instrset[0xAA] = (instr){addrm_abs, js};
	instrset[0xAB] = (instr){addrm_abs, jns};
	instrset[0xAC] = (instr){addrm_abs, jo};
	instrset[0xAD] = (instr){addrm_abs, jno};
	instrset[0xAE] = (instr){addrm_abs, ja};
	instrset[0xAF] = (instr){addrm_abs, jna};
	instrset[0xB0] = (instr){addrm_abs, jl};
	instrset[0xB1] = (instr){addrm_abs, jge};
	instrset[0xB2] = (instr){addrm_abs, jg};
	instrset[0xB3] = (instr){addrm_abs, jng};

	instrset[0xB4] = (instr){addrm_abs, loop};

	instrset[0xB5] = (instr){addrm_abs, call};
	instrset[0xB6] = (instr){addrm_imp, ret};

	instrset[0xB7] = (instr){addrm_imp, clc};
	instrset[0xB8] = (instr){addrm_imp, clz};
	instrset[0xB9] = (instr){addrm_imp, cls};
	instrset[0xBA] = (instr){addrm_imp, clo};
	instrset[0xBB] = (instr){addrm_imp, cld};

	instrset[0xBC] = (instr){addrm_imp, sec};
	instrset[0xBD] = (instr){addrm_imp, sez};
	instrset[0xBE] = (instr){addrm_imp, ses};
	instrset[0xBF] = (instr){addrm_imp, seo};
	instrset[0xC0] = (instr){addrm_imp, sed};

	instrset[0xC1] = (instr){addrm_imm, ldf};

	instrset[0xC2] = (instr){addrm_imp, pusha};
	instrset[0xC3] = (instr){addrm_imp, pushx};
	instrset[0xC4] = (instr){addrm_imp, pushy};
	instrset[0xC5] = (instr){addrm_imp, pushf};
	instrset[0xC6] = (instr){addrm_imp, pushall};
	instrset[0xC7] = (instr){addrm_imm, push};

	instrset[0xC8] = (instr){addrm_imp, popa};
	instrset[0xC9] = (instr){addrm_imp, popx};
	instrset[0xCA] = (instr){addrm_imp, popy};
	instrset[0xCB] = (instr){addrm_imp, popf};
	instrset[0xCC] = (instr){addrm_imp, popall};
	instrset[0xCD] = (instr){addrm_dir, pop};

	instrset[0xCE] = (instr){addrm_imm, intr};

	instrset[0xCF] = (instr){addrm_imp, lods};
	instrset[0xD0] = (instr){addrm_imp, stos};
	instrset[0xD1] = (instr){addrm_imp, movs};

	instrset[0xD2] = (instr){addrm_imp, tyes};
	instrset[0xD3] = (instr){addrm_imp, tesy};

	instrset[0xD4] = (instr){addrm_abs, pop};

	instrset[0xFF] = (instr){addrm_imp, stop};
}

void addrm_imp(void){}

void addrm_imm(void){
	location = PC++;
}

void addrm_dir(void){
	location = addrcat(DS, readcurr());
}

void addrm_dirx(void){
	location = addrcat(DS, readcurr()) + X;
}

void addrm_diry(void){
	location = addrcat(DS, readcurr()) + Y;
}

void addrm_prei(void){
	location = addrcat(ES, memory[addrcat(DS, readcurr()) + X]);
}

void addrm_posi(void){
	location = addrcat(ES, memory[addrcat(DS, readcurr())]) + Y;
}

void addrm_abs(void){
	location = addrcat(readcurr(), readcurr());
}

void addrm_absx(void){
	location = addrcat(readcurr(), readcurr()) + X;
}

void addrm_absy(void){
	location = addrcat(readcurr(), readcurr()) + Y;
}

void nop(void){}

void lda(void){
	A = fetched; update_flagsZS(A);
}

void ldx(void){
	X = fetched; update_flagsZS(X);
}

void ldy(void){
	Y = fetched; update_flagsZS(Y);
}

void sta(void){
	memory[location] = A;
}

void stx(void){
	memory[location] = X;
}

void sty(void){
	memory[location] = Y;
}

void tax(void){
	A = X; update_flagsZS(A);
}

void tay(void){
	A = Y; update_flagsZS(A);
}

void txa(void){
	X = A; update_flagsZS(X);
}

void txy(void){
	X = Y; update_flagsZS(X);
}

void txsp(void){
	X = SP; update_flagsZS(X);
}

void txss(void){
	X = SS; update_flagsZS(X);
}

void tya(void){
	Y = A; update_flagsZS(Y);
}

void tyx(void){
	Y = X; update_flagsZS(Y);
}

void tyds(void){
	Y = DS; update_flagsZS(Y);
}

void tyes(void){
	Y = ES; update_flagsZS(Y);
}

void tspx(void){
	SP = X; update_flagsZS(SP);
}

void tssx(void){
	SS = X; update_flagsZS(SS);
}

void tdsy(void){
	DS = Y; update_flagsZS(DS);
}

void tesy(void){
	ES = Y; update_flagsZS(ES);
}

void ina(void){
	A++; update_flagsZS(A);
}

void inx(void){
	X++; update_flagsZS(X);
}

void iny(void){
	Y++; update_flagsZS(Y);
}

void inc(void){
	memory[location]++; update_flagsZS(memory[location]);
}

void dea(void){
	A--; update_flagsZS(A);
}

void dex(void){
	X--; update_flagsZS(X);
}

void dey(void){
	Y--; update_flagsZS(Y);
}

void dec(void){
	memory[location]--; update_flagsZS(memory[location]);
}

void adc(void){
	temp = A + fetched + get_flag(CARRY);
	set_flag(CARRY, temp > 255);

	if(sign(A) && sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(A) && !sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	A = temp;
	update_flagsZS(A);
}

void sbb(void){ 
	temp = A - fetched - get_flag(CARRY);
	set_flag(CARRY, temp > 255);

	if(sign(A) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(A) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	A = temp;
	update_flagsZS(A);
}

void mul(void){
	temp = A * fetched;
	A = temp;

	set_flag(CARRY, temp > 255);
	update_flagsZS(A);
}

void divs(void){
	A /= fetched; update_flagsZS(A);
}

void mod(void){
	A %= fetched; update_flagsZS(A);
}

void and(void){
	A &= fetched; update_flagsZS(A);
}

void or(void){
	A |= fetched; update_flagsZS(A);
}

void xor(void){
	A ^= fetched; update_flagsZS(A);
}

void shla(void){
	set_flag(CARRY, sign(A));
	A <<= 1; update_flagsZS(A);
}

void shl(void){
	set_flag(CARRY, sign(memory[location]));
	memory[location] <<= 1; update_flagsZS(memory[location]);
}

void shra(void){
	set_flag(CARRY, A & 0b00000001);
	A >>= 1; update_flagsZS(A);
}

void shr(void){
	set_flag(CARRY, memory[location] & 0b00000001);
	memory[location] >>= 1; update_flagsZS(memory[location]);
}

void rola(void){
	temp = sign(A);
	A <<= 1;
	A |= get_flag(CARRY);
	set_flag(CARRY, temp);
	update_flagsZS(A);
}

void rol(void){
	temp = sign(memory[location]);
	memory[location] <<= 1;
	memory[location] |= get_flag(CARRY);
	set_flag(CARRY, temp);
	update_flagsZS(memory[location]);
}

void rora(void){
	temp = A & 0b00000001;
	A >>= 1;
	A |= get_flag(CARRY) << 7;
	set_flag(CARRY, temp);
	update_flagsZS(A);
}

void rorr(void){
	temp = memory[location] & 0b00000001;
	memory[location] >>= 1;
	memory[location] |= get_flag(CARRY) << 7;
	set_flag(CARRY, temp);
	update_flagsZS(memory[location]);
}

void cmp(void){
	temp = A - fetched;
	set_flag(CARRY, temp > 255);

	if(sign(A) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(A) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	update_flagsZS(temp);
}

void cpx(void){
	temp = X - fetched;
	set_flag(CARRY, temp > 255);

	if(sign(X) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(X) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	update_flagsZS(temp);
}

void cpy(void){
	temp = Y - fetched;
	set_flag(CARRY, temp > 255);

	if(sign(Y) && !sign(fetched) && !sign(temp)) set_flag(OVERFLOW, 1);
	else if(!sign(Y) && sign(fetched) && sign(temp)) set_flag(OVERFLOW, 1);
	else set_flag(OVERFLOW, 0);

	update_flagsZS(temp);
}

void jmp(void){
	PC = location;
}

void jc(void){
	if(get_flag(CARRY)) PC = location;
}

void jnc(void){
	if(!get_flag(CARRY)) PC = location;
}

void je(void){
	if(get_flag(ZERO)) PC = location;
}

void jne(void){
	if(!get_flag(ZERO)) PC = location;
}

void js(void){
	if(get_flag(SIGN)) PC = location;
}

void jns(void){
	if(!get_flag(SIGN)) PC = location;
}

void jo(void){
	if(get_flag(OVERFLOW)) PC = location;
}

void jno(void){
	if(!get_flag(OVERFLOW)) PC = location;
}

void ja(void){
	if(!get_flag(CARRY) && !get_flag(ZERO)) PC = location;
}

void jna(void){
	if(get_flag(CARRY) || get_flag(ZERO)) PC = location;
}

void jl(void){
	if(get_flag(SIGN) != get_flag(OVERFLOW)) PC = location;
}

void jge(void){
	if(get_flag(SIGN) == get_flag(OVERFLOW)) PC = location;
}

void jg(void){
	if(!get_flag(ZERO) && get_flag(SIGN) == get_flag(OVERFLOW)) PC = location;
}

void jng(void){
	if(get_flag(ZERO) || get_flag(SIGN) != get_flag(OVERFLOW)) PC = location;
}

void loop(void){
	if(Y){
		Y--;
		PC = location;
	}
}

void call(void){
	memory[addrcat(SS, --SP)] = PC >> 8;
	memory[addrcat(SS, --SP)] = PC;
	PC = location;
}

void ret(void){
	PC = memory[addrcat(SS, SP++)] << 8 | memory[addrcat(SS, SP++)];
}

void clc(void){
	set_flag(CARRY, 0);
}

void clz(void){
	set_flag(ZERO, 0);
}

void cls(void){
	set_flag(SIGN, 0);
}

void clo(void){
	set_flag(OVERFLOW, 0);
}

void cld(void){
	set_flag(DIRECTION, 0);
}

void sec(void){
	set_flag(CARRY, 1);
}

void sez(void){
	set_flag(ZERO, 1);
}

void ses(void){
	set_flag(SIGN, 1);
}

void seo(void){
	set_flag(OVERFLOW, 1);
}

void sed(void){
	set_flag(DIRECTION, 1);
}

void ldf(void){
	F = fetched;
}

void pusha(void){
	memory[addrcat(SS, --SP)] = A;	
}

void pushx(void){
	memory[addrcat(SS, --SP)] = X;	
}

void pushy(void){
	memory[addrcat(SS, --SP)] = Y;
}

void pushf(void){
	memory[addrcat(SS, --SP)] = F;	
}

void pushall(void){
	memory[addrcat(SS, --SP)] = A;
	memory[addrcat(SS, --SP)] = X;
	memory[addrcat(SS, --SP)] = Y;
	memory[addrcat(SS, --SP)] = F;
}

void push(void){
	memory[addrcat(SS, --SP)] = fetched;
}

void popa(void){
	A = memory[addrcat(SS, SP++)];	
}

void popx(void){
	X = memory[addrcat(SS, SP++)];	
}

void popy(void){
	Y = memory[addrcat(SS, SP++)];
}

void popf(void){
	F = memory[addrcat(SS, SP++)];	
}

void popall(void){
	F = memory[addrcat(SS, SP++)];
	Y = memory[addrcat(SS, SP++)];
	X = memory[addrcat(SS, SP++)];
	A = memory[addrcat(SS, SP++)];
}

void pop(void){
	memory[location] = memory[addrcat(SS, SP++)];
}

void intr(void){
	//TODO: BIOS
}

void lods(void){
	A = memory[addrcat(DS, X)];
	X = get_flag(DIRECTION) ? X - 1 : X + 1;
}

void stos(void){
	memory[addrcat(ES, Y)] = A;
	Y = get_flag(DIRECTION) ? Y - 1 : Y + 1;
}

void movs(void){
	memory[addrcat(ES, Y)] = memory[addrcat(DS, X)];
	X = get_flag(DIRECTION) ? X - 1 : X + 1;
	Y = get_flag(DIRECTION) ? Y - 1 : Y + 1;
}

void stop(void){
	running = 0;
}