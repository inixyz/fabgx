#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
	
namespace fab8{
	class Window{
		protected:
			sf::RenderWindow render_window;

		private:
			unsigned int width, height;
			std::string title;
			float scale;
			sf::Event event;
			sf::Clock clock;
			sf::View view;
			std::thread thread;

		public:
			Window(unsigned int width, unsigned int height, float scale, std::string title);

		private:
			virtual void draw();
			virtual void process();
			void run();
	};
}