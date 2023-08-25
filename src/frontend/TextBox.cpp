#include <iostream>
#include <cmath>

#include "TextBox.hpp"

using namespace Frontend;

const sf::Color TextBox::GREY = sf::Color(93, 93, 93);

TextBox::TextBox(int n_width, int n_height, int n_margin)
	: Component(n_width, n_height),
	  container_(nullptr),
	  margin_(n_margin), outline_thickness_(-2),
	  background_color_(sf::Color(245, 245, 245)), // nearly white
	  is_typing_(0), is_typable_(1), is_wrapped_(0)
{
	background_text_.setFont(getFont());
	foreground_text_.setFont(getFont());
	setFont("resources/font/font-awesome-5/Font-Awesome-5-Free-Regular-400.otf");
	setBackgroundTextColor(GREY); // grey
	setForegroundTextColor(sf::Color::Black);
	setCharacterSize(20);
	foreground_text_.setLineSpacing(1);

	setTypingOutlineColor(sf::Color::Green);
	setUntypingOutlineColor(sf::Color::Black);
	
	updateTexture();
}

void TextBox::processEvent(const sf::Event &event)
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
		if (isTypable())
		{
			setTypingEnabled(is_inside(event.mouseButton.x, event.mouseButton.y));
		}
		break;

	case sf::Event::TextEntered:
		if (isTyping())
		{
			updateText(event);
		}
		break;
		
	default:
		break;
	}
	updateTexture();
}

sf::Vector2f TextBox::findWindowRelativePos() const
{
	return getPosition() + (getContainer() ? getContainer()->findWindowRelativePos() :
							sf::Vector2f(0, 0));
}

const Component* TextBox::getContainer() const
{
	return container_;
}

int TextBox::getMargin() const
{
	return margin_;
}

int TextBox::getCharacterSize() const
{
	return foreground_text_.getCharacterSize();
}

int TextBox::getOutlineThickness() const
{
	return outline_thickness_;
}

const sf::String& TextBox::getBackgroundString() const
{
	return background_string_;
}

const sf::String& TextBox::getForegroundString() const
{
	return foreground_string_;
}

const sf::Font& TextBox::getFont() const
{
	return font_;
}

const sf::Color& TextBox::getBackgroundColor() const
{
	return background_color_;
}

const sf::Color& TextBox::getBackgroundTextColor() const
{
	return background_text_.getFillColor();
}

const sf::Color& TextBox::getForegroundTextColor() const
{
	return foreground_text_.getFillColor();
}

const sf::Color& TextBox::getTypingOutlineColor() const
{
	return typing_outline_color_;
}

const sf::Color& TextBox::getUntypingOutlineColor() const
{
	return untyping_outline_color_;
}

bool TextBox::isTyping() const
{
	return is_typing_;
}

bool TextBox::isWrapped() const
{
	return is_wrapped_;
}

bool TextBox::isTypable() const
{
	return is_typable_;
}

void TextBox::setContainer(const Component *n_container)
{
	container_ = n_container;
}

void TextBox::setMargin(int n_margin)
{
	margin_ = n_margin;
	updateTexture();
}

void TextBox::setCharacterSize(int size)
{
	foreground_text_.setCharacterSize(size);
	background_text_.setCharacterSize(size);
	updateTexture();
}

void TextBox::setOutlineThickness(int n_thickness)
{
	outline_thickness_ = n_thickness;
	updateTexture();
}

void TextBox::setBackgroundString(const sf::String &text)
{
	background_string_ = text;
	background_text_.setString(text);
	updateTexture();
}

void TextBox::setForegroundString(const sf::String &text)
{
	foreground_string_ = text;
	foreground_text_.setString(foreground_string_);
	updateTexture();
}

void TextBox::setFont(const sf::String &filename)
{
	font_.loadFromFile(filename.toAnsiString());
	updateTexture();
}

void TextBox::setFont(const sf::Font &n_font)
{
	font_ = n_font;
}

void TextBox::setBackgroundColor(const sf::Color &color)
{
	background_color_ = color;
	updateTexture();
}

void TextBox::setBackgroundTextColor(const sf::Color &color)
{
	background_text_.setFillColor(color);
	updateTexture();
}

void TextBox::setForegroundTextColor(const sf::Color &color)
{
	foreground_text_.setFillColor(color);
	updateTexture();
}

void TextBox::setTypingOutlineColor(const sf::Color &color)
{
	typing_outline_color_ = color;
	updateTexture();
}

void TextBox::setUntypingOutlineColor(const sf::Color &color)
{
	untyping_outline_color_ = color;
	updateTexture();
}

void TextBox::setTypingEnabled(bool n_is_typing)
{
	is_typing_ = n_is_typing;
	updateTexture();
}

void TextBox::setWrappedEnabled(bool n_is_wrapped)
{
	is_wrapped_ = n_is_wrapped;
	updateTexture();
}

void TextBox::setTypability(bool n_is_typable)
{
	is_typable_ = n_is_typable;
}

void TextBox::centerText(sf::Text &text_display)
{
	int text_height = text_display.getLocalBounds().height;
	text_display.setPosition(getMargin(), (getHeight() - text_height) / 2);
}

void TextBox::updateTexture()
{
	texture_.clear(getBackgroundColor());
	
	centerText(background_text_);
	if (isWrapped())
	{
		wrapText();
	}
	else
	{
		centerText(foreground_text_);
	}
	
	sf::RectangleShape outline(sf::Vector2f(getWidth(), getHeight()));
	outline.setFillColor(sf::Color::Transparent);
	outline.setOutlineColor(isTyping() ?
							getTypingOutlineColor() : getUntypingOutlineColor());
	outline.setOutlineThickness(getOutlineThickness());
	
	const sf::Text &text_display = (isTyping() || getForegroundString().getSize() ?
									foreground_text_ : background_text_);
	
	texture_.draw(outline);
	texture_.draw(text_display);
	
	texture_.display();
}

void TextBox::updateText(const sf::Event &event)
{
	if (!isTypable() || event.type != sf::Event::TextEntered)
	{
		return;
	}

	switch (event.text.unicode)
	{
	case '\b':
		if (getForegroundString().getSize() > 0)
		{
			setForegroundString(getForegroundString().substring(0, getForegroundString().getSize() - 1));
		}
		break;

	case '\n':
	case '\r':
		break;

	default:
		int character_width = getFont().getGlyph(event.text.unicode,
												 getCharacterSize(), 0).bounds.width;
		if (isWrapped() || foreground_text_.getLocalBounds().width
			+ character_width + foreground_text_.getLetterSpacing()
			<= getWidth() - 2*getMargin())
		{
			setForegroundString(getForegroundString() + event.text.unicode);
		}
		break;
	}
	updateTexture();
}

void TextBox::wrapText()
{
	sf::String tmp_string = foreground_string_;
	foreground_text_.setString(tmp_string);
	int curr_width = 0;
	int num_lines = 1;
	for (int i = 0; i < tmp_string.getSize(); ++i)
	{
		int character_width = getFont().getGlyph(tmp_string[i],
												 getCharacterSize(), 0).bounds.width;
		if (foreground_text_.findCharacterPos(i).x < getWidth() - 2*getMargin())
		{
			continue;
		}

		++num_lines;
		for (int j = i; j >= 0; --j)
		{
			if (tmp_string[j] != ' ')
			{
				continue;
			}
			
			tmp_string[j] = '\n';
			foreground_text_.setString(tmp_string);
			break;
		}
	}
	sf::FloatRect global_bounds = foreground_text_.getGlobalBounds();
	setHeight(std::ceil(global_bounds.height + 0.5f*getCharacterSize()));
	foreground_text_.setPosition(0, 0);
}
