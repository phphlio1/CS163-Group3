#include "Application.hpp"
#include "TextBox.hpp"
#include "InGame.hpp"
#include

Application::Application()
	: window_width_(1280), window_height_(720),
	  window_title_("CS163 Dictionary")
{
	run();
}

void Application::run()
{
	sf::RenderWindow window(sf::VideoMode(getWindowWidth(), getWindowHeight()),
							getWindowTitle());

	Frontend::InGame game(Frontend::GameMenu::WORD_TO_DEF);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			game.processEvent(event);
		}

		window.clear(sf::Color::White);
		window.draw(game);
		window.display();
	}
}

int Application::getWindowWidth() const
{
	return window_width_;
}

int Application::getWindowHeight() const
{
	return window_height_;
}

const sf::String &Application::getWindowTitle() const
{
	return window_title_;
}
