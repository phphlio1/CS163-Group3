#include "InGame.hpp"

using namespace Frontend;

sf::Font InGame::getFont()
{
    return font;
}

sf::Text InGame::getKeyText()
{
    return key;
}

int InGame::getAns()
{
    return ans;
}

int InGame::getScore()
{
    return score;
}

int InGame::getCounter()
{
    return counter;
}

void InGame::setFont(std::string filename)
{
    font.loadFromFile(filename);
    updateTexture();
}

void InGame::setMetric(int startCount, int startScore, int numberOfQuestions)
{
    counter = startCount;
    score = startScore;
    maxCounter = numberOfQuestions;
    updateTexture();
}

void InGame::setQuestionParams()
{
    // call backend function to update params
    setParams(keyStr, ansStrs, ans);

    setButton();
    setQuestion();
    // setOutlineAns();

    updateTexture();
}

void InGame::setUtilityTexts()
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

    congrats.setFont(font);
    congrats.setString("CONGRATULATIONS!");
    congrats.setFillColor(sf::Color(25, 69, 107));
    congrats.setCharacterSize(60);
    congrats.setPosition(331, 217);

    subCongrats.setFont(font);
    subCongrats.setString("You've earned");
    subCongrats.setFillColor(sf::Color(25, 69, 107));
    subCongrats.setCharacterSize(45);
    subCongrats.setPosition(480, 299);

    updateTexture();
}

void InGame::setFinalScore()
{
    finalScore.setFont(font);
    finalScore.setString(std::to_string(score) + " pts");
    finalScore.setFillColor(sf::Color(22, 199, 154));
    finalScore.setCharacterSize(60);
    centerText(finalScore, 378);
    updateTexture();
}

void InGame::setButton()
{
    quit.setPosition(1205, 684);
    quit.setText(font, "Quit", 23, sf::Color::White);
    quit.setTextPosition(sf::Vector2f(0, 0));
    quit.setContainer(this);

    ans1.setPosition(154, 266);
    ans1.setText(font, "A.      " + ansStrs.at(0), 20, sf::Color::Black);
    ans1.setTextPosition(sf::Vector2f(36, 0));
    ans1.wrapTextVertical();
    ans1.centerVertical();
    ans1.setContainer(this);

    ans2.setPosition(154, 366);
    ans2.setText(font, "B.      " + ansStrs.at(1), 20, sf::Color::Black);
    ans2.setTextPosition(sf::Vector2f(36, 0));
    ans2.wrapTextVertical();
    ans2.centerVertical();
    ans2.setContainer(this);

    ans3.setPosition(154, 466);
    ans3.setText(font, "C.      " + ansStrs.at(2), 20, sf::Color::Black);
    ans3.setTextPosition(sf::Vector2f(36, 0));
    ans3.wrapTextVertical();
    ans3.centerVertical();
    ans3.setContainer(this);

    ans4.setPosition(154, 566);
    ans4.setText(font, "D.      " + ansStrs.at(3), 20, sf::Color::Black);
    ans4.setTextPosition(sf::Vector2f(36, 0));
    ans4.wrapTextVertical();
    ans4.centerVertical();
    ans4.setContainer(this);

    home.setPosition(553, 636);
    home.setText(font, "Back to Home", 25, sf::Color(0, 0, 0, 125));
    home.setTextPosition(sf::Vector2f(0, 0));
    home.setContainer(this);

    updateTexture();
}

void InGame::centerText(sf::Text &keyword, float y)
{
    sf::FloatRect textRect = keyword.getLocalBounds();
    keyword.setPosition((1280 - textRect.width) / 2, y);
    updateTexture();
}

void InGame::centerDefinition(sf::Text &definition)
{
    sf::FloatRect defRect = definition.getLocalBounds();
    if (defRect.width <= 960) // ans button width
    {
        definition.setPosition((1280 - defRect.width) / 2, 160);
        return;
    }

    int closestSpaceIndex = 0;
    for (int i = 0; i < definition.getString().getSize() / 2 + 1; ++i)
    {
        if (definition.getString()[i] == ' ')
            closestSpaceIndex = i;
    }

    sf::String str;
    str += definition.getString();
    str.erase(closestSpaceIndex);
    str.insert(closestSpaceIndex, "\n");
    definition.setString(str);

    defRect = definition.getLocalBounds();

    definition.setPosition((1280 - defRect.width) / 2, 125);

    updateTexture();
}

void InGame::setQuestion()
{
    if (inGameMode == WORD_TO_DEF)
    {
        questionForWordToDef.setFont(font);
        questionForWordToDef.setString("What is the meaning of");
        questionForWordToDef.setFillColor(sf::Color(25, 69, 107));
        questionForWordToDef.setCharacterSize(50);
        questionForWordToDef.setPosition(345, 115);

        key.setFont(font);
        key.setFillColor(sf::Color(22, 199, 154));
        std::string str = keyStr + "?";
        key.setString(str);
        key.setCharacterSize(50);
        centerText(key, 183);
    }
    else if (inGameMode == DEF_TO_WORD)
    {
        key.setFont(font);
        key.setFillColor(sf::Color(25, 69, 107));
        key.setString(keyStr);
        key.setCharacterSize(40);
        centerDefinition(key);
    }

    updateTexture();
}

void InGame::setOutlineAns()
{
    sf::RectangleShape firstAnsOutline(sf::Vector2f(960, 75));
    firstAnsOutline.setPosition(ans1.getPosition());
    firstAnsOutline.setFillColor(sf::Color::Transparent);
    firstAnsOutline.setOutlineColor(sf::Color::Black);
    firstAnsOutline.setOutlineThickness(1);

    sf::RectangleShape secondAnsOutline(sf::Vector2f(960, 75));
    secondAnsOutline.setPosition(ans2.getPosition());
    secondAnsOutline.setFillColor(sf::Color::Transparent);
    secondAnsOutline.setOutlineColor(sf::Color::Black);
    secondAnsOutline.setOutlineThickness(1);

    sf::RectangleShape thirdAnsOutline(sf::Vector2f(960, 75));
    thirdAnsOutline.setPosition(ans3.getPosition());
    thirdAnsOutline.setFillColor(sf::Color::Transparent);
    thirdAnsOutline.setOutlineColor(sf::Color::Black);
    thirdAnsOutline.setOutlineThickness(1);

    sf::RectangleShape fourthAnsOutline(sf::Vector2f(960, 75));
    fourthAnsOutline.setPosition(ans4.getPosition());
    fourthAnsOutline.setFillColor(sf::Color::Transparent);
    fourthAnsOutline.setOutlineColor(sf::Color::Black);
    fourthAnsOutline.setOutlineThickness(1);

    ansOutline.push_back(firstAnsOutline);
    ansOutline.push_back(secondAnsOutline);
    ansOutline.push_back(thirdAnsOutline);
    ansOutline.push_back(fourthAnsOutline);

    updateTexture();
}

InGame::InGame(short unsigned gameMode)
    : Component(1280, 720),
      inGameMode(gameMode),
      header(sf::Vector2f(1280, 40)),
      footer(sf::Vector2f(1280, 40)),
      quit(51, 31, sf::Color(17, 105, 142), sf::Color(255, 255, 255, 50), sf::Color(17, 105, 142)),
      ans1(960, 75, sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206)),
      ans2(960, 75, sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206)),
      ans3(960, 75, sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206)),
      ans4(960, 75, sf::Color(231, 240, 243), sf::Color(173, 196, 206), sf::Color(173, 196, 206)),
      home(174, 34, sf::Color::Transparent, sf::Color::Transparent, sf::Color::Transparent)
{
    header.setPosition(0, 70);
    header.setFillColor(sf::Color(17, 105, 142));

    footer.setPosition(0, 680);
    footer.setFillColor(sf::Color(17, 105, 142));

    setFont();
    setMetric();
    setUtilityTexts();
    setQuestionParams();
    // setButton();
    // setQuestion();
    setOutlineAns();

    updateTexture();
}

InGame::~InGame()
{
}

void InGame::updateCounter()
{
    ++counter;
    std::string counterString = std::to_string(counter) + " of " + std::to_string(maxCounter);
    counterText.setString(counterString);
    updateTexture();
}

void InGame::updateScores()
{
    score += 100;
    scoreText.setString("Score: " + std::to_string(score));
    updateTexture();
}

void InGame::highlightAns(bool showAns)
{
    for (int i = 0; i < ansOutline.size(); ++i)
    {
        if (showAns)
        {
            if (i == ans)
            {
                ansOutline[i].setOutlineColor(sf::Color(22, 199, 154));
                ansOutline[i].setOutlineThickness(3);
            }
            else
            {
                ansOutline[i].setOutlineColor(sf::Color(205, 102, 136, 75));
                ansOutline[i].setOutlineThickness(3);
            }
        }
        else
        {
            ansOutline[i].setOutlineColor(sf::Color::Black);
            ansOutline[i].setOutlineThickness(1);
        }
    }
    updateTexture();
}

void InGame::processEvent(const sf::Event &event)
{
    if (counter > maxCounter)
    {
        home.processEvent(event);
        if (home.isPressed())
        {
            setVisibility(false);
        }
        setFinalScore();
    }
    else
    {
        quit.processEvent(event);
        ans1.processEvent(event);
        ans2.processEvent(event);
        ans3.processEvent(event);
        ans4.processEvent(event);

        if (quit.isPressed())
            setVisibility(false);

        static bool showAns = false;
        if (showAns == false && (ans1.isPressed() || ans2.isPressed() || ans3.isPressed() || ans4.isPressed()))
        {
            showAns = true;
            if (ans1.isPressed() && ans == 0 || ans2.isPressed() && ans == 1 || ans3.isPressed() && ans == 2 || ans4.isPressed() && ans == 3)
            {
                updateScores();
            }
        }
        highlightAns(showAns);

        if (showAns == true)
        {
            if (event.type == sf::Event::MouseButtonPressed && !(ans1.isPressed() || ans2.isPressed() || ans3.isPressed() || ans4.isPressed()))
            {
                updateCounter();
                if (counter <= maxCounter)
                    setQuestionParams();
                showAns = false;
            }
        }
    }
}

void InGame::updateTexture()
{
    texture_.clear(sf::Color::Transparent);

    texture_.draw(header);
    texture_.draw(footer);

    if (counter > maxCounter)
    {
        texture_.draw(congrats);
        texture_.draw(subCongrats);
        texture_.draw(finalScore);
        texture_.draw(home);
    }
    else
    {
        if (inGameMode == WORD_TO_DEF)
            texture_.draw(questionForWordToDef);

        texture_.draw(scoreText);
        texture_.draw(counterText);
        texture_.draw(quit);
        texture_.draw(key);
        texture_.draw(ans1);
        texture_.draw(ans2);
        texture_.draw(ans3);
        texture_.draw(ans4);

        for (auto &outline : ansOutline)
            texture_.draw(outline);
    }

    texture_.display();
}

// test functionalities here

void setParams(std::string &key_n, std::vector<std::string> &ansStr_n, int &ans_n)
{
    static std::vector<std::string> key = {"sequence", "happy"};
    static std::vector<std::vector<std::string>> ansStr = {
        {"a series of related things or events, or the order in which they follow each other",
         "to combine things in a particular order, or discover the order in which they are combined",
         "to discover the order in which nucleotides (= chemical substances) are combined within DNA",
         "all of the above"},
        {"the state of joyfulness",
         "what you feel when you failed your test",
         "a feeling of nothingness",
         "all of the above"}};

    static std::vector<int> ans = {3, 0};
    static int i = 0;
    key_n = key.at(i);
    ansStr_n = ansStr.at(i);
    ans_n = ans.at(i);
    ++i;
}