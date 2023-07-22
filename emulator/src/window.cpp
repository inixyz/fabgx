#include "window.hpp"
#include "imgui.h"
#include "imgui-SFML.h"

using namespace fab8;

Window::Window(unsigned int width, unsigned int height, float scale, std::string title){
	this->width = width;
	this->height = height;
	this->title = title;
	this->scale = scale;

	view = sf::View(sf::FloatRect(0, 0, width, height));

	thread = std::thread(&Window::run, this);
}

void Window::draw(){}

void Window::process(){}

void Window::run(){
	render_window.create(sf::VideoMode(width * scale, height * scale), title, sf::Style::Default);
	render_window.setFramerateLimit(60);
	render_window.setVerticalSyncEnabled(true);
	render_window.setView(view);

	ImGui::SFML::Init(render_window);

	while(render_window.isOpen()){
		while(render_window.pollEvent(event)){
			ImGui::SFML::ProcessEvent(render_window, event);
			if(event.type == sf::Event::Closed) render_window.close();
		}

		ImGui::SFML::Update(render_window, clock.restart());
		ImGui::SFML::SetCurrentWindow(render_window);

		process();

		render_window.clear();
		draw();
		ImGui::SFML::Render(render_window);
		render_window.display();
	}

	ImGui::SFML::Shutdown(render_window);
}