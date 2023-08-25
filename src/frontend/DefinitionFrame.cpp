#include <iostream>
#include <string>

#include "DefinitionFrame.hpp"
#include "TextBox.hpp"
#include "Trie.h"
#include "HistoryBar.hpp"
#include "EditDefinition.hpp"
#include "Global.hpp"

using namespace Frontend;

DefinitionFrame::DefinitionFrame(int n_width, int n_height)
	: Component(n_width, n_height),
	  history_bar_(nullptr), edit_screen_(nullptr),
	  definition_bar_height_(152), bottom_bar_height_(40),
	  bars_color_(17, 105, 142),
	  button_circle_(25),
	  edit_definition_button_(button_circle_.getRadius() * 2,
							  button_circle_.getRadius() * 2,
							  sf::Color::Transparent,
							  sf::Color(255, 255, 255, 160),
							  sf::Color(255, 255, 255, 200)),
	  add_to_favorites_button_(button_circle_.getRadius() * 2,
							   button_circle_.getRadius() * 2,
							   sf::Color::Transparent,
							   sf::Color(255, 255, 255, 160),
							   sf::Color(255, 255, 255, 200)),
	  definition_margin_(30),
	  type_color_(17, 105, 142), type_character_size_(30),
	  defi_character_size_(20), defi_defi_spacing_(10), defi_type_spacing_(20)
{
	edit_definition_button_.setContainer(static_cast<Component*>(this));
	add_to_favorites_button_.setContainer(static_cast<Component*>(this));
	
	int button_circle_width = button_circle_.getLocalBounds().width,
		button_circle_height = button_circle_.getLocalBounds().height;
	button_circle_.setOrigin(int(button_circle_width - 1) / 2,
							 int(button_circle_height - 1) / 2);
	button_circle_.setFillColor(sf::Color::Transparent);
	button_circle_.setOutlineThickness(-2);
	button_circle_.setOutlineColor(sf::Color::White);

	createEditDefinitionButton();
	createAddToFavoritesButton();

	setEditDefinitionPos(500, 70);
	setAddToFavoritesPos(405, 70);

	setPosition(330, 70);
	
	keyword_text_.setFont(getFont());
	setFont("resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf");
	setKeywordTextCharacterSize(35);
	setKeywordTextColor(sf::Color::White);
	setKeywordTextYPos(23);

	defi_pane_screen_.width = getWidth() - 2*getDefinitionMargin();
	defi_pane_screen_.height = getHeight() - getDefinitionBarHeight() - getBottomBarHeight() - 2*getDefiDefiSpacing();
}

void DefinitionFrame::processEvent(const sf::Event &event)
{
	auto is_inside = [&](int x, int y) -> bool
    {
		sf::FloatRect bounds_in_window = getSprite().getGlobalBounds();
		sf::Vector2f window_relative_pos = findWindowRelativePos();
		bounds_in_window.left = window_relative_pos.x;
		bounds_in_window.top = window_relative_pos.y;
		return bounds_in_window.contains(x, y);
    };

	edit_definition_button_.processEvent(event);
	add_to_favorites_button_.processEvent(event);

	if (event.type == sf::Event::MouseWheelScrolled
		&& is_inside(event.mouseWheelScroll.x, event.mouseWheelScroll.y))
	{
		defi_pane_screen_.top -= 3*event.mouseWheelScroll.delta;
	}

	if (edit_definition_button_.isPressed() && !editDefinitonIsPressed())
	{
		setVisibility(0);
		edit_screen_->setVisibility(1);
	}
	if (add_to_favorites_button_.isPressed() && !addToFavoritesIsPressed())
	{
		g_curr_trie->addToFavoriteList(getKeyword().toAnsiString(),
									   add_to_favorites_message_);
		std::string message;
		g_curr_trie->viewFavoriteList(g_favorites, message);
	}
	updateTexture();
	setEditDefinitionPressedState(edit_definition_button_.isPressed());
	setAddToFavoritesPressedState(add_to_favorites_button_.isPressed());
}

int DefinitionFrame::getKeywordTextCharacterSize() const
{
	return keyword_text_.getCharacterSize();
}

const sf::Color& DefinitionFrame::getKeywordTextColor() const
{
	return keyword_text_.getFillColor();
}

const sf::String& DefinitionFrame::getKeyword() const
{
	return keyword_text_.getString();
}

int DefinitionFrame::getKeywordTextYPos() const
{
	return keyword_text_.getPosition().y;
}

const sf::Font& DefinitionFrame::getFont() const
{
	return font_;
}

int DefinitionFrame::getDefinitionBarHeight() const
{
	return definition_bar_height_;
}

int DefinitionFrame::getBottomBarHeight() const
{
	return bottom_bar_height_;
}

const sf::Color& DefinitionFrame::getBarsColor() const
{
	return bars_color_;
}

int DefinitionFrame::getButtonRadius() const
{
	return button_circle_.getRadius();
}

int DefinitionFrame::getButtonOutlineThickness() const
{
	return button_circle_.getOutlineThickness();
}

const sf::Color& DefinitionFrame::getButtonOutlineColor() const
{
	return button_circle_.getOutlineColor();
}

const sf::Vector2f& DefinitionFrame::getEditDefinitionPos() const
{
	return edit_definition_button_.getPosition();
}

const sf::Vector2f& DefinitionFrame::getAddToFavoritesPos() const
{
	return add_to_favorites_button_.getPosition();
}

bool DefinitionFrame::editDefinitonIsPressed() const
{
	return edit_definition_is_pressed_;
}

bool DefinitionFrame::addToFavoritesIsPressed() const
{
	return add_to_favorites_is_pressed_;
}

int DefinitionFrame::getDefiDefiSpacing() const
{
	return defi_defi_spacing_;
}

int DefinitionFrame::getDefiTypeSpacing() const
{
	return defi_type_spacing_;
}

int DefinitionFrame::getDefinitionMargin() const
{
	return definition_margin_;
}

int DefinitionFrame::getTypeCharacterSize() const
{
	return type_character_size_;
}

int DefinitionFrame::getDefiCharacterSize() const
{
	return defi_character_size_;
}

const sf::Color& DefinitionFrame::getTypeColor() const
{
	return type_color_;
}

void DefinitionFrame::setKeywordTextCharacterSize(int n_size)
{
	keyword_text_.setCharacterSize(n_size);
	updateTexture();
}

void DefinitionFrame::setKeywordTextColor(const sf::Color &n_color)
{
	keyword_text_.setFillColor(n_color);
	updateTexture();
}

void DefinitionFrame::setKeyword(const sf::String &n_keyword)
{
	keyword_text_.setString(n_keyword);

	std::string message;
	g_curr_trie->addToHistory(getKeyword().toAnsiString(), message);
	g_curr_trie->takeHistory(g_history, message);
	if (history_bar_)
	{
		history_bar_->updateTexture();
	}
	
	definitions_.clear();
	std::vector<std::string> tmp_definitions;
	g_curr_trie->findWordInTrie(getKeyword().toAnsiString(), tmp_definitions);
	split_Definition(tmp_definitions, definitions_);
	
	setEditDefinitionPressedState(0);
	setAddToFavoritesPressedState(0);

	drawDefinitions();
	
	updateTexture();
}

void DefinitionFrame::setKeywordTextYPos(int n_y_pos)
{
	keyword_text_.setPosition(keyword_text_.getPosition().x, n_y_pos);
	updateTexture();
}

void DefinitionFrame::setFont(const sf::String &filename)
{
	font_.loadFromFile(filename);
	updateTexture();
}

void DefinitionFrame::setDefinitionBarHeight(int n_height)
{
	definition_bar_height_ = n_height;
	updateTexture();
}

void DefinitionFrame::setBottomBarHeight(int n_height)
{
	bottom_bar_height_ = n_height;
	updateTexture();
}

void DefinitionFrame::setBarsColor(const sf::Color &n_color)
{
	bars_color_ = n_color;
	updateTexture();
}

void DefinitionFrame::setButtonRadius(int n_radius)
{
	button_circle_.setRadius(n_radius);
	updateTexture();
}

void DefinitionFrame::setButtonOutlineThickness(int n_thickness)
{
	button_circle_.setOutlineThickness(n_thickness);
	updateTexture();
}

void DefinitionFrame::setButtonOutlineColor(const sf::Color &n_color)
{
	button_circle_.setOutlineColor(n_color);
	updateTexture();
}

void DefinitionFrame::setEditDefinitionPos(int x, int y)
{
	setEditDefinitionPos(sf::Vector2f(x, y));
}

void DefinitionFrame::setEditDefinitionPos(const sf::Vector2f &n_pos)
{
	edit_definition_button_.setPosition(n_pos);
	updateTexture();
}

void DefinitionFrame::setAddToFavoritesPos(int x, int y)
{
	setAddToFavoritesPos(sf::Vector2f(x, y));
}

void DefinitionFrame::setAddToFavoritesPos(const sf::Vector2f &n_pos)
{
	add_to_favorites_button_.setPosition(n_pos);
	updateTexture();
}

void DefinitionFrame::setDefiDefiSpacing(int n_spacing)
{
	defi_defi_spacing_ = n_spacing;
	drawDefinitions();
}

void DefinitionFrame::setDefiTypeSpacing(int n_spacing)
{
	defi_type_spacing_ = n_spacing;
	drawDefinitions();
}

void DefinitionFrame::setDefinitionMargin(int n_margin)
{
	definition_margin_ = n_margin;
	updateTexture();
}

void DefinitionFrame::setTypeCharacterSize(int n_size)
{
	type_character_size_ = n_size;
	drawDefinitions();
}

void DefinitionFrame::setDefiCharacterSize(int n_size)
{
	defi_character_size_ = n_size;
	drawDefinitions();
}

void DefinitionFrame::setTypeColor(const sf::Color &n_color)
{
	type_color_ = n_color;
	drawDefinitions();
}

void DefinitionFrame::setHistoryBar(HistoryBar *n_history_bar)
{
	history_bar_ = n_history_bar;
}

void DefinitionFrame::setEditScreen(EditDefinition *n_edit_screen)
{
	edit_screen_ = n_edit_screen;
}

void DefinitionFrame::updateTexture()
{
	texture_.clear(sf::Color::White);
	
	sf::RectangleShape definition_bar(sf::Vector2f(getWidth(), getDefinitionBarHeight()));
	definition_bar.setFillColor(getBarsColor());
	
	sf::RectangleShape bottom_bar(sf::Vector2f(getWidth(), getBottomBarHeight()));
	bottom_bar.setPosition(0, getHeight() - getBottomBarHeight());
	bottom_bar.setFillColor(getBarsColor());
	centerKeywordText();
	
	texture_.draw(definition_bar);
	texture_.draw(bottom_bar);
	texture_.draw(keyword_text_);
	texture_.draw(edit_definition_button_);
	texture_.draw(add_to_favorites_button_);

	if (add_to_favorites_button_.isPressed())
	{
		sf::Text output_text(add_to_favorites_message_, getFont(), 20);
		output_text.setFillColor(sf::Color::Green);
		sf::Vector2f output_text_pos = getAddToFavoritesPos();
		output_text_pos.x = (getWidth() - output_text.getGlobalBounds().width) / 2;
		output_text_pos.y += add_to_favorites_button_.getHeight();
		output_text.setPosition(output_text_pos);
		
		texture_.draw(output_text);
	}

	sf::Sprite definition_sprite(definition_pane_.getTexture());
	definition_sprite.setTextureRect(defi_pane_screen_);
	definition_sprite.setPosition(getDefinitionMargin(),
								  getDefinitionBarHeight() + getDefiDefiSpacing());
	texture_.draw(definition_sprite);

	texture_.display();
}

void DefinitionFrame::centerKeywordText()
{
	int keyword_text_width = keyword_text_.getLocalBounds().width;
	keyword_text_.setPosition((getWidth() - keyword_text_width) / 2,
							  getKeywordTextYPos());
}

void DefinitionFrame::createEditDefinitionButton()
{
	int button_width = edit_definition_button_.getWidth(),
		button_height = edit_definition_button_.getHeight();
	
	sf::Texture image;
	image.loadFromFile("resources/img/edit-definition.png");
	int image_width = image.getSize().x, image_height = image.getSize().y;
	
	sf::Sprite sprite(image);
	// center the image
	sprite.setOrigin((image_width - 1) / 2, (image_height - 1) / 2);
	sprite.setPosition((button_width - 1) / 2, (button_height - 1) / 2);

	button_circle_.setPosition(sprite.getPosition());

	edit_definition_texture_.create(button_width, button_height);
	edit_definition_texture_.clear(sf::Color::Transparent);
	edit_definition_texture_.draw(sprite);
	edit_definition_texture_.draw(button_circle_);
	edit_definition_texture_.display();

	edit_definition_button_.setTexture(edit_definition_texture_.getTexture(), 0, 0);
}

void DefinitionFrame::createAddToFavoritesButton()
{
	int button_width = add_to_favorites_button_.getWidth(),
		button_height = add_to_favorites_button_.getHeight();
	
	sf::Texture image;
	image.loadFromFile("resources/img/add-to-favorites.png");
	int image_width = image.getSize().x, image_height = image.getSize().y;
	
	sf::Sprite sprite(image);
	// center the image
	sprite.setOrigin((image_width - 1) / 2, (image_height - 1) / 2);
	sprite.setPosition((button_width - 1) / 2, (button_height - 1) / 2);

	button_circle_.setPosition(sprite.getPosition());

	add_to_favorites_texture_.create(button_width, button_height);
	add_to_favorites_texture_.clear(sf::Color::Transparent);
	add_to_favorites_texture_.draw(sprite);
	add_to_favorites_texture_.draw(button_circle_);
	add_to_favorites_texture_.display();

	add_to_favorites_button_.setTexture(add_to_favorites_texture_.getTexture(), 0, 0);
}

void DefinitionFrame::drawDefinitions()
{
	definition_pane_.create(getWidth() - getDefinitionMargin() * 2,
							250 * definitions_.size());
	definition_pane_.clear(sf::Color::White);

	TextBox type_text(definition_pane_.getSize().x, 45, 0);
	type_text.setContainer(this);
	type_text.setTypability(0);
	type_text.setWrappedEnabled(1);
	type_text.setFont(getFont());
	type_text.setCharacterSize(getTypeCharacterSize());
	type_text.setBackgroundColor(sf::Color::Transparent);
	type_text.setOutlineThickness(0);
	type_text.setForegroundTextColor(getTypeColor());
	
	TextBox defi_text(definition_pane_.getSize().x, 30, 0);
	defi_text.setContainer(this);
	defi_text.setTypability(0);
	defi_text.setWrappedEnabled(1);
	defi_text.setFont(getFont());
	defi_text.setCharacterSize(getDefiCharacterSize());
	defi_text.setBackgroundColor(sf::Color::Transparent);
	defi_text.setOutlineThickness(0);
	defi_text.setForegroundTextColor(sf::Color::Black);
	
	sf::Vector2f curr_pos(0, 0);
	for (int i = 0; i < definitions_.size(); ++i)
	{
		auto [type, definition] = definitions_[i];
		
		if (i == 0 || type != definitions_[i-1].first)
		{
			type_text.setForegroundString(type);
			type_text.setPosition(curr_pos);
			definition_pane_.draw(type_text);
			curr_pos.y += type_text.getHeight() + getDefiDefiSpacing();
		}
		sf::String defi_string = std::to_string(i+1) + "   : ";
		defi_string += definition;
		defi_text.setForegroundString(defi_string);
		defi_text.setPosition(curr_pos);
		definition_pane_.draw(defi_text);
		curr_pos.y += defi_text.getHeight();
		curr_pos.y += (i+1 < definitions_.size() && type != definitions_[i+1].first ?
					   getDefiTypeSpacing() : getDefiDefiSpacing());
	}

	definition_pane_.display();
	updateTexture();
}

void DefinitionFrame::setEditDefinitionPressedState(bool n_state)
{
	edit_definition_is_pressed_ = n_state;
	
	updateTexture();
}

void DefinitionFrame::setAddToFavoritesPressedState(bool n_state)
{
	add_to_favorites_is_pressed_ = n_state;
	updateTexture();
}
