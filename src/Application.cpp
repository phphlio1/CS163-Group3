#include <SFML/Graphics.hpp>

#include "Application.h"
#include "TextBox.h"

Application::Application()
{
	run();
}

void Application::run()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
	Frontend::TextBox text_box(500, 200);
	text_box.setBackgroundColor(sf::Color::Blue);
	text_box.setBackgroundString("background");
	text_box.setForegroundString("foreground");
	text_box.setFont("../resources/JetBrainsMonoNL-Regular.ttf");

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;

			default:
				text_box.processEvent(event);
				break;
			}
        }

        window.clear(sf::Color::White);
		window.draw(text_box);
        window.display();
    }
}
