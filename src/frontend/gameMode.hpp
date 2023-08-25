#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

#include "button.hpp"
#include "Component.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

namespace Frontend
{
    enum GameMenu
    {
        GAME_MODE_MENU,
        WORD_TO_DEF,
        DEF_TO_WORD
    };

    class GameModeMenu : public Component
    {
    private:
        GameMenu gameMenu;
        sf::Font font;
        sf::Texture wordToDefIcon;
        sf::Texture defToWordIcon;

        std::vector<sf::RectangleShape> rectShapes;
        std::vector<sf::Text> titles;
        Button wordToDefBtn, defToWordBtn;

    public:
        GameModeMenu();
        ~GameModeMenu();

        GameMenu getCurrentGameMenu();

        void setFont();
        void setButtons();
        void setTexture();
        void setTitles();
        void setShapes();
        void setGameMenu(GameMenu menu);

        virtual void processEvent(const sf::Event &event) override;

    protected:
        virtual void updateTexture() override;
    };

}

#endif