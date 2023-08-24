#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>

#include "Trie.h"
#include "Dictionary.h"
#include "Component.hpp"

extern sf::RenderWindow *g_window;
extern Trie *g_tries[];
extern Trie *g_curr_trie;

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
	void setupFrontend();
	void initTries();

	int window_width_, window_height_, window_style_;
	sf::String window_title_;
	std::vector<Frontend::Component*> components_;
};

#endif
