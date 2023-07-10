#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

void addrm_imp(void){}
void addrm_imm(void);
void addrm_dir(void);
void addrm_dirx(void);
void addrm_diry(void);
void addrm_prei(void);
void addrm_posi(void);
void addrm_abs(void);
void addrm_absx(void);
void addrm_absy(void);

void lda(void);
void ldx(void);
void ldy(void);

void sta(void);
void stx(void);
void sty(void);

void tax(void);
void tay(void);
void txa(void);
void txy(void);
void txsp(void);
void txss(void);
void tya(void);
void tyx(void);
void tyds(void);
void tyes(void);
void tspx(void);
void tssx(void);
void tdsy(void);
void tesy(void);

void ina(void);
void inx(void);
void iny(void);
void inc(void);

void dea(void);
void dex(void);
void dey(void);
void dec(void);

void adc(void);
void sbb(void);

void mul(void);
void div(void);
void mod(void);

void and(void);
void or(void);
void xor(void);

void shla(void);
void shl(void);
void shra(void);
void shr(void);

void rola(void);
void rol(void);
void rora(void);
void rorr(void);

void cmp(void);
void cpx(void);
void cpy(void);

void jmp(void);
void jc(void);
void jnc(void);
void je(void);
void jne(void);
void js(void);
void jns(void);
void jo(void);
void jno(void);
void ja(void);
void jna(void);
void jl(void);
void jge(void);
void jg(void);
void jng(void);

void loop(void);

void call(void);

#endif
