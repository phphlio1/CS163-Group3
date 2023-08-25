#ifndef TEXT_BOX_HPP
#define TEXT_BOX_HPP

#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace Frontend
{
	class TextBox : public Component
	{
	public:
		TextBox(int n_width = 475, int n_height = 40, int n_margin = 50);
		
		virtual void processEvent(const sf::Event &event) override;
		virtual sf::Vector2f findWindowRelativePos() const override;
		
		const Component* getContainer() const;
		int getMargin() const;
		int getCharacterSize() const;
		int getOutlineThickness() const;
		const sf::String& getBackgroundString() const;
		const sf::String& getForegroundString() const;
		const sf::Font& getFont() const;
		const sf::Color& getBackgroundColor() const;
		const sf::Color& getBackgroundTextColor() const;
		const sf::Color& getForegroundTextColor() const;
		const sf::Color& getTypingOutlineColor() const;
		const sf::Color& getUntypingOutlineColor() const;
		bool isTyping() const;
		bool isWrapped() const;
		bool isTypable() const;
		
		void setContainer(const Component *n_container);
		void setMargin(int n_margin);
		void setCharacterSize(int size);
		void setOutlineThickness(int n_thickness);
		void setBackgroundString(const sf::String &text);
		void setForegroundString(const sf::String &text);
		void setFont(const sf::String &filename);
		void setFont(const sf::Font &n_font);
		void setBackgroundColor(const sf::Color &color);
		void setBackgroundTextColor(const sf::Color &color);
		void setForegroundTextColor(const sf::Color &color);
		void setTypingOutlineColor(const sf::Color &color);
		void setUntypingOutlineColor(const sf::Color &color);
		void setTypingEnabled(bool n_is_typing);
		void setWrappedEnabled(bool n_is_wrapped);
		void setTypability(bool n_is_typable);

	protected:
		virtual void updateTexture() override;
		
	private:
		static const sf::Color GREY;
		
		void centerText(sf::Text &text_display);
		void updateText(const sf::Event &event);
		void wrapText();

		int width_, height_, margin_, outline_thickness_;
		sf::Font font_;
		sf::Color background_color_, typing_outline_color_, untyping_outline_color_;
		sf::String background_string_, foreground_string_;
		sf::Text background_text_, foreground_text_;
		bool is_typing_, is_wrapped_, is_typable_;

		const Component *container_;
	};
}

#endif
