#ifndef APPLICATION_H
#define APPLICATION_H

#include <SFML/Graphics.hpp>

class Application
{
public:
	Application();
	
	void run();

	int getWindowWidth() const;
	int getWindowHeight() const;
	const sf::String& getWindowTitle() const;

private:
	int window_width_, window_height_, window_style_;
	sf::String window_title_;
};

#endif
