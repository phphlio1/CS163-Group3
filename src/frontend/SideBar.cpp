#include <iostream>
#include <algorithm>

#include "SideBar.hpp"
#include "DefinitionFrame.hpp"
#include "Global.hpp"

using namespace Frontend;

const sf::Color SideBar::GREY = sf::Color(237, 237, 237);
const int SideBar::NUM_WORDS = 10;

SideBar::SideBar(int n_width, int n_height)
	: Component(n_width, n_height),
	  definition_frame_(nullptr),
	  background_color_(GREY), character_size_(22),
	  word_box_spacing_(10), first_word_box_pos_(15, 45),
	  edit_favorites_pos_(290, 13),
	  close_edit_favorites_thickness_(5), close_edit_favorites_size_(25),
	  is_favorites_editing_(0)
{
	words_ = &g_favorites;
	
	setWordBoxWidth(300);
	setWordBoxHeight(50);
	setWordBoxColor(sf::Color::White);
	setWordFont("resources/font/Frank_Ruhl_Libre_font/FrankRuhlLibre-Medium.ttf");

	edit_favorites_button_.loadFromFile("resources/img/edit-favorites.png");
	remove_from_favorites_button_.loadFromFile("resources/img/trash-bin.png");
	createCloseEditFavoritesButton();
	createAddToFavoritesButton();
    setRemoveFromFavoritesPos(getWordBoxWidth() - 10 - remove_from_favorites_button_.getSize().x,
							  (getWordBoxHeight() - remove_from_favorites_button_.getSize().y) / 2);

	edit_favorites_sprite_.setTexture(edit_favorites_button_);
	close_edit_favorites_sprite_.setTexture(close_edit_favorites_button_.getTexture());
	edit_favorites_sprite_.setPosition(getEditFavoritesPos());
	close_edit_favorites_sprite_.setPosition(getEditFavoritesPos());
	
	updateTexture();
}

void SideBar::processEvent(const sf::Event &event)
{
    auto is_inside = [&](int x, int y) -> bool
    {
		sf::FloatRect bounds_in_window = getSprite().getGlobalBounds();
		sf::Vector2f window_relative_pos = findWindowRelativePos();
		bounds_in_window.left = window_relative_pos.x;
		bounds_in_window.top = window_relative_pos.y;
		return bounds_in_window.contains(x, y);
    };
	
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (!is_inside(event.mouseButton.x, event.mouseButton.y))
		{
			break;
		}

		{
			int mouseX = event.mouseButton.x - getPosition().x;
			int mouseY = event.mouseButton.y - getPosition().y;
			if (isFavoritesEditing())
			{
				if (close_edit_favorites_sprite_.getGlobalBounds().contains(mouseX, mouseY))
				{
					setFavoritesEditingEnabled(0);
				}
			}
			else if (edit_favorites_sprite_.getGlobalBounds().contains(mouseX, mouseY))
			{
				setFavoritesEditingEnabled(1);
			}
		}
		
		clicked_word_ = findClickedWord(event.mouseButton.x, event.mouseButton.y);
		if (!is_favorites_editing_ && definition_frame_ && getClickedWord() != -1)
		{
			definition_frame_->setKeyword((*words_)[words_->size() - getClickedWord() - 1]);
		}

		if (isFavoritesEditing() && getClickedWord() != -1)
		{
			std::string message;
			g_curr_trie->removeAWordFromFavoriteList(g_favorites.size() - getClickedWord(), message);
			g_curr_trie->viewFavoriteList(g_favorites, message);
		}
		break;

	default:
		break;
	}
	
	updateTexture();
}

const sf::Color& SideBar::getBackgroundColor() const
{
	return background_color_;
}

int SideBar::getWordBoxWidth() const
{
	return word_box_.getSize().x;
}

int SideBar::getWordBoxHeight() const
{
	return word_box_.getSize().y;
}

const sf::Color& SideBar::getWordBoxColor() const
{
	return word_box_.getFillColor();
}

const sf::Font& SideBar::getWordFont() const
{
	return word_font_;
}

const sf::Vector2f& SideBar::getFirstWordBoxPos() const
{
	return first_word_box_pos_;
}

int SideBar::getWordBoxSpacing() const
{
	return word_box_spacing_;
}

int SideBar::getCharacterSize() const
{
	return character_size_;
}

int SideBar::getClickedWord() const
{
	return clicked_word_;
}

const sf::Vector2f& SideBar::getEditFavoritesPos() const
{
	return edit_favorites_pos_;
}

int SideBar::getCloseEditFavoritesThickness() const
{
	return close_edit_favorites_thickness_;
}

int SideBar::getCloseEditFavoritesSize() const
{
	return close_edit_favorites_size_;
}

bool SideBar::isFavoritesEditing() const
{
	return is_favorites_editing_;
}

const sf::Vector2f& SideBar::getRemoveFromFavoritesPos() const
{
	return remove_from_favorites_pos_;
}

void SideBar::setBackgroundColor(const sf::Color &n_color)
{
	word_box_.setFillColor(n_color);
	updateTexture();
}

void SideBar::setWordBoxWidth(int n_width)
{
	word_box_.setSize(sf::Vector2f(n_width, getWordBoxHeight()));
	updateTexture();
}

void SideBar::setWordBoxHeight(int n_height)
{
	word_box_.setSize(sf::Vector2f(getWordBoxWidth(), n_height));
	updateTexture();
}

void SideBar::setWordBoxColor(const sf::Color &n_color)
{
	word_box_.setFillColor(n_color);
	updateTexture();
}

void SideBar::setWordFont(const sf::String &filename)
{
	word_font_.loadFromFile(filename);
	updateTexture();
}

void SideBar::setFirstWordBoxPos(const sf::Vector2f &n_pos)
{
	first_word_box_pos_ = n_pos;
	updateTexture();
}

void SideBar::setWordBoxSpacing(int n_spacing)
{
	word_box_spacing_ = n_spacing;
	updateTexture();
}

void SideBar::setCharacterSize(int n_size)
{
	character_size_ = n_size;
	updateTexture();
}

void SideBar::setEditFavoritesPos(int x, int y)
{
	setEditFavoritesPos(x, y);
}

void SideBar::setEditFavoritesPos(const sf::Vector2f &n_pos)
{
	edit_favorites_pos_ = n_pos;
	updateTexture();
}

void SideBar::setCloseEditFavoritesThickness(int n_thickness)
{
	close_edit_favorites_thickness_ = n_thickness;
	updateTexture();
}

void SideBar::setCloseEditFavoritesSize(int n_size)
{
	close_edit_favorites_size_ = n_size;
}

void SideBar::setFavoritesEditingEnabled(bool n_is_fav_editing)
{
	is_favorites_editing_ = n_is_fav_editing;
	updateTexture();
}

void SideBar::setRemoveFromFavoritesPos(int x, int y)
{
	setRemoveFromFavoritesPos(sf::Vector2f(x, y));
}

void SideBar::setRemoveFromFavoritesPos(const sf::Vector2f &n_pos)
{
	remove_from_favorites_pos_ = n_pos;
	updateTexture();
}

void SideBar::setDefinitionFrame(DefinitionFrame *n_definition_frame)
{
	definition_frame_ = n_definition_frame;
}

void SideBar::updateTexture()
{
	texture_.clear(background_color_);

	drawWordBoxes();
	
	sf::Sprite top_right;
	top_right.setPosition(getEditFavoritesPos());
	if (isFavoritesEditing())
	{
		// top_right.setTexture(close_edit_favorites_button_.getTexture());
		texture_.draw(close_edit_favorites_sprite_);
	}
	else
	{
		// top_right.setTexture(edit_favorites_button_);
		texture_.draw(edit_favorites_sprite_);
	}
	// texture_.draw(top_right);

	texture_.display();
}

int SideBar::findClickedWord(int mouseX, int mouseY) const
{
	sf::Vector2f window_relative_pos = findWindowRelativePos();
	mouseX -= window_relative_pos.x;
	mouseY -= window_relative_pos.y;
	for (int i = 0; i < std::min(int(words_->size()), NUM_WORDS); ++i)
	{
		sf::FloatRect word_box_bounds(getWordBoxPosition(i),
									  sf::Vector2f(getWordBoxWidth(), getWordBoxHeight()));
		if (word_box_bounds.contains(mouseX, mouseY))
		{
			return i;
		}
	}
	return -1;
}

void SideBar::drawWordBoxes()
{
	int word_id = 0;
	std::for_each(words_->rbegin(),
				  std::next(words_->rbegin(), std::min(int(words_->size()), NUM_WORDS)),
				  [&](const std::string &word)
				  {
					  drawWordBox(word, word_id++);
				  });
}

void SideBar::drawWordBox(const sf::String &word, int word_id)
{
    word_box_.setPosition(getWordBoxPosition(word_id));
	
	sf::Text word_text(word, getWordFont(), getCharacterSize());
	word_text.setFillColor(sf::Color::Black);
	centerText(word_text);
	
	texture_.draw(word_box_);
	texture_.draw(word_text);

	if (isFavoritesEditing())
	{
		sf::Sprite remove_from_favorites_sprite(remove_from_favorites_button_);
		remove_from_favorites_sprite.setPosition(word_box_.getPosition() + getRemoveFromFavoritesPos());
		texture_.draw(remove_from_favorites_sprite);
	}
}

sf::Vector2f SideBar::getWordBoxPosition(int word_id) const
{
	return getFirstWordBoxPos()
		+ sf::Vector2f(0.f,
					   1.f * word_id * (getWordBoxSpacing() + getWordBoxHeight()));
}

void SideBar::centerText(sf::Text &text) const
{
	text.setPosition(23, word_box_.getPosition().y
					 + (getWordBoxHeight() - getCharacterSize()) / 2);
}

void SideBar::createCloseEditFavoritesButton()
{
	sf::VertexArray main_diag(sf::TriangleStrip, 4);
	createMainDiag(main_diag);

	sf::VertexArray minor_diag(sf::TriangleStrip, 4);
	createMinorDiag(minor_diag);

	for (int i = 0; i < 4; ++i)
	{
		main_diag[i].color = minor_diag[i].color = sf::Color(25, 69, 107);
	}

	sf::RenderTexture &button = close_edit_favorites_button_;
	button.create(getCloseEditFavoritesSize(), getCloseEditFavoritesSize());
	button.clear(sf::Color::Transparent);
	button.draw(main_diag);
	button.draw(minor_diag);
	button.display();
}

void SideBar::createMainDiag(sf::VertexArray &main_diag)
{
	main_diag[0].position = sf::Vector2f(getCloseEditFavoritesThickness() - 1, 0);
	main_diag[1].position = sf::Vector2f(0, getCloseEditFavoritesThickness() - 1);
	main_diag[2].position = sf::Vector2f(getCloseEditFavoritesSize() - 1,
										 getCloseEditFavoritesSize() - getCloseEditFavoritesThickness());
	main_diag[3].position = sf::Vector2f(getCloseEditFavoritesSize() - getCloseEditFavoritesThickness(),
										 getCloseEditFavoritesSize() - 1);
}

void SideBar::createMinorDiag(sf::VertexArray &minor_diag)
{
	minor_diag[0].position = sf::Vector2f(getCloseEditFavoritesSize() - getCloseEditFavoritesThickness(), 0);
	minor_diag[1].position = sf::Vector2f(getCloseEditFavoritesSize() - 1,
										  getCloseEditFavoritesThickness() - 1);
	minor_diag[2].position = sf::Vector2f(0, getCloseEditFavoritesSize() - getCloseEditFavoritesThickness());
	minor_diag[3].position = sf::Vector2f(getCloseEditFavoritesThickness() - 1,
										  getCloseEditFavoritesSize() - 1);
}

void SideBar::createAddToFavoritesButton()
{
	sf::RectangleShape line(sf::Vector2f(getCloseEditFavoritesThickness(),
										 getCloseEditFavoritesSize()));
	line.setFillColor(sf::Color(25, 69, 107));
	
	sf::RenderTexture &button = add_to_favorites_button_;
	button.create(getCloseEditFavoritesSize(), getCloseEditFavoritesSize());
	button.clear(sf::Color::Transparent);
	
	// draw vertical
	line.setPosition((button.getSize().x - line.getSize().x) / 2, 0);
	button.draw(line);

	// draw horizontal
	line.setOrigin(line.getSize().x - 1, 0);
	line.setRotation(270);
	line.setPosition(0, (button.getSize().y - line.getSize().x) / 2);
	button.draw(line);

	button.display();
}

// void SideBar::drawAddToFavorites()
// {
// 	sf::Sprite add_to_favorites_sprite(add_to_favorites_button_.getTexture());
// 	sf::Vector2f add_to_favorites_pos = getEditFavoritesPos();
// 	add_to_favorites_pos.x = getWidth() - getEditFavoritesPos().x - edit_favorites_button_.getSize().x;
// 	add_to_favorites_sprite.setPosition(add_to_favorites_pos);
// 	texture_.draw(add_to_favorites_sprite);	
// }
