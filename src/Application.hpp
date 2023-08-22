#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

#include "Component.hpp"

class Application
{
public:
	Application();
	virtual ~Application();

	void run();

	int getWindowWidth() const;
	int getWindowHeight() const;
	const sf::String& getWindowTitle() const;

private:
	void setup();

	int window_width_, window_height_, window_style_;
	sf::String window_title_;
	std::vector<Frontend::Component*> components_;

	Trie *tries_[4];
};

#endif
