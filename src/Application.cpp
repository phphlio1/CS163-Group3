#include "Application.hpp"
#include "TextBox.hpp"

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
	
	Frontend::TextBox text_box(500, 200);
	text_box.setBackgroundString("background");
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

int Application::getWindowWidth() const
{
	return window_width_;
}

int Application::getWindowHeight() const
{
	return window_height_;
}

const sf::String& Application::getWindowTitle() const
{
	return window_title_;
}
