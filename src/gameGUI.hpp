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

class Game : public sf::Drawable
{
private:
    GameMode mode;
    GameMenu menu;

    sf::Font font;
    std::vector<sf::Text *> texts;
    std::vector<Button *> buttons;

    // Button wordToDefBtn;
    // Button defToWordBtn;

    sf::Text ModeMenuTitle;
    sf::Text ModeMenuSubTitle;
    sf::Sprite WordToDefIcon;
    sf::Sprite DefToWordIcon;

    void initFont();
    void initButtons();
    void initSprites();
    void initTexts();

public:
    Game();
    ~Game();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void Update(const sf::Vector2f mousePosRelativeToWindow);
};