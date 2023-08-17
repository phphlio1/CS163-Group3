#include "Application.hpp"
#include "TextBox.hpp"
#include "SideBar.hpp"
#include "DefinitionFrame.hpp"

Application::Application()
	: window_width_(1280), window_height_(720),
	  window_title_("CS163 Dictionary")
{
	run();
}

void Application::run()
{
    sf::RenderWindow window(sf::VideoMode(getWindowWidth(), getWindowHeight()),
							getWindowTitle(),
							sf::Style::Titlebar | sf::Style::Close);

	Frontend::TextBox text_box;
	text_box.setPosition(701, 18);
	Frontend::SideBar side_bar;
	side_bar.setPosition(0, 70);
	Frontend::DefinitionFrame definition_frame;
	definition_frame.setPosition(330, 70);
	definition_frame.setKeyword("welcome");

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
				side_bar.processEvent(event);
				break;
			}
        }

        window.clear(sf::Color::White);
		window.draw(text_box);
		window.draw(side_bar);
		window.draw(definition_frame);
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
