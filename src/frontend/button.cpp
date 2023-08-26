#include "button.hpp"

using namespace Frontend;

Button::Button(int width, int height, sf::Color idle, sf::Color hover, sf::Color active)
    : Component(width, height),
      idleColor(idle),
      hoverColor(hover),
      activeColor(active),
	  is_pressed_(0)
{
    shape.setPosition(0, 0);
    shape.setSize(sf::Vector2f(width, height));
	setButtonInactive();
}

Button::~Button()
{
}

void Button::updateTexture()
{
	switch (buttonState)
	{
	case BTN_IDLE:
		shape.setFillColor(idleColor);
		break;

	case BTN_HOVER:
		shape.setFillColor(hoverColor);
		break;

	case BTN_ACTIVE:
		shape.setFillColor(activeColor);
	}
	
    texture_.clear(sf::Color::Transparent);
	
	texture_.draw(shape);
    texture_.draw(text);
    texture_.draw(sprite);

    texture_.display();
}

void Button::processEvent(const sf::Event &event)
{
    static bool pressed = false;
    auto is_inside = [&](int x, int y) -> bool
    {
		sf::FloatRect bounds_in_window = getSprite().getGlobalBounds();
		sf::Vector2f window_relative_pos = findWindowRelativePos();
		bounds_in_window.left = window_relative_pos.x;
		bounds_in_window.top = window_relative_pos.y;
		return bounds_in_window.contains(x, y);
    };

	ButtonState state;
	switch (event.type)
	{
	case sf::Event::MouseButtonPressed:
		if (is_inside(event.mouseButton.x, event.mouseButton.y))
		{
			state = (event.mouseButton.button == sf::Mouse::Left ?
					 BTN_ACTIVE : BTN_HOVER);
		}
		else
		{
			state = BTN_IDLE;
		}
	    setPressedState(0);
		break;

	case sf::Event::MouseButtonReleased:
		if (is_inside(event.mouseButton.x, event.mouseButton.y))
		{
		    setPressedState(1);
			state = BTN_HOVER;
		}
		else
		{
		    setPressedState(0);
			state = BTN_IDLE;
		}
		break;

	case sf::Event::MouseMoved:
		if (is_inside(event.mouseMove.x, event.mouseMove.y))
		{
			state = (getButtonState() == BTN_ACTIVE ? BTN_ACTIVE : BTN_HOVER);
		}
		else
		{
			state = BTN_IDLE;
		}
		break;

	default:
		break;
	}
	setButtonState(state);
}

sf::Vector2f Button::findWindowRelativePos() const
{
	return getPosition() + getContainer()->findWindowRelativePos();
}

void Button::centerVertical()
{
    text.setPosition(text.getPosition().x, shape.getPosition().y + (shape.getSize().y - text.getLocalBounds().height) / 2);
    updateTexture();
}

bool Button::isPressed() const
{
    return is_pressed_;
}

ButtonState Button::getButtonState() const
{
	return buttonState;
}

const sf::String& Button::getString() const
{
    return text.getString();
}

const sf::Text& Button::getText() const
{
	return text;
}

const Component* Button::getContainer() const
{
	return container_;
}

void Button::wrapTextVertical()
{
    float rightMarginX = (shape.getPosition().x + shape.getLocalBounds().width) - (text.getPosition().x - shape.getPosition().x);
    if (text.getPosition().x + text.getLocalBounds().width <= rightMarginX)
        return;
    int closestSpaceIndex = 0;
    for (int i = 0; i < getString().getSize(); ++i)
    {
        if (text.getString()[i] == ' ')
            closestSpaceIndex = i;
        if (text.findCharacterPos(i).x > rightMarginX)
        {
            sf::String str;
            str += text.getString();
            str.insert(closestSpaceIndex, "\n");
            text.setString(str);
        }
    }
    updateTexture();
}

void Button::setText(sf::Font &font, std::string newText, int textSize, sf::Color textColor)
{
    text.setFont(font);
    text.setString(newText);
    text.setCharacterSize(textSize);
    text.setFillColor(textColor);
    updateTexture();
}

void Button::setTextString(const std::string &newStr)
{
    text.setString(newStr);
    updateTexture();
}

void Button::setTextPosition(const sf::Vector2f pos)
{
    text.setPosition(pos);
    updateTexture();
}

void Button::setTexture(const sf::Texture &texture, float texture_x, float texture_y)
{
    sprite.setTexture(texture);
    sprite.setPosition(texture_x, texture_y);
    updateTexture();
}

void Button::setColor(sf::Color idle, sf::Color hover, sf::Color active)
{
    idleColor = idle;
    hoverColor = hover;
    activeColor = active;
}

void Button::setPressedState(bool n_is_pressed)
{
	is_pressed_ = n_is_pressed;
}

void Button::setButtonState(ButtonState n_state)
{
	if (buttonState == n_state)
	{
		return;
	}
	
	buttonState = n_state;
	updateTexture();
}

void Button::setButtonActive()
{
	setButtonState(BTN_ACTIVE);
}

void Button::setButtonInactive()
{
	setButtonState(BTN_IDLE);
}

void Button::setButtonHover()
{
	setButtonState(BTN_HOVER);
}

void Button::setContainer(const Component *n_container)
{
	container_ = n_container;
}
