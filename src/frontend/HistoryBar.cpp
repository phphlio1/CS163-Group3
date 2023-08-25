#include "Global.hpp"
#include "HistoryBar.hpp"

using namespace Frontend;

HistoryBar::HistoryBar(int n_width, int n_height)
	: SideBar(n_width, n_height)
{
	words_ = &g_history;
	
	updateTexture();
}

void HistoryBar::processEvent(const sf::Event &event)
{
	SideBar::processEvent(event);
}

void HistoryBar::updateTexture()
{
	texture_.clear(getBackgroundColor());
	drawWordBoxes();
	texture_.display();
}
