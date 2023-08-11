#include "wordToDefGame.hpp"

void WordToDefGame::setFont()
{
    font.loadFromFile("resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf");
}

void WordToDefGame::setMetric()
{
    counter = 0;
    score = 0;
    maxCounter = getKeywordsRef().size();
}

void WordToDefGame::setUtilityTexts()
{
    counterText.setFont(font);
    counterText.setString(std::to_string(counter) + " of " + std::to_string(maxCounter));
    counterText.setFillColor(sf::Color::White);
    coutnerText.setCharacterSize(23);
    counterText.setPosition(1002, 73);

    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setFillColor(sf::Color::White);
    scoreText.setCharacterSize(23);
    scoreText.setPosition(1127, 73);
}

void WordToDefGame::setButton()
{
    quit = new Button(1205, 684, 51, 31,
                      &font, "Quit", 1205, 684, sf::Color::White,
                      sf::Color::Transparent, sf::Color(0, 0, 0, 126), sf::Color::Transparent);
}

void WordToDefGame::centerKeyword(sf::Text *keyword)
{
    sf::FloatRect textRect = keyword->getLocalBounds();
    keyword->setPosition((1280 - textRect.width) / 2, 183);
}

void WordToDefGame::setQuestion(std::vector<std::string> &keywordStr)
{
    question.setFont(font);
    question.setString("What is the meaning of");
    question.setFillColor(sf::Color(25, 69, 107));
    question.setCharacterSize(50);
    question.setPosition(345, 115);

    for (auto &str : keywordStr)
    {
        sf::Text *keyWordText = new sf::Text(str + '?', font, 50);
        keyWordText->setFillColor(sf::Color(22, 199, 154));
        centerKeyword(keyWordText);
        keywords.push_back(keyWordText);
    }
}

void WordToDefGame::setAns(std::vector<std::vector<std::string>> &definitionsStr)
{
    for (auto &listOfOptions : definitionsStr)
    {
        for (auto &option : listOfOptions)
        {
            std::vector<Button *> optionsToButton;
            Button *firstAns = new Button(154, 266, 960, 75,
                                          &font, "A.    " + option, 20, 190, 290, sf::Color::Black,
                                          sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206));
            optionsToButton.push_back(firstAns);
            Button *secondAns = new Button(154, 366, 960, 75,
                                           &font, "B.    " + option, 20, 190, 379, sf::Color::Black,
                                           sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206));
            optionsToButton.push_back(secondAns);
            Button *thirdAns = new Button(154, 466, 960, 75,
                                          &font, "C.    " + option, 20, 190, 479, sf::Color::Black,
                                          sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206));
            optionsToButton.push_back(thirdAns);
            Button *fourthAns = new Button(154, 566, 960, 75,
                                           &font, "D.    " + option, 20, 190, 591, sf::Color::Black,
                                           sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206));
            optionsToButton.push_back(fourthAns);
        }
    }
}

WordToDefGame::~WordToDefGame()
{
    for (auto keyword : keywords)
        delete keyword;
}