#include <SFML/Graphics.hpp>

#include "Application.hpp"
#include "header.hpp"
#include "SideBar.hpp"
#include "DefinitionFrame.hpp"

sf::RenderWindow *g_window;
Trie *g_tries[4];
Trie *g_curr_trie;

Application::Application()
	: window_width_(1280), window_height_(720),
	  window_title_("CS163 Dictionary")
{
	initTries();
	setupFrontend();
	run();
}

Application::~Application()
{
	for (auto component : components_)
	{
		delete component;
	}
	
	std::string message = "";
	for (auto trie : g_tries)
	{
		trie->Serialization_DFS(message);
		delete trie;
	}
}

void Application::setupFrontend()
{
	Frontend::TextBox *text_box = new Frontend::TextBox;
	text_box->setPosition(701, 18);
	
	Frontend::SideBar *side_bar = new Frontend::SideBar;
	side_bar->setPosition(0, 70);
	
	Frontend::DefinitionFrame *definition_frame = new Frontend::DefinitionFrame;
	definition_frame->setPosition(330, 70);
	// definition_frame->setKeyword("welcome");

	Frontend::Header *header = new Frontend::Header;
	header->setPosition(0, 0);
	
	components_ = std::move(std::vector<Frontend::Component*>
							{text_box, side_bar, definition_frame, header});
}

void Application::initTries()
{
	tries_[0] = new Trie(Datasets::Eng_Eng);
	tries_[1] = new Trie(Datasets::Eng_Viet);
	tries_[2] = new Trie(Datasets::Viet_Eng);
	tries_[3] = new Trie(Datasets::Emoji);

	std::string message = "";
	for (auto trie : tries_)
	{
		trie->Deserialization_DFS(message);
	}
}

void Application::run()
{
	g_window = new sf::RenderWindow(sf::VideoMode(getWindowWidth(), getWindowHeight()),
									getWindowTitle(),
									sf::Style::Titlebar | sf::Style::Close);
	
    while (g_window->isOpen())
    {
        sf::Event event;
        while (g_window->pollEvent(event))
        {
            switch (event.type)
			{
			case sf::Event::Closed:
				g_window->close();
				break;

			default:
				break;
			}
        }
		for (Frontend::Component *component : components_)
		{
			if (component->isVisible())
			{
				component->processEvent(event);
			}
		}

        g_window->clear(sf::Color::White);
		
		for (const Frontend::Component *component : components_)
		{
			if (component->isVisible())
			{
				g_window->draw(*component);
			}
		}
		
        g_window->display();
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

void Application::setupFrontend()
{
	Frontend::SideBar *side_bar = new Frontend::SideBar;
	side_bar->setPosition(0, 70);
	
	Frontend::DefinitionFrame *definition_frame = new Frontend::DefinitionFrame;
	definition_frame->setPosition(330, 70);
	// definition_frame->setKeyword("welcome");

	Frontend::Header *header = new Frontend::Header;
	header->setPosition(0, 0);
	
	components_ = std::move(std::vector<Frontend::Component*>
							{side_bar, definition_frame, header});
}

void Application::initTries()
{
	g_tries[0] = new Trie(Datasets::Eng_Eng);
	g_tries[1] = new Trie(Datasets::Eng_Viet);
	g_tries[2] = new Trie(Datasets::Viet_Eng);
	g_tries[3] = new Trie(Datasets::Emoji);

	std::string message;
	for (auto trie : g_tries)
	{
		trie->Deserialization_DFS(message);
	}

	g_curr_trie = g_tries[0];
}
