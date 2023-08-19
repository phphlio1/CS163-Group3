#include "button.hpp"

Button::Button()
{
}
// constructor for text-only buttons
Button::Button(float x, float y, float width, float height,
               sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setCharacterSize(textSize);
    this->text.setPosition(sf::Vector2f(t_x, t_y));
    this->text.setFillColor(textColor);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::Button(float x, float y, float width, float height,
               sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
               sf::Texture &texture, float texture_x, float texture_y,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setCharacterSize(textSize);
    this->text.setPosition(sf::Vector2f(t_x, t_y));
    this->text.setFillColor(textColor);

    this->sprite.setTexture(texture);
    this->sprite.setPosition(texture_x, texture_y);

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->shape.setFillColor(this->idleColor);
}

Button::~Button()
{
}

void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(this->shape, states);

    target.draw(this->sprite, states);

    target.draw(this->text, states);
}

void Button::update(const sf::Event &event, sf::Vector2f mousePosRelativeToWindow)
{
    this->buttonState = BTN_IDLE;
    if (this->shape.getGlobalBounds().contains(mousePosRelativeToWindow))
    {
        this->buttonState = BTN_HOVER;
        if (event.type == sf::Event::MouseButtonPressed)
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(idleColor);
        // this->sprite.setColor(idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(hoverColor);
        // this->sprite.setColor(hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(activeColor);
        // this->sprite.setColor(activeColor);
        break;
    default: // should never happen
        this->shape.setFillColor(sf::Color::Red);
        this->sprite.setColor(sf::Color::Red);
        break;
    }
}

const bool Button::isPressed() const
{
    return (buttonState == BTN_ACTIVE);
}

void Button::centerVertical()
{
    text.setPosition(text.getPosition().x, shape.getPosition().y + (shape.getSize().y - text.getLocalBounds().height) / 2);
}

sf::String Button::getString()
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
}

void Button::setText(std::string newText)
{
    text.setString(newText);
}

void Button::setTextPosition(const sf::Vector2f pos)
{
    text.setPosition(pos);
}