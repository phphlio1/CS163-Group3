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
		ButtonState getButtonState() const;
		
		void setPressedState(bool n_is_pressed);
		void setButtonState(ButtonState n_state);
        void setButtonActive();
        void setButtonInactive();
        void setButtonHover();
		
        ButtonState buttonState;
        sf::Text text;
        sf::RectangleShape shape;
        sf::Sprite sprite;

        sf::Color idleColor, hoverColor, activeColor;

		const Component *container_;
		bool is_pressed_;

    public:
        virtual void processEvent(const sf::Event &event) override;
		virtual sf::Vector2f findWindowRelativePos() const override;

        void setText(sf::Font &font, std::string newText, int textSize, sf::Color textColor);
        void setTextPosition(const sf::Vector2f pos);
        void setTextString(const std::string &newStr);
        void setTexture(const sf::Texture &texture, float texture_x, float texture_y);
        void setColor(sf::Color idle, sf::Color hover, sf::Color active);
		void setContainer(const Component *n_container);

        Button(int width, int height, sf::Color idle, sf::Color hover, sf::Color active);

        ~Button();

        // accessors
        bool isPressed() const;
        const sf::String& getString() const;
        const sf::Text& getText() const;
		const Component* getContainer() const;

        // functions
        void centerVertical();
        void wrapTextVertical();
        void updateColor(sf::Event &event);

    protected:
        virtual void updateTexture() override;
    };
}

#endif
