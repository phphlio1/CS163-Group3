#ifndef ADD_WORD_SCREEN_HPP
#define ADD_WORD_SCREEN_HPP

#include <SFML/Graphics.hpp>

#include "EditDefinition.hpp"
#include "Global.hpp"

namespace Frontend
{
	class AddWordScreen : public EditDefinition
	{
	public:
		AddWordScreen(int n_width = 950, int n_height = 650);

		virtual void processEvent(const sf::Event &event) override;

	protected:
		// virtual void updateTexture() override;
		virtual void internalProcess() override;
	};
}

#endif
