#include <SFML/Graphics.hpp>

#include "InGame.hpp"
#include "Application.hpp"
#include "header.hpp"
// #include "SideBar.hpp"
// #include "DefinitionFrame.hpp"
#include "Global.hpp"
// #include "HistoryBar.hpp"

sf::RenderWindow *g_window;
Trie *g_tries[4];
Trie *g_curr_trie;
std::vector<std::string> g_favorites, g_history;

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
	for (Trie *trie : g_tries)
	{
		trie->Serialization_DFS(message);
		delete trie;
	}
}

void Application::setupFrontend()
{
	Frontend::Header *header = new Frontend::Header;
	header->setPosition(0, 0);
	components_.push_back(header);

	Frontend::InGame *game = new Frontend::InGame(Frontend::DEF_TO_WORD);
	components_.push_back(game);

	// std::string message;
	// g_curr_trie->takeHistory(g_history, message);
	// g_curr_trie->viewFavoriteList(g_favorites, message);

	// Frontend::HistoryBar *history_bar = new Frontend::HistoryBar;
	// history_bar->setPosition(0, 70);
	// components_.push_back(history_bar);

	// Frontend::DefinitionFrame *definition_frame = new Frontend::DefinitionFrame;
	// definition_frame->setHistoryBar(history_bar);
	// definition_frame->setPosition(330, 70);
	// definition_frame->setKeyword("test");
	// definition_frame->setKeyword("welcome");
	// definition_frame->setKeyword("sequence");
	// components_.push_back(definition_frame);

	// history_bar->setDefinitionFrame(definition_frame);

	// Frontend::SideBar *side_bar = new Frontend::SideBar;
	// side_bar->setDefinitionFrame(definition_frame);
	// side_bar->setPosition(0, 70);
	// components_.push_back(side_bar);
	// side_bar->setVisibility(0);
}

void Application::initTries()
{
	g_tries[0] = new Trie(Datasets::Eng_Eng);
	g_tries[1] = new Trie(Datasets::Eng_Viet);
	g_tries[2] = new Trie(Datasets::Viet_Eng);
	g_tries[3] = new Trie(Datasets::Emoji);

	std::string message = "";
	// Fix backend bugs
	for (auto trie : g_tries)
	{
		trie->build_Trie_From_Origin(message);
		int num = trie->num_line;
		trie->delete_Whole_Trie();
		trie->num_line = num;
	}
	for (auto trie : g_tries)
	{
		trie->Deserialization_DFS(message);
	}
}

void Application::run()
{
	g_window = new sf::RenderWindow(sf::VideoMode(getWindowWidth(), getWindowHeight()),
									getWindowTitle(),
									sf::Style::Titlebar | sf::Style::Close);
	g_window->setFramerateLimit(60);

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

			for (Frontend::Component *component : components_)
			{
				if (!component->isVisible())
				{
					continue;
				}

				component->processEvent(event);
			}
		}

		g_window->clear(sf::Color::White);

		for (const Frontend::Component *component : components_)
		{
			if (!component->isVisible())
			{
				continue;
			}

			g_window->draw(*component);
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

const sf::String &Application::getWindowTitle() const
{
	return window_title_;
}