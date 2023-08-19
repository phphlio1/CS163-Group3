#ifndef HEADER_CPP
#define HEADER_CPP

#include "button.hpp"
#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>

enum SearchOptions
{
    WORD_TO_DEFINITION,
    DEFINITION_TO_WORD
};

enum LanguageOfChoice
{
    ENG_TO_VIE,
    ENG_TO_ENG,
    VIE_TO_ENG,
    EMO_TO_ENG
};

enum Tab
{
    DICTIONARY,
    DAILY,
    FAVORITE,
    GAME
}

extern const std::vector<std::string>
    LanguageOfChoicDisplay;
extern const std::vector<sf::Vector2f> LanguageTextPos;

class Header : public sf::Drawable
{
private:
    short unsigned currentTab;
    short unsigned searchOptions;
    short unsigned languageOfChoice;
    bool isWarning;
    bool isReset;
    sf::Font fontAwesome, serif, sans;

    sf::Text warningText;

    sf::Texture icon, dictionary, daily, favorite, game, swap, search, config, reset;
    sf::Sprite iconSprite, searchSprite;

    sf::RectangleShape background, iconSeperate, warningBackground;

    Button *dictionaryBtn, *dailyBtn, *favBtn, *gameBtn, *setLangBtn, *configBtn, *resetBtn, *yesBtn, *noBtn;
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
    void setWarningBox();

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    void update(const sf::Event &event, const sf::Vector2f mousePosRelativeToWindow);
    void updateTextBox(const sf::Event &event);
    void updateLangOfChoiceBtn();
    void updateSearchOptions();

    std::string getUserLookUp();
    std::string getCurrentLanguageOfChoice();
    std::string getSearchOption();
    bool getIsReset();
    short unsigned getCurrentTab();
};

#endif