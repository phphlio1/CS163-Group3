#ifndef DEFINITION_FRAME_HPP
#define DEFINITION_FRAME_HPP

#include <vector>

#include "Component.hpp"

namespace Frontend
{
	class DefinitionFrame : public Component
	{
	public:
		DefinitionFrame(int n_width = 950, int n_height = 650);
		
		virtual void processEvent(const sf::Event &event) override;
		int getKeywordTextCharacterSize() const;
		const sf::Color& getKeywordTextColor() const;
		const sf::String& getKeyword() const;
		int getKeywordTextYPos() const;
		const sf::Font& getFont() const;
		int getDefinitionBarHeight() const;
		int getBottomBarHeight() const;
		const sf::Color& getBarsColor() const;
		int getButtonRadius() const;
		int getButtonOutlineThickness() const;
		const sf::Color& getButtonOutlineColor() const;
		const sf::Vector2f& getEditDefinitionPos() const;
		const sf::Vector2f& getAddToFavoritesPos() const;

		void setKeywordTextCharacterSize(int n_size);
		void setKeywordTextColor(const sf::Color &n_color);
		void setKeyword(const sf::String &n_keyword);
		void setKeywordTextYPos(int n_y_pos);
		void setFont(const sf::String &filename);
		void setDefinitionBarHeight(int n_height);
		void setBottomBarHeight(int n_height);
		void setBarsColor(const sf::Color &n_color);
		void setButtonRadius(int n_radius);
		void setButtonOutlineThickness(int n_thickness);
		void setButtonOutlineColor(const sf::Color &n_color);
		void setEditDefinitionPos(int x, int y);
		void setEditDefinitionPos(const sf::Vector2f &n_pos);
		void setAddToFavoritesPos(int x, int y);
		void setAddToFavoritesPos(const sf::Vector2f &n_pos);

		std::vector<sf::String>& definitions();
		const std::vector<sf::String>& definitions() const;

	protected:
		virtual void updateTexture() override;

	private:
		void centerKeywordText();
		void drawButton(const sf::Texture &button_texture, const sf::Vector2f &position);
		void drawDefinition(const sf::String &definition);
		
		int definition_bar_height_, bottom_bar_height_;

		sf::Color bars_color_;
		sf::Font font_;
		sf::Text keyword_text_;
		sf::Vector2f edit_definition_pos_, add_to_favorites_pos_;
		sf::CircleShape button_circle_;
		sf::Texture edit_definition_button_, add_to_favorites_button_;
		std::vector<sf::String> definitions_;
	};
}

#endif
