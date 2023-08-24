#ifndef DEFINITION_FRAME_HPP
#define DEFINITION_FRAME_HPP

#include <vector>

#include "Component.hpp"
#include "button.hpp"

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
		bool editDefinitonIsPressed() const;
		bool addToFavoritesIsPressed() const;
		int getDefiDefiSpacing() const;
		int getDefiTypeSpacing() const;
		const sf::Vector2f& getFirstDefinitionPos() const;

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
		void setDefiDefiSpacing(int n_spacing);
		void setDefiTypeSpacing(int n_spacing);
		void setFirstDefinitionPos(int x, int y);
		void setFirstDefinitionPos(const sf::Vector2f &n_pos);
		
	protected:
		virtual void updateTexture() override;

	private:
		void centerKeywordText();
		void createEditDefinitionButton();
		void createAddToFavoritesButton();

		void setEditDefinitionPressedState(bool n_state);
		void setAddToFavoritesPressedState(bool n_state);

		// void drawDefinitions();

		std::vector<std::pair<std::string, std::string>> definitions_;
		
		int definition_bar_height_, bottom_bar_height_;
		sf::Color bars_color_;
		sf::Font font_;
		sf::Text keyword_text_;
		sf::CircleShape button_circle_;
		sf::RenderTexture edit_definition_texture_, add_to_favorites_texture_;

		bool edit_definition_is_pressed_, add_to_favorites_is_pressed_;
		Button edit_definition_button_, add_to_favorites_button_;

		sf::RenderTexture definition_pane_;
		sf::Vector2f first_definition_pos_;
		int defi_defi_spacing_, defi_type_spacing_;
	};
}

#endif
