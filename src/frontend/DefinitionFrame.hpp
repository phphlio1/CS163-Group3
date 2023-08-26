#ifndef DEFINITION_FRAME_HPP
#define DEFINITION_FRAME_HPP

#include <vector>

#include "Component.hpp"
#include "button.hpp"

namespace Frontend
{
	class HistoryBar;
	class EditDefinition;
	class AddWordScreen;
	
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
		int getTypeCharacterSize() const;
		const sf::Color& getTypeColor() const;
		int getDefiDefiSpacing() const;
		int getDefiTypeSpacing() const;
		int getDefinitionMargin() const;
		int getDefiCharacterSize() const;

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
		void setTypeCharacterSize(int n_size);
		void setTypeColor(const sf::Color &n_color);
		void setDefiDefiSpacing(int n_spacing);
		void setDefiTypeSpacing(int n_spacing);
		void setDefinitionMargin(int n_margin);
		void setDefiCharacterSize(int n_size);

		void setHistoryBar(HistoryBar *n_history_bar);
		void setEditScreen(EditDefinition *n_edit_screen);

		void setSubDefi(const std::string &sub_defi);
		
	protected:
		virtual void updateTexture() override;

	private:
		void centerKeywordText();
		void createEditDefinitionButton();
		void createAddToFavoritesButton();

		void setEditDefinitionPressedState(bool n_state);
		void setAddToFavoritesPressedState(bool n_state);

		void drawDefinitions();

		std::vector<std::pair<std::string, std::string>> definitions_;
		std::vector<std::string> words_;
		
		HistoryBar *history_bar_;
		EditDefinition *edit_screen_;
		AddWordScreen *add_word_screen_;
		
		int definition_bar_height_, bottom_bar_height_;
		sf::Color bars_color_;
		sf::Font font_;
		sf::Text keyword_text_;
		sf::CircleShape button_circle_;
		sf::RenderTexture edit_definition_texture_, add_to_favorites_texture_;

		bool edit_definition_is_pressed_, add_to_favorites_is_pressed_;
		Button edit_definition_button_, add_to_favorites_button_;
		std::string add_to_favorites_message_;

		sf::RenderTexture definition_pane_;
		sf::IntRect defi_pane_screen_;
		sf::Color type_color_;
		int defi_defi_spacing_, defi_type_spacing_, definition_margin_;
		int type_character_size_, defi_character_size_;

		Button add_word_button_, remove_word_button_;
		sf::Texture remove_word_texture_, add_word_texture_;
		bool add_word_pressed_, remove_word_pressed_;

		friend class EditDefinition;
	};
}

#endif
