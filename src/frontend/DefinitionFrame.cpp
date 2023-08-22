#include <iostream>

#include "DefinitionFrame.hpp"

using namespace Frontend;

DefinitionFrame::DefinitionFrame(int n_width, int n_height)
	: Component(n_width, n_height),
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
							   sf::Color(255, 255, 255, 200))
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
}

void DefinitionFrame::processEvent(const sf::Event &event)
{
	edit_definition_button_.processEvent(event);
	add_to_favorites_button_.processEvent(event);
	updateTexture();
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

std::vector<sf::String>& DefinitionFrame::definitions()
{
	return definitions_;
}

const std::vector<sf::String>& DefinitionFrame::definitions() const
{
	return definitions_;
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
	// for (const sf::String &definition : definitions())
	// {
	// 	drawDefinition(definition);
	// }

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

void DefinitionFrame::drawDefinition(const sf::String &definition)
{
	
}
