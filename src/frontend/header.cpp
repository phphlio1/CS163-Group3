#include "Trie.h"
#include "header.hpp"
#include "DefinitionFrame.hpp"
#include "SideBar.hpp"
#include "HistoryBar.hpp"
#include "InGame.hpp"
#include "Global.hpp"

using namespace Frontend;

const std::vector<std::string> LanguageOfChoiceDisplay = {"Eng              Eng", "Eng             Vie", "Vie               Eng", "Emo              Eng"};
const std::vector<sf::Vector2f> LanguageTextPos = {sf::Vector2f(17, 15), sf::Vector2f(17, 15), sf::Vector2f(22, 15), sf::Vector2f(9, 15)};

const LanguageOfChoice Header::toLang[] = {        ENG_TO_ENG,
        ENG_TO_VIE,
        VIE_TO_ENG,
        EMO_TO_ENG
};

const SearchOptions Header::toSearch[] = {        WORD_TO_DEFINITION,
        DEFINITION_TO_WORD
};

const Tab Header::toTab[] = {        DICTIONARY,
        DAILY,
        FAVORITE,
        GAME
};

void Header::setSuggestionBtns()
{
    for (int i = 0; i < 4; ++i)
    {
        Button *suggest = new Button(473, 40, sf::Color::White, sf::Color(215, 215, 215), sf::Color(215, 215, 215));
        suggest->setPosition(698, i * 40 + 56);

        suggest->setTextPosition(sf::Vector2f(53, 9));
        suggest->setContainer(this);
        suggestBtns.push_back(suggest);

        sf::RectangleShape outline(sf::Vector2f(471, 40));
        outline.setFillColor(sf::Color::Transparent);
        outline.setPosition(sf::Vector2f(suggest->getPosition().x + 1, suggest->getPosition().y));
        outline.setOutlineThickness(1);
        outline.setOutlineColor(sf::Color(215, 215, 215));
        suggestOulines.push_back(outline);
    }
    updateTexture();
}

void Header::setSuggestionStr()
{
    int maxSuggestions = (suggestions.size() < 4 ? suggestions.size() : 4);

    if (maxSuggestions < 4)
    {
        for (int i = maxSuggestions; i < 4; ++i)
            suggestBtns.at(i)->setText(roboto, "", 20, sf::Color::Black);
    }

    for (int i = 0; i < maxSuggestions; ++i)
    {
        suggestBtns.at(i)->setText(roboto, suggestions.at(i), 20, sf::Color::Black);
    }
    // suggestBtns.at(i)->setText(fontAwesome, suggestions.at(i), 20, sf::Color::Black);

    updateTexture();
}

void Header::setFonts()
{
    roboto.loadFromFile("resources/font/Roboto/Roboto-Regular.ttf");
    fontAwesome.loadFromFile("resources/font/font-awesome-5/Font-Awesome-5-Free-Regular-400.otf");
    serif.loadFromFile("resources/font/DM_Serif_Text/DMSerifText-Regular.ttf");
    sans.loadFromFile("resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf");
    updateTexture();
}

void Header::setBackground()
{
    background.setSize(sf::Vector2f(1280, 70));
    background.setOutlineColor(sf::Color::Black);
    background.setPosition(0, 0);
    background.setFillColor(sf::Color(25, 69, 107));

    iconSeperate.setSize(sf::Vector2f(4, 70));
    iconSeperate.setPosition(80, 0);
    iconSeperate.setFillColor(sf::Color::White);
    updateTexture();
}

void Header::setTextures()
{
    icon.loadFromFile("resources/img/icon.png");
    dictionary.loadFromFile("resources/img/dictionary.png");
    daily.loadFromFile("resources/img/daily-word.png");
    favorite.loadFromFile("resources/img/favorite-list.png");
    game.loadFromFile("resources/img/game.png");
    swap.loadFromFile("resources/img/double-sided-arrow.png");
    search.loadFromFile("resources/img/Search-icon.png");
    config.loadFromFile("resources/img/word-to-definition-settings.png");
    reset.loadFromFile("resources/img/reset-app.png");
    updateTexture();
}

void Header::setSprites()
{
    iconSprite.setTexture(icon);
    iconSprite.setPosition(16, 10);

    searchSprite.setTexture(search);
    searchSprite.setPosition(706, 19);
	updateTexture();
}

void Header::setButtons()
{
    dictionaryBtn.setPosition(94, 0);
    dictionaryBtn.setText(fontAwesome, "History", 18, sf::Color::White);
    dictionaryBtn.setTextPosition(sf::Vector2f(19, 51));
    dictionaryBtn.setTexture(dictionary, 24, 7);
	dictionaryBtn.setContainer(this);

    dailyBtn.setPosition(193, 0);
    dailyBtn.setText(fontAwesome, "Daily", 18, sf::Color::White);
    dailyBtn.setTextPosition(sf::Vector2f(16, 51));
    dailyBtn.setTexture(daily, 15, 5);
	dailyBtn.setContainer(this);

    favBtn.setPosition(267, 0);
    favBtn.setText(fontAwesome, "Favorite", 18, sf::Color::White);
    favBtn.setTextPosition(sf::Vector2f(8, 51));
    favBtn.setTexture(favorite, 19, 9);
	favBtn.setContainer(this);

    gameBtn.setPosition(354, 0);
    gameBtn.setText(fontAwesome, "Game", 18, sf::Color::White);
    gameBtn.setTextPosition(sf::Vector2f(10, 51));
    gameBtn.setTexture(game, 10, 0);
	gameBtn.setContainer(this);

    configBtn.setPosition(1129, 18);
    configBtn.setTexture(config, 0, 0);
	configBtn.setContainer(this);

    resetBtn.setPosition(1193, 0);
    resetBtn.setTexture(reset, 12, 12);
	resetBtn.setContainer(this);

    setLangBtn.setPosition(447, 0);
    setLangBtn.setText(serif, LanguageOfChoiceDisplay.at(languageOfChoice), 30, sf::Color::White);
    setLangBtn.setTextPosition(LanguageTextPos.at(languageOfChoice));
    setLangBtn.setTexture(swap, 90, 10);
	setLangBtn.setContainer(this);

	searchBar.setContainer(this);

    updateTexture();
}

void Header::setTextBox()
{
    // searchBar = Frontend::TextBox(475, 40, 50);
    searchBar.setFont("resources/font/font-awesome-5/Font-Awesome-5-Free-Regular-400.otf");
    searchBar.setBackgroundString("Search word to definition");
    searchBar.setPosition(697, 15);
    updateTexture();
}

Header::Header()
    : Component(1280, 220),
	  definition_frame_(nullptr),
      searchBar(475, 40, 50),
      dictionaryBtn(99, 70, sf::Color(25, 69, 107), sf::Color(95, 125, 151), sf::Color(95, 125, 151)),
      dailyBtn(74, 70, sf::Color(25, 69, 107), sf::Color(95, 125, 151), sf::Color(95, 125, 151)),
      favBtn(87, 70, sf::Color(25, 69, 107), sf::Color(95, 125, 151), sf::Color(95, 125, 151)),
      gameBtn(69, 70, sf::Color(25, 69, 107), sf::Color(95, 125, 151), sf::Color(95, 125, 151)),
      configBtn(35, 35, sf::Color(254, 254, 254), sf::Color(215, 215, 215), sf::Color(254, 254, 254)),
      resetBtn(73, 70, sf::Color(25, 69, 107), sf::Color(95, 125, 151), sf::Color(95, 125, 151)),
      setLangBtn(229, 70, sf::Color(25, 69, 107), sf::Color(95, 125, 151), sf::Color(95, 125, 151))
{
	
    currentTab = DICTIONARY;
    isReset = false;
    // isWarning = false;
    searchOptions = WORD_TO_DEFINITION;
	languageOfChoice = ENG_TO_ENG;
	g_curr_trie = g_tries[languageOfChoice];
    setFonts();
    setBackground();
    setTextures();
    setSprites();
    setButtons();
    setTextBox();
    setSuggestionBtns();
    // setWarningBox();
    updateTexture();
}

Header::~Header()
{
    for (auto button : suggestBtns)
        delete button;
}

void Header::updateTexture()
{
    texture_.clear(sf::Color::Transparent);
    texture_.draw(background);
    texture_.draw(iconSeperate);
    texture_.draw(searchBar);
    texture_.draw(iconSprite);
    texture_.draw(searchSprite);

    texture_.draw(dictionaryBtn);
    texture_.draw(dailyBtn);
    texture_.draw(favBtn);
    texture_.draw(gameBtn);
    texture_.draw(configBtn);
    texture_.draw(resetBtn);
    texture_.draw(setLangBtn);

    if (getUserLookUp() != "" && getSearchOption() == WORD_TO_DEFINITION)
    {
        for (int i = 0; i < suggestBtns.size(); ++i)
            if (suggestBtns.at(i)->getString() != "")
            {
                texture_.draw(*suggestBtns.at(i));
                texture_.draw(suggestOulines.at(i));
            }
    }

    texture_.display();
}

void Header::processEvent(const sf::Event &event)
{
	// std::cerr << "processed events\n";
	if (getSearchOption() == WORD_TO_DEFINITION)
	{
		for (auto btn : suggestBtns)
		{
			if (btn->getString() != "")
				btn->processEvent(event);
		}
	}

    static sf::Clock clock;

	// std::cerr << clock.getElapsedTime().asSeconds() << '\n';
    if (searchBar.isTyping())
    {
        std::string currentTextBoxString = getUserLookUp();
		if (getSearchOption() == WORD_TO_DEFINITION)
		{
			std::vector<std::string> suggestions;
			g_curr_trie->searchForAWord_withSuggestion(currentTextBoxString, suggestions);
			this->suggestions = suggestions;
		}
        
		if (event.type == sf::Event::KeyPressed
			&& event.key.code == sf::Keyboard::Enter)
		{
			std::cerr << "enter pressed\n";
			if (definition_frame_)
			{
				if (getSearchOption() == WORD_TO_DEFINITION)
				{
					definition_frame_->setKeyword(getUserLookUp());
				}
				else
				{
					definition_frame_->setSubDefi(getUserLookUp());
				}
			}
		}

        setSuggestionStr();
        clock.restart();
    }

    if (!searchBar.isTyping())
    {
        for (auto btn : suggestBtns)
            btn->setText(fontAwesome, "", 20, sf::Color::Black);
    }
	
    dictionaryBtn.processEvent(event);
    dailyBtn.processEvent(event);
    favBtn.processEvent(event);
    gameBtn.processEvent(event);
    configBtn.processEvent(event);
    resetBtn.processEvent(event);
    setLangBtn.processEvent(event);
    searchBar.processEvent(event);
	// std::cerr << searchBar.getForegroundString().toAnsiString() << '\n';
	
    if (dictionaryBtn.isPressed() && !dictionaryBtn_pressed_)
    {
        currentTab = DICTIONARY;
		std::string message;
		g_curr_trie->takeHistory(g_history, message);
		side_bar_->setVisibility(0);
		history_bar_->setVisibility(1);
		in_game_->setVisibility(0);
		definition_frame_->setVisibility(1);
		history_bar_->updateTexture();
    }
    else if (dailyBtn.isPressed() && !dailyBtn_pressed_)
    {
        currentTab = DAILY;
		std::string word;
		std::vector<std::string> defi_list;
		g_curr_trie->getRandomWordAndDefi(word, defi_list);
		definition_frame_->setKeyword(word);
		side_bar_->setVisibility(0);
		history_bar_->setVisibility(1);
		in_game_->setVisibility(0);
		definition_frame_->setVisibility(1);
    }
    else if (favBtn.isPressed() && !favBtn_pressed_)
    {
        currentTab = FAVORITE;
		std::string message;
		g_curr_trie->viewFavoriteList(g_favorites, message);
	    side_bar_->setVisibility(1);
		history_bar_->setVisibility(0);
		in_game_->setVisibility(0);
		definition_frame_->setVisibility(1);
	    side_bar_->updateTexture();
    }
    else if (gameBtn.isPressed() && !gameBtn_pressed_)
    {
        currentTab = GAME;
		side_bar_->setVisibility(0);
		history_bar_->setVisibility(0);
		in_game_->setVisibility(1);
		definition_frame_->setVisibility(0);
    }
	else if (setLangBtn.isPressed() && !setLangBtn_pressed_)
	{
		updateLangOfChoiceBtn();
		g_curr_trie = g_tries[getCurrentLanguageOfChoice()];
	}
	else if (configBtn.isPressed() && !configBtn_pressed_)
	{
		updateSearchOptions();
	}
	else if (resetBtn.isPressed() && !resetBtn_pressed_)
	{
		resetTrie();
	}
	updateTexture();
	dictionaryBtn_pressed_ = dictionaryBtn.isPressed();
	dailyBtn_pressed_ = dailyBtn.isPressed();
	favBtn_pressed_ = favBtn.isPressed();
	gameBtn_pressed_ = gameBtn.isPressed();
	setLangBtn_pressed_ = setLangBtn.isPressed();
	resetBtn_pressed_ = resetBtn.isPressed();
	configBtn_pressed_ = configBtn.isPressed();
}

std::string Header::getUserLookUp()
{
    return searchBar.getForegroundString().toAnsiString();
}

LanguageOfChoice Header::getCurrentLanguageOfChoice()
{
	return languageOfChoice;
}

void Header::updateLangOfChoiceBtn()
{
	int lang_of_choice = languageOfChoice;
	lang_of_choice = (lang_of_choice + 1) % 4;
	languageOfChoice = toLang[lang_of_choice];
	setLangBtn.setTextString(LanguageOfChoiceDisplay.at(lang_of_choice));
	setLangBtn.setTextPosition(LanguageTextPos.at(lang_of_choice));
    updateTexture();
}

void Header::updateSearchOptions()
{
	int search_options = searchOptions;
	search_options = (search_options + 1) % 2;
	searchOptions = toSearch[search_options];
    switch (search_options)
    {
    case WORD_TO_DEFINITION:
        searchBar.setBackgroundString("Search word to definition");
        break;

    case DEFINITION_TO_WORD:
        searchBar.setBackgroundString("Search defintion to word");
        break;

    default:
        searchBar.setBackgroundString("Something went wrong");
        break;
    }
    updateTexture();
}

SearchOptions Header::getSearchOption()
{
	return searchOptions;
}

bool Header::getIsReset()
{
    return isReset;
}

Tab Header::getCurrentTab()
{
    return currentTab;
}

void Header::setDefinitionFrame(DefinitionFrame *n_definition_frame)
{
	definition_frame_ = n_definition_frame;
}

void Header::setSideBar(SideBar *n_side_bar)
{
	side_bar_ = n_side_bar;
}

void Header::setHistoryBar(HistoryBar *n_history_bar)
{
	history_bar_=  n_history_bar;
}

void Header::setInGame(InGame *n_in_game)
{
	in_game = n_in_game;
}

void Header::resetTrie()
{
    for (int i = 0; i < 4; ++i)
    {
        std::string resetMessage = "Reset trie (" + std::to_string(i) + ") sucessfully";
        g_tries[i]->resetToOriginal(resetMessage);
    }
	std::string message;
	g_curr_trie->viewFavoriteList(g_favorites, message);
	g_curr_trie->takeHistory(g_history, message);
	side_bar_->updateTexture();
	history_bar_->updateTexture();
}

// void Header::getStr(std::vector<std::string> suggestions)
// {
//     this->suggestions = suggestions;
// }
