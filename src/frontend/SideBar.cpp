#include <iostream>

#include "SideBar.hpp"

using namespace Frontend;

const sf::Color SideBar::GREY = sf::Color(237, 237, 237);
const int SideBar::NUM_WORDS = 10;

SideBar::SideBar(int n_width, int n_height)
	: Component(n_width, n_height),
	  background_color_(GREY), character_size_(22),
	  word_box_spacing_(10), first_word_box_pos_(15, 41)
{
	sprite_.setPosition(0, 74);

	initializeWords();

	setWordBoxWidth(300);
	setWordBoxHeight(50);
	setWordBoxColor(sf::Color::White);
	setWordFont("../resources/JetBrainsMonoNL-Regular.ttf");
}

void SideBar::processEvent(const sf::Event &event)
{
	bool is_left_mouse_clicked = 0;
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		is_left_mouse_clicked = (event.mouseButton.button == sf::Mouse::Left);
		break;

	default:
		break;
	}

	int mouseX = event.mouseButton.x, mouseY = event.mouseButton.y;
	sf::FloatRect global_bounds = getSprite().getGlobalBounds();
	if (is_left_mouse_clicked
		&& global_bounds.contains(mouseX, mouseY))
	{
		setClickedWord(findClickedWord(mouseX, mouseY));
	}
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

const sf::String& SideBar::getClickedWord() const
{
	return clicked_word_;
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

std::list<sf::String>& SideBar::words()
{
	return words_;
}

const std::list<sf::String>& SideBar::words() const
{
	return words_;
}

void SideBar::updateTexture()
{
	texture_.clear(background_color_);

	int word_id = 0;
	for (const sf::String &word : words())
	{
		drawWordBox(word, word_id++);
	}

	texture_.display();
}

void SideBar::setClickedWord(const sf::String &n_word)
{
	clicked_word_ = n_word;
}

sf::String SideBar::findClickedWord(int mouseX, int mouseY) const
{
	mouseX -= getSprite().getPosition().x;
	mouseY -= getSprite().getPosition().y;
	for (int i = 0; i < NUM_WORDS; ++i)
	{
		sf::FloatRect word_box_bounds(getWordBoxPosition(i),
									sf::Vector2f(getWordBoxWidth(), getWordBoxHeight()));
		if (word_box_bounds.contains(mouseX, mouseY))
		{
			return *std::next(words().begin(), i);
		}
	}
	return "";
}

void SideBar::initializeWords()
{
	sf::String tmp;
	for (int i = 0; i < NUM_WORDS; ++i)
	{
		words().push_back(tmp += char('a' + i));
	}
}

void SideBar::drawWordBox(const sf::String &word, int word_id)
{
    word_box_.setPosition(getWordBoxPosition(word_id));
	
	sf::Text word_text(word, getWordFont(), getCharacterSize());
	word_text.setStyle(sf::Text::Bold);
	word_text.setFillColor(sf::Color::Black);
	centerText(word_text);
	
	texture_.draw(word_box_);
	texture_.draw(word_text);
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
