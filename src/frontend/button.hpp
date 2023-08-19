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
    sf::String getString();
    const sf::Texture *getTexturePack() { return sprite.getTexture(); }
    sf::Sprite getSprite() { return sprite; }
    sf::Text getText() { return text; }

    void setText(std::string newText);
    void setTextPosition(const sf::Vector2f pos);

    Button();
    // text-only buttons
    Button(float x, float y, float width, float height,
           sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    // text and sprite buttons
    Button(float x, float y, float width, float height,
           sf::Font *font, std::string text, float textSize, float t_x, float t_y, sf::Color textColor,
           sf::Texture &texture, float texture_x, float texture_y,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);

    ~Button();

    // accessors
    const bool isPressed() const;

    // functions
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(const sf::Event &event, const sf::Vector2f mousePosRelativeToWindow);
    void centerVertical();
    void wrapTextVertical();
};

#endif