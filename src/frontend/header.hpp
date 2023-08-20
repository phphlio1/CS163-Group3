#ifndef HEADER_CPP
#define HEADER_CPP

#include "Component.hpp"
#include "button.hpp"
#include "TextBox.hpp"
#include <SFML/Graphics.hpp>
#include <vector>
#include <cstring>

extern const std::vector<std::string> LanguageOfChoiceDisplay;
extern const std::vector<sf::Vector2f> LanguageTextPos;

namespace Frontend
{
    enum SearchOptions
    {
        WORD_TO_DEFINITION = 0,
        DEFINITION_TO_WORD
    };

    enum LanguageOfChoice
    {
        ENG_TO_VIE = 0,
        ENG_TO_ENG,
        VIE_TO_ENG,
        EMO_TO_ENG
    };

    enum Tab
    {
        DICTIONARY = 0,
        DAILY,
        FAVORITE,
        GAME
    };

    class Header : public Component
    {
    private:
        short unsigned currentTab;
        short unsigned searchOptions;
        short unsigned languageOfChoice;
        // bool isWarning;
        bool isReset;
        sf::Font fontAwesome, serif, sans;

        // sf::Text warningText;

        sf::Texture icon, dictionary, daily, favorite, game, swap, search, config, reset;
        sf::Sprite iconSprite, searchSprite;

        sf::RectangleShape background, iconSeperate; //, warningBackground;

        Button dictionaryBtn, dailyBtn, favBtn, gameBtn, setLangBtn, configBtn, resetBtn; //, yesBtn, noBtn;
        Frontend::TextBox searchBar;

    public:
        Header();
        ~Header();

        virtual void processEvent(const sf::Event &event) override;

        void setFonts();
        void setTextures();
        void setBackground();
        void setSprites();
        void setButtons();
        void setTextBox();
        // void setWarningBox();

        void updateLangOfChoiceBtn();
        void updateSearchOptions();

        std::string getUserLookUp();
        std::string getCurrentLanguageOfChoice();
        std::string getSearchOption();
        bool getIsReset();
        short unsigned getCurrentTab();

    protected:
        virtual void updateTexture() override;
        // virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    };
}

#endif