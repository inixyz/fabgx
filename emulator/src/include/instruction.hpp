#pragma once

#include "cpu.hpp"

namespace fab8{
	class Instruction{
	public:
		void (*addressing_mode)(Cpu&), (*operation)(Cpu&);

	public:
		static void nop(Cpu& cpu);
		static void stop(Cpu& cpu);

		static void lda(Cpu& cpu);
		static void ldx(Cpu& cpu);
		static void ldy(Cpu& cpu);
		static void ldf(Cpu& cpu);

		static void sta(Cpu& cpu);
		static void stx(Cpu& cpu);
		static void sty(Cpu& cpu);

		static void tax(Cpu& cpu);
		static void tay(Cpu& cpu);
		static void txa(Cpu& cpu);
		static void txy(Cpu& cpu);
		static void txsp(Cpu& cpu);
		static void txss(Cpu& cpu);
		static void tya(Cpu& cpu);
		static void tyx(Cpu& cpu);
		static void tyds(Cpu& cpu);
		static void tyes(Cpu& cpu);
		static void tspx(Cpu& cpu);
		static void tssx(Cpu& cpu);
		static void tdsy(Cpu& cpu);
		static void tesy(Cpu& cpu);

		static void ina(Cpu& cpu);
		static void inx(Cpu& cpu);
		static void iny(Cpu& cpu);
		static void inc(Cpu& cpu);

		static void dea(Cpu& cpu);
		static void dex(Cpu& cpu);
		static void dey(Cpu& cpu);
		static void dec(Cpu& cpu);

		static void adc(Cpu& cpu);
		static void sbb(Cpu& cpu);
		static void mul(Cpu& cpu);
		static void div(Cpu& cpu);
		static void mod(Cpu& cpu);

		static void _and(Cpu& cpu);
		static void _or(Cpu& cpu);
		static void _xor(Cpu& cpu);

		static void shla(Cpu& cpu);
		static void shl(Cpu& cpu);
		static void shra(Cpu& cpu);
		static void shr(Cpu& cpu);

		static void rola(Cpu& cpu);
		static void rol(Cpu& cpu);
		static void rora(Cpu& cpu);
		static void ror(Cpu& cpu);

		static void cmp(Cpu& cpu);
		static void cpx(Cpu& cpu);
		static void cpy(Cpu& cpu);

		static void jmp(Cpu& cpu);
		static void jc(Cpu& cpu);
		static void jnc(Cpu& cpu);
		static void je(Cpu& cpu);
		static void jne(Cpu& cpu);
		static void js(Cpu& cpu);
		static void jns(Cpu& cpu);
		static void jo(Cpu& cpu);
		static void jno(Cpu& cpu);
		static void ja(Cpu& cpu);
		static void jna(Cpu& cpu);
		static void jl(Cpu& cpu);
		static void jge(Cpu& cpu);
		static void jg(Cpu& cpu);
		static void jng(Cpu& cpu);

		static void loop(Cpu& cpu);

		static void call(Cpu& cpu);
		static void ret(Cpu& cpu);

		static void clc(Cpu& cpu);
		static void clz(Cpu& cpu);
		static void cls(Cpu& cpu);
		static void clo(Cpu& cpu);
		static void cld(Cpu& cpu);

		static void sec(Cpu& cpu);
		static void sez(Cpu& cpu);
		static void ses(Cpu& cpu);
		static void seo(Cpu& cpu);
		static void sed(Cpu& cpu);

		static void pusha(Cpu& cpu);
		static void pushx(Cpu& cpu);
		static void pushy(Cpu& cpu);
		static void pushf(Cpu& cpu);
		static void pushall(Cpu& cpu);
		static void push(Cpu& cpu);

		static void popa(Cpu& cpu);
		static void popx(Cpu& cpu);
		static void popy(Cpu& cpu);
		static void popf(Cpu& cpu);
		static void popall(Cpu& cpu);
		static void pop(Cpu& cpu);

		static void lods(Cpu& cpu);
		static void stos(Cpu& cpu);
		static void movs(Cpu& cpu);

		static void intr(Cpu& cpu);

		static void init();
	};

	extern Instruction instruction_set[256];
}

