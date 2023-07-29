#include "button.hpp"

// constructor for text-only buttons
Button::Button(float x, float y, float width, float height,
               sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    buttonType = BTN_TEXT_ONLY;
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
               sf::Texture *texture,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor)
{
    buttonType = BTN_TEXT_ONLY;
    buttonState = BTN_IDLE;

    this->shape.setPosition(sf::Vector2f(x, y));
    this->shape.setSize(sf::Vector2f(width, height));

    this->text.setFont(*font);
    this->text.setString(text);
    this->text.setCharacterSize(textSize);
    this->text.setPosition(sf::Vector2f(t_x, t_y));
    this->text.setFillColor(textColor);

    sf::IntRect intRect(x, y, width, height);
    this->sprite.setTexture(*texture);
    this->sprite.setTextureRect(intRect);

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
    target.draw(this->text, states);
    if (buttonState != BTN_TEXT_ONLY)
        target.draw(this->sprite, states);
}

void Button::update(const sf::Vector2f mousePos)
{
    this->buttonState = BTN_IDLE;

    // bool mouseInButton = mousePos.x >= this->shape.getPosition().x - this->shape.getGlobalBounds().width / 2 && mousePos.x <= this->shape.getPosition().x + this->shape.getGlobalBounds().width / 2 && mousePos.y >= this->shape.getPosition().y - this->shape.getGlobalBounds().height / 2 && mousePos.y <= this->shape.getPosition().y + this->shape.getGlobalBounds().height / 2;

    if (this->shape.getGlobalBounds().contains(mousePos))
    {
        this->buttonState = BTN_HOVER;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (buttonState)
    {
    case BTN_IDLE:
        this->shape.setFillColor(idleColor);
        break;
    case BTN_HOVER:
        this->shape.setFillColor(hoverColor);
        break;
    case BTN_ACTIVE:
        this->shape.setFillColor(activeColor);
        break;
    default: // should never happen
        this->shape.setFillColor(sf::Color::Red);
        break;
    }
}

const bool Button::isPressed() const
{
    return (buttonState == BTN_ACTIVE);
}
