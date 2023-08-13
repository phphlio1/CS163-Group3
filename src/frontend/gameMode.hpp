#ifndef GAME_MODE_HPP
#define GAME_MODE_HPP

#include "button.hpp"
#include <vector>
#include <SFML/Graphics.hpp>

enum class GameMode
{
    WORD_TO_DEF,
    DEF_TO_WORD
};

enum class GameMenu
{
    GAME_MODE_MENU,
    IN_GAME
};

class GameModeMenu : public sf::Drawable
{
private:
    GameMode mode;
    GameMenu menu;

    sf::Font font;
    sf::Texture wordToDefIcon;
    sf::Texture defTOWordIcon;

    std::vector<sf::RectangleShape *> rectShapes;
    std::vector<sf::Text *> titles;
    std::vector<Button *> buttons;

public:
    GameModeMenu();
    ~GameModeMenu();

    void initFont();
    void initButtons();
    void initTexture();
    void initTitles();
    void initShapes();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void Update(const sf::Vector2f mousePosRelativeToWindow);
};

#endif