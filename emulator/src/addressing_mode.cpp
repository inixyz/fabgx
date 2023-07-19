#include "addressing_mode.hpp"
#include "utils.hpp"

using namespace fab8;

void AddressingMode::imp(Cpu& cpu){}

void AddressingMode::imm(Cpu& cpu){
	cpu.location = cpu.pc++;
}

void AddressingMode::dir(Cpu& cpu){
	cpu.location = phy_addr(cpu.ds, cpu.read_next());
}

void AddressingMode::dirx(Cpu& cpu){
	cpu.location = phy_addr(cpu.ds, cpu.read_next()) + cpu.x;
}

void AddressingMode::diry(Cpu& cpu){
	cpu.location = phy_addr(cpu.ds, cpu.read_next()) + cpu.y;
}

void AddressingMode::prei(Cpu& cpu){
	cpu.location = phy_addr(cpu.es, cpu.memory[phy_addr(cpu.ds, cpu.read_next() + cpu.x)]);
}

void AddressingMode::posi(Cpu& cpu){
	cpu.location = phy_addr(cpu.es, cpu.memory[phy_addr(cpu.ds, cpu.read_next())]) + cpu.y;
}

void AddressingMode::abs(Cpu& cpu){
	cpu.location = phy_addr(cpu.read_next(), cpu.read_next());
}

void AddressingMode::absx(Cpu& cpu){
	cpu.location = phy_addr(cpu.read_next(), cpu.read_next()) + cpu.x;
}

void AddressingMode::absy(Cpu& cpu){
	cpu.location = phy_addr(cpu.read_next(), cpu.read_next()) + cpu.y;
}