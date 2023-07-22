#pragma once

#include <SFML/Graphics.hpp>
#include <thread>
	
namespace fab8{
	class Window{
		protected:
			sf::RenderWindow render_window;
			unsigned int width, height;
			float scale;
			std::string title;

		private:
			sf::Event event;
			sf::Clock clock;
			sf::View view;
			std::thread thread;

		public:
			Window(unsigned int width, unsigned int height, std::string title, float scale);

		private:
			virtual void process();
			virtual void draw();
			void run();
	};
}