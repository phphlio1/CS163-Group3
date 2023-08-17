#include "wordToDefGame.hpp"

sf::Font
WordToDefGame::getFont()
{
    return font;
}

std::vector<sf::Text *> WordToDefGame::getKeywordsRef()
{
    return keywords;
}
std::vector<std::vector<Button *>> WordToDefGame::getDefinitionsRef()
{
    return definitions;
}

std::vector<int> WordToDefGame::getAns()
{
    return ans;
}

int WordToDefGame::getScore()
{
    return score;
}

int WordToDefGame::getCounter()
{
    return counter;
}

void WordToDefGame::setFont()
{
    font.loadFromFile("resources/font/open-sans-hebrew/OpenSansHebrew-Bold.ttf");
}

void WordToDefGame::setMetric()
{
    counter = 1;
    score = 0;
    maxCounter = getKeywordsRef().size();
}

void WordToDefGame::setUtilityTexts()
{
    counterText.setFont(font);
    std::string counterString = std::to_string(counter) + " of " + std::to_string(maxCounter);
    counterText.setString(counterString);
    counterText.setFillColor(sf::Color::White);
    counterText.setCharacterSize(23);
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
                      &font, "Quit", 23, 1205, 684, sf::Color::White,
                      sf::Color(17, 105, 142), sf::Color(255, 255, 255, 50), sf::Color(17, 105, 142));
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
        sf::Text *keyWordText = new sf::Text(str + "?", font, 50);
        keyWordText->setFillColor(sf::Color(22, 199, 154));
        centerKeyword(keyWordText);
        keywords.push_back(keyWordText);
    }
}

void WordToDefGame::setOptions(std::vector<std::vector<std::string>> &definitionsStr)
{
    for (auto &listOfOptions : definitionsStr)
    {
        int i = 0;
        std::vector<Button *> groupButtonHolder;
        for (auto &option : listOfOptions)
        {
            std::string order;
            order = (char)65 + i;
            std::vector<Button *> optionsToButton;
            Button *ans = new Button(154, 266 + (100 * i), 960, 75,
                                     &font, order + ".    " + option, 20, 190, 290 + (100 * i), sf::Color::Black,
                                     sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206));
            ans->wrapTextVertical();
            ans->centerVertical();
            groupButtonHolder.push_back(ans);
            ++i;
        }
        definitions.push_back(groupButtonHolder);
    }
}

void WordToDefGame::setAns(std::vector<int> &randomizedAns)
{
    ans = randomizedAns;
}

void WordToDefGame::setOutlineAns()
{
    sf::RectangleShape firstAnsOutline(sf::Vector2f(960, 75));
    firstAnsOutline.setPosition(154, 266);
    firstAnsOutline.setFillColor(sf::Color::Transparent);
    firstAnsOutline.setOutlineColor(sf::Color::Black);
    firstAnsOutline.setOutlineThickness(1);

    sf::RectangleShape secondAnsOutline(sf::Vector2f(960, 75));
    secondAnsOutline.setPosition(154, 366);
    secondAnsOutline.setFillColor(sf::Color::Transparent);
    secondAnsOutline.setOutlineColor(sf::Color::Black);
    secondAnsOutline.setOutlineThickness(1);

    sf::RectangleShape thirdAnsOutline(sf::Vector2f(960, 75));
    thirdAnsOutline.setPosition(154, 466);
    thirdAnsOutline.setFillColor(sf::Color::Transparent);
    thirdAnsOutline.setOutlineColor(sf::Color::Black);
    thirdAnsOutline.setOutlineThickness(1);

    sf::RectangleShape fourthAnsOutline(sf::Vector2f(960, 75));
    fourthAnsOutline.setPosition(154, 566);
    fourthAnsOutline.setFillColor(sf::Color::Transparent);
    fourthAnsOutline.setOutlineColor(sf::Color::Black);
    fourthAnsOutline.setOutlineThickness(1);

    ansOutline.push_back(firstAnsOutline);
    ansOutline.push_back(secondAnsOutline);
    ansOutline.push_back(thirdAnsOutline);
    ansOutline.push_back(fourthAnsOutline);
}

WordToDefGame::WordToDefGame(std::vector<std::string> &keywordStr, std::vector<std::vector<std::string>> &definitionStr, std::vector<int> &randomizedAns)
{
    setFont();
    setMetric();
    setUtilityTexts();
    setButton();
    setQuestion(keywordStr);
    setOptions(definitionStr);
    setAns(randomizedAns);
    setOutlineAns();
}

WordToDefGame::~WordToDefGame()
{
    for (auto keyword : keywords)
        delete keyword;

    for (auto options : definitions)
        for (auto button : options)
            delete button;
}

void WordToDefGame::updateCounter()
{
    // ++counter;
    // counterText.setString(std::to_string(counter) + " of " + std::to_string(maxCounter));
}

void WordToDefGame::updateScores()
{
    // ++score;
    // scoreText.setString("Score: " + std::to_string(score));
}

void WordToDefGame::highlightAns()
{
    // for (int i = 0; i < 4; ++i)
    // {
    //     if (i == ans[counter - 1])
    //         ansOutline[i].setOutlineColor(sf::Color::Green);
    //     else
    //         ansOutline[i].setOutlineColor(sf::Color::Red);
    // }
}

void WordToDefGame::updateButtons(const sf::Event &event, sf::Vector2f mousePosRelativeToWindow)
{
    quit->update(event, mousePosRelativeToWindow);
    for (auto button : definitions[counter - 1])
        button->update(event, mousePosRelativeToWindow);
}

void WordToDefGame::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    target.draw(question);
    target.draw(scoreText);
    target.draw(counterText);
    target.draw(*quit);
    target.draw(*(keywords[0]));
    for (auto button : definitions[counter - 1])
        target.draw(*button);
    for (auto outline : ansOutline)
        target.draw(outline);
}