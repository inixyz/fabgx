#include "memory_view.hpp"

using namespace fab8;

MemoryView::MemoryView(Cpu* cpu, unsigned int width, unsigned int height, float scale, std::string title) : Window(width, height, scale, title){
	this->cpu = cpu;
}

void MemoryView::draw(){}