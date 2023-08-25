#ifndef HISTORY_BAR_HPP
#define HISTORY_BAR_HPP

#include <SFML/Graphics.hpp>

#include "SideBar.hpp"

namespace Frontend
{
	class DefinitionFrame;
	
	class HistoryBar : public SideBar
	{
	public:
		HistoryBar(int n_width = 330, int n_height = 650);
		
		virtual void processEvent(const sf::Event &event) override;

	protected:
		virtual void updateTexture() override;

		friend class DefinitionFrame;
	};
}

#endif
