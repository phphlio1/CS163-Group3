#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

enum TypesOfButton
{
    BTN_TEXT_ONLY,
    BTN_BOTH
};

enum ButtonState
{
    BTN_IDLE,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button : public sf::Drawable
{
private:
    short unsigned buttonType;
    short unsigned buttonState;
    sf::Text text;
    sf::Sprite sprite;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    sf::RectangleShape shape;
    // text-only buttons
    Button(float x, float y, float width, float height,
           sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    // text and sprite buttons
    Button(float x, float y, float width, float height,
           sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
           sf::Texture *texture,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    ~Button();

    // accessors
    const bool isPressed() const;

    // functions
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(const sf::Vector2f mousePos);
};

#endif