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
	class DefinitionFrame;
	class SideBar;
	class HistoryBar;
	class InGame;
	
    enum SearchOptions
    {
        WORD_TO_DEFINITION = 0,
        DEFINITION_TO_WORD
    };

    enum LanguageOfChoice
    {
        ENG_TO_ENG = 0,
        ENG_TO_VIE,
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
		static const LanguageOfChoice toLang[];
		static const SearchOptions toSearch[];
		static const Tab toTab[];
		
		DefinitionFrame *definition_frame_;
		SideBar *side_bar_;
		HistoryBar *history_bar_;
		InGame *in_game_;
		
        Tab currentTab;
        SearchOptions searchOptions;
        LanguageOfChoice languageOfChoice;
        // bool isWarning;
        bool isReset;
        sf::Font fontAwesome, serif, sans, roboto;

        std::vector<std::string> suggestions;
        std::vector<Button *> suggestBtns;
        std::vector<sf::RectangleShape> suggestOulines;

        // sf::Text warningText;

        sf::Texture icon, dictionary, daily, favorite, game, swap, search, config, reset;
        sf::Sprite iconSprite, searchSprite;

        sf::RectangleShape background, iconSeperate; //, warningBackground;

        Button dictionaryBtn, dailyBtn, favBtn, gameBtn, setLangBtn, configBtn, resetBtn; //, yesBtn, noBtn;
		bool dictionaryBtn_pressed_, dailyBtn_pressed_, favBtn_pressed_, gameBtn_pressed_, setLangBtn_pressed_, configBtn_pressed_, resetBtn_pressed_;
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
        void setSuggestionBtns();
        void setSuggestionStr();
        // void setWarningBox();

        void updateLangOfChoiceBtn();
        void updateSearchOptions();

        std::string getUserLookUp();
        LanguageOfChoice getCurrentLanguageOfChoice();
        SearchOptions getSearchOption();
        bool getIsReset();
        Tab getCurrentTab();

		void setDefinitionFrame(DefinitionFrame *n_definition_frame);
		void setSideBar(SideBar *n_side_bar);
		void setHistoryBar(HistoryBar *n_history_bar);
		void setInGame(InGame *n_in_game);

        void getStr(std::vector<std::string> suggestions);
        void resetTrie();

    protected:
        virtual void updateTexture() override;
    };
}

#endif
