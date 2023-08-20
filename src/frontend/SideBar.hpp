#ifndef SIDE_BAR_HPP
#define SIDE_BAR_HPP

#include <list>
#include <SFML/Graphics.hpp>

#include "Component.hpp"

namespace Frontend
{
	class SideBar : public Component
	{
	public:
		SideBar(int n_width = 330, int n_height = 650);
		
		virtual void processEvent(const sf::Event &event) override;

		const sf::Color& getBackgroundColor() const;
		int getWordBoxWidth() const;
		int getWordBoxHeight() const;
		const sf::Color& getWordBoxColor() const;
		const sf::Font& getWordFont() const;
		const sf::Vector2f& getFirstWordBoxPos() const;
		int getWordBoxSpacing() const;
		int getCharacterSize() const;
		const sf::String* getClickedWord() const;
		const sf::Vector2f& getEditFavoritesPos() const;
		int getCloseEditFavoritesThickness() const;
		int getCloseEditFavoritesSize() const;
		bool isFavoritesEditing() const;
		const sf::Vector2f& getRemoveFromFavoritesPos() const;

		void setBackgroundColor(const sf::Color &color);
		void setWordBoxWidth(int n_width);
		void setWordBoxHeight(int n_height);
		void setWordBoxColor(const sf::Color &n_color);
		void setWordFont(const sf::String &filename);
		void setFirstWordBoxPos(const sf::Vector2f &n_pos);
		void setWordBoxSpacing(int n_spacing);
		void setCharacterSize(int n_size);
		void setEditFavoritesPos(int x, int y);
		void setEditFavoritesPos(const sf::Vector2f &n_pos);
		void setCloseEditFavoritesThickness(int n_thickness);
		void setCloseEditFavoritesSize(int n_size);
		void setFavoritesEditingEnabled(bool n_is_fav_editing);
		void setRemoveFromFavoritesPos(int x, int y);
		void setRemoveFromFavoritesPos(const sf::Vector2f &n_pos);

		std::list<sf::String>& words();
		const std::list<sf::String>& words() const;

	protected:
		virtual void updateTexture() override;

	private:
		static const sf::Color GREY;
		static const int NUM_WORDS;

		const sf::String* findClickedWord(int mouseX, int mouseY) const;

		void initializeWords();
		void drawWordBox(const sf::String &word, int word_id);
		sf::Vector2f getWordBoxPosition(int word_id) const;
		void centerText(sf::Text &text) const;
		void createCloseEditFavoritesButton();
		void createAddToFavoritesButton();
		void createMainDiag(sf::VertexArray &main_diag);
		void createMinorDiag(sf::VertexArray &minor_diag);
		void drawAddToFavorites();

		std::list<sf::String> words_;
		int character_size_, word_box_spacing_;
		bool is_favorites_editing_;
		int close_edit_favorites_thickness_, close_edit_favorites_size_;
		sf::Vector2f first_word_box_pos_, edit_favorites_pos_, remove_from_favorites_pos_;
		sf::Color background_color_;
		sf::Font word_font_;
		sf::RectangleShape word_box_;
		sf::Texture edit_favorites_button_, remove_from_favorites_button_;
		sf::RenderTexture close_edit_favorites_button_, add_to_favorites_button_;

		const sf::String *clicked_word_;
	};
}

#endif
