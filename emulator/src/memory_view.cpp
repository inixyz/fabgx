#include "memory_view.hpp"
#include "imgui.h"
#include "imgui-SFML.h"
#include "utils.hpp"
#include <cstdlib>

using namespace fab8;

MemoryView::MemoryView(Cpu* cpu, unsigned int width, unsigned int height, std::string title, float scale) : Window(width, height, title, scale){
	this->cpu = cpu;
}

void MemoryView::process(){
	ImGui::SetNextWindowSize(ImVec2(width * scale, height * scale));
	ImGui::SetNextWindowPos(ImVec2(0, 0));

	ImGui::Begin(title.c_str(), NULL, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
	ImGui::Text("A: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->a ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->a);
	ImGui::SameLine(0, 0);
	ImGui::Text("X: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->x ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->x);
	ImGui::SameLine(0, 0);
	ImGui::Text("Y: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->y ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->y);
	ImGui::SameLine(0, 0);
	ImGui::Text("SP: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->sp ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->sp);
	ImGui::SameLine(0, 0);
	ImGui::Text("SS: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->ss ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->ss);
	ImGui::SameLine(0, 0);
	ImGui::Text("DS: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->ds ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->ds);
	ImGui::SameLine(0, 0);
	ImGui::Text("ES: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->es ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->es);
	ImGui::SameLine(0, 0);
	ImGui::Text("active: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->active ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%d  ", cpu->active);
	ImGui::SameLine(0, 0);
	ImGui::Text("PC: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->pc ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.4x  ", cpu->pc);

	ImGui::Text("CF:");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->get_flag(Cpu::Flag::CARRY) ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%d  ", cpu->get_flag(Cpu::Flag::CARRY));
	ImGui::SameLine(0, 0);
	ImGui::Text("ZF:");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->get_flag(Cpu::Flag::ZERO) ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%d  ", cpu->get_flag(Cpu::Flag::ZERO));
	ImGui::SameLine(0, 0);
	ImGui::Text("SF:");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->get_flag(Cpu::Flag::SIGN) ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%d  ", cpu->get_flag(Cpu::Flag::SIGN));
	ImGui::SameLine(0, 0);
	ImGui::Text("OF:");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->get_flag(Cpu::Flag::OVERFLOW) ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%d  ", cpu->get_flag(Cpu::Flag::OVERFLOW));
	ImGui::SameLine(0, 0);
	ImGui::Text("DF:");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->get_flag(Cpu::Flag::DIRECTION) ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%d    ", cpu->get_flag(Cpu::Flag::DIRECTION));
	ImGui::SameLine(0, 0);
	ImGui::Text("fetched: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->fetched ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x  ", cpu->fetched);
	ImGui::SameLine(0, 0);
	ImGui::Text("location: ");
	ImGui::SameLine(0, 0);
	ImGui::TextColored(cpu->location ? ImVec4(0, 1, 0, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.4x  ", cpu->location);

	ImGui::Text(" ");

	ImGui::Text("Segment: ");
	ImGui::SameLine(0, 0);
	ImGui::InputText("##", seg_str, IM_ARRAYSIZE(seg_str));

	seg_str[0] = tolower(seg_str[0]);
	seg_str[1] = tolower(seg_str[1]);

	if(!strcmp(seg_str, "ss")) seg_addr = cpu->ss;
	else if(!strcmp(seg_str, "ds")) seg_addr = cpu->ds;
	else if(!strcmp(seg_str, "es")) seg_addr = cpu->es;
	else seg_addr = strtoul(seg_str, NULL, 16);
	
	ImGui::Text(" ");

	for(int y = 0; y < 16; y++){
		ImGui::TextColored(ImVec4(1, 1, 0, 1), "%.2x:%x0  ", seg_addr, y);
		for(int x = 0; x < 16; x++){
			ImGui::SameLine(0, 0);
			if(phy_addr(seg_addr, x + y * 16) == cpu->pc)
				ImGui::TextColored(ImVec4(0, 1, 0, 1), "%.2x ", cpu->memory[phy_addr(seg_addr, x + y * 16)]);
			else
				ImGui::TextColored(cpu->memory[phy_addr(seg_addr, x + y * 16)] ? ImVec4(1, 1, 1, 1) : ImVec4(0.7, 0.7, 0.7, 0.7), "%.2x ", cpu->memory[phy_addr(seg_addr, x + y * 16)]);
		}

		ImGui::SameLine(0, 0);
		ImGui::Text("  ");
		for(int x = 0; x < 16; x++){
			ImGui::SameLine(0, 0);
			char c = cpu->memory[phy_addr(seg_addr, x + y * 16)];
			if(c >= 32 && c <= 126) ImGui::TextColored(ImVec4(1, 1, 1, 1), "%c", c);
			else ImGui::TextColored(ImVec4(0.7, 0.7, 0.7, 0.7), ".");
		}
	}
	ImGui::End();
}