#ifndef COMPONENT_H
#define COMPONENT_H

#include <SFML/Graphics.hpp>

namespace Frontend
{
	class Component : public sf::Drawable
	{
	public:
		Component();
		
		bool isVisible() const;
		void setVisibility(bool n_is_visible);
		virtual void processEvent(const sf::Event &event) = 0;

	protected:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override = 0;
		virtual void createTexture(int width, int height) = 0;
		virtual void updateTexture() = 0;
		
		bool is_visible_;
	};
}

#endif
