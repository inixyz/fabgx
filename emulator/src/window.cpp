#include "window.hpp"

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

void Window::run(){
	render_window.create(sf::VideoMode(width * scale, height * scale), title, sf::Style::Default);
	render_window.setFramerateLimit(60);
	render_window.setVerticalSyncEnabled(true);
	render_window.setView(view);

	while(render_window.isOpen()){
		while(render_window.pollEvent(event))
			if(event.type == sf::Event::Closed) render_window.close();

		render_window.clear();
		draw();
		render_window.display();
	}
}