#include "button.hpp"

using namespace Frontend;

Button::Button(int width, int height, sf::Color idle, sf::Color hover, sf::Color active)
    : Component(width, height),
      idleColor(idle),
      hoverColor(hover),
      activeColor(active)
{
    shape.setPosition(0, 0);
    shape.setSize(sf::Vector2f(width, height));
    // shape.setFillColor(idleColor);
}

Button::~Button()
{
}

void Button::updateTexture()
{
    texture_.clear(sf::Color::White);
    texture_.draw(shape);
    texture_.draw(text);
    texture_.draw(sprite);
    texture_.display();
}

void Button::processEvent(const sf::Event &event)
{
    static bool pressed = false;
    auto is_inside = [=](int x, int y) -> bool
    {
        return getSprite().getGlobalBounds().contains(x, y);
    };

    setButtonInactive();

    if ((is_inside(event.mouseMove.x, event.mouseMove.y)))
    {
        setButtonHover();
    }
    if (is_inside(event.mouseButton.x, event.mouseButton.y) && event.type == sf::Event::MouseButtonPressed)
    {
        setButtonActive();
    }
}

const bool Button::isPressed() const
{
    return (buttonState == BTN_ACTIVE);
}

void Button::centerVertical()
{
    text.setPosition(text.getPosition().x, shape.getPosition().y + (shape.getSize().y - text.getLocalBounds().height) / 2);
    updateTexture();
}

const sf::String Button::getString()
{
    return text.getString();
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

void Button::setTexture(sf::Texture &texture, float texture_x, float texture_y)
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

void Button::setButtonActive()
{
    buttonState = BTN_ACTIVE;
    shape.setFillColor(activeColor);
    sprite.setColor(sf::Color(215, 215, 215));
    updateTexture();
}

void Button::setButtonInactive()
{
    buttonState = BTN_IDLE;
    shape.setFillColor(idleColor);
    sprite.setColor(sf::Color::White);
    updateTexture();
}

void Button::setButtonHover()
{
    buttonState = BTN_HOVER;
    shape.setFillColor(hoverColor);
    sprite.setColor(sf::Color(215, 215, 215));
    updateTexture();
}