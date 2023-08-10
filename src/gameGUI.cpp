#include "gameGUI.hpp"

void Game::initFont()
{
    if (!this->font.loadFromFile("/Users/win/Documents/Stupid-subjects/CS163/CS163-Project/CS163-Group3/src/resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf"))

        throw "No font found!" && __cpp_exceptions;
}

void Game::initSprites()
{
}

void Game::initButtons()
{
    Button *WordToDefBtn = new Button(240, 270, 270, 300,
                                      &this->font, "Word to Defintion", 24, 264, 537, sf::Color::Black,
                                      sf::Color::White, sf::Color(215, 215, 215), sf::Color::White);

    Button *DefToWordBtn = new Button(780, 270, 270, 300,
                                      &this->font, "Defintion to Word", 24, 804, 537, sf::Color::Black,
                                      sf::Color::White, sf::Color(215, 215, 215), sf::Color::White);

    this->buttons.push_back(WordToDefBtn);
    this->buttons.push_back(DefToWordBtn);
}

void Game::initTexts()
{
    // sf::Text *ModeMenuTitle = new sf::Text();
    this->ModeMenuTitle.setString("Choose Your Game Mode");
    this->ModeMenuTitle.setFont(this->font);
    this->ModeMenuTitle.setFillColor(sf::Color(25, 69, 107));
    this->ModeMenuTitle.setCharacterSize(50);
    this->ModeMenuTitle.setPosition(sf::Vector2f(346, 112));

    // sf::Text *ModeMenuSubTitle = new sf::Text();
    this->ModeMenuSubTitle.setString("Remember to switch to your desired language!");
    this->ModeMenuSubTitle.setFont(this->font);
    this->ModeMenuSubTitle.setFillColor(sf::Color(25, 69, 107));
    this->ModeMenuSubTitle.setCharacterSize(24);
    this->ModeMenuSubTitle.setPosition(sf::Vector2f(381, 180));

    // this->texts.push_back(ModeMenuTitle);
    // this->texts.push_back(ModeMenuSubTitle);
}

Game::Game()
{
    this->menu = GameMenu::GAME_MODE_MENU;
    this->initFont();
    this->initSprites();
    this->initButtons();
}

Game::~Game()
{
    for (auto button : buttons)
    {
        delete button;
    }
    // for (auto text : texts)
    // {
    //     delete text;
    // }
}

void Game::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto button : buttons)
    {
        target.draw(*button, states);
    }
    // for (auto text : texts)
    // {
    //     target.draw(*text, states);
    // }
    // target.draw(wordToDefBtn, states);
    // target.draw(defToWordBtn, states);
    // target.draw(ModeMenuTitle, states);
    // target.draw(ModeMenuSubTitle, states);
}

void Game::Update(const sf::Vector2f mousePosRelativeToWindow)
{
    for (auto button : this->buttons)
    {
        button->update(mousePosRelativeToWindow);
    }
}
