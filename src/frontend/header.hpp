#ifndef HEADER_CPP
#define HEADER_CPP

#include "button.hpp"
#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>

enum class SearchOptions
{
    WORD_TO_DEFINITION,
    DEFINITION_TO_WORD
};

class Header : public sf::Drawable
{
private:
    SearchOptions searchOptions;
    sf::Font fontAwesome;
    sf::Font serif;

    sf::Texture icon, dictionary, daily, favorite, game, swap, search, config, reset;
    sf::Sprite iconSprite, searchSprite;

    sf::RectangleShape background, iconSeperate;

    Button *dictionaryBtn, *dailyBtn, *favBtn, *gameBtn, *setLangBtn, *configBtn, *resetBtn;
    Frontend::TextBox *searchBar;

public:
    Header();
    ~Header();
    void setFonts();
    void setTextures();
    void setBackground();
    void setSprites();
    void setButtons();
    void setTextBox();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(const sf::Vector2f mousePosRelativeToWindow);
};

#endif