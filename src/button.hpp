#ifndef BUTTON_HPP
#define BUTTON_HPP
#include <SFML/Graphics.hpp>
#include <iostream>

enum ButtonState
{
    BTN_IDLE,
    BTN_HOVER,
    BTN_ACTIVE
};

class Button : public sf::Drawable
{
private:
    short unsigned buttonState;
    sf::Text text;
    sf::Sprite sprite;
    sf::RectangleShape shape;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

public:
    const sf::Texture *getTexturePack() { return sprite.getTexture(); }
    sf::Sprite getSprite() { return sprite; }
    Button();
    // text-only buttons
    Button(float x, float y, float width, float height,
           sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    // text and sprite buttons
    Button(float x, float y, float width, float height,
           sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
           sf::Texture &texture,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    ~Button();

    // accessors
    const bool isPressed() const;

    // functions
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(const sf::Vector2f mousePosRelativeToWindow);
};

#endif