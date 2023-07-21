#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
	
namespace fab8{
	class Window{
		private:
			unsigned int width, height;
			std::string title;
			float scale;
			sf::RenderWindow render_window;
			sf::Event event;
			sf::View view;
			std::thread thread;

		public:
			Window(unsigned int width, unsigned int height, std::string title, float scale){
				this->width = width;
				this->height = height;
				this->title = title;
				this->scale = scale;

				view = sf::View(sf::FloatRect(0, 0, width, height));

				thread = std::thread(&Window::run, this);
			}

		private:
			virtual void draw(){}

			void run(){
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
	};
}