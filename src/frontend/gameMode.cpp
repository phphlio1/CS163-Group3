#include "gameMode.hpp"

using namespace Frontend;

GameMenu GameModeMenu::getCurrentGameMenu()
{
    return gameMenu;
}

void GameModeMenu::setGameMenu(GameMenu menu)
{
    gameMenu = menu;
}

void GameModeMenu::setFont()
{
    font.loadFromFile("resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf");
    updateTexture();
}

void GameModeMenu::setShapes()
{
    sf::RectangleShape gameHeader(sf::Vector2f(1280, 40));
    gameHeader.setFillColor(sf::Color(17, 105, 142));
    gameHeader.setPosition(0, 70);
    rectShapes.push_back(gameHeader);

    sf::RectangleShape gameFooter(sf::Vector2f(1280, 40));
    gameFooter.setFillColor(sf::Color(17, 105, 142));
    gameFooter.setPosition(0, 680);
    rectShapes.push_back(gameFooter);

    updateTexture();
}

void GameModeMenu::setTexture()
{
    wordToDefIcon.loadFromFile("resources/img/word-to-def.png");
    defToWordIcon.loadFromFile("resources/img/def-to-word.png");

    updateTexture();
}

void GameModeMenu::setButtons()
{
    wordToDefBtn.setPosition(240, 270);
    wordToDefBtn.setText(font, "Word to Definition", 24, sf::Color::Black);
    wordToDefBtn.setTextPosition(sf::Vector2f(24, 267));
    wordToDefBtn.setTexture(wordToDefIcon, 0, 0);
    wordToDefBtn.setContainer(this);

    defToWordBtn.setPosition(780, 270);
    defToWordBtn.setText(font, "Definition to Word", 24, sf::Color::Black);
    defToWordBtn.setTextPosition(sf::Vector2f(24, 267));
    defToWordBtn.setTexture(defToWordIcon, 0, 0);
    defToWordBtn.setContainer(this);

    updateTexture();
}

void GameModeMenu::setTitles()
{
    sf::Text GameModeTitle("Choose Your Game Mode", font, 50);
    GameModeTitle.setPosition(sf::Vector2f(346, 112));
    GameModeTitle.setFillColor(sf::Color(25, 69, 107));

    sf::Text GameModeSubtitle("Remember to switch to your desired language!", font, 24);
    GameModeSubtitle.setPosition(sf::Vector2f(381, 180));
    GameModeSubtitle.setFillColor(sf::Color(25, 69, 107));

    titles.push_back(GameModeTitle);
    titles.push_back(GameModeSubtitle);

    updateTexture();
}

GameModeMenu::GameModeMenu()
    : Component(1280, 720),
      gameMenu(GAME_MODE_MENU),
      wordToDefBtn(270, 300, sf::Color::White, sf::Color(215, 215, 215), sf::Color(215, 215, 215)),
      defToWordBtn(270, 300, sf::Color::White, sf::Color(215, 215, 215), sf::Color(215, 215, 215))
{
    setFont();
    setTexture();
    setTitles();
    setShapes();
    setButtons();

    updateTexture();
}

GameModeMenu::~GameModeMenu()
{
}

void GameModeMenu::processEvent(const sf::Event &event)
{
    wordToDefBtn.processEvent(event);
    defToWordBtn.processEvent(event);

    if (wordToDefBtn.isPressed())
        gameMenu = WORD_TO_DEF;
    else if (defToWordBtn.isPressed())
        gameMenu = DEF_TO_WORD;
}

void GameModeMenu::updateTexture()
{
    texture_.clear(sf::Color::White);

    for (auto title : titles)
        texture_.draw(title);

    for (auto shape : rectShapes)
        texture_.draw(shape);

    texture_.draw(wordToDefBtn);
    texture_.draw(defToWordBtn);

    texture_.display();
}
