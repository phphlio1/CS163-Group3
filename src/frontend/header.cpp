#include "header.hpp"

void Header::setFonts()
{
    fontAwesome.loadFromFile("resources/font/font-awesome-5/Font-Awesome-5-Free-Regular-400.otf");
    serif.loadFromFile("resources/font/DM_Serif_Text/DMSerifText-Regular.ttf");
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
}

void Header::setSprites()
{
    iconSprite.setTexture(icon);
    iconSprite.setPosition(16, 10);

    searchSprite.setTexture(search);
    searchSprite.setPosition(710, 22);
}

void Header::setButtons()
{
    dictionaryBtn = new Button(94, 0, 99, 70,
                               &fontAwesome, "Dictionary", 18, 100, 51, sf::Color::White,
                               dictionary, 118, 7,
                               sf::Color(25, 69, 107), sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 75));
    dailyBtn = new Button(193, 0, 74, 70,
                          &fontAwesome, "Daily", 18, 209, 51, sf::Color::White,
                          daily, 208, 5,
                          sf::Color(25, 69, 107), sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 75));
    favBtn = new Button(267, 0, 87, 70,
                        &fontAwesome, "Favorite", 18, 276, 51, sf::Color::White,
                        favorite, 286, 9,
                        sf::Color(25, 69, 107), sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 75));
    gameBtn = new Button(354, 0, 69, 70,
                         &fontAwesome, "Game", 18, 364, 51, sf::Color::White,
                         game, 364, 0,
                         sf::Color(25, 69, 107), sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 75));
    configBtn = new Button(1133, 21, 35, 35,
                           &fontAwesome, "", 0, 0, 0, sf::Color::Transparent,
                           config, 1133, 21,
                           sf::Color(254, 254, 254), sf::Color(215, 215, 215), sf::Color(254, 254, 254));
    resetBtn = new Button(1193, 0, 73, 70,
                          &fontAwesome, "", 0, 0, 0, sf::Color::Transparent,
                          reset, 1205, 12,
                          sf::Color(25, 69, 107), sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 75));
}

void Header::setTextBox()
{
    searchBar = new Frontend::TextBox(475, 40, 50);
    searchBar->setFont("../resources/font/font-awesome-5/Font-Awesome-5-Free-Regular-400.otf");
    searchBar->setBackgroundString("Search word to definition");
    searchBar->setPosition(701, 18);
}

Header::Header()
{
    searchOptions = SearchOptions::WORD_TO_DEFINITION;
    setFonts();
    setBackground();
    setTextures();
    setSprites();
    setButtons();
    setTextBox();
}

Header::~Header()
{
    delete dictionaryBtn;
    delete dailyBtn;
    delete favBtn;
    delete gameBtn;
    delete configBtn;
    delete resetBtn;

    delete searchBar;
}

void Header::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(background);
    target.draw(*searchBar);
    target.draw(iconSeperate);
    target.draw(iconSprite);
    target.draw(searchSprite);

    target.draw(*dictionaryBtn);
    target.draw(*dailyBtn);
    target.draw(*favBtn);
    target.draw(*gameBtn);
    target.draw(*configBtn);
    target.draw(*resetBtn);
}

void Header::update(const sf::Vector2f mousePosRelativeToWindow)
{
    dictionaryBtn->update(mousePosRelativeToWindow);
    dailyBtn->update(mousePosRelativeToWindow);
    favBtn->update(mousePosRelativeToWindow);
    gameBtn->update(mousePosRelativeToWindow);
    configBtn->update(mousePosRelativeToWindow);
    resetBtn->update(mousePosRelativeToWindow);
}
