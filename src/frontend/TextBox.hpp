#ifndef TEXT_BOX_H
#define TEXT_BOX_H

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace Frontend
{
	class TextBox : public Component
	{
	public:
		TextBox(int n_width = 0, int n_height = 0, int n_margin = 10);
		
		virtual void processEvent(const sf::Event &event) override;
		
		int getWidth() const;
		int getHeight() const;
		int getMargin() const;
		int getCharacterSize() const;
		const sf::String& getBackgroundString() const;
		const sf::String& getForegroundString() const;
		const sf::Font& getFont() const;
		const sf::Color& getBackgroundColor() const;
		const sf::Color& getBackgroundTextColor() const;
		const sf::Color& getForegroundTextColor() const;
		const sf::Color& getTypingOutlineColor() const;
		const sf::Color& getUntypingOutlineColor() const;
		bool isTyping() const;
		
		void setWidth(int n_width);
		void setHeight(int n_height);
		void setMargin(int n_margin);
		void setCharacterSize(int size);
		void setBackgroundString(const sf::String &text);
		void setForegroundString(const sf::String &text);
		void setFont(const sf::String &filename);
		void setBackgroundColor(const sf::Color &color);
		void setBackgroundTextColor(const sf::Color &color);
		void setForegroundTextColor(const sf::Color &color);
		void setTypingOutlineColor(const sf::Color &color);
		void setUntypingOutlineColor(const sf::Color &color);
		void setTypingEnabled(bool n_is_typing);

	protected:
		virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
		virtual void createTexture(int width, int height) override;
		virtual void updateTexture() override;
		
	private:
		static const int OUTLINE_THICKNESS = -2; // inward outline is negative
		
		void updateText(const sf::Event &event);
		void centerText(sf::Text &text_display);
		
		const sf::RenderTexture& getTexture() const;
		const sf::Sprite& getSprite() const;
		
		int width_, height_, margin_;
		sf::Font font_;
		sf::Color background_color_, typing_outline_color_, untyping_outline_color_;
		sf::Text background_text_, foreground_text_;
		bool is_typing_;

		sf::RenderTexture texture_;
		sf::Sprite sprite_;
	};
}

#endif
