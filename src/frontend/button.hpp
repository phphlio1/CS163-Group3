#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "Component.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

namespace Frontend
{
    enum ButtonState
    {
        BTN_IDLE,
        BTN_HOVER,
        BTN_ACTIVE
    };

    class Button : public Component
    {
    private:
        // int width_n, height_n;
        short unsigned buttonState;
        sf::Text text;
        sf::RectangleShape shape;
        sf::Sprite sprite;

        sf::Color idleColor, hoverColor, activeColor;

    public:
        virtual void processEvent(const sf::Event &event) override;

        void setText(sf::Font &font, std::string newText, int textSize, sf::Color textColor);
        void setTextPosition(const sf::Vector2f pos);
        void setTextString(const std::string &newStr);
        void setTexture(sf::Texture &texture, float texture_x, float texture_y);
        void setColor(sf::Color idle, sf::Color hover, sf::Color active);
        void setButtonActive();
        void setButtonInactive();
        void setButtonHover();

        Button(int width, int height, sf::Color idle, sf::Color hover, sf::Color active);

        ~Button();

        // accessors
        const bool isPressed() const;
        const sf::String getString();
        const sf::Text getText() { return text; }

        // functions
        void centerVertical();
        void wrapTextVertical();
        void updateColor(sf::Event &event);

    protected:
        virtual void updateTexture() override;
    };
}

#endif