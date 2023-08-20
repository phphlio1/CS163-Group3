#include "Application.hpp"
#include "TextBox.hpp"
#include "SideBar.hpp"
#include "DefinitionFrame.hpp"

Application::Application()
	: window_width_(1280), window_height_(720),
	  window_title_("CS163 Dictionary")
{
	Frontend::TextBox *text_box = new Frontend::TextBox;
	text_box->setPosition(701, 18);
	
	Frontend::SideBar *side_bar = new Frontend::SideBar;
	side_bar->setPosition(0, 70);
	
	Frontend::DefinitionFrame *definition_frame = new Frontend::DefinitionFrame;
	definition_frame->setPosition(330, 70);
	definition_frame->setKeyword("welcome");
	
	components_ = std::move(std::vector<Frontend::Component*>
							{text_box, side_bar, definition_frame});
	
	run();
}

Application::~Application()
{
	for (auto component : components_)
	{
		delete component;
	}
}

void Application::run()
{
    sf::RenderWindow window(sf::VideoMode(getWindowWidth(), getWindowHeight()),
							getWindowTitle(),
							sf::Style::Titlebar | sf::Style::Close);

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
				break;
			}
        }
		for (auto component : components_)
		{
			if (component->isVisible())
			{
				component->processEvent(event);	
			}
		}

		window.clear(sf::Color::White);
		for (auto component : components_)
		{
			if (component->isVisible())
			{
				window.draw(*component);	
			}
		}
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
