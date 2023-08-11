#include "gameMode.hpp"

void GameModeMenu::initFont()
{
    if (!this->font.loadFromFile("resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf"))

        throw "No font found!" && __cpp_exceptions;
}

void GameModeMenu::initShapes()
{
    sf::RectangleShape *gameHeader = new sf::RectangleShape(sf::Vector2f(1280, 40));
    gameHeader->setFillColor(sf::Color(17, 105, 142));
    gameHeader->setPosition(0, 70);
    this->rectShapes.push_back(gameHeader);

    sf::RectangleShape *gameFooter = new sf::RectangleShape(sf::Vector2f(1280, 40));
    gameFooter->setFillColor(sf::Color(17, 105, 142));
    gameFooter->setPosition(0, 680);
    this->rectShapes.push_back(gameFooter);

    sf::RectangleShape *test = new sf::RectangleShape(sf::Vector2f(1280, 70));
    test->setFillColor(sf::Color(25, 69, 107));
    test->setPosition(0, 0);
    this->rectShapes.push_back(test);
}

void GameModeMenu::initTexture()
{
    this->wordToDefIcon.loadFromFile("resources/img/word-to-def.png");
    this->defTOWordIcon.loadFromFile("resources/img/def-to-word.png");
}

void GameModeMenu::initButtons()
{
    Button *wordToDefButton = new Button(240, 270, 270, 300, &this->font, "Word to Definition", 24, 264, 537, sf::Color::Black, wordToDefIcon, sf::Color::White, sf::Color(215, 215, 215), sf::Color::White);
    Button *defToWordButton = new Button(780, 270, 270, 300, &this->font, "Definition to Word", 24, 804, 537, sf::Color::Black, defTOWordIcon, sf::Color::White, sf::Color(215, 215, 215), sf::Color::White);
    this->buttons.push_back(wordToDefButton);
    this->buttons.push_back(defToWordButton);
}

void GameModeMenu::initTitles()
{
    std::string Title = "Choose Your Game Mode";
    sf::Text *GameModeTitle = new sf::Text(Title, this->font, 50);
    GameModeTitle->setPosition(sf::Vector2f(346, 112));
    GameModeTitle->setFillColor(sf::Color(25, 69, 107));

    std::string Subtitle = "Remember to switch to your desired language!";
    sf::Text *GameModeSubtitle = new sf::Text(Subtitle, this->font, 24);
    GameModeSubtitle->setPosition(sf::Vector2f(381, 180));
    GameModeSubtitle->setFillColor(sf::Color(25, 69, 107));

    this->titles.push_back(GameModeTitle);
    this->titles.push_back(GameModeSubtitle);
}

GameModeMenu::GameModeMenu()
{
    this->menu = GameMenu::GAME_MODE_MENU;
    this->initFont();
    this->initTexture();
    this->initButtons();
    this->initTitles();
    this->initShapes();
}

GameModeMenu::~GameModeMenu()
{
    for (auto button : buttons)
    {
        delete button;
    }
    for (auto title : titles)
    {
        delete title;
    }
    for (auto shape : rectShapes)
    {
        delete shape;
    }
}

void GameModeMenu::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (auto button : buttons)
    {
        target.draw(*button, states);
    }
    for (auto title : titles)
    {
        target.draw(*title, states);
    }
    for (auto shape : rectShapes)
    {
        target.draw(*shape, states);
    }
}

void GameModeMenu::Update(const sf::Vector2f mousePosRelativeToWindow)
{
    for (auto button : buttons)
    {
        button->update(mousePosRelativeToWindow);
    }
    if (this->buttons[0]->isPressed())
    {
        this->menu = GameMenu::IN_GAME;
        this->mode = GameMode::WORD_TO_DEF;
    }
    if (this->buttons[1]->isPressed())
    {
        this->menu = GameMenu::IN_GAME;
        this->mode = GameMode::DEF_TO_WORD;
    }
}

// void GameModeMenu::centerKeyword(sf::Text *textDisplay)
// {
//     sf::FloatRect textRect = textDisplay->getLocalBounds();
//     textDisplay->setPosition((1280 - textRect.width) / 2, 183);
// }

// void GameModeMenu::getWordToDefQuestions(std::vector<std::string> questionsStr)
// {
//     if (this->menu == GameMenu::GAME_MODE_MENU && this->mode == GameMode::WORD_TO_DEF)
//     {
//         for (auto &question : questionsStr)
//         {
//             std::string firstClauseStr = "What is the meaning of ";
//             sf::Text *firstClause = new sf::Text(firstClauseStr, this->font, 50);
//             firstClause->setFillColor(sf::Color(17, 105, 142));
//             firstClause->setPosition(345, 115);

//             sf::Text *keyWord = new sf::Text(question, this->font, 50);
//             keyWord->setFillColor(sf::Color(22, 199, 154));
//             centerKeyword(keyWord);

//             this->renderedQuestions.push_back(wholeQuestion);
//         }
//     }
// }
