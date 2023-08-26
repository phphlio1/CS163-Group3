#include "AddWordScreen.hpp"

using namespace Frontend;

AddWordScreen::AddWordScreen(int n_width, int n_height)
	: EditDefinition(n_width, n_height)
{
}

void AddWordScreen::processEvent(const sf::Event &event)
{
	std::cerr << "before process\n";
	EditDefinition::processEvent(event);
	std::cerr << "after process\n";
}

void AddWordScreen::internalProcess()
{
	std::string message;
	g_curr_trie->addWordAndDefiToTrie(getKeyword(), getDefinition());
}
